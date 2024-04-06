#ifndef CSCENE_SCENE_PRIVATE_H
#define CSCENE_SCENE_PRIVATE_H

#include <cscene/gui/gtk/scene.h>

#include "scene-click.h"
#include "scene-drag.h"
#include "scene-scale.h"

/* Forward declaration of the board structure. */
struct cscene_board;

/**
 * @brief The possible lock values for a scene object.
 */
enum cscene_scene_lock
{
    CSCENE_SCENE_CLICK = (1 << 0),

    CSCENE_SCENE_DRAG = (1 << 1),

    CSCENE_SCENE_SCALE = (1 << 2),
};

/**
 * @brief The private scene structure.
 */
struct _CSceneScene
{
    GtkWidget parent_instance;

    /**
     * @brief The horizontal offset of the scene view.
     */
    gdouble hoffset;

    /**
     * @brief The vertical offset of the scene view.
     */
    gdouble voffset;

    /**
     * @brief The ratio of the scene view.
     */
    gdouble ratio;

    /**
     * @brief The lock of the scene object.
     */
    uint32_t lock;

    /**
     * @brief The object that handles click events.
     */
    struct cscene_scene_click click;

    /**
     * @brief The object that handles dragging scene child objects on the view.
     */
    struct cscene_scene_drag drag;

    /**
     * @brief The object that handles scaling the scene view in and out.
     */
    struct cscene_scene_scale scale;

    /**
     * @brief The last known horizontal position of the cursor.
     *
     * @note This field is set by the event controller from the scene-drag.c
     * source file.
     *
     * @note This field is used by the event controller callback in the
     * scene-scale.c source file.
     */
    gdouble last_cursor_x;

    /**
     * @brief The last known vertical position of the cursor.
     *
     * @note This field is set by the event controller from the scene-drag.c
     * source file.
     *
     * @note This field is used by the event controller callback in the
     * scene-scale.c source file.
     */
    gdouble last_cursor_y;
};

enum cscene_scene_signal
{
    CSCENE_SCENE_SIGNAL_CLICKED,

    CSCENE_SCENE_SIGNAL_DRAW,

    CSCENE_SCENE_SIGNAL_COUNT,
};

extern guint cscene_scene_signals[CSCENE_SCENE_SIGNAL_COUNT];

/**
 * @brief Get the scene event lock.
 *
 * @param scene The scene to get the lock of.
 * @param value The lock value to assign.
 *
 * @return A non-zero value if the lock was obtained, 0 otherwise.
 */
int cscene_scene_lock(CSceneScene *scene, uint32_t value);

/**
 * @brief Check wether a lock has a cpecific value.
 *
 * @param scene The scene to get the lock status of.
 * @param value The lock value to check for.
 *
 * @return A non-zero value if the lock is held with the given value.
 */
int cscene_scene_locked(CSceneScene *scene, uint32_t value);

/**
 * @brief Swap the scene event lock.
 *
 * @param scene The scene to swap the lock of.
 * @param old_value The lock value to release.
 * @param new_value The lock value to swap to.
 *
 * @return A non-zero value if the lock was swapped, 0 otherwise.
 */
int cscene_scene_swap(CSceneScene *scene, uint32_t old_value, uint32_t new_value);

/**
 * @brief Release the scene event lock.
 *
 * @param scene The scene to release the lock of.
 * @param value The lock value to release.
 *
 * @return A non-zero value if the lock was release, 0 otherwise.
 */
int cscene_scene_unlock(CSceneScene *scene, uint32_t value);

#endif /* !CSCENE_SCENE_PRIVATE_H */
