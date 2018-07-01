#ifndef EVENTOS_H
#define EVENTOS_H

#include <gtk/gtk.h>
#include "data.h"
#include "interface.h"
#include "system.h"

void clique_mouse(GtkWidget *event_box,GdkEventButton *event,gpointer data);
gboolean mouse_moved(GtkWidget *widget,GdkEventMotion *event, gpointer user_data);
gboolean focus_out(GtkWidget *widget, GdkEvent  *event,gpointer   user_data);
void init_mouse();
void comprar_cartas_user(GtkWidget *widget, gpointer data);
void finaliza_jogada_user(GtkWidget *widget, gpointer data);

#endif //EVENTOS_H