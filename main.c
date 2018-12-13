//#include <config.h>
//#define MNIST_DOUBLE

#include "/home/pi/projects/som/main.h"
#include "/home/pi/projects/som/menubar.h"
#include <sys/resource.h>

GtkWidget* create_window (GtkBuilder *builder, GtkWidget ***weight_images, som * the_map){

	GtkWidget *window;
    GtkWidget *statbar;
    GtkWidget *menubar;
    guchar *pixel, *p;
    GtkAccelGroup *group;
    guint statbar_context;
    int rowstride;
    
    //--- Initial settings ---

	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);    
    grid_of_weight_images = gtk_grid_new();
    grid = gtk_grid_new();
    GtkWidget *scwin = gtk_scrolled_window_new(NULL, NULL);
    statbar = gtk_statusbar_new();
    group = gtk_accel_group_new();
        
    //---
    
    // Create the main grid
    
    gtk_grid_insert_row (GTK_GRID (grid), 0);
    gtk_grid_insert_row (GTK_GRID (grid), 1);
    gtk_grid_insert_row (GTK_GRID (grid), 2);    
    //gtk_grid_set_row_baseline_position ((GtkGrid*)grid, 10,GTK_BASELINE_POSITION_BOTTOM);
	gtk_container_add (GTK_CONTAINER (window), grid);
    
    // Create the scroll window

    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scwin), GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
    gtk_grid_attach (GTK_GRID (grid), scwin, 0, 1, 1, 1);
    gtk_container_add(GTK_CONTAINER(scwin), grid_of_weight_images);
    
	// Create the main window
    
	gtk_window_set_title (GTK_WINDOW (window), "OdarTec SOM");
    gtk_window_add_accel_group(GTK_WINDOW(window), group);

    // Create the menu bar

    menubar = make_menubar (statbar, builder, the_map, grid, &program_state, graph_window, (GtkWindow*) window);
    gtk_widget_set_valign (menubar, GTK_ALIGN_START);
    gtk_grid_attach (GTK_GRID (grid), menubar, 0, 0, 1, 1);
    
    // Create the statusbar
    
    gtk_widget_set_name (statbar,"statusbar");
    statbar_context = gtk_statusbar_get_context_id(GTK_STATUSBAR (statbar), "Statusbar example");
    gtk_widget_set_valign (statbar, GTK_ALIGN_END);
    gtk_widget_set_hexpand (statbar, TRUE);
    gtk_grid_attach (GTK_GRID (grid), statbar, 0, 2, 1, 1);
    gtk_widget_show (statbar);
    gtk_widget_set_vexpand (grid_of_weight_images, TRUE);


	//--- Connect signals ---

	//--- Exit when the window is closed
    
	g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

	return window;
}

int setup_weight_images(som *the_map){

    /************************************************************************************************************************
    *
    * Function name:                    - setup_weight_images
    * 
    * Function purpose:                 - Setup/change the weight images
    * 
    * Input parameter:
    * 
    *   the_net         [neural_net *]  -
    * 
    * Return parameter:
    * 
    *   return_value    [int]           - 0 = ok
    *                                     1 = something went wrong
    *
    ************************************************************************************************************************/

#ifdef DEBUG
    printf("\nInside setup_weight_images.\n");
#endif

    //--- Variables ---

    int return_value;

    //--- Initial settings ---

    return_value = 0;
    // Delete all rows and columns of the grid and 
    
    if(program_state.number_of_rows_in_grid_of_weight_images != 0){
        
        // Free the memory allocated for the images
        
        // Delete all rows and columns
        
        for(int i=0; i<program_state.number_of_columns_in_grid_of_weight_images; i++){
            gtk_grid_remove_column ((GtkGrid*) grid_of_weight_images, 0);
        }
        for(int i=0; i<=program_state.number_of_rows_in_grid_of_weight_images; i++){
            gtk_grid_remove_row ((GtkGrid*) grid_of_weight_images, 0);
        }
        //program_state.grid_of_weight_images_is_created = 0;
    }

    // ---
    printf("here");
    // Allocate memory for the images
    // Allocate memory for the image layer / rows + 1 for the image that gets learned
    weight_images = calloc(the_map->map_topology.width_of_cluster_map + 1, sizeof *weight_images); 
    pixbuf_of_weight_images = calloc(the_map->map_topology.width_of_cluster_map + 1, sizeof *pixbuf_of_weight_images);
    for(int i=0; i <= the_map->map_topology.width_of_cluster_map; i++){
        if(i==0){
            weight_images[0] = calloc(1, sizeof **weight_images);
            pixbuf_of_weight_images[0] = calloc(1, sizeof **pixbuf_of_weight_images);
            pixbuf_of_weight_images[0][0] = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 8, the_map->map_topology.width_of_input_map, the_map->map_topology.height_of_input_map);
            weight_images[0][0] = gtk_image_new_from_pixbuf(pixbuf_of_weight_images[0][0]);
            gtk_widget_show(weight_images[0][0]);
        }else{
            weight_images[i] = calloc(the_map->map_topology.width_of_cluster_map, sizeof **weight_images);
            pixbuf_of_weight_images[i] = calloc(the_map->map_topology.width_of_cluster_map, sizeof **pixbuf_of_weight_images);
            for(int j=0; j < the_map->map_topology.width_of_cluster_map; j++){
                pixbuf_of_weight_images [i][j] = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 8, the_map->map_topology.width_of_input_map, the_map->map_topology.height_of_input_map);
                weight_images[i][j] = gtk_image_new_from_pixbuf(pixbuf_of_weight_images [i][j]);
                gtk_widget_show(weight_images[i][j]);
            }
        }
    }

    program_state.weight_images_are_created = 1;
    return return_value;
}

