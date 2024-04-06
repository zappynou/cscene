#ifndef CSCENE_SCENE_H
#define CSCENE_SCENE_H

#include <gtk/gtk.h>

/* The glib declarations begin here. */
G_BEGIN_DECLS

/**
 * @brief Get the glib-style type identifier of a CScene scene.
 */
#define CSCENE_TYPE_SCENE cscene_scene_get_type()

/**
 * @brief Declare the glib-style type of a CScene scene.
 *
 * The scene widget is a `GtkWidget` which provides the following signals:
 *
 * - `draw`
 *
 *   ~~~
 *   void on_draw(CSceneScene *scene,
 *                cairo_t *cr,
 *                guint width, guint height,
 *                gdouble hoffset, gdouble voffset,
 *                gdouble ratio,
 *                gpointer user_data);
 *   ~~~
 *
 *   This signal is emitted when the `GtkWidget` gets refreshed (see the
 *   documentation of `GtkWidget.scanpshot` for details): it provides a cairo
 *   context to draw the scene (=`cr`), along with the dimensions of the widget
 *   (=`width` and `height`), the horizontal and vertical offsets of the
 *   content of the scene (=`hoffset` and `voffset`, respectively), and the
 *   expected ratio of the content (=`ratio`).
 *
 *   These offsets and ratio get updated when the user does any of the
 *   following:
 *
 *   - the "drag" is provoked by pressing the middle button of a mouse, then
 *     moving the cursor before releasing the button;
 *   - the "scale" is provoked by the vertical scroll on the mouse wheel;
 *
 *   As soon as any of these offsets or the ratio are updated with these
 *   methods, the "draw" signal gets emitted;
 *
 * - `clicked`
 *
 *   ~~~
 *   void on_clicked(CSceneScene *scene,
 *                   gint button,
 *                   gdouble x, gdouble y,
 *                   gpointer user_data);
 *   ~~~
 *
 *   This signal is emitted when the scene widget gets clicked on with either
 *   the left or right click.
 *
 *   The button pressed by the user which emitted the signal is provided as
 *   the `button` parameter. The `x` and `y` parameters provide the actual
 *   position of the mouse cursor when the click occurred;
 */
G_DECLARE_FINAL_TYPE(CSceneScene, cscene_scene, CSCENE, SCENE, GtkWidget)

/**
 * @brief Create a new CScene scene widget.
 *
 * @return A new CScene scene widget.
 */
GtkWidget *cscene_scene_new(void);

/**
 * @brief Get the horizontal offset of a scene.
 *
 * @param scene The scene widget to get the horizontal offset of.
 * @param[out] hoffset The location to store the offset on, or NULL.
 */
void cscene_scene_get_hoffset(CSceneScene *scene, gdouble *hoffset);

/**
 * @brief Get the vertical offset of a scene.
 *
 * @param scene The scene widget to get the vertical offset of.
 * @param[out] voffset The location to store the offset on, or NULL.
 */
void cscene_scene_get_voffset(CSceneScene *scene, gdouble *voffset);

/**
 * @brief Get both the horizontal and vertical offsets of a scene.
 *
 * @param scene The scene widget to get the offsets of.
 * @param[out] hoffset The location to store the horizontal offset on, or NULL.
 * @param[out] voffset The location to store the vertical offset on, or NULL.
 */
void cscene_scene_get_offsets(CSceneScene *scene,
                              gdouble *hoffset,
                              gdouble *voffset);

/**
 * @brief Set the horizontal offset of a scene.
 *
 * @param scene The scene widget to set the horizontal offset of.
 * @param hoffset The horizontal offset to set.
 *
 * @note This function does not queue a call to re-draw the scene, the caller
 * must do it themselves by using `gtk_widget_queue_draw` when all the
 * configurations have been applied to the scene.
 */
void cscene_scene_set_hoffset(CSceneScene *scene, gdouble hoffset);

/**
 * @brief Set the vertical offset of a scene.
 *
 * @param scene The scene widget to set the vertical offset of.
 * @param voffset The vertical offset to set.
 *
 * @note This function does not queue a call to re-draw the scene, the caller
 * must do it themselves by using `gtk_widget_queue_draw` when all the
 * configurations have been applied to the scene.
 */
void cscene_scene_set_voffset(CSceneScene *scene, gdouble voffset);

/**
 * @brief Set both the horizontal and vertical offsets of a scene.
 *
 * @param scene The scene widget to set the offsets of.
 * @param hoffset The horizontal offset to set.
 * @param voffset The vertical offset to set.
 *
 * @note This function does not queue a call to re-draw the scene, the caller
 * must do it themselves by using `gtk_widget_queue_draw` when all the
 * configurations have been applied to the scene.
 */
void cscene_scene_set_offsets(CSceneScene *scene,
                              gdouble hoffset,
                              gdouble voffset);

/**
 * @brief Get the view ratio of the scene.
 *
 * @param scene The scene widget to get the view ratio of.
 * @param[out] ratio The current value of the scene view ratio.
 */
void cscene_scene_get_ratio(CSceneScene *scene, gdouble *ratio);

/**
 * @brief Set the view ratio of the scene.
 *
 * @param scene The scene widget to set the view ratio of.
 * @param[out] ratio The value to set for the scene view ratio.
 */
void cscene_scene_set_ratio(CSceneScene *scene, gdouble ratio);

/* The glib declarations end here. */
G_END_DECLS

#endif /* !CSCENE_SCENE_H */
