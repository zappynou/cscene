#include <inttypes.h>

#include <sys/param.h>

#include <cscene/gui/gtk/scene.h>

#include "scene-private.h"

struct _CSceneSceneClass
{
    GtkWidgetClass parent_class;
};

/** The name with which all scene widgets can be referred to in CSS. */
static const char *scene_css_name = "cscenescene";

guint cscene_scene_signals[CSCENE_SCENE_SIGNAL_COUNT] = {0};

/** Define the type CSceneScene, which extends GtkWidget. */
G_DEFINE_TYPE_WITH_CODE(CSceneScene, cscene_scene, GTK_TYPE_WIDGET,);

static void cscene_scene_snapshot(GtkWidget *widget, GtkSnapshot *snapshot)
{
    CSceneScene *scene = CSCENE_SCENE(widget);
    const int width = gtk_widget_get_width(GTK_WIDGET(scene));
    const int height = gtk_widget_get_height(GTK_WIDGET(scene));

    const graphene_rect_t rect = {
        .origin = {0, 0},
        .size = {width, height},
    };

    /* Setup a Cairo context to draw custom shapes. */
    cairo_t *cr = gtk_snapshot_append_cairo(snapshot, &rect);

    /* Allow the client to draw the content of the scene. */
    g_signal_emit(
        scene,
        cscene_scene_signals[CSCENE_SCENE_SIGNAL_DRAW], 0,
        cr, width, height,
        scene->hoffset, scene->voffset, scene->ratio);

    /* We're done with Cairo. */
    cairo_destroy(cr);

    (void)scene;
    (void)snapshot;
}

/**
 * @brief Initialize a new CSCENE scene object.
 *
 * @param scene The CSCENE scene to initialise.
 */
static void cscene_scene_init(CSceneScene *scene)
{
    scene->hoffset = 250;
    scene->voffset = 250;

    scene->ratio = 1.;

    scene->lock = 0;

    cscene_scene_click_init(&scene->click);
    cscene_scene_drag_init(&scene->drag);
    cscene_scene_scale_init(&scene->scale);
}

/**
 * @brief Destroy a CSCENE scene.
 *
 * @param object The CSCENE scene object (in disguise) and its children.
 */
static void cscene_scene_dispose(GObject *object)
{
    CSceneScene *scene = CSCENE_SCENE(object);

    cscene_scene_scale_clear(&scene->scale);
    cscene_scene_drag_clear(&scene->drag);
    cscene_scene_click_clear(&scene->click);

    G_OBJECT_CLASS(cscene_scene_parent_class)->dispose(object);
}

static void cscene_scene_class_init(CSceneSceneClass *klass)
{
    GObjectClass *object_class = G_OBJECT_CLASS(klass);
    GtkWidgetClass *widget_class = GTK_WIDGET_CLASS(klass);

    object_class->dispose = cscene_scene_dispose;
    widget_class->snapshot = cscene_scene_snapshot;

    gtk_widget_class_set_css_name(widget_class, scene_css_name);

    cscene_scene_signals[CSCENE_SCENE_SIGNAL_DRAW] = g_signal_new(
        "draw",
        G_TYPE_FROM_CLASS(object_class),
        G_SIGNAL_RUN_LAST | G_SIGNAL_NO_RECURSE | G_SIGNAL_NO_HOOKS,
        0,
        NULL,
        NULL,
        NULL,
        G_TYPE_NONE,
        6,
        G_TYPE_POINTER,
        G_TYPE_UINT,
        G_TYPE_UINT,
        G_TYPE_DOUBLE,
        G_TYPE_DOUBLE,
        G_TYPE_DOUBLE);

    cscene_scene_signals[CSCENE_SCENE_SIGNAL_CLICKED] = g_signal_new(
        "clicked",
        G_TYPE_FROM_CLASS(object_class),
        G_SIGNAL_RUN_LAST | G_SIGNAL_NO_RECURSE | G_SIGNAL_NO_HOOKS,
        0,
        NULL,
        NULL,
        NULL,
        G_TYPE_NONE,
        3,
        G_TYPE_INT,
        G_TYPE_DOUBLE,
        G_TYPE_DOUBLE);
}

GtkWidget *cscene_scene_new(void)
{
    return g_object_new(CSCENE_TYPE_SCENE, NULL);
}

__attribute__((visibility("hidden")))
int cscene_scene_lock(CSceneScene *scene, uint32_t value)
{
    if (!CSCENE_IS_SCENE(scene))
        return 0;

    return __sync_val_compare_and_swap(&scene->lock, 0, value) == 0;
}

__attribute__((visibility("hidden")))
int cscene_scene_locked(CSceneScene *scene, uint32_t value)
{
    if (!CSCENE_IS_SCENE(scene))
        return 0;

    return __sync_fetch_and_or(&scene->lock, 0) == value;
}

__attribute__((visibility("hidden")))
int cscene_scene_swap(CSceneScene *scene, uint32_t old_value, uint32_t new_value)
{
    if (!CSCENE_IS_SCENE(scene))
        return 0;

    return __sync_val_compare_and_swap(
        &scene->lock, old_value, new_value) == old_value;
}

__attribute__((visibility("hidden")))
int cscene_scene_unlock(CSceneScene *scene, uint32_t value)
{
    if (!CSCENE_IS_SCENE(scene))
        return 0;

    return __sync_val_compare_and_swap(&scene->lock, value, 0) == value;
}

void cscene_scene_get_hoffset(CSceneScene *scene, gdouble *hoffset)
{
    if (!CSCENE_IS_SCENE(scene))
        return;

    if (hoffset)
        *hoffset = scene->hoffset;
}

void cscene_scene_get_voffset(CSceneScene *scene, gdouble *voffset)
{
    if (!CSCENE_IS_SCENE(scene))
        return;

    if (voffset)
        *voffset = scene->voffset;
}

void cscene_scene_get_offsets(CSceneScene *scene,
                              gdouble *hoffset,
                              gdouble *voffset)
{
    if (!CSCENE_IS_SCENE(scene))
        return;

    if (hoffset)
        *hoffset = scene->hoffset;
    if (voffset)
        *voffset = scene->voffset;
}

void cscene_scene_set_hoffset(CSceneScene *scene, gdouble hoffset)
{
    if (!CSCENE_IS_SCENE(scene))
        return;

    scene->hoffset = hoffset;
}

void cscene_scene_set_voffset(CSceneScene *scene, gdouble voffset)
{
    if (!CSCENE_IS_SCENE(scene))
        return;

    scene->voffset = voffset;
}

void cscene_scene_set_offsets(CSceneScene *scene,
                              gdouble hoffset,
                              gdouble voffset)
{
    if (!CSCENE_IS_SCENE(scene))
        return;

    scene->hoffset = hoffset;
    scene->voffset = voffset;
}

void cscene_scene_get_ratio(CSceneScene *scene, gdouble *ratio)
{
    if (!CSCENE_IS_SCENE(scene))
        return;

    if (ratio)
        *ratio = scene->ratio;
}

void cscene_scene_set_ratio(CSceneScene *scene, gdouble ratio)
{
    if (!CSCENE_IS_SCENE(scene))
        return;

    scene->ratio = ratio;
}
