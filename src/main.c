#include <gtk/gtk.h>


GtkWidget *window;
GtkWidget *fixed;

GtkWidget *btn1;
GtkWidget *btn2;
GtkWidget *btn3;

GtkWidget *image;


void constroi(){
    g_signal_connect(G_OBJECT(window), "destroy", 
    G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(window);
}

void bt_img(){
    image = gtk_image_new_from_file("icon.png"); // put path to your image here
    gtk_fixed_put(GTK_FIXED(fixed), image, 500, 500);
    gtk_widget_set_size_request(image, 40, 40);
    gtk_widget_show_all(window);
}

int main(int argc, char *argv[]) {
    


  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "GtkFixed");
  gtk_window_set_default_size(GTK_WINDOW(window), 800, 800);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

  fixed = gtk_fixed_new();
  gtk_container_add(GTK_CONTAINER(window), fixed);

  btn1 = gtk_button_new_with_label("Button");
  gtk_fixed_put(GTK_FIXED(fixed), btn1, 150, 50);
  gtk_widget_set_size_request(btn1, 80, 30);

  btn2 = gtk_button_new_with_label("Button");
  gtk_fixed_put(GTK_FIXED(fixed), btn2, 15, 15);
  gtk_widget_set_size_request(btn2, 80, 30);

  btn3 = gtk_button_new_with_label("Button");
  gtk_fixed_put(GTK_FIXED(fixed), btn3, 100, 100);
  gtk_widget_set_size_request(btn3, 80, 30);


  g_signal_connect(G_OBJECT(btn1), "clicked", G_CALLBACK(bt_img), NULL);

  constroi();
  gtk_main();

  return 0;
}

