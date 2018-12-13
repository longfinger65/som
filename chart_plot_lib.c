#include "/home/pi/projects/filter_test_002/chart_plot_lib.h"


/* constructors and destructors */

void init_chart_plotter (chart_plotter* const me,
                        void (*function_set_chart_options)(chart_plotter* const me, void *, char *),
                        void* (*function_get_chart_options)(chart_plotter* const me, char *),
                        void (*function_update_plotter_to_actual_options)(chart_plotter* const me, chart_options),
                        int (*function_plot)(chart_plotter* const me),
                        int (*function_add_point_to_graph)(void* const me, double, int, int, int, double, double),
                        gboolean (*function_draw_callback)(GtkWidget *, cairo_t *, gpointer),
                        int (*function_create_coordinate_system)(chart_plotter* const me, int, double, double, double, double, double, double),
                        int (*function_set_labels)(chart_plotter* const me, char *, char *, char *, char *, char *, char *),
                        int (*function_serialize_chart_plotter)(chart_plotter* const me, FILE *, int),
                        GtkBuilder* builder){

    /************************************************************************************************************************
    *
    * Function name: init_neural_net
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

    //--- Initial settings ---
    
    //--- Setting the methodes
    
    me->set_chart_options = function_set_chart_options;
    me->get_chart_options = function_get_chart_options;
    me->update_plotter_to_actual_options = function_update_plotter_to_actual_options;
    me->plot = function_plot;
    me->add_point_to_graph = function_add_point_to_graph;
    me->draw_callback = function_draw_callback;
    me->create_coordinate_system = function_create_coordinate_system;
    me->set_labels = function_set_labels;
    me->serialize_chart_plotter = function_serialize_chart_plotter;
    
    //--- Setting the member variables
    
	me->the_options.x_min = 0;                                       // E.g. the number of color layers (the number for RGB is 3)
	me->the_options.x_max = 100;                                             // The width of the map that will be classified
	me->the_options.y_min = 0;                                           // The height of the map that will be classified
	me->the_options.y_max = 100;                                // This value includes the first and the other convolutional layers
	me->the_options.z_min = 0; 
	me->the_options.z_max = 100; 
    me->the_options.view_port_width = 120;
    me->the_options.view_port_height = 120;
    me->the_options.zoomfactor = 1;
	me->the_options.background_color[0] = 255;
	me->the_options.background_color[1] = 255;
	me->the_options.background_color[2] = 255;
    me->the_options.number_of_graphs = 1;
    me->the_options.number_of_axes = 2;                             // Min. = 2 (x and y), max. = 3 (x, y and z)
    me->the_options.label_x = "x";
    me->the_options.label_y = "y";
    me->the_options.label_z = "z";
    me->the_options.chart_plotter_is_visible = 0;
    
    // Set 1 graph at creation time
    
    me->graphs = calloc(1, sizeof *me->graphs);
    me->graphs->color[0] = 255;
    me->graphs->color[1] = 0;
    me->graphs->color[2] = 0;
    me->graphs->graph_name = "first_graph";
    me->graphs->is_visible = 1;
    me->graphs->linestyle = NOT_CONNECTED;
    me->graphs->points[3] = calloc(1, sizeof **me->graphs->points);
    me->graphs->point_count = 0;
    
    // Set the coordinate system values
    
    me->coordinates.points_to_connect = NULL;                           // E.g. the number of color layers (the number for RGB is 3)
    me->coordinates.point_count = 0;
	me->coordinates.linestyle = LINE_LINEAR_INTERPOLATED;                  // The width of the map that will be classified
	me->coordinates.color[0] = 0;                                          // The height of the map that will be classified 
	me->coordinates.color[1] = 0;                                          // The height of the map that will be classified 
	me->coordinates.color[2] = 0;                                          // The height of the map that will be classified 
	me->coordinates.x_min = 0;                                      // E.g. the number of color layers (the number for RGB is 3)
	me->coordinates.x_max = 390;                                            // The width of the map that will be classified
	me->coordinates.y_min = 0;                                           // The height of the map that will be classified
	me->coordinates.y_max = 390;                               // This value includes the first and the other convolutional layers
	me->coordinates.z_min = 0;
	me->coordinates.z_max = 390;
    me->coordinates.number_of_axes = 2;                             // Min. = 2 (x and y), max. = 3 (x, y and z)

    me->create_coordinate_system(me, 2, 0, 390, 0, 390, 0, 0);

    
    me->errors = NULL;
    me->builder = builder;
    gtk_builder_add_from_file (me->builder, "charts.xml", NULL);
    me->main_frame = GTK_WIDGET(gtk_builder_get_object (me->builder, "chart-plotter-1"));
    me->area = GTK_WIDGET(gtk_builder_get_object (me->builder, "drawing-area"));
    gtk_widget_set_visible(me->main_frame, FALSE);
    g_signal_connect (G_OBJECT (me->area), "draw", G_CALLBACK (me->draw_callback), me);
    me->value_list = create_vlist();

}

/* Constructor and destructor */

chart_plotter * create_chart_plotter(GtkBuilder* builder){
	chart_plotter * me = (chart_plotter *)malloc(sizeof(chart_plotter));
	if(me!=NULL){
		init_chart_plotter(me,
                        set_chart_options,
                        get_chart_options,
                        update_plotter_to_actual_options,
                        plot,
                        add_point_to_graph,
                        draw_callback,
                        create_coordinate_system,
                        set_labels,
                        serialize_chart_plotter, 
                        builder);
		printf("Chart plotter was successfully created.\n");
	}else{
		printf("Not enough memory to create the chart plotter object.\n");
	}
	return me;
}

void destroy_chart_plotter(chart_plotter* const me){
	if(me!=NULL){
		cleanup_chart_plotter(me);
		free(me);
	}
}

void cleanup_chart_plotter(chart_plotter* const me){
    
}

//--- Getter - Setter ---

void set_chart_options(chart_plotter* const me, void * option, char * option_name){
    
    if(strcmp(option_name, "is_visible")==0){
        int* is_visible = (int*)option;
        if(* is_visible==1){
            me->the_options.chart_plotter_is_visible = 1;
            gtk_widget_set_visible(me->main_frame, TRUE);
            gtk_widget_set_size_request (me->area, 400, 400);
            //g_signal_connect (G_OBJECT (me->area), "draw", G_CALLBACK (me->draw_callback), me);
            printf("visible");
        }else{
            me->the_options.chart_plotter_is_visible = 0;
            gtk_widget_set_visible(me->main_frame, FALSE);
        } 
        
    }
}

void* get_chart_options(chart_plotter* const me, char * option_name){
    
    if(strcmp(option_name, "background_color")==0){
        return me->the_options.background_color;
    }else if(strcmp(option_name, "background_color")==0){
        
    }
    
    return NULL;
}


//--- Methodes ---

void update_plotter_to_actual_options(chart_plotter* const me, chart_options options){
    
}

int plot(chart_plotter* const me){
    
}

int add_point_to_graph(void* const me, double y_value, int epoches, int number_of_image, int batch_size, double learning_rate, double average_error_pro_class){
    
    
#ifdef DEBUG
    printf("\nNow I am in add_point_to_graph.\n");
#endif
    
    //--- Variables ---
    
    GObject *chart_plotter_feature;
    char value[30];
    char e[20];
    char noi[20];
    char bs[10];    //Batch size
    char lr[10];    //Learning rate
    char aepc[30];  //Average error pro class
    
    //--- Initial settings ---
    
    snprintf(value, 20, "%f", y_value);
    snprintf(e, 20, "%i", epoches);
    snprintf(noi, 20, "%i", number_of_image);
    snprintf(bs, 10, "%i", batch_size);
    snprintf(lr, 10, "%f", learning_rate);
    snprintf(aepc, 30, "%f", average_error_pro_class);
    chart_plotter* const mee = (chart_plotter*) me;
    
    //---
    
    if(mee->value_list->get_node_count(mee->value_list) < 440){
        mee->value_list->add_last_node(mee->value_list);
        mee->value_list->set_node_value(mee->value_list, mee->value_list->get_node_count(mee->value_list)-1, y_value);
    }else{
        mee->value_list->rotate_and_add_last(mee->value_list, y_value);
    }
    
    chart_plotter_feature = gtk_builder_get_object (mee->builder, "label-1-1");
    gtk_label_set_text ((GtkLabel*)chart_plotter_feature, e);
    chart_plotter_feature = gtk_builder_get_object (mee->builder, "label-2-1");
    gtk_label_set_text ((GtkLabel*)chart_plotter_feature, noi);
    chart_plotter_feature = gtk_builder_get_object (mee->builder, "label-3-1");
    gtk_label_set_text ((GtkLabel*)chart_plotter_feature, bs);
    chart_plotter_feature = gtk_builder_get_object (mee->builder, "label-5-1");
    gtk_label_set_text ((GtkLabel*)chart_plotter_feature, lr);

    chart_plotter_feature = gtk_builder_get_object (mee->builder, "label-4-1");
    gtk_label_set_text ((GtkLabel*)chart_plotter_feature, value);
    chart_plotter_feature = gtk_builder_get_object (mee->builder, "label-6-1");
    gtk_label_set_text ((GtkLabel*)chart_plotter_feature, aepc);

    gtk_widget_queue_draw_area (mee->area, 0, 0, 400, 400);

}

gboolean draw_callback (GtkWidget *widget, cairo_t *cr, gpointer data){

    /************************************************************************************************************************
    *
    * Function name:            - draw_callback
    * 
    * Function purpose:         - Setup/change the topology of the neural net
    * 
    * Input parameter:
    * 
    *   widget  [GtkWidget*]    -
    *   cr      [cairo_t*]      -
    *   data    [gpointer]      -
    * 
    * Return parameter:
    * 
    *   ret -
    *
    ************************************************************************************************************************/

    //--- Variables ---

    guint width, height;
    GdkRGBA color;
    GtkStyleContext *context;
    chart_plotter * me;
    graph* my_graph;
    coordinate_system* coordinates;
    double normalizing_factor;
    double max_value;
    double moving_average[400];
    
    //--- Initial settings ---

    me = (chart_plotter*)data;
    my_graph = me->graphs;
    coordinates = &me->coordinates;
    context = gtk_widget_get_style_context (widget);
    width = gtk_widget_get_allocated_width (widget);
    height = gtk_widget_get_allocated_height (widget);
    gtk_render_background (context, cr, 0, 0, width, height);
    max_value = 0;
    
    // ---

    gtk_style_context_get_color (context, gtk_style_context_get_state (context), &color);

    // Draw the coordinates
    cairo_set_source_rgba (cr, me->coordinates.color[0], me->coordinates.color[1], me->coordinates.color[2],1.0);//&color);

    cairo_move_to(cr, me->coordinates.points_to_connect[0][0] + 10, height-me->coordinates.points_to_connect[0][1] - 10);
    for(int i=1; i<me->coordinates.point_count; i++){
        cairo_line_to (cr, me->coordinates.points_to_connect[i][0] + 10, height-me->coordinates.points_to_connect[i][1] - 10);
    }
    cairo_stroke(cr);
    
    // Calculate the moving average values
    if(me->value_list->get_node_count(me->value_list) >= 340){
        for(int i=0; i < 390; i++){
            moving_average[i] = 0;
            for(int j=0; j < 50; j++){
                moving_average[i] += me->value_list->get_node_value(me->value_list, i+j);
            }
            moving_average[i] /= 50;
        }
    
        // Normalize the values
        for(int x=0; x < 390; x++){
            if(moving_average[x] > max_value){
                max_value = moving_average[x];
            }
        }
        normalizing_factor = 390 / max_value;
    
        for(int x=0; x < 390; x++){
            cairo_line_to (cr, x+10, height-(moving_average[x] * normalizing_factor)-10);
        }
    }
    cairo_set_source_rgba (cr, my_graph[0].color[0], my_graph[0].color[1], my_graph[0].color[2],1.0);//&color);
    printf("Color is %f",my_graph[0].color[0]);

    //cairo_fill (cr);
    //cairo_paint(cr);
    cairo_stroke(cr);
    return FALSE;
}

int create_coordinate_system(chart_plotter* const me, int number_of_axes, double x_min, double x_max, double y_min, double y_max, double z_min, double z_max){

    /****************************************************************
    *
    * Function name: create_coordinate_system
    * Function purpose: Setup/change the topology of the neural net
    * Input parameter:
    *               me -
    *               v -
    * Return parameter:
    *               ret -
    *
    *****************************************************************/

    //--- Variables ---

    int return_value;
    int number_of_points;
    
    //--- Initial settings ---
    
    return_value = 0;
    number_of_points = 3;
    
    //---
    
    if(me->coordinates.points_to_connect==NULL){
        free(me->coordinates.points_to_connect);
    }
    
    me->coordinates.points_to_connect = calloc(number_of_points, sizeof *me->coordinates.points_to_connect);
    for (int i=0; i<4; i++){
        me->coordinates.points_to_connect[i] = calloc(4, sizeof **me->coordinates.points_to_connect);
    }
    me->coordinates.point_count = number_of_points;
    
    me->coordinates.points_to_connect[0][0] = 0;
    me->coordinates.points_to_connect[0][1] = y_max;
    me->coordinates.points_to_connect[0][2] = 0;
    me->coordinates.points_to_connect[0][3] = 0;
    me->coordinates.points_to_connect[1][0] = 0;
    me->coordinates.points_to_connect[1][1] = 0;
    me->coordinates.points_to_connect[1][2] = 0;
    me->coordinates.points_to_connect[1][3] = 1;
    me->coordinates.points_to_connect[2][0] = x_max;
    me->coordinates.points_to_connect[2][1] = 0;
    me->coordinates.points_to_connect[2][2] = 0;
    me->coordinates.points_to_connect[2][3] = 1;
    
    return return_value;

}

int set_labels(chart_plotter* const me, char *label_1, char *label_2, char *label_3, char *label_4, char *label_5, char *label_6){

    /************************************************************************************************************************
    *
    * Function name:                        - train_neural_net
    * 
    * Function purpose:                     - Fills the weights (incl. the filter kernels)
    * 
    * Input parameter:
    * 
    *   me              [neural_net* const] -
    *   update_pixmap   [int]               -
    * 
    * Return parameter:
    * 
    *   return_value    [int]               - int, if 1, the picture is too large
    *
    ************************************************************************************************************************/
    
    
#ifdef DEBUG
    printf("\nNow I am in set_labels\n");
#endif
    
    //--- Variables ---
    
    int return_value;
    GObject *chart_plotter_label;
    
    //--- Initial settings ---
    
    return_value = 0;
    
    //---
    
    chart_plotter_label = gtk_builder_get_object (me->builder, "label-1");
    gtk_label_set_text ((GtkLabel*)chart_plotter_label, label_1);
    chart_plotter_label = gtk_builder_get_object (me->builder, "label-2");
    gtk_label_set_text ((GtkLabel*)chart_plotter_label, label_2);
    chart_plotter_label = gtk_builder_get_object (me->builder, "label-3");
    gtk_label_set_text ((GtkLabel*)chart_plotter_label, label_3);
    chart_plotter_label = gtk_builder_get_object (me->builder, "label-4");
    gtk_label_set_text ((GtkLabel*)chart_plotter_label, label_4);
    chart_plotter_label = gtk_builder_get_object (me->builder, "label-5");
    gtk_label_set_text ((GtkLabel*)chart_plotter_label, label_5);
    chart_plotter_label = gtk_builder_get_object (me->builder, "label-6");
    gtk_label_set_text ((GtkLabel*)chart_plotter_label, label_6);

}



int serialize_chart_plotter(chart_plotter* const me, FILE *file, int open_option){
    
}
