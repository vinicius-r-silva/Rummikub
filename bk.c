#include <gtk/gtk.h>

GtkWidget *g_lbl_count;
GtkBuilder *builder; 
GtkWidget *window;
GtkWidget *image;
GtkWidget *layout;

int main(int argc, char *argv[])
{
    
    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "glade/window_main.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    gtk_builder_connect_signals(builder, NULL);

    //box = GTK_FLOW_BOX(gtk_builder_get_object(builder, "id_conteiner"));

    g_object_unref(builder);
    gtk_widget_show(window);  
    gtk_main();

    return 0;
}
void bt_img(){
    layout = GTK_WIDGET(gtk_builder_get_object(builder, "id_conteiner"));
    image = gtk_image_new_from_file("icon.png"); // put path to your image here
    gtk_layout_put(GTK_LAYOUT(layout), image, 0, 0);
}
void on_window_main_destroy()
{
    gtk_main_quit();
}