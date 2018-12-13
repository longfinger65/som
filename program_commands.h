#include <glib/gi18n.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <math.h>
#include <string.h>
#include "/home/pi/projects/filter_test_002/read_mnist.h"

#ifndef PROGRAM_COMMANDS_H_
#define PROGRAM_COMMANDS_H_

extern GtkWidget **image2;

void starte_modal_dialog (GtkWidget *w, GtkBuilder *b);
void on_about (GtkWidget *w, GtkBuilder *b);
void on_open_image (GtkWidget* sender, gpointer user_data);
void on_load_mnist_image (GtkWidget* sender, gpointer user_data);
int setup_neural_net(mnist_data **dat);

#endif /* PROGRAM_COMMANDS_H_ */
