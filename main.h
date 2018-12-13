#include <glib/gi18n.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <math.h>
#include <string.h>
#include "/home/pi/projects/som/read_mnist.h"
#include <sys/time.h>
#include "/home/pi/projects/som/otmath.h"
#include "/home/pi/projects/som/command.h"
#include "/home/pi/projects/som/program_info.h"
#include "/home/pi/projects/som/som.h"
#include "/home/pi/projects/som/chart_plot_lib.h"


#ifndef LOAD_ONN_FILE 
#define LOAD_ONN_FILE                                               0
#endif
#ifndef SAVE_ONN_FILE
#define	SAVE_ONN_FILE				                                1
#endif


#ifndef MAIN_H_
#define MAIN_H_


GtkWidget ***weight_images;
GdkPixbuf ***pixbuf_of_weight_images;
GtkWidget *grid, *grid_of_weight_images;
chart_plotter *graph_window;

const gchar *myCssFile = "mystyle.css";

typedef struct system_state system_state;

struct system_state{
    
    int show_weight_images;                              // 1 = show
    int number_of_rows_in_grid_of_weight_images;         // 1 = created
    int number_of_columns_in_grid_of_weight_images;      // 1 = created
    int weight_images_are_created;                       // 1 = created
    
    
};

system_state program_state;
mnist_data image_data;
unsigned char char_pixel[28][28];


gboolean close_screen(gpointer data){
    
    gtk_widget_destroy((GtkWidget*)data);
    gtk_main_quit ();
    return(FALSE);
    
}

void show_splash_screen(char* image_name,int time,int width,int height){

    /************************************************************************************************************************
    *
    * Function name: show_splash_screen
    * 
    * Function purpose: Setup/change the topology of the neural net
    * 
    * Input parameter:
    * 
    *               me -
    *               v -
    * 
    * Return parameter:
    * 
    *               ret -
    *
    ************************************************************************************************************************/

    //--- Variables ---

    GtkWidget *splash_screen, *image, *info, *box;
    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;
    GError *error = 0;

    //--- Initial settings ---

    box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);

    // ---

    splash_screen = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_name (splash_screen,"splash_screen");
    gtk_widget_set_size_request (splash_screen, width, height);
    gtk_window_set_decorated(GTK_WINDOW (splash_screen), FALSE);
    gtk_window_set_position(GTK_WINDOW(splash_screen),GTK_WIN_POS_CENTER_ALWAYS);
    gtk_window_set_resizable(GTK_WINDOW(splash_screen), FALSE);
    image=gtk_image_new_from_file(image_name);
    info=gtk_label_new ("OdarTec SOM c 2017 - 2018");
    gtk_widget_set_name (info,"info");
    
    gtk_box_pack_start (GTK_BOX (box), image, FALSE, FALSE, 0);
    gtk_box_pack_end (GTK_BOX (box), info, FALSE, FALSE, 0);

	gtk_container_add (GTK_CONTAINER (splash_screen), box);
    
    provider = gtk_css_provider_new ();
    display = gdk_display_get_default ();
    screen = gdk_display_get_default_screen (display);
    gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    gtk_css_provider_load_from_file(provider, g_file_new_for_path(myCssFile), &error);
    g_object_unref (provider);
    
    
    
    
    gtk_widget_show_all (splash_screen);
    g_timeout_add (time, close_screen, splash_screen);
    gtk_widget_show_all (splash_screen);

    gtk_main ();
    
}

int setup_weight_images(som *the_map);
int organize_weight_image_grid(som *the_map);

#endif /* MAIN_H_ */
