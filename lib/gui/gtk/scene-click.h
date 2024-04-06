#ifndef CSCENE_SCENE_CLICK_H
#define CSCENE_SCENE_CLICK_H

#include <cscene/gui/gtk/scene.h>

struct cscene_scene_click_button
{
    guint button;
    struct cscene_scene_click *click;
};

struct cscene_scene_click
{
    gdouble x;
    gdouble y;

    GtkGesture *primary_click;
    GtkGesture *secondary_click;

    struct cscene_scene_click_button primary;
    struct cscene_scene_click_button secondary;
};

/**
 * @brief Initialize a scene click object for a scene widget.
 *
 * @param click The scene click object to initialize.
 *
 * @note The given @p click object must be located inside a @ref CSceneScene
 * structure.
 */
void cscene_scene_click_init(struct cscene_scene_click *click);

/**
 * @brief Clear a scene click object.
 *
 * @param click The scene click object to clear.
 */
void cscene_scene_click_clear(struct cscene_scene_click *click);

#endif /* !CSCENE_SCENE_CLICK_H */
