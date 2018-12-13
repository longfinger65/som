/*
 * som.h
 *
 * Created    : 02.01.2018 15:36:22
 * Author     : Ralf P.
 * Description: som is a class that describes a simple CNN. It consists of a convolutional
 *              part and a fully connectet hidden layer part.
 * 
 * Conventions: Used iterator descriptors in iterations:
 *                  - l = used to iterate in layers
 *                  - m = used to iterate through the maps in a layer
 *                  - i = used to iterate through the rows in a map (referred to as "height")
 *                  - j = used to iterate through the columns in a map (referred to as "width")
 *
 */

#include <glib/gi18n.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <string.h>
#include "/home/pi/projects/som/read_mnist.h"
#include "/home/pi/projects/som/otmath.h"
#include <math.h>
#include <float.h>
#include <signal.h>

extern int show_modal_info_dialog(char *caption, char * info_text, gint width, gint height, GdkWindow *parent_window);

#ifndef LOAD_ONN_FILE 
#define LOAD_ONN_FILE                                               0
#endif
#ifndef SAVE_ONN_FILE
#define	SAVE_ONN_FILE				                                1
#endif

// #define DEBUG

#ifndef SOM_H_
#define SOM_H_


#define WIDTH_OF_INPUT_MAP                                           0
#define	HEIGHTS_OF_INPUT_MAP				                         1
#define	WIDTH_OF_CLUSTER_MAP				                         2

typedef struct som_topology{

	int width_of_input_map;                                             // The width of the map that will be classified
	int height_of_input_map;                                            // The height of the map that will be classified
	int width_of_cluster_map;                                           // More than one if kind_of_classification = 0

} som_topology;

typedef struct som_training_parameter{

    int number_of_epochs;
	double neighborhood_size_r;                                               // Number of training rounds
    double end_neighborhood_size_r;
	int number_of_training_maps;
	int number_of_test_maps;
	char *path_to_training_maps;                                      // The full path to the maps to train (incl. the file name)
	char *path_to_test_maps;                                          // The full path to the maps to train (incl. the file name)
	double learning_rate;                                               // 0 = max pooling, 1 = average pooling
    double end_learning_rate;

} som_training_parameter;

typedef struct indexed_value{
    
    double value;
    int i;
    int j;
    
} indexed_value;


