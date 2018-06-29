#include "libs/interface.h"

extern GtkWidget *fixed;

void move_imagem(GtkWidget *image,int descola_X, int descola_Y){
  int img_X, img_Y;
  gtk_widget_translate_coordinates(image, gtk_widget_get_toplevel(image), 0, 0, &img_X, &img_Y);

  img_X += descola_X;
  img_Y += descola_Y;

  if (img_X < 1){
    img_X = 1;
  }
  else if(img_X > SCREEN_SIZE_X-TAM_X_CARTA){
    img_X = SCREEN_SIZE_X-TAM_X_CARTA;
  }

  if (img_Y < 1){
    img_Y = 1;
  }
  else if(img_Y > SCREEN_SIZE_Y-TAM_Y_CARTA){
    img_Y = SCREEN_SIZE_Y-TAM_Y_CARTA;
  }
  gtk_fixed_move (GTK_FIXED(fixed),image,img_X,img_Y);

}