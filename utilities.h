/*
 * utilities.h
 *
 * Created: 02.07.2018 15:36:22
 *  Author: Boss
 */ 

#include <glib/gi18n.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <string.h>
#include "/home/pi/projects/som/som.h"


extern GdkPixbuf ***pixbuf_of_weight_images;
extern GtkWidget ***weight_images;


#ifndef UTILITIES_H_
#define UTILITIES_H_

int show_modal_info_dialog(char *caption, char * info_text, gint width, gint height, GdkWindow *parent_window);
int update_pixmap(som *the_map, int options);

#endif //--- UTILITIES_H_ ---
