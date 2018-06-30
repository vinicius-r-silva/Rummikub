#ifndef EVENTOS_H
#define EVENTOS_H

#include <gtk/gtk.h>
#include "data.h"
#include "interface.h"

void clique_mouse(GtkWidget *event_box,GdkEventButton *event,gpointer data);
gboolean mouse_moved(GtkWidget *widget,GdkEventMotion *event, gpointer user_data);
gboolean focus_out(GtkWidget *widget, GdkEvent  *event,gpointer   user_data);
void init_mouse();

#endif //EVENTOS_H