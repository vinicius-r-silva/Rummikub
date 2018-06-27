#include <gtk/gtk.h>
#include <string.h>  /* for css */



GtkWidget *image;
GtkWidget *img_mesa;
GtkWidget *img_user1;
GtkWidget *img_user2;
GtkWidget *img_user3;
GtkWidget *img_user4;
GtkWidget *img_user5;

GtkWidget *img_user1_foco;
GtkWidget *img_user2_foco;
GtkWidget *img_user3_foco;
GtkWidget *img_user4_foco;
GtkWidget *img_user5_foco;

GtkWidget *img_mao;

/*---- CSS ------------------*/
GtkCssProvider *provider;
GdkDisplay *display;
GdkScreen *screen;
/*---------------------------*/

void css_add(){
    provider = gtk_css_provider_new ();
    display = gdk_display_get_default ();
    screen = gdk_display_get_default_screen (display);
    gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    const gchar* home = "src/style.css";
    GError *error = 0;
    gtk_css_provider_load_from_file(provider, g_file_new_for_path(home), &error);
    g_object_unref (provider);
}

void constroi(){
    g_signal_connect(G_OBJECT(window), "destroy", 
    G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(window);
}

void bt_img(GtkWidget *widget, gpointer data){
	printf("OIII");
    //image = gtk_image_new_from_file("src/image/cartas/A@.png"); // put path to your image here
    //gtk_fixed_put(GTK_FIXED(fixed), image, 0, 0);
    //gtk_widget_show_all(window);
}

int main(int argc, char *argv[]) {

  GtkWidget *window;
  GtkWidget *fixed;

  GtkWidget *bt_compra_carta;
  GtkWidget *bt_finaliza_jog;


  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "Rummikub");
  gtk_window_set_default_size(GTK_WINDOW(window), 1000, 563);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  
  //fixed = gtk_fixed_new();
  //gtk_container_add(GTK_CONTAINER(window), fixed);


  bt_compra_carta = gtk_button_new_with_label("OIOIIIII");
  gtk_container_add(GTK_CONTAINER(window), bt_compra_carta);
  //gtk_fixed_put(GTK_FIXED(fixed), bt_compra_carta, 20,420);
  //gtk_widget_set_size_request(bt_compra_carta, 88, 60);
  //gtk_widget_set_name(bt_compra_carta,"bt_compra_carta");


  // bt_finaliza_jog = gtk_button_new_with_label("");
  // gtk_fixed_put(GTK_FIXED(fixed), bt_finaliza_jog, 20,488);
  // gtk_widget_set_size_request(bt_finaliza_jog, 88, 60);
  // gtk_widget_set_name(bt_finaliza_jog,"bt_finaliza_jog");

  // img_mesa = gtk_image_new_from_file("src/image/mesa.png"); 
  // gtk_fixed_put(GTK_FIXED(fixed), img_mesa,120, 15);

  // img_mao = gtk_image_new_from_file("src/image/mao.png"); 
  // gtk_fixed_put(GTK_FIXED(fixed), img_mao,120, 420);

  // img_user1 = gtk_image_new_from_file("src/image/user1_foco.png"); 
  // gtk_fixed_put(GTK_FIXED(fixed), img_user1,20, 15);

  // img_user2 = gtk_image_new_from_file("src/image/user2.png"); 
  // gtk_fixed_put(GTK_FIXED(fixed), img_user2, 20, 95);

  // img_user3 = gtk_image_new_from_file("src/image/user3.png"); 
  // gtk_fixed_put(GTK_FIXED(fixed), img_user3, 20, 175);

  // img_user4 = gtk_image_new_from_file("src/image/user4.png"); 
  // gtk_fixed_put(GTK_FIXED(fixed), img_user4, 20, 255);

  // img_user5 = gtk_image_new_from_file("src/image/user5.png"); 
  // gtk_fixed_put(GTK_FIXED(fixed), img_user5, 20, 335);

  //FUNCAO QUE REMOVE ELEMNTO AQUIIII gtk_widget_destroy((img_user5));

  g_signal_connect(G_OBJECT(bt_compra_carta),"clicked", G_CALLBACK(bt_img), NULL);

  //css_add();

  constroi();
  gtk_main();

  return 0;
}

