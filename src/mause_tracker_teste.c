#include <gtk/gtk.h>
#include "libs/data.h"

int prev_X = 0;
int prev_Y = 0;
GtkWidget *fixed;

GdkDisplay *display;
GdkDeviceManager *device_manager;
GdkDevice *device;

void clique_mouse(GtkWidget *event_box,GdkEventButton *event,gpointer data){
	gint x,y;
	gdk_device_get_position (device, NULL, &x, &y);
	prev_X = x;
	prev_Y = y;
}
static gboolean mouse_moved(GtkWidget *widget,GdkEventMotion *event, gpointer user_data) {
	gint x,y;
    if (event->state & GDK_BUTTON1_MASK) {
  
        gint wx, wy;
        gdk_device_get_position (device, NULL, &x, &y);
        g_print("Coordinates: (%u,%u)\n", x,y);
		gtk_widget_translate_coordinates(widget, gtk_widget_get_toplevel(widget), 0, 0, &wx, &wy);
		//if((wx <= SCREEN_SIZE_X-TAM_X_CARTA && wy <= SCREEN_SIZE_Y-TAM_Y_CARTA) || ((wx >= SCREEN_SIZE_X-TAM_X_CARTA) && (prev_X > x))){
		if( !((wx >= SCREEN_SIZE_X-(TAM_X_CARTA*1.5) && prev_X < x) || (wy >= SCREEN_SIZE_Y-(TAM_Y_CARTA*1.5) && prev_Y < y) ) && !( (wx <= 30 && prev_X > x) || (wy <= 30 && prev_Y > y) ) ){
			gtk_fixed_move (GTK_FIXED(fixed),widget, wx + x - prev_X ,wy + y - prev_Y);
		}
		// else if( (wx <= 30 && prev_X > x) || (wy <= 30 && prev_Y > y) ){
			
  //       }
  //       else{
  //       	gtk_fixed_move (GTK_FIXED(fixed),widget, wx + x - prev_X ,wy + y - prev_Y);
  //       }
		prev_X = x;
		prev_Y = y;

    }
    return 1;
}
int main(int argc, char *argv[]){
	gtk_init(&argc, &argv);
	GtkWidget *window;
	
	GtkWidget *event_box;
	GtkWidget *image;
	GdkSeat * seat;

	display = gdk_display_get_default();
	seat = gdk_display_get_default_seat (display);
	//device_manager = gdk_display_get_device_manager (display);
	device = gdk_seat_get_pointer (seat);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Rummikub");
	gtk_window_set_default_size(GTK_WINDOW(window), SCREEN_SIZE_X,SCREEN_SIZE_Y);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);


	fixed = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(window), fixed);

	event_box = gtk_event_box_new();
	gtk_fixed_put(GTK_FIXED(fixed), event_box,0, 0);

	image = gtk_image_new_from_file("src/image/cartas/A@.png"); // put path to your image here
	gtk_container_add(GTK_CONTAINER(event_box), image);

	g_signal_connect (G_OBJECT(event_box),"button_press_event",G_CALLBACK(clique_mouse), NULL);
	g_signal_connect (G_OBJECT (event_box),"motion_notify_event",G_CALLBACK(mouse_moved), NULL);


	g_signal_connect(G_OBJECT(window), "destroy",G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(window);
    gtk_main();
	return 0;
}