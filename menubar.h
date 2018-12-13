/*
 * menubar.h
 *
 * Created: 02.07.2016 15:36:22
 *  Author: Boss
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib/gi18n.h>
#include <gtk/gtk.h>
#include "/home/pi/projects/som/som.h"
#include "/home/pi/projects/som/chart_plot_lib.h"


#ifndef MENUBAR_H_
#define MENUBAR_H_


//--- Commands --- 

gboolean statusbar_hint(GtkMenuItem * menuitem, GdkEventProximity *event, GtkStatusbar *statusbar);
GtkWidget* make_menubar (GtkWidget* statusbar, GtkBuilder *builder, som *the_map, GtkWidget* image_grid, void * the_program_state, chart_plotter * graph_window, GtkWindow *main_window);

#endif /* MENUBAR_H_ */
