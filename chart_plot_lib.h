/*
 * command.h
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
#include <math.h>
#include "/home/pi/projects/filter_test_002/vlist.h"

#ifndef CHART_PLOTTER_H_
#define CHART_PLOTTER_H_


#define NOT_CONNECTED                                               0
#define	DOTS_EVENLY_SPACED				                            1
#define DOTS_UNEVENLY_SPACED                                        2
#define LINE_LINEAR_INTERPOLATED                                    3
#define LINE_TANGEND                                                4

typedef struct chart_options{

	double x_min;                                       // E.g. the number of color layers (the number for RGB is 3)
	double x_max;                                             // The width of the map that will be classified
	double y_min;                                            // The height of the map that will be classified
	double y_max;                                // This value includes the first and the other convolutional layers
	double z_min;
	double z_max;
    int view_port_width;
    int view_port_height;
    double zoomfactor;
	int background_color[3];
    int number_of_graphs;
    int number_of_axes;                             // Min. = 2 (x and y), max. = 3 (x, y and z)
    char* label_x;
    char* label_y;
    char* label_z;
    int chart_plotter_is_visible;                   // Not visible = 0, visible = 1
    

} chart_options;

typedef struct graph{

	double *points[3];                                       // E.g. the number of color layers (the number for RGB is 3)
    int point_count;
	int linestyle;                                             // The width of the map that will be classified
	int color[3];                                            // The height of the map that will be classified 
    char *graph_name;   
    int is_visible;
    
} graph;

typedef struct coordinate_system{

	double **points_to_connect;                                       // E.g. the number of color layers (the number for RGB is 3)
    int point_count;
	int linestyle;                                             // The width of the map that will be classified
	int color[3];                                            // The color of the coordinate system 
    int is_visible;
	double x_min;                                       // E.g. the number of color layers (the number for RGB is 3)
	double x_max;                                             // The width of the map that will be classified
	double y_min;                                            // The height of the map that will be classified
	double y_max;                                // This value includes the first and the other convolutional layers
	double z_min;
	double z_max;
    int number_of_axes;                             // Min. = 2 (x and y), max. = 3 (x, y and z)

} coordinate_system;


//--- Begin class chart_plotter ---

    typedef struct chart_plotter chart_plotter;

    struct chart_plotter{

        //--- Chart options ---

        chart_options the_options;
        graph * graphs;
        coordinate_system coordinates;
        GtkBuilder *builder;       // The weights of the filter aka. filter kernel
        GtkWidget * main_frame;
        GError *errors;
        GtkWidget *area;
        vlist *value_list;

        //--- Getters and setters ---

        void (*set_chart_options)(chart_plotter* const me, void *, char *);
        void* (*get_chart_options)(chart_plotter* const me, char *);

        //--- Methodes ---

        void (*update_plotter_to_actual_options)(chart_plotter* const me, chart_options);
        int (*plot)(chart_plotter* const me);
        int (*add_point_to_graph)(void* const me, double, int, int, int, double, double);
        gboolean (*draw_callback)(GtkWidget *, cairo_t *, gpointer);
        int (*create_coordinate_system)(chart_plotter* const me, int, double, double, double, double, double, double);
        int (*set_labels)(chart_plotter* const me, char *, char *, char *, char *, char *, char *);
        int (*serialize_chart_plotter)(chart_plotter* const me, FILE *, int);
	};

	/* constructors and destructors */

	chart_plotter * create_chart_plotter(GtkBuilder* builder);
    void init_chart_plotter (chart_plotter* const me,
                        void (*function_set_chart_options)(chart_plotter* const me, void *, char *),
                        void* (*function_get_chart_options)(chart_plotter* const me, char *),
                        void (*function_plotter_to_actual_options)(chart_plotter* const me, chart_options),
                        int (*function_plot)(chart_plotter* const me),
                        int (*function_add_point_to_graph)(void* const me, double, int, int, int, double, double),
                        gboolean (*function_draw_callback)(GtkWidget *, cairo_t *, gpointer),
                        int (*function_create_coordinate_system)(chart_plotter* const me, int, double, double, double, double, double, double),
                        int (*function_set_labels)(chart_plotter* const me, char *, char *, char *, char *, char *, char *),
                        int (*function_serialize_chart_plotter)(chart_plotter* const me, FILE *, int),
                        GtkBuilder* builder);
    void destroy_chart_plotter (chart_plotter* const me);
    void cleanup_chart_plotter(chart_plotter* const me);

    //--- Getter and setter ---

    void set_chart_options(chart_plotter* const me, void * option, char * option_name);
    void* get_chart_options(chart_plotter* const me, char * option_name);

	//--- Methodes ---

    void update_plotter_to_actual_options(chart_plotter* const me, chart_options options);
    int plot(chart_plotter* const me);
    int add_point_to_graph(void* const me, double y_value, int epoches, int number_of_image, int batch_size, double learning_rate, double average_error_pro_class);
    gboolean draw_callback (GtkWidget *widget, cairo_t *cr, gpointer data);
    int create_coordinate_system(chart_plotter* const me, int number_of_axes, double x_min, double x_max, double y_min, double y_max, double z_min, double z_max);
    int set_labels(chart_plotter* const me, char *label_1, char *label_2, char *label_3, char *label_4, char *label_5, char *label_6);
    int serialize_chart_plotter(chart_plotter* const me, FILE *file, int open_option);


#endif //--- CHART_PLOTTER_H_ ---
