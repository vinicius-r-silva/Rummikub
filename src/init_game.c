#include "libs/init_game.h"


extern GtkWidget *fixed;
extern GdkDevice *mouse;

void carrega_estilo_jogo(){
    GtkCssProvider *provider = gtk_css_provider_new ();
    GdkDisplay *display = gdk_display_get_default ();
    GdkScreen *screen = gdk_display_get_default_screen (display);
    gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    const gchar* home = "glade/style.css";
    GError *error = 0;
    gtk_css_provider_load_from_file(provider, g_file_new_for_path(home), &error);
    g_object_unref (provider);
}

//Cria o icone na janela
GdkPixbuf *create_pixbuf(const gchar * filename) {
  GdkPixbuf *pixbuf;
  GError *error = NULL;
  pixbuf = gdk_pixbuf_new_from_file(filename, &error);
  if (!pixbuf) {  fprintf(stderr, "%s\n", error->message);g_error_free(error);}
  return pixbuf;
}

void init_mouse(){
  GdkSeat * seat;
  GdkDisplay *display;
  display = gdk_display_get_default();
  seat = gdk_display_get_default_seat (display);
  //device_manager = gdk_display_get_device_manager (display);
  mouse = gdk_seat_get_pointer (seat);
}

void tela_home(LISTA_CARTAS_PTR Baralho, JOGADORES_PTR *Lista_Jogadores){
  GtkWidget *home = gtk_fixed_new();
  gtk_fixed_put(GTK_FIXED(fixed), home, 0, 0);

  GtkWidget *event_box = gtk_event_box_new();
  gtk_fixed_put(GTK_FIXED(home), event_box,0, 0);
  gtk_widget_set_size_request(event_box, SCREEN_SIZE_X, SCREEN_SIZE_Y);
  gtk_widget_set_name(event_box,"tela_home");

  GtkWidget *n_jogador2 = gtk_button_new_with_label("");
  gtk_fixed_put(GTK_FIXED(home), n_jogador2,340,300);
  gtk_widget_set_size_request(n_jogador2, 70, 67);
  gtk_widget_set_name(n_jogador2,"bt_n_jog_2");
  GtkStyleContext *context_bt1 = gtk_widget_get_style_context(n_jogador2);
  gtk_style_context_add_class(context_bt1,"bt_n_jog_2");

  GtkWidget *n_jogador3 = gtk_button_new_with_label("");
  gtk_fixed_put(GTK_FIXED(home), n_jogador3,442,300);
  gtk_widget_set_size_request(n_jogador3, 70, 67);
  gtk_widget_set_name(n_jogador3,"bt_n_jog_3");
   GtkStyleContext *context_bt2 = gtk_widget_get_style_context(n_jogador3);
  gtk_style_context_add_class(context_bt2,"bt_n_jog_3");

  GtkWidget *n_jogador4 = gtk_button_new_with_label("");
  gtk_fixed_put(GTK_FIXED(home), n_jogador4,544,300);
  gtk_widget_set_size_request(n_jogador4, 70, 67);
  gtk_widget_set_name(n_jogador4,"bt_n_jog_4");
   GtkStyleContext *context_bt3 = gtk_widget_get_style_context(n_jogador4);
  gtk_style_context_add_class(context_bt3,"bt_n_jog_4");

  GtkWidget *n_jogador5 = gtk_button_new_with_label("");
  gtk_fixed_put(GTK_FIXED(home), n_jogador5,646,300);
  gtk_widget_set_size_request(n_jogador5, 70, 67);
  gtk_widget_set_name(n_jogador5,"bt_n_jog_5");
   GtkStyleContext *context_bt4 = gtk_widget_get_style_context(n_jogador5);
  gtk_style_context_add_class(context_bt4,"bt_n_jog_5");

  GtkWidget *bt_inicial = gtk_button_new_with_label("");
  gtk_fixed_put(GTK_FIXED(home), bt_inicial,400, 415);
  gtk_widget_set_size_request(bt_inicial, 260, 66);
  gtk_widget_set_name(bt_inicial,"bt_iniciar");

  LISTA_BT_JOG_PTR bts_n_jog = (LISTA_BT_JOG_PTR)malloc(sizeof(LISTA_BT_JOG));
  memset(bts_n_jog,0,sizeof(LISTA_BT_JOG));
  bts_n_jog->n_2 = n_jogador2;
  bts_n_jog->n_3 = n_jogador3;
  bts_n_jog->n_4 = n_jogador4;
  bts_n_jog->n_5 = n_jogador5;

  bts_n_jog->bt_ativo = 0;
  bts_n_jog->obj_home = home;
  bts_n_jog->Baralho = Baralho;
  bts_n_jog->Lista_Jogadores = Lista_Jogadores;

  //
  g_signal_connect(G_OBJECT(n_jogador2),"button_press_event",G_CALLBACK(ativa_n_jog),bts_n_jog); 
  g_signal_connect(G_OBJECT(n_jogador3),"button_press_event",G_CALLBACK(ativa_n_jog),bts_n_jog); 
  g_signal_connect(G_OBJECT(n_jogador4),"button_press_event",G_CALLBACK(ativa_n_jog),bts_n_jog); 
  g_signal_connect(G_OBJECT(n_jogador5),"button_press_event",G_CALLBACK(ativa_n_jog),bts_n_jog);

  g_signal_connect(G_OBJECT(bt_inicial),"button_press_event",G_CALLBACK(comeca_jogo),bts_n_jog);

}