//--- Begin class som ---

    typedef struct som som;

    struct som{

        //--- Net topology ---

        som_topology map_topology;
        som_topology old_map_topology;

		double **input_map;
        /* The first layer in the network consisting of a number of maps according to the input channels*/
        
        double **cluster;
        /* The neuron lyers in the fully connected part of the net (not including the output layer)*/
        
        double ****weights;
        /* Weights connecting the general input layer with the first hidden layer */
                
        //--- Parameter for learning ---
        
        som_training_parameter map_training_parameter;

        int number_of_actual_image;
        int winning_node[2];

        //--- Other setting parameters ---

        int som_state;                 // Bit 0 = net topology has changed, bit 1 = memory is allocated, bit 2 = memory has to be allocated or reallocated (if bit 1 is set), bit 3 = training parameter are changed
        mnist_data * mn_dat;
        int ongoing_result_update; // E.g. to create a graph with ongoing updated values
        int number_of_correct_predictions;
        int state_of_training;
        int weights_show_interval;
        double weights_image_scaling_factor;
        
        //--- Getters and setters ---

        int (*set_width_of_input_map)(som* const me, int);
        int (*get_width_of_input_map)(som* const me);
        int (*set_height_of_input_map)(som* const me, int);
        int (*get_height_of_input_map)(som* const me);
        int (*set_width_of_cluster_map)(som* const me, int);
        int (*get_width_of_cluster_map)(som* const me);
        int (*set_old_topology_values)(som* const me);

        int (*set_number_of_epochs)(som* const me, int);
        int (*get_number_of_epochs)(som* const me);
        int (*set_neighborhood_size_r)(som* const me, double);
        double (*get_neighborhood_size_r)(som* const me);
        int (*set_number_of_training_maps)(som* const me, int);
        int (*get_number_of_training_maps)(som* const me);
        int (*set_number_of_test_maps)(som* const me, int);
        int (*get_number_of_test_maps)(som* const me);
        int (*set_path_to_training_maps)(som* const me, char*);
        char* (*get_path_to_training_maps)(som* const me);
        int (*set_path_to_test_maps)(som* const me, char*);
        char* (*get_path_to_test_maps)(som* const me);
        int (*set_learning_rate)(som* const me, double);
        double (*get_learning_rate)(som* const me);

        int (*get_pointer_to_input_map)(som* const me, double **);

        //--- Methodes ---

        int (*update_som_parameters)(som* const me, som_topology, som_training_parameter);
        int (*setup_som)(som* const me, som_topology, som_training_parameter);
        int (*free_allocated_memory)(som* const me);
        int (*check_if_som_topology_is_valid)(som* const me, som_topology, som_training_parameter);
        int (*train_som)(som* const me, int (*update_pixmap)(som *, int), void*);
        int (*cluster_a_data_map)(som* const me, void**, int, int, int);
        int (*fill_weights_randomly)(som* const me);
        int (*reverse_int)(som* const me, int);
        void (*read_mnist)(som* const me, char *);
        int (*find_the_winning_node)(som* const me);
        int (*update_weights)(som* const me, double, double);
        int (*serialize_the_som)(som* const me, FILE *, int);
	};

	/* constructors and destructors */

	som * create_som(void);
	void init_som (som* const me,
                        int (*function_set_width_of_input_map)(som* const me, int),
                        int (*function_get_width_of_input_map)(som* const me),
                        int (*function_set_height_of_input_map)(som* const me, int),
                        int (*function_get_height_of_input_map)(som* const me),
                        int (*function_set_width_of_cluster_map)(som* const me, int),
                        int (*function_get_width_of_cluster_map)(som* const me),
                        int (*function_set_old_topology_values)(som* const me),
                        int (*function_set_number_of_epochs)(som* const me, int),
                        int (*function_get_number_of_epochs)(som* const me),
                        int (*function_set_neighborhood_size_r)(som* const me, double),
                        double (*function_get_neighborhood_size_r)(som* const me),
                        int (*function_set_number_of_training_maps)(som* const me, int),
                        int (*function_get_number_of_training_maps)(som* const me),
                        int (*function_set_number_of_test_maps)(som* const me, int),
                        int (*function_get_number_of_test_maps)(som* const me),
                        int (*function_set_path_to_training_maps)(som* const me, char*),
                        char* (*function_get_path_to_training_maps)(som* const me),
                        int (*function_set_path_to_test_maps)(som* const me, char*),
                        char* (*function_get_path_to_test_maps)(som* const me),
                        int (*function_set_learning_rate)(som* const me, double),
                        double (*function_get_learning_rate)(som* const me),
                        int (*function_get_pointer_to_input_map)(som* const me, double**),
                        int (*function_update_som_parameters)(som* const me, som_topology, som_training_parameter),
                        int (*function_setup_som)(som* const me, som_topology, som_training_parameter),
                        int (*function_free_allocated_memory)(som* const me),
                        int (*function_check_if_som_topology_is_valid)(som* const me, som_topology, som_training_parameter),
                        int (*function_train_som)(som* const me, int (*update_pixmap)(som *, int), void*),
                        int (*function_cluster_a_data_map)(som* const me, void**, int, int, int),
                        int (*function_fill_weights_randomly)(som* const me),
                        int (*function_reverse_int)(som* const me, int),
                        void (*function_read_mnist)(som* const me, char *),
                        int (*function_find_the_winning_node)(som* const me),
                        int (*function_update_weights)(som* const me, double, double),
                        int (*function_serialize_the_som)(som* const me, FILE *, int));
    void destroy_som (som* const me);
    void cleanup_som(som* const me);

    //--- Getter and setter ---

    int set_width_of_input_map(som* const me, int width_of_input_map);
    int get_width_of_input_map(som* const me);
    int set_height_of_input_map(som* const me, int height_of_input_map);
    int get_height_of_input_map(som* const me);
    int set_width_of_cluster_map(som* const me, int width_of_cluster_map);
    int get_width_of_cluster_map(som* const me);
    int set_old_topology_values(som* const me);

    int set_number_of_epochs(som* const me, int number_of_epochs);
    int get_number_of_epochs(som* const me);
    int set_neighborhood_size_r(som* const me, double neighborhood_size_r);
    double get_neighborhood_size_r(som* const me);
    int set_number_of_training_maps(som* const me, int number_of_training_maps);
    int get_number_of_training_maps(som* const me);
    int set_number_of_test_maps(som* const me, int number_of_test_maps);
    int get_number_of_test_maps(som* const me);
    int set_path_to_training_maps(som* const me, char* path_to_training_maps);
    char* get_path_to_training_maps(som* const me);
    int set_path_to_test_maps(som* const me, char* path_to_test_maps);
    char* get_path_to_test_maps(som* const me);
    int set_learning_rate(som* const me, double learning_rate);
    double get_learning_rate(som* const me);

    int get_pointer_to_input_map(som* const me, double **input_map);

	//--- Methodes ---

    int update_som_parameters(som* const me, som_topology map_topology, som_training_parameter map_training_parameter);
    int setup_som(som* const me, som_topology map_parameter, som_training_parameter map_training_parameter);
    int free_allocated_memory(som* const me);
    int check_if_som_topology_is_valid(som* const me, som_topology map_topology, som_training_parameter map_training_parameter);
	int train_som(som* const me, int (*update_pixmap)(som *, int), void* chart_plot);
    int cluster_a_data_map(som* const me, void **map, int map_height, int map_width, int data_type);
    int fill_weights_randomly(som* const me);
    int reverse_int(som* const me, int);
    void read_mnist(som* const me, char * full_path);
    int find_the_winning_node(som* const me);
    int update_weights(som* const me, double learning_rate, double neighborhood_factor);
    int serialize_the_som(som* const me, FILE *file, int open_option);


//--- End class som ---

#endif /* SOM_H_ */
