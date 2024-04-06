#include "scene-private.h"
#include "scene-click.h"

#define TO_SCENE(click)                                                 \
    ((CSceneScene *)(((void *)(click)) - offsetof(CSceneScene, click)))

static void cscene_scene_click_start(GtkGestureClick *_self,
                                       gint n_press,
                                       gdouble x,
                                       gdouble y,
                                       gpointer user_data)
{
    struct cscene_scene_click_button *const button = user_data;
    struct cscene_scene_click *const click = button->click;

    if (!cscene_scene_lock(TO_SCENE(click), CSCENE_SCENE_CLICK))
        return;

    click->x = x;
    click->y = y;

    (void)_self;
    (void)n_press;
}

static void cscene_scene_click_stop(GtkGestureClick *_self,
                                      gint n_press,
                                      gdouble x,
                                      gdouble y,
                                      gpointer user_data)
{
    struct cscene_scene_click_button *const button = user_data;
    struct cscene_scene_click *const click = button->click;

    if (!cscene_scene_unlock(TO_SCENE(click), CSCENE_SCENE_CLICK))
        return;

    if (x < click->x - 2 || click->x + 2 < x
        || y < click->y - 2 || click->y + 2 < y)
        return;

    click->x -= TO_SCENE(click)->hoffset;
    click->x /= TO_SCENE(click)->ratio;
    click->y -= TO_SCENE(click)->voffset;
    click->y /= TO_SCENE(click)->ratio;

    g_signal_emit(
        TO_SCENE(click),
        cscene_scene_signals[CSCENE_SCENE_SIGNAL_CLICKED], 0,
        button->button, click->x, click->y);

    (void)_self;
    (void)n_press;
    (void)x;
    (void)y;
}

__attribute__((visibility("hidden")))
void cscene_scene_click_init(struct cscene_scene_click *click)
{
    click->primary.button = GDK_BUTTON_PRIMARY;
    click->primary.click = click;
    click->secondary.button = GDK_BUTTON_SECONDARY;
    click->secondary.click = click;

    click->primary_click = gtk_gesture_click_new();
    gtk_gesture_single_set_button(
        GTK_GESTURE_SINGLE(click->primary_click), GDK_BUTTON_PRIMARY);
    g_signal_connect(G_OBJECT(click->primary_click), "pressed",
                     G_CALLBACK(cscene_scene_click_start), &click->primary);
    g_signal_connect(G_OBJECT(click->primary_click), "released",
                     G_CALLBACK(cscene_scene_click_stop), &click->primary);
    gtk_widget_add_controller(
        GTK_WIDGET(TO_SCENE(click)),
        GTK_EVENT_CONTROLLER(click->primary_click));

    click->secondary_click = gtk_gesture_click_new();
    gtk_gesture_single_set_button(
        GTK_GESTURE_SINGLE(click->secondary_click), GDK_BUTTON_SECONDARY);
    g_signal_connect(G_OBJECT(click->secondary_click), "pressed",
                     G_CALLBACK(cscene_scene_click_start), &click->secondary);
    g_signal_connect(G_OBJECT(click->secondary_click), "released",
                     G_CALLBACK(cscene_scene_click_stop), &click->secondary);
    gtk_widget_add_controller(
        GTK_WIDGET(TO_SCENE(click)),
        GTK_EVENT_CONTROLLER(click->secondary_click));
}

__attribute__((visibility("hidden")))
void cscene_scene_click_clear(struct cscene_scene_click *click)
{
    gtk_widget_remove_controller(
        GTK_WIDGET(TO_SCENE(click)),
        GTK_EVENT_CONTROLLER(click->secondary_click));
    gtk_widget_remove_controller(
        GTK_WIDGET(TO_SCENE(click)),
        GTK_EVENT_CONTROLLER(click->primary_click));
}