void comeca_jogo(GtkWidget *bt, gint response_id, LISTA_BT_JOG_PTR data){
  g_print("\n\n%d\n\n",data->bt_ativo);
  JOGADORES_PTR Lista_Jogadores = *(data->Lista_Jogadores);

  if(data->bt_ativo > 1){
    gtk_widget_destroy((data->obj_home));
    
    criar_jogadores(&Lista_Jogadores,data->bt_ativo);
    cria_mao_jogadores(&Lista_Jogadores, data->Baralho);

    Imprime_mao_jogador(&(Lista_Jogadores->cartas), 0, 0, INICIO_X_MAO, INICIO_Y_MAO);
    tela_bem_vindo();
    atualiza_janela();
    *(data->Lista_Jogadores) = Lista_Jogadores;

    tela_tipo_entrada();
    
  }
  else{
    g_print("Nao selecionou n jogadores");
  }
  return;
}

void ativa_n_jog(GtkWidget *bt, gint response_id, LISTA_BT_JOG_PTR data){
  const gchar *id_bt =  gtk_widget_get_name((bt));
  //g_print("%s\n", id_bt);

  GtkStyleContext *context2 = gtk_widget_get_style_context(data->n_2);
  gtk_style_context_remove_class(context2,"bt_n_jog_2_foco");
  GtkStyleContext *context3 = gtk_widget_get_style_context(data->n_3);
  gtk_style_context_remove_class(context3,"bt_n_jog_3_foco");
  GtkStyleContext *context4 = gtk_widget_get_style_context(data->n_4);
  gtk_style_context_remove_class(context4,"bt_n_jog_4_foco");
  GtkStyleContext *context5 = gtk_widget_get_style_context(data->n_5);
  gtk_style_context_remove_class(context5,"bt_n_jog_5_foco");


  GtkStyleContext *context = gtk_widget_get_style_context(bt);
  if(strcmp(id_bt,"bt_n_jog_2") == 0){
    gtk_style_context_add_class(context,"bt_n_jog_2_foco");
    data->bt_ativo = 2;
  }
  else if(strcmp(id_bt,"bt_n_jog_3") == 0){
    gtk_style_context_add_class(context,"bt_n_jog_3_foco");
    data->bt_ativo = 3;
  }
  else if(strcmp(id_bt,"bt_n_jog_4") == 0){
    gtk_style_context_add_class(context,"bt_n_jog_4_foco");
    data->bt_ativo = 4;
  }
  else if(strcmp(id_bt,"bt_n_jog_5") == 0){
    gtk_style_context_add_class(context,"bt_n_jog_5_foco");
    data->bt_ativo = 5;
  }
  else{
    return;
  }
  return;
}

//Constroi janela - funções do GTK
void constroi_janela_jogo(GtkWidget *window){
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(window);
}

//Adiciona botões no jogo e seus eventos
void cria_botoes_jogo(GtkWidget *bt_compra_carta, GtkWidget *bt_finaliza_jog){
  //Cria botão de COMPRA CARTAS
  bt_compra_carta = gtk_button_new_with_label("");
  gtk_fixed_put(GTK_FIXED(fixed), bt_compra_carta, 20,420);
  gtk_widget_set_size_request(bt_compra_carta, 88, 60);
  gtk_widget_set_name(bt_compra_carta,"bt_compra_carta");
  
  //Adiciona a class para o botão COMPRA CARTAS
  GtkStyleContext *context_bt1 = gtk_widget_get_style_context(bt_compra_carta);
  gtk_style_context_add_class(context_bt1,"bt_compra_carta");
    
  //Evento que realiza COMPRA CARTAS para o usuario
  g_signal_connect(G_OBJECT(bt_compra_carta),"button_press_event",G_CALLBACK(comprar_cartas_user), NULL); 

  //Cria botão de FINALIZAR JOGADA
  bt_finaliza_jog = gtk_button_new_with_label("");
  gtk_fixed_put(GTK_FIXED(fixed), bt_finaliza_jog, 20,485);
  gtk_widget_set_size_request(bt_finaliza_jog, 88, 65);
  gtk_widget_set_name(bt_finaliza_jog,"bt_finaliza_jog");
  
  GtkStyleContext *context_bt2 = gtk_widget_get_style_context(bt_finaliza_jog);
  gtk_style_context_add_class(context_bt2,"bt_finaliza_jog");
  
  //Evento que realiza FINALIZAR JOGADA para o usuario
  g_signal_connect(G_OBJECT(bt_finaliza_jog),"button_press_event",G_CALLBACK(finaliza_jogada_user), NULL); 
}

//Função para criar imagens do jogo
void cria_jogo_imagens(){
  GtkWidget *img_mesa = gtk_image_new_from_file("src/image/mesa.png"); 
  gtk_fixed_put(GTK_FIXED(fixed), img_mesa,120, 15);

  GtkWidget *img_mao = gtk_image_new_from_file("src/image/mao.png"); 
  gtk_fixed_put(GTK_FIXED(fixed), img_mao,120, 420);
}