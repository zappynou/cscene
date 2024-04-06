#ifndef CSCENE_SCENE_SCALE_H
#define CSCENE_SCENE_SCALE_H

#include <cscene/gui/gtk/scene.h>

struct cscene_scene_scale
{
    GtkEventController *event;
};

/**
 * @brief Initialize a scene scale object for a scene widget.
 *
 * @param scale The scene scale object to initialize.
 *
 * @note The given @p scale object must be located inside a @ref CSceneScene
 * structure.
 */
void cscene_scene_scale_init(struct cscene_scene_scale *scale);

/**
 * @brief Clear a scene scale object.
 *
 * @param scale The scene scale object to clear.
 */
void cscene_scene_scale_clear(struct cscene_scene_scale *scale);

#endif /* !CSCENE_SCENE_SCALE_H */
