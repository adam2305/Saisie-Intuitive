#include <stdlib.h>
#include <stdio.h>
#include "data.h"
#include "prediction.h"
#include <string.h>
#include <gtk/gtk.h>

//Déclaration des élements 
GtkBuilder *builder;
GtkWidget *window;
GtkWidget *txt1;
GtkWidget *txt2;
GtkWidget *entry1;
GtkWidget *button1;
GtkWidget *button2;
GtkWidget *button3;
GtkWidget *button4;
GtkWidget *button5;
GtkWidget *button6;
GtkWidget *button7;
GtkWidget *check1;
GtkWidget *check2;
GtkWidget *label1;
GtkWidget *entry1;
GtkWidget *txt3;
GtkWidget *txt4;
GtkWidget *txt5;
GtkWidget *prediction1;
GtkWidget *prediction2;
GtkWidget *prediction3;
GtkTextBuffer *buffer;
GtkTextBuffer *buffer1;
GtkTextIter start, end;

FrequentWordTab hashtab;
int mode = 0;

Element p1;
Element p2;
Element p3;




void button1_clicked_cb(GtkButton *b);
void button2_clicked(GtkButton *b);
void button3_clicked(GtkButton *b);
void button6_clicked(GtkButton *b);
void button4_clicked(GtkButton *b);
void button5_clicked(GtkButton *b);
void check1_toggled(GtkToggleButton *b);
void check2_toggled(GtkToggleButton *b);
void entry1_changed(GtkEntry *e);
void button7_clicked(GtkButton *b);
void prediction1_clicked(GtkButton *b);
void prediction2_clicked(GtkButton *b);
void prediction3_clicked(GtkButton *b);



void button1_clicked_cb(GtkButton *b){
  buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(txt1));
  gtk_text_buffer_get_start_iter(buffer, &start);
  gtk_text_buffer_get_end_iter(buffer, &end);
  char *text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
  if(text[0]!=NULL){
    InsertElement(&hashtab,text,true);
  }
  g_free(text);
  gtk_text_buffer_set_text(buffer, "", -1);
}

void button2_clicked(GtkButton *b){
  buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(txt2));
  gtk_text_buffer_get_start_iter(buffer, &start);
  gtk_text_buffer_get_end_iter(buffer, &end);
  char *text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
  if(text[0]!=NULL){
    RemoveElement(&hashtab,text);
  }
  g_free(text);
  gtk_text_buffer_set_text(buffer, "", -1);
}

void button3_clicked(GtkButton *b){
  GtkWidget *popup_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
  GtkWidget *text_view = gtk_text_view_new();
  gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
  GtkTextBuffer *buffer;
  buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
  gtk_text_buffer_set_text(buffer,   ShowPersonalDictionnary(&hashtab), -1);
  gtk_container_add(GTK_CONTAINER(scrolled_window), text_view);
  gtk_window_set_default_size(GTK_WINDOW(popup_window), 300, 570);
  gtk_window_set_title(GTK_WINDOW(popup_window), "Dictionnaire Personnel");
    // Add a label to the popup window
  GtkWidget *label = gtk_label_new("This is a popup window!\ntest");
  gtk_container_add(GTK_CONTAINER(popup_window), scrolled_window);

    // Show the popup window
  gtk_widget_show_all(popup_window);
  //free(buffer);
}

void button4_clicked(GtkButton *b){
  char tmp[128];
  strcpy(tmp,gtk_entry_get_text(entry1));
  strcat(tmp," ");
  read_words(&hashtab,tmp);
  gtk_entry_set_text(GTK_ENTRY(entry1), "");
}

void button6_clicked(GtkButton *b){
  GtkWidget *popup_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
  GtkWidget *text_view = gtk_text_view_new();
  gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
  GtkTextBuffer *buffer;
  buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
  gtk_text_buffer_set_text(buffer, ShowDictionnary(&hashtab), -1);
  gtk_container_add(GTK_CONTAINER(scrolled_window), text_view);
  gtk_window_set_default_size(GTK_WINDOW(popup_window), 300, 570);
  gtk_window_set_title(GTK_WINDOW(popup_window), "Dictionnaire Français");
  GtkWidget *label = gtk_label_new("This is a popup window!\ntest");
  gtk_container_add(GTK_CONTAINER(popup_window), scrolled_window);
  gtk_widget_show_all(popup_window);
}

