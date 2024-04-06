#include <gtk/gtk.h>

#include <cscene/gui/gtk/scene.h>

static void on_draw(CSceneScene *scene,
                    cairo_t *cr,
                    guint width, guint height,
                    gdouble hoffset, gdouble voffset,
                    gdouble ratio,
                    gpointer user_data)
{
    cairo_set_source_rgb(cr, 0., 0., 0.);
    cairo_rectangle(cr, 0, 0, width, height);
    cairo_fill(cr);

    cairo_set_source_rgba(cr, 1., 1., 1., .8);
    cairo_rectangle(cr, hoffset, voffset,
                    10 * ratio, 10 * ratio);
    cairo_fill(cr);

    cairo_set_source_rgba(cr, 1., .0, 1., .8);
    cairo_rectangle(cr, hoffset + 10 * ratio, voffset + 10 * ratio,
                    10 * ratio, 10 * ratio);
    cairo_fill(cr);

    (void)scene;
    (void)user_data;
}

static void on_clicked(CSceneScene *scene,
                       gint button,
                       gdouble x, gdouble y,
                       gpointer user_data)
{
    gdouble hoffset;
    gdouble voffset;
    gdouble ratio;

    cscene_scene_get_hoffset(scene, &hoffset);
    cscene_scene_get_voffset(scene, &voffset);
    cscene_scene_get_ratio(scene, &ratio);

    printf("Clicked at %f,%f [button=%d];\n"
           "\trectangle#1 at %f %f (width=%f height=%f)\n"
           "\trectangle#2 at %f %f (width=%f height=%f)\n",
           x, y, button,
           hoffset, voffset,
           10 * ratio, 10 * ratio,
           hoffset + 10 * ratio, voffset + 10 * ratio,
           10 * ratio, 10 * ratio);

    (void)scene;
    (void)user_data;
}

static void on_activate(GtkApplication *app, gpointer user_data)
{
    GtkWidget *window;
    GtkWidget *hbox;
    GtkWidget *vbox;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "CScene");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 800);

    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_set_homogeneous(GTK_BOX(hbox), TRUE);
    gtk_window_set_child(GTK_WINDOW(window), hbox);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_set_homogeneous(GTK_BOX(vbox), TRUE);

    gtk_box_append(GTK_BOX(hbox), gtk_box_new(GTK_ORIENTATION_VERTICAL, 5));
    gtk_box_append(GTK_BOX(hbox), vbox);
    gtk_box_append(GTK_BOX(hbox), gtk_box_new(GTK_ORIENTATION_VERTICAL, 5));

    GtkWidget *scene = cscene_scene_new();
    g_signal_connect(scene, "draw", G_CALLBACK(on_draw), NULL);
    g_signal_connect(scene, "clicked", G_CALLBACK(on_clicked), NULL);

    gtk_box_append(GTK_BOX(vbox), gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5));
    gtk_box_append(GTK_BOX(vbox), scene);
    gtk_box_append(GTK_BOX(vbox), gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5));

    gtk_widget_set_visible(window, true);

    (void)user_data;
}

int main(int argc, char *argv[])
{
    GtkApplication *app;
    int ret;

    app = gtk_application_new(
        "app.cscene.gtk4", G_APPLICATION_DEFAULT_FLAGS);

    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);
    ret = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return ret;
}
