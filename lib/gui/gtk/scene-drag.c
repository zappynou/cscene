#include "scene-private.h"
#include "scene-drag.h"

#define TO_SCENE(drag)                                                  \
    ((CSceneScene *)(((void *)(drag)) - offsetof(CSceneScene, drag)))

static void cscene_scene_drag_start(GtkGestureClick *_self,
                                      gint n_press,
                                      gdouble x,
                                      gdouble y,
                                      gpointer user_data)
{
    struct cscene_scene_drag *const drag = user_data;

    if (!cscene_scene_lock(TO_SCENE(drag), CSCENE_SCENE_DRAG))
        return;

    drag->x = x;
    drag->y = y;

    gtk_widget_set_cursor_from_name(GTK_WIDGET(TO_SCENE(drag)), "grab");

    (void)_self;
    (void)n_press;
}

static void cscene_scene_drag_motion(GtkEventControllerMotion *_self,
                                     gdouble x,
                                     gdouble y,
                                     gpointer user_data)
{
    struct cscene_scene_drag *const drag = user_data;
    CSceneScene *const scene = TO_SCENE(drag);
    gdouble hdiff, vdiff;

    scene->last_cursor_x = x;
    scene->last_cursor_y = y;

    if (!cscene_scene_locked(scene, CSCENE_SCENE_DRAG))
        return;

    hdiff = (x - drag->x);
    vdiff = (y - drag->y);

    if (hdiff) {
        TO_SCENE(drag)->hoffset += hdiff;
        drag->x = x;
    }

    if (vdiff) {
        TO_SCENE(drag)->voffset += vdiff;
        drag->y = y;
    }

    if (hdiff || vdiff)
        gtk_widget_queue_allocate(GTK_WIDGET(scene));

    (void)_self;
}

static void cscene_scene_drag_stop(GtkGestureClick *_self,
                                     gint n_press,
                                     gdouble x,
                                     gdouble y,
                                     gpointer user_data)
{
    struct cscene_scene_drag *const drag = user_data;

    if (!cscene_scene_unlock(TO_SCENE(drag), CSCENE_SCENE_DRAG))
        return;

    gtk_widget_set_cursor(GTK_WIDGET(TO_SCENE(drag)), NULL);

    (void)_self;
    (void)n_press;
    (void)x;
    (void)y;
}

__attribute__((visibility("hidden")))
void cscene_scene_drag_init(struct cscene_scene_drag *drag)
{
    drag->click = gtk_gesture_click_new();
    gtk_gesture_single_set_button(
        GTK_GESTURE_SINGLE(drag->click), GDK_BUTTON_MIDDLE);
    g_signal_connect(G_OBJECT(drag->click), "pressed",
                     G_CALLBACK(cscene_scene_drag_start), drag);
    g_signal_connect(G_OBJECT(drag->click), "released",
                     G_CALLBACK(cscene_scene_drag_stop), drag);
    gtk_widget_add_controller(
        GTK_WIDGET(TO_SCENE(drag)), GTK_EVENT_CONTROLLER(drag->click));

    drag->motion = gtk_event_controller_motion_new();
    g_signal_connect(G_OBJECT(drag->motion), "motion",
                     G_CALLBACK(cscene_scene_drag_motion), drag);
    gtk_widget_add_controller(
        GTK_WIDGET(TO_SCENE(drag)), drag->motion);
}

__attribute__((visibility("hidden")))
void cscene_scene_drag_clear(struct cscene_scene_drag *drag)
{
    gtk_widget_remove_controller(
        GTK_WIDGET(TO_SCENE(drag)), drag->motion);
    gtk_widget_remove_controller(
        GTK_WIDGET(TO_SCENE(drag)), GTK_EVENT_CONTROLLER(drag->click));
}
