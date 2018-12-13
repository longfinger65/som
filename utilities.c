#include "/home/pi/projects/som/utilities.h"

int show_modal_info_dialog(char *caption, char * info_text, gint width, gint height, GdkWindow *parent_window){
    
    /************************************************************************************************************************
    *
    * Function name: get_pointer_to_input_maps
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

	int return_value;
    GtkWidget *dialog, *dialog_label;
    GtkBuilder *builder;
    GError *errors = NULL;
    gint knopf;
    builder = gtk_builder_new ();
    gtk_builder_add_from_file (builder, "dialog3.xml", &errors);

    //--- Initial settings ---

    return_value = 0;

    // ---

    dialog = (GtkWidget*)gtk_builder_get_object (builder, "modal_info_dialog");
    // gtk_widget_set_parent_window (dialog, parent_window);
    gtk_window_set_title (GTK_WINDOW( dialog ), caption);
    gtk_window_set_default_size (GTK_WINDOW( dialog ), width, height);
    g_signal_connect_swapped (dialog, "response", G_CALLBACK (gtk_widget_hide), dialog);
    dialog_label = (GtkWidget*)gtk_builder_get_object (builder, "modal_info_dialog_label_1");
    gtk_label_set_text ((GtkLabel*)dialog_label, info_text);
    gtk_widget_show_all (dialog);
    knopf = gtk_dialog_run (GTK_DIALOG(dialog));
    switch (knopf){
        case 2:
            printf("modal info dialog was shown\n");
        break;
        default:
        break;
    }   

    return return_value;
}

int update_pixmap(som *the_map, int options){
    
    /************************************************************************************************************************
    *
    * Function name:                - update_pixmap
    * 
    * Function purpose:             - Setup/change the topology of the neural net
    * 
    * Input parameter:
    * 
    *   the_net     [neural_net *]  -
    *
    * Return parameter:
    * 
    *   ret_value   [int]           - 0 = ok
    *                                 1 = something went wrong
    *
    ************************************************************************************************************************/

#ifdef DEBUG    
        printf("\nI am in update_pixmap.\n");
#endif

    //--- Variables ---

	int return_value;
    int rowstride, n_channels;
    int pixmap_width;
    int pixmap_height;
    double min_value;
    double max_value;
    double difference;
    double normalizing_factor;
    guchar *pixels, *p;
    GdkPixbuf *temp_pixbuf;

    //--- Initial settings ---

    return_value = 0;
    n_channels = 3;

    // ---
    
    // Update the picture that is learned
    temp_pixbuf = gtk_image_get_pixbuf((GtkImage*)weight_images [0][0]);
    temp_pixbuf = gdk_pixbuf_scale_simple (temp_pixbuf, the_map->map_topology.width_of_input_map, the_map->map_topology.height_of_input_map, GDK_INTERP_BILINEAR);
    pixels = gdk_pixbuf_get_pixels(temp_pixbuf);
    rowstride = gdk_pixbuf_get_rowstride (temp_pixbuf);

    for (int i=0; i < the_map->map_topology.width_of_input_map; i++){
        for (int j=0; j < the_map->map_topology.height_of_input_map; j++){
            p = pixels + i * rowstride + j * n_channels;
            p[0] = (char)(int)(the_map->input_map[i][j]);
            p[1] = (char)(int)(the_map->input_map[i][j]);
            p[2] = (char)(int)(the_map->input_map[i][j]);
        }
    }
    pixbuf_of_weight_images[0][0] = gdk_pixbuf_scale_simple (temp_pixbuf, 30, 30,GDK_INTERP_BILINEAR);
    gtk_image_set_from_pixbuf ((GtkImage*)weight_images[0][0],pixbuf_of_weight_images[0][0]);
    
    // Update the weight images
    if(options == 0){
        for(int ci=0; ci < the_map->map_topology.width_of_cluster_map; ci++){
            for(int cj=0; cj < the_map->map_topology.width_of_cluster_map; cj++){
                temp_pixbuf = gtk_image_get_pixbuf((GtkImage*)weight_images [ci+1][cj]);
                temp_pixbuf = gdk_pixbuf_scale_simple (temp_pixbuf, the_map->map_topology.width_of_input_map, the_map->map_topology.height_of_input_map, GDK_INTERP_BILINEAR);
                pixels = gdk_pixbuf_get_pixels(temp_pixbuf);
                rowstride = gdk_pixbuf_get_rowstride (temp_pixbuf);
                // Calculate normalization
                min_value = the_map->weights[ci][cj][0][0];
                max_value = the_map->weights[ci][cj][0][0];
                for (int i=0; i < the_map->map_topology.height_of_input_map; i++){
                    for (int j=0; j < the_map->map_topology.width_of_input_map; j++){
                        if(the_map->weights[ci][cj][i][j] < min_value){
                            min_value = the_map->weights[ci][cj][i][j];
                        }
                        if(the_map->weights[ci][cj][i][j] > max_value){
                            max_value = the_map->weights[ci][cj][i][j];
                        }
                    }
                }
                difference = max_value - min_value;
                if(difference==0){
                    difference=1;
                }
                normalizing_factor = 255 / difference;
                // Update the filter kernel images
                for (int i=0; i < the_map->map_topology.height_of_input_map; i++){
                    for (int j=0; j < the_map->map_topology.width_of_input_map; j++){
                        p = pixels + i * rowstride + j * n_channels;
                        p[0] = (char)(int)(255-((the_map->weights[ci][cj][i][j]-min_value)*normalizing_factor)*255);
                        p[1] = (char)(int)(255-((the_map->weights[ci][cj][i][j]-min_value)*normalizing_factor)*255);
                        p[2] = (char)(int)(255-((the_map->weights[ci][cj][i][j]-min_value)*normalizing_factor)*255);
                    }
                }
                pixbuf_of_weight_images [ci+1][cj] = gdk_pixbuf_scale_simple (temp_pixbuf, (int)(the_map->map_topology.width_of_input_map*the_map->weights_image_scaling_factor), (int)(the_map->map_topology.height_of_input_map*the_map->weights_image_scaling_factor),GDK_INTERP_BILINEAR);
                gtk_image_set_from_pixbuf ((GtkImage*)weight_images[ci+1][cj],pixbuf_of_weight_images[ci+1][cj]);
            }
        }
    }
    while (g_main_context_pending(NULL)) {
        g_main_context_iteration(NULL,FALSE);
    }
    sleep(0.01);
    return return_value;
}