int organize_weight_image_grid(som *the_map){

    /************************************************************************************************************************
    *
    * Function name:                    - organize_weight_image_grid
    * 
    * Function purpose:                 - Setup/change the weight images
    * 
    * Input parameter:
    * 
    *   the_net         [som *]  - The self organizing map
    *
    * Return parameter:
    * 
    *   return_value    [int]           - 0 = ok
    *                                     1 = something went wrong
    *
    ************************************************************************************************************************/

#ifdef DEBUG    
        printf("\nI am in organize_weight_image_grid.\n");
#endif

    //--- Variables ---

    int return_value;
    
    //--- Initial settings ---
    
    return_value = 0;

    // Delete all rows and columns of the grid and 
    
    if(program_state.number_of_rows_in_grid_of_weight_images != 0){
        
        // Free the memory allocated for the images
        
        // Delete all rows and columns
        
        for(int j=0; j < program_state.number_of_columns_in_grid_of_weight_images; j++){
            gtk_grid_remove_column ((GtkGrid*) grid_of_weight_images, 0);
        }
        for(int i=0; i < program_state.number_of_rows_in_grid_of_weight_images; i++){
            gtk_grid_remove_row ((GtkGrid*) grid_of_weight_images, 0);
        }
        //program_state.grid_of_filter_weight_is_created = 0;
    }

    // ---
        
    for(int i=0; i <= the_map->map_topology.width_of_cluster_map; i++){     //<= because of the first image that is the input image
        gtk_grid_insert_row (GTK_GRID (grid_of_weight_images), 0);
    }
    for(int j=0; j < the_map->map_topology.width_of_cluster_map; j++){
        gtk_grid_insert_column (GTK_GRID (grid_of_weight_images), 0);
    }
    for(int i=0; i <= the_map->map_topology.width_of_cluster_map; i++){     //<= because of the first image that is the input image
        if(i==0){
            gtk_grid_attach (GTK_GRID (grid_of_weight_images), weight_images[0][0], 0, 1, 1, 1);
        }else{
            for(int j=0; j < the_map->map_topology.width_of_cluster_map; j++){
                gtk_grid_attach (GTK_GRID (grid_of_weight_images), weight_images[i][j], j, i+1, 1, 1);
            }
        }
    }

    return return_value;

}

int main (int argc, char *argv[]){

    GError *errors = NULL;
    GtkWidget *window;
    GtkBuilder *builder;
    GtkWidget **weight_images;
    som * the_map;
    // core dumps may be disallowed by parent of this process; change that
    struct rlimit core_limits;
    core_limits.rlim_cur = core_limits.rlim_max = RLIM_INFINITY;
    setrlimit(RLIMIT_CORE, &core_limits);


#ifdef ENABLE_NLS
	bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
	bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
	textdomain (GETTEXT_PACKAGE);
#endif

    //--- Initialisations ---
    
    // Initialize the program state
    
    program_state.show_weight_images = 0;
    program_state.number_of_rows_in_grid_of_weight_images = 0;
    program_state.number_of_columns_in_grid_of_weight_images = 0;
    
    the_map = create_som();
	gtk_init (&argc, &argv);
    
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "dialog3.xml", &errors);
    graph_window = create_chart_plotter(builder);
    graph_window->set_labels(graph_window, "epoche", "image count", "batch size", "quadratic error", "learning rate", "average error pro class");
	window = create_window (builder, &weight_images, the_map);
    gtk_widget_set_size_request (window, 700, 500);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER_ALWAYS);
    show_splash_screen("/home/pi/projects/filter_test_002/image/ic_launcher.jpg",2000, 300, 300);
	gtk_widget_show_all (window);
    
    gtk_main ();
	return 0;
}