void button5_clicked(GtkButton *b){
  buffer1 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(txt3));
  gtk_text_buffer_get_start_iter(buffer1, &start);
  gtk_text_buffer_get_end_iter(buffer1, &end);
  char *text = gtk_text_buffer_get_text(buffer1, &start, &end, FALSE);
  if(text[0]!=NULL){
    AddPersonalDict(&hashtab,text);
  }
  g_free(text);
  gtk_text_buffer_set_text(buffer1, "", -1);
}

void button7_clicked(GtkButton *b){
  buffer1 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(txt4));
  gtk_text_buffer_get_start_iter(buffer1, &start);
  gtk_text_buffer_get_end_iter(buffer1, &end);
  char *text = gtk_text_buffer_get_text(buffer1, &start, &end, FALSE);
  buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(txt5));
  gtk_text_buffer_get_start_iter(buffer, &start);
  gtk_text_buffer_get_end_iter(buffer, &end);
  char *text1 = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
  if(text[0]!=NULL && text1[0]!=NULL){
    modifier(&hashtab,text,text1);
  }
  g_free(text);
  gtk_text_buffer_set_text(buffer, "", -1);
  g_free(text1);
  gtk_text_buffer_set_text(buffer1, "", -1);
}

void prediction1_clicked(GtkButton *b){
  char *text = gtk_button_get_label(b);
  to_lower(text);
  char tmp1[200];
  strcpy(tmp1,gtk_entry_get_text(entry1));
  changeLastWord(tmp1,text);
  strcat(tmp1," ");
  gtk_entry_set_text(entry1, tmp1);
}

void prediction2_clicked(GtkButton *b){
  char *text = gtk_button_get_label(b);
  to_lower(text);
  char tmp2[200];
  strcpy(tmp2,gtk_entry_get_text(entry1));
  changeLastWord(tmp2,text);
  strcat(tmp2," ");
  gtk_entry_set_text(entry1,tmp2);
}

void prediction3_clicked(GtkButton *b){
  char *text = gtk_button_get_label(b);
  to_lower(text);
  char tmp3[200];
  strcpy(tmp3,gtk_entry_get_text(entry1));
  changeLastWord(tmp3,text);
  strcat(tmp3," ");
  gtk_entry_set_text(entry1, tmp3);
}


void check1_toggled(GtkToggleButton *b){
  gboolean checked = gtk_toggle_button_get_active(b);
  if (checked) {
    gtk_toggle_button_set_active(check2,FALSE);
    mode = 0;
  }
}

void check2_toggled(GtkToggleButton *b){
 
  gboolean checked = gtk_toggle_button_get_active(b);
  if (checked) {
    gtk_toggle_button_set_active(check1,FALSE);
    mode = 1;
  } 
}

void entry1_changed(GtkEntry *e){
  char tmp[200];
  strcpy(tmp,gtk_entry_get_text(e));
    if(strlen(tmp)>=1)
        strcpy(tmp,get_last_word(tmp));
    if(strlen(tmp)>=1){
        PropositionFreq(&hashtab,tmp,&p1,&p2,&p3,mode);
        gtk_button_set_label(prediction1,p1.word);
        gtk_button_set_label(prediction2,p2.word);
        gtk_button_set_label(prediction3,p3.word);
    }
    else{
        gtk_button_set_label(prediction1," ");
        gtk_button_set_label(prediction2," ");
        gtk_button_set_label(prediction3," ");
    }
    
}

