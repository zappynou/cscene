#ifndef CSCENE_SCENE_DRAG_H
#define CSCENE_SCENE_DRAG_H

#include <cscene/gui/gtk/scene.h>

struct cscene_scene_drag
{
    gdouble x;
    gdouble y;

    GtkGesture *click;
    GtkEventController *motion;
};

/**
 * @brief Initialize a scene drag object for a scene widget.
 *
 * @param drag The scene drag object to initialize.
 *
 * @note The given @p drag object must be located inside a @ref CSceneScene
 * structure.
 */
void cscene_scene_drag_init(struct cscene_scene_drag *drag);

/**
 * @brief Clear a scene drag object.
 *
 * @param drag The scene drag object to clear.
 */
void cscene_scene_drag_clear(struct cscene_scene_drag *drag);

#endif /* !CSCENE_SCENE_DRAG_H */
