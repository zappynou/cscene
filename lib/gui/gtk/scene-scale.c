#include <gdk/gdk.h>

#include "scene-private.h"
#include "scene-scale.h"

#define TO_SCENE(scale)                                                 \
    ((CSceneScene *)(((void *)(scale)) - offsetof(CSceneScene, scale)))

static gboolean cscene_scene_scroll(GtkEventControllerScroll *_self,
                                    gdouble dx,
                                    gdouble dy,
                                    gpointer user_data)
{
    struct cscene_scene_scale *const scale = user_data;
    CSceneScene *const scene = TO_SCENE(scale);
    static const gdouble step = 1.2;
    const gdouble factor = pow(step, -dy);
    const gdouble ratio = factor * scene->ratio;

    GtkWidget *widget = GTK_WIDGET(scene);

    const gdouble mousex = scene->last_cursor_x;
    const gdouble mousey = scene->last_cursor_y;

    gdouble horigin;
    gdouble vorigin;

    if (__sync_fetch_and_or(&scene->lock, 0) != 0)
        return TRUE;

    if (.2 < ratio && ratio < 10.
        && scene->ratio != ratio) {
        /* We're going to need to draw the widget again. */
        gtk_widget_queue_draw(widget);

        /* Considering the following drawing, with the sizes of the items:
         *
         *   <-10->
         * ^ +----+
         * | |    |
         * 10|    |
         * v +----+----+ ^
         *        |    | 10
         *        |    | |
         *        +----+ v
         *        <-10->
         *
         * The top left '+' is located at the position `(hoffset, voffset)`.
         * The middle '+' is located at `(hoffset + 10, voffset + 10)`.
         * The bottom right '+' is located at `(hoffset + 20, voffset + 20)`.
         *
         * With that drawing in mind, consider the following locations:
         *
         *   0
         *  0+    +
         *
         *
         *     +    +    +
         *
         *
         *          +    #20
         *              20
         *
         * Here, all '+'s are the same as before, and '#' is the position of
         * the mouse cursor at `(mousex, mousey)` which in this example also
         * is the bottom-right '+' (no longer represented here).
         *
         * After zooming in, we expect all distances to get away from each
         * other by the `step`: that's done simply by updating `scene->ratio`.
         *
         * Now, we also want the top-left '+' to no longer be at the same
         * location: if `hoffset`, `voffset` was the top-left of the widget
         * (ie. at `(0, 0)` with the bottom-right '+' at `(20, 20)`) we expect
         * the mouse cursor to remain "at the same distance from the
         * bottom-right '+' relatively to the top-left '+'".
         *
         * So, after applying only a "zoom" 1.0 updated to 1.2, we get the
         * following positions:
         *
         *   0
         *  0+    +
         *
         *
         *   +    +    +
         *
         *
         *        +    #24
         *            24
         *
         * However, we want the mouse cursor '#' to remain at the same location
         * as before, so, basically, it should become:
         *
         *   -4
         * -4+    +
         *
         *
         *   +    +    +
         *
         *
         *        +    #20
         *            20
         */

        horigin = mousex - scene->hoffset;
        vorigin = mousey - scene->voffset;

        scene->hoffset -= horigin * (ratio - scene->ratio);
        scene->voffset -= vorigin * (ratio - scene->ratio);

        scene->ratio = ratio;
    }

    return TRUE;

    (void)_self;
    (void)dx;
}

__attribute__((visibility("hidden")))
void cscene_scene_scale_init(struct cscene_scene_scale *scale)
{
    scale->event = gtk_event_controller_scroll_new(
        GTK_EVENT_CONTROLLER_SCROLL_VERTICAL);
    g_signal_connect(
        G_OBJECT(scale->event), "scroll", G_CALLBACK(cscene_scene_scroll), scale);
    gtk_widget_add_controller(GTK_WIDGET(TO_SCENE(scale)), scale->event);
}

__attribute__((visibility("hidden")))
void cscene_scene_scale_clear(struct cscene_scene_scale *scale)
{
    gtk_widget_remove_controller(
        GTK_WIDGET(TO_SCENE(scale)), scale->event);
}