void main(int argc,char *argv[]){

  InitializeFrequentWordTab(&hashtab);
  AddAllDictionnary(&hashtab,"ods6.txt");
  AddPersonalDict(&hashtab,"mots_courants.txt");
  printf("*** Lancement du programme ***\n");
  printf("*** Chargement des données terminé avec succés ***\n");
  char tmp[200] = "ab";
  char *word = "abaisson";
  changeLastWord(tmp,word);
  printf("%s",tmp);
  gtk_init(&argc, &argv);

  builder = gtk_builder_new_from_file ("interface.glade");
  window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
  txt1 = GTK_WIDGET(gtk_builder_get_object(builder, "txt1"));
  txt2 = GTK_WIDGET(gtk_builder_get_object(builder, "txt2"));
  entry1 = GTK_WIDGET(gtk_builder_get_object(builder, "entry1"));
  button1 = GTK_WIDGET(gtk_builder_get_object(builder, "button1"));
  button2 = GTK_WIDGET(gtk_builder_get_object(builder, "button2"));
  button3 = GTK_WIDGET(gtk_builder_get_object(builder, "button3"));
  button4 = GTK_WIDGET(gtk_builder_get_object(builder, "button4"));
  button5 = GTK_WIDGET(gtk_builder_get_object(builder, "button5"));
  button6 = GTK_WIDGET(gtk_builder_get_object(builder, "button6"));
  button7 = GTK_WIDGET(gtk_builder_get_object(builder, "button7"));
  check1 = GTK_WIDGET(gtk_builder_get_object(builder, "check1"));
  check2 = GTK_WIDGET(gtk_builder_get_object(builder, "check2"));
  //entry1 = GTK_WIDGET(gtk_builder_get_object(builder, "entry1"));
  txt3 = GTK_WIDGET(gtk_builder_get_object(builder, "txt3"));
  txt4 = GTK_WIDGET(gtk_builder_get_object(builder, "txt4"));
  txt5 = GTK_WIDGET(gtk_builder_get_object(builder, "txt5"));
  prediction1 = GTK_WIDGET(gtk_builder_get_object(builder, "prediction1"));
  prediction2 = GTK_WIDGET(gtk_builder_get_object(builder, "prediction2"));
  prediction3 = GTK_WIDGET(gtk_builder_get_object(builder, "prediction3"));

  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  gtk_builder_connect_signals(builder, NULL);

  GdkColor color;
  color.red = 0x8C8C;
  color.green = 0x4242;
  color.blue = 0xd7d7;
  gtk_widget_modify_bg(GTK_WIDGET(window),GTK_STATE_NORMAL,&color);

  g_signal_connect(G_OBJECT(button1), "clicked", G_CALLBACK(button1_clicked_cb), NULL);
  g_signal_connect(G_OBJECT(button2), "clicked", G_CALLBACK(button2_clicked), NULL);
  g_signal_connect(G_OBJECT(button3), "clicked", G_CALLBACK(button3_clicked), NULL);
  g_signal_connect(G_OBJECT(button4), "clicked", G_CALLBACK(button4_clicked), NULL);
  g_signal_connect(G_OBJECT(button5), "clicked", G_CALLBACK(button5_clicked), NULL);
  g_signal_connect(G_OBJECT(button6), "clicked", G_CALLBACK(button6_clicked), NULL);
  g_signal_connect(G_OBJECT(button7), "clicked", G_CALLBACK(button7_clicked), NULL);
  g_signal_connect(G_OBJECT(prediction1), "clicked", G_CALLBACK(prediction1_clicked), NULL);
  g_signal_connect(G_OBJECT(prediction2), "clicked", G_CALLBACK(prediction2_clicked), NULL);
  g_signal_connect(G_OBJECT(prediction3), "clicked", G_CALLBACK(prediction3_clicked), NULL);
  g_signal_connect(G_OBJECT(check1), "toggled", G_CALLBACK(check1_toggled), NULL);
  g_signal_connect(G_OBJECT(check2), "toggled", G_CALLBACK(check2_toggled), NULL);
  g_signal_connect(G_OBJECT(entry1), "changed", G_CALLBACK(entry1_changed), NULL);

  gtk_toggle_button_set_active(check1,TRUE);
  gtk_toggle_button_set_active(check2,FALSE);


  gtk_widget_show(window);
  gtk_main();
}





