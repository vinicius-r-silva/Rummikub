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

GtkWidget* Insere_Carta_Interface(int Naipe, int Valor, GtkWidget *Painel, char Interacao){
  GtkWidget *img_carta;
  GtkWidget *event_box;

  char V = int_2_hexa(Valor);
  char N = Int_2_Naipe(Naipe);

  char resultado[27]; memset(resultado, 0, sizeof(char)*27);
  sprintf(resultado,"src/image/cartas/%c%c.png",V,N);
  //g_print("N: %2d (%c), V: %2d (%c)\n", Naipe, N, Valor, V);

  char NomeCarta[6];
  sprintf(NomeCarta,"%cC_%c%c",Interacao, V, N);
  NomeCarta[5] = '\0';

  char NomeEventBox[6];
  sprintf(NomeEventBox,"%cE_%c%c",Interacao, V,N);
  NomeEventBox[5] = '\0';

  event_box = gtk_event_box_new();
  gtk_fixed_put(GTK_FIXED(Painel), event_box,0, 0);
  gtk_widget_set_child_visible(event_box, 0);
  gtk_widget_set_name(event_box, NomeEventBox);

  img_carta = gtk_image_new_from_file(resultado);
  gtk_widget_set_name(img_carta, NomeCarta);
  gtk_container_add(GTK_CONTAINER(event_box), img_carta);

  g_signal_connect (G_OBJECT(event_box),"button_press_event",G_CALLBACK(clique_mouse), NULL);
  g_signal_connect (G_OBJECT(event_box),"motion_notify_event",G_CALLBACK(mouse_moved), NULL);
  g_signal_connect (G_OBJECT(event_box), "button-release-event",G_CALLBACK(focus_out), NULL);
  return event_box;
}


void Insere_Img_Jogador(JOGADORES_PTR Jogador){
  char Caminho[40]; memset(Caminho, 0, sizeof(char)*40);

  if(Jogador->Sua_Vez)
    sprintf(Caminho,"src/image/user%d_foco.png",Jogador->Id+1);
  else
    sprintf(Caminho,"src/image/user%d.png",Jogador->Id+1);

  Jogador->img = gtk_image_new_from_file(Caminho); 
  gtk_fixed_put(GTK_FIXED(fixed), Jogador->img ,INICIO_X_JOGADORES, INICIO_Y_JOGADORES + ESPACO_Y_JOGADORES*Jogador->Id);
}


void Coloca_Borda_Jogador(JOGADORES_PTR Jogador){
  Jogador->Sua_Vez = 1;
  char Caminho[40]; memset(Caminho, 0, sizeof(char)*40);
  sprintf(Caminho,"src/image/user%d_foco.png",Jogador->Id+1);

  gtk_image_set_from_file(GTK_IMAGE(Jogador->img), Caminho);
}

void Tira_Borda_Jogador(JOGADORES_PTR Jogador){
  Jogador->Sua_Vez = 0;
  char Caminho[40]; memset(Caminho, 0, sizeof(char)*40);
  sprintf(Caminho,"src/image/user%d.png",Jogador->Id+1);

  gtk_image_set_from_file(GTK_IMAGE(Jogador->img), Caminho);
}