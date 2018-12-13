#include "/home/pi/projects/som/som.h"


/* constructors and destructors */

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
                        int (*function_get_pointer_to_input_map)(som* const me, double **),
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
                        int (*function_serialize_the_som)(som* const me, FILE *, int)){

    /***********************************************************************************************************************
    *
    * Function name:                - init_som
    * 
    * Function purpose:
    *                               - Setup/change the topology of the neural net
    * Input parameter:
    * 
    *   me  [som* const]     - A pointer to the actual object.
    *            
    * Return parameter:
    * 
    *   return_value [int]
    *
    ***********************************************************************************************************************/

    //--- Initial settings ---
    
    //--- Setting the methodes
    
    me->set_width_of_input_map = function_set_width_of_input_map;
    me->get_width_of_input_map = function_get_width_of_input_map;
    me->set_height_of_input_map = function_set_height_of_input_map;
    me->get_height_of_input_map = function_get_height_of_input_map;
    me->set_width_of_cluster_map = function_set_width_of_cluster_map;
    me->get_width_of_cluster_map = function_get_width_of_cluster_map;
    me->set_old_topology_values = function_set_old_topology_values;
    me->set_number_of_epochs = function_set_number_of_epochs;
    me->get_number_of_epochs = function_get_number_of_epochs;
    me->set_neighborhood_size_r = function_set_neighborhood_size_r;
    me->get_neighborhood_size_r = function_get_neighborhood_size_r;
    me->set_number_of_training_maps = function_set_number_of_training_maps;
    me->get_number_of_training_maps = function_get_number_of_training_maps;
    me->set_number_of_test_maps = function_set_number_of_test_maps;
    me->get_number_of_test_maps = function_get_number_of_test_maps;
    me->set_path_to_training_maps = function_set_path_to_training_maps;
    me->get_path_to_training_maps = function_get_path_to_training_maps;
    me->set_path_to_test_maps = function_set_path_to_test_maps;
    me->get_path_to_test_maps = function_get_path_to_test_maps;
    me->set_learning_rate = function_set_learning_rate;
    me->get_learning_rate = function_get_learning_rate;
    me->get_pointer_to_input_map = function_get_pointer_to_input_map;
    me->update_som_parameters = function_update_som_parameters;
    me->setup_som = function_setup_som;
    me->free_allocated_memory = function_free_allocated_memory;
    me->check_if_som_topology_is_valid = function_check_if_som_topology_is_valid;
    me->train_som = function_train_som;
    me->cluster_a_data_map = function_cluster_a_data_map;
    me->fill_weights_randomly = function_fill_weights_randomly;
    me->reverse_int =  function_reverse_int;
    me->read_mnist = function_read_mnist;
    me->find_the_winning_node = function_find_the_winning_node;
    me->update_weights = function_update_weights;
    me->serialize_the_som = function_serialize_the_som;
    
    //--- Setting the member variables
    
    me->weights_show_interval = 100;
    me->weights_image_scaling_factor = 1;
    
	me->map_topology.width_of_input_map = 28;
	me->map_topology.height_of_input_map = 28;
	me->map_topology.width_of_cluster_map = 4;
    
 	me->old_map_topology.width_of_input_map = 28;
	me->old_map_topology.height_of_input_map = 28;
	me->old_map_topology.width_of_cluster_map = 4;
   
    me->input_map = NULL;
    me->cluster = NULL;
    me->weights = NULL;
    
	me->map_training_parameter.number_of_epochs = 30;
	me->map_training_parameter.neighborhood_size_r = 0.4;
    me->map_training_parameter.end_neighborhood_size_r = 0.3;
	me->map_training_parameter.number_of_training_maps = 60000;
	me->map_training_parameter.number_of_test_maps = 10000;
	//strcpy(me->net_training_parameter.path_to_training_images, "/home/pi/projects/data/mnist/train-images-idx3-ubyte");
	//strcpy(me->net_training_parameter.path_to_test_images, "/home/pi/projects/data/mnist/train-labels-idx1-ubyte");
	me->map_training_parameter.learning_rate = 0.3;
    me->map_training_parameter.end_learning_rate = 0.1;
    
    me->som_state = 0b0000000000000100; // No net topology is available, no memory is allocated ...

}

/* Constructor and destructor */

som * create_som(void){
	som * me = (som *)malloc(sizeof(som));
	if(me!=NULL){
		init_som(me,
                        set_width_of_input_map,
                        get_width_of_input_map,
                        set_height_of_input_map,
                        get_height_of_input_map,
                        set_width_of_cluster_map,
                        get_width_of_cluster_map,
                        set_old_topology_values,
                        set_number_of_epochs,
                        get_number_of_epochs,
                        set_neighborhood_size_r,
                        get_neighborhood_size_r,
                        set_number_of_training_maps,
                        get_number_of_training_maps,
                        set_number_of_test_maps,
                        get_number_of_test_maps,
                        set_path_to_training_maps,
                        get_path_to_training_maps,
                        set_path_to_test_maps,
                        get_path_to_test_maps,
                        set_learning_rate,
                        get_learning_rate,
                        get_pointer_to_input_map,
                        update_som_parameters,
                        setup_som,
                        free_allocated_memory,
                        check_if_som_topology_is_valid,
                        train_som,
                        cluster_a_data_map,
                        fill_weights_randomly,
                        reverse_int,
                        read_mnist,
                        find_the_winning_node,
                        update_weights,
                        serialize_the_som);
		printf("SOM was successfully created.\n");
	}else{
		printf("Not enough memory to create the SOM object.\n");
	}
	return me;
}

void destroy_som(som* const me){
	if(me!=NULL){
		cleanup_som(me);
		free(me);
	}
}

void cleanup_som(som* const me){
    
}

//--- Getter - Setter ---

int set_width_of_input_map(som* const me, int width_of_input_map){

    /***********************************************************************************************************************
    *
    * Function name:                        - set_width_of_input_map
    * 
    * Function purpose:                     - Set and check the width of the input map.
    * 
    * Input parameter:
    * 
    *   me                  [som* const]    - A pointer to the actual som object
    *   width_of_input_map  [int]           - The value the width of the input map should be set to.
    * 
    * Return parameter:
    * 
    *   return_value        [int]           - 0 = ok
    *                                         1 = something went wrong
    *
    ***********************************************************************************************************************/

#ifdef DEBUG
    printf("\nInside set_width_of_input_map.\n");
#endif

    //--- Variables ---

	int return_value;

    //--- Initial settings ---

    return_value = 0;

    // ---
    
	me->map_topology.width_of_input_map = width_of_input_map;
    me->som_state |= (1<<0);  // Net topology change flag is set; reallocation / allocation of memory has to follow
    
    return return_value;

}

int get_width_of_input_map(som* const me){

    /***********************************************************************************************************************
    *
    * Function name:                    - get_width_of_input_map
    * 
    * Function purpose:                 - Returns the width of the input map.
    * 
    * Input parameter:
    * 
    *   me              [som* const]    - A pointer to the actual som object
    * 
    * Return parameter:
    * 
    *   return_value    [int]           - me->map_topology.width_of_input_map
    *
    ***********************************************************************************************************************/

#ifdef DEBUG
    printf("\nInside get_width_of_input_map.\n");
#endif

    //--- Variables ---

	int return_value;

    //--- Initial settings ---

    return_value = me->map_topology.width_of_input_map;

    // ---

	return return_value;
}

int set_height_of_input_map(som* const me, int height_of_input_map){

    /***********************************************************************************************************************
    *
    * Function name:                        - set_height_of_input_map
    * 
    * Function purpose:                     - Check and set the height of the input map.
    * 
    * Input parameter:
    * 
    *   me                  [som* const]    - A pointer to the actual som object
    *   height_of_input_map [int]           - The value the height of the input map should be set to.
    * 
    * Return parameter:
    * 
    *   return_value        [int]           - 0 = ok
    *                                         1 = something went wrong
    *
    ***********************************************************************************************************************/

#ifdef DEBUG
    printf("\nInside set_height_of_input_map.\n");
#endif

    //--- Variables ---

	int return_value;

    //--- Initial settings ---

    return_value = 0;

    // ---

	me->map_topology.height_of_input_map = height_of_input_map;
    me->som_state |= (1<<0);  // Net topology change flag is set; reallocation / allocation of memory has to follow
    
    return return_value;
}

int get_height_of_input_map(som* const me){
    
    /***********************************************************************************************************************
    *
    * Function name:                    - get_height_of_input_map
    * 
    * Function purpose:                 - Returns the height of the input map.
    * 
    * Input parameter:
    * 
    *   me              [som* const]    - A pointer to the actual som object
    * 
    * Return parameter:
    * 
    *   return_value    [int]           - me->map_topology.height_of_input_map
    *
    ***********************************************************************************************************************/
    
#ifdef DEBUG
    printf("\nInside get_height_of_input_map.\n");
#endif

    //--- Variables ---

	int return_value;

    //--- Initial settings ---

    return_value = me->map_topology.height_of_input_map;

    // ---

	return return_value;
}


int set_width_of_cluster_map(som* const me, int width_of_cluster_map){
    
    /***********************************************************************************************************************
    *
    * Function name:                            - set_width_of_cluster_map
    * 
    * Function purpose:                         - Check and set the width of the cluster map.
    * 
    * Input parameter:
    * 
    *   me                      [som* const]    - A pointer to the actual som object
    *   width_of_cluster_map    [int]           - The value the width of the cluster map should be set to.
    * 
    * Return parameter:
    * 
    *   return_value            [int]           - 0 = ok
    *                                             1 = something went wrong
    *
    ***********************************************************************************************************************/
    
#ifdef DEBUG
    printf("\nInside set_width_of_cluster_map.\n");
#endif

    //--- Variables ---

	int return_value;

    //--- Initial settings ---

    return_value = 0;

    // ---
    
	me->map_topology.width_of_cluster_map = width_of_cluster_map;
    me->som_state |= (1<<0);  // Net topology change flag is set; reallocation / allocation of memory has to follow
    
    return return_value;
}

int get_width_of_cluster_map(som* const me){
    
    /***********************************************************************************************************************
    *
    * Function name:                    - get_width_of_cluster_map
    * 
    * Function purpose:                 - Return the width of the cluster map.
    * 
    * Input parameter:
    * 
    *   me              [som* const]    - A pointer to the actual som object
    * 
    * Return parameter:
    * 
    *   return_value    [int]           - me->map_topology.width_of_cluster_map
    *
    ***********************************************************************************************************************/
    
#ifdef DEBUG
    printf("\nInside get_width_of_cluster_map.\n");
#endif

    //--- Variables ---

	int return_value;

    //--- Initial settings ---

    return_value = me->map_topology.width_of_cluster_map;

    // ---

	return return_value;
}


int set_old_topology_values(som* const me){
    
    /***********************************************************************************************************************
    *
    * Function name:                    - set_old_topology_values
    * 
    * Function purpose:                 - Sets the old topology values.
    * 
    * Input parameter:
    * 
    *   me              [som* const]    - A pointer to the actual som object
    * 
    * Return parameter:
    * 
    *   return_value    [int]           - 0 = ok
    *                                     1 = something went wrong
    *
    ***********************************************************************************************************************/
    
#ifdef DEBUG
    printf("\nInside set_old_topology_values.\n");
#endif

    //--- Variables ---

	int return_value;

    //--- Initial settings ---

    return_value = 0;

    // ---
    
    me->old_map_topology.width_of_input_map = me->map_topology.width_of_input_map;
	me->old_map_topology.height_of_input_map = me->map_topology.height_of_input_map;
	me->old_map_topology.width_of_cluster_map = me->map_topology.width_of_cluster_map;

    return return_value;
}

int set_number_of_epochs(som* const me, int number_of_epochs){
    
    /***********************************************************************************************************************
    *
    * Function name:                            - set_number_of_epochs
    * 
    * Function purpose:                         - Check and set the number of training maps.
    * 
    * Input parameter:
    * 
    *   me                      [som* const]    - A pointer to the actual som object
    *   number_of_epochs [int]           - The value the number of training maps should be set to.
    * 
    * Return parameter:
    * 
    *   return_value            [int]           - 0 = ok
    *                                             1 = something went wrong
    *
    ***********************************************************************************************************************/

#ifdef DEBUG
    printf("\nInside set_number_of_epochs.\n");
#endif

    //--- Variables ---

	int return_value;

    //--- Initial settings ---

    return_value = 0;

    // ---
    
	me->map_training_parameter.number_of_epochs = number_of_epochs;
    me->som_state |= (1<<3);  // Training parameter change flag is set; reallocation / allocation of memory has to follow
    
    return return_value;
}
    
int get_number_of_epochs(som* const me){
    
    /***********************************************************************************************************************
    *
    * Function name:                            - get_number_of_epochs
    * 
    * Function purpose:                         - Check and set the number of training maps.
    * 
    * Input parameter:
    * 
    *   me                      [som* const]    - A pointer to the actual som object
    *   number_of_training_maps [int]           - The value the number of training maps should be set to.
    * 
    * Return parameter:
    * 
    *   return_value            [int]           - me->map_training_parameter.number_of_epochs
    *
    ***********************************************************************************************************************/

#ifdef DEBUG
    printf("\nInside get_number_of_epochs.\n");
#endif

    //--- Variables ---

	int return_value;

    //--- Initial settings ---

    return_value = me->map_training_parameter.number_of_epochs;
    
    return return_value;
}
    
int set_neighborhood_size_r(som* const me, double neighborhood_size_r){
    
    /***********************************************************************************************************************
    *
    * Function name:                            - set_neighborhood_size_r
    * 
    * Function purpose:                         - Check and set the number of training maps.
    * 
    * Input parameter:
    * 
    *   me                      [som* const]    - A pointer to the actual som object
    *   number_of_training_maps [int]           - The value the number of training maps should be set to.
    * 
    * Return parameter:
    * 
    *   return_value            [int]           - 0 = ok
    *                                             1 = something went wrong
    *
    ***********************************************************************************************************************/

#ifdef DEBUG
    printf("\nInside set_neighborhood_size_r.\n");
#endif

    //--- Variables ---

	int return_value;

    //--- Initial settings ---

    return_value = 0;

    // ---
    
	me->map_training_parameter.neighborhood_size_r = neighborhood_size_r;
    me->som_state |= (1<<3);  // Training parameter change flag is set; reallocation / allocation of memory has to follow
    
    return return_value;
}
    
double get_neighborhood_size_r(som* const me){
    
    /***********************************************************************************************************************
    *
    * Function name:                            - get_neighborhood_size_r
    * 
    * Function purpose:                         - Check and set the number of training maps.
    * 
    * Input parameter:
    * 
    *   me                      [som* const]    - A pointer to the actual som object
    *   number_of_training_maps [int]           - The value the number of training maps should be set to.
    * 
    * Return parameter:
    * 
    *   return_value            [double]        - me->map_training_parameter.neighborhood_size_r
    *
    ***********************************************************************************************************************/

#ifdef DEBUG
    printf("\nInside get_neighborhood_size_r.\n");
#endif

    //--- Variables ---

	double return_value;

    //--- Initial settings ---

    return_value = me->map_training_parameter.neighborhood_size_r;
    
    return return_value;
}

int set_number_of_training_maps(som* const me, int number_of_training_maps){
    
    /***********************************************************************************************************************
    *
    * Function name:                            - set_number_of_training_maps
    * 
    * Function purpose:                         - Check and set the number of training maps.
    * 
    * Input parameter:
    * 
    *   me                      [som* const]    - A pointer to the actual som object
    *   number_of_training_maps [int]           - The value the number of training maps should be set to.
    * 
    * Return parameter:
    * 
    *   return_value            [int]           - 0 = ok
    *                                             1 = something went wrong
    *
    ***********************************************************************************************************************/

#ifdef DEBUG
    printf("\nInside set_number_of_training_maps.\n");
#endif

    //--- Variables ---

	int return_value;

    //--- Initial settings ---

    return_value = 0;

    // ---
    
	me->map_training_parameter.number_of_training_maps = number_of_training_maps;
    me->som_state |= (1<<3);  // Training parameter change flag is set; reallocation / allocation of memory has to follow
    
    return return_value;
}

int get_number_of_training_maps(som* const me){
    
    /***********************************************************************************************************************
    *
    * Function name:                    - get_number_of_training_maps
    * 
    * Function purpose:                 - Return the number of training maps.
    * 
    * Input parameter:
    * 
    *   me              [som* const]    - A pointer to the actual som object
    * 
    * Return parameter:
    * 
    *   return_value    [int]           - me->map_training_parameter.number_of_training_maps
    *
    ***********************************************************************************************************************/
    
#ifdef DEBUG
    printf("\nInside get_number_of_training_maps.\n");
#endif

    //--- Variables ---

	int return_value;

    //--- Initial settings ---

    return_value = me->map_training_parameter.number_of_training_maps;

	return return_value;
}

int set_number_of_test_maps(som* const me, int number_of_test_maps){
    
    /***********************************************************************************************************************
    *
    * Function name:                            - set_number_of_test_maps
    * 
    * Function purpose:                         - Check and set the number of test maps.
    * 
    * Input parameter:
    * 
    *   me                      [som* const]    - A pointer to the actual som object
    *   number_of_test_images   [int]           - The value the number of test maps should be se to.
    * 
    * Return parameter:
    * 
    *   return_value            [int]           - 0 = ok
    *                                             1 = something went wrong
    *
    ***********************************************************************************************************************/
    
#ifdef DEBUG
    printf("\nInside set_number_of_test_maps.\n");
#endif

    //--- Variables ---

	int return_value;

    //--- Initial settings ---

    return_value = 0;

    // ---
    
	me->map_training_parameter.number_of_test_maps = number_of_test_maps;
    me->som_state |= (1<<3);  // Training parameter change flag is set; reallocation / allocation of memory has to follow
    
    return return_value;
}

int get_number_of_test_maps(som* const me){
    
    /***********************************************************************************************************************
    *
    * Function name:                            - get_number_of_test_maps
    * 
    * Function purpose:                         - Returns the number of test maps.
    * 
    * Input parameter:
    * 
    *   me                      [som* const]    - A pointer to the actual som object
    * 
    * Return parameter:
    * 
    *   return_value            [int]           - me->map_training_parameter.number_of_test_maps
    *
    ***********************************************************************************************************************/
    
#ifdef DEBUG
    printf("\nInside get_number_of_test_maps.\n");
#endif

    //--- Variables ---

	int return_value;

    //--- Initial settings ---

    return_value = me->map_training_parameter.number_of_test_maps;

	return return_value;
}

int set_path_to_training_maps(som* const me, char* path_to_training_maps){
    
    /***********************************************************************************************************************
    *
    * Function name:                            - set_path_to_training_maps
    * 
    * Function purpose:                         - Check and set the path to the training maps.
    * 
    * Input parameter:
    * 
    *   me                      [som* const]    - A pointer to the actual som object
    *   path_to_training_maps   [char*]         - The path the path to the training maps should be se to.
    * 
    * Return parameter:
    * 
    *   return_value            [int]           - 0 = ok
    *                                             1 = something went wrong
    *
    ***********************************************************************************************************************/
    
#ifdef DEBUG
    printf("\nInside set_path_to_training_maps.\n");
#endif

    //--- Variables ---

	int return_value;

    //--- Initial settings ---

    return_value = 0;

    // ---
    
	me->map_training_parameter.path_to_training_maps = path_to_training_maps;
    me->som_state |= (1<<3);  // Training parameter change flag is set; reallocation / allocation of memory has to follow
    
    return return_value;
}

char* get_path_to_training_maps(som* const me){
    
    /***********************************************************************************************************************
    *
    * Function name:                    - get_path_to_training_maps
    * 
    * Function purpose:                 - Check and set the path to the training maps.
    * 
    * Input parameter:
    * 
    *   me              [som* const]    - A pointer to the actual som object.
    * 
    * Return parameter:
    * 
    *   return_value    [char*]         - me->map_training_parameter.path_to_training_maps
    *
    ***********************************************************************************************************************/
    
#ifdef DEBUG
    printf("\nInside get_path_to_training_maps.\n");
#endif

    //--- Variables ---

	char *return_value;
    
    //--- Initial settings ---
    
    return_value = me->map_training_parameter.path_to_training_maps;

	return return_value;
}

int set_path_to_test_maps(som* const me, char* path_to_test_maps){
    
    /***********************************************************************************************************************
    *
    * Function name:                        - set_path_to_test_maps
    * 
    * Function purpose:                     - Check and set the path to the test maps.
    * 
    * Input parameter:
    * 
    *   me                  [som* const]    - A pointer to the actual som object.
    *   path_to_test_maps   [char*]         - The path the path to test maps should be se to.
    * 
    * Return parameter:
    * 
    *   return_value        [int]           - 0 = ok
    *                                         1 = something went wrong
    *
    ***********************************************************************************************************************/
    
#ifdef DEBUG
    printf("\nInside set_path_to_test_maps.\n");
#endif

    //--- Variables ---

	int return_value;

    //--- Initial settings ---

    return_value = 0;

    // ---
    
	me->map_training_parameter.path_to_test_maps = path_to_test_maps;
    me->som_state |= (1<<3);  // Training parameter change flag is set; reallocation / allocation of memory has to follow
    
    return return_value;
}

char* get_path_to_test_maps(som* const me){
    
    /***********************************************************************************************************************
    *
    * Function name:                    - get_path_to_test_maps
    * 
    * Function purpose:                 - Check and set the learning rate.
    * 
    * Input parameter:
    * 
    *   me              [som* const]    - A pointer to the actual som object.
    *   learning_rate   [double]        - The value the learning rate should be set to.
    * 
    * Return parameter:
    * 
    *   ret_value       [int]           - me->map_training_parameter.path_to_test_maps
    *
    ***********************************************************************************************************************/
    
#ifdef DEBUG
    printf("\nInside get_path_to_test_maps.\n");
#endif

    //--- Variables ---

    char *return_value;

    //--- Initial settings ---
    
    return_value = me->map_training_parameter.path_to_test_maps;

	return return_value;
}

int set_learning_rate(som* const me, double learning_rate){
    
    /***********************************************************************************************************************
    *
    * Function name:                    - set_learning_rate
    * 
    * Function purpose:                 - Check and set the learning rate.
    * 
    * Input parameter:
    * 
    *   me              [som* const]    - A pointer to the actual som object.
    *   learning_rate   [double]        - The value the learning rate should be set to.
    * 
    * Return parameter:
    * 
    *   ret_value       [int]           - 0 = ok
    *                                     1 = something went wrong
    *
    ***********************************************************************************************************************/
    
#ifdef DEBUG
    printf("\nInside set_learning_rate.\n");
#endif

    //--- Variables ---

	int return_value;

    //--- Initial settings ---

    return_value = 0;

    // ---
    
	me->map_training_parameter.learning_rate = learning_rate;
    me->som_state |= (1<<3);  // Training parameter change flag is set; reallocation / allocation of memory has to follow
    
    return return_value;
}

double get_learning_rate(som* const me){

    /***********************************************************************************************************************
    *
    * Function name:                    - get_learning_rate
    * 
    * Function purpose:                 - Returns the learning rate
    * 
    * Input parameter:
    * 
    *   me              [som* const]    - A pointer to the actual object
    * 
    * Return parameter:
    * 
    *   return_value    [double]        - me->map_training_parameter.learning_rate        -
    *
    ***********************************************************************************************************************/

#ifdef DEBUG
    printf("\nInside get_learning_rate.\n");
#endif

    //--- Variables ---
    
	return me->map_training_parameter.learning_rate;
}

int get_pointer_to_input_map(som* const me, double **input_map){

    /***********************************************************************************************************************
    *
    * Function name:                        - get_pointer_to_input_maps
    * 
    * Function purpose:                     - Setup/change the topology of the neural net
    * 
    * Input parameter:
    * 
    *   me              [som* const] -
    *   input_maps      [double ***]        -
    * 
    * Return parameter:
    * 
    *   return_value    [int]               -
    *
    ***********************************************************************************************************************/

#ifdef DEBUG
    printf("\nInside get_pointer_to_input_maps.\n");
#endif

    //--- Variables ---

	int return_value;

    //--- Initial settings ---

    return_value = 0;

    // ---
    
    if(me->input_map != NULL){
        input_map = me->input_map;
        return_value = 1;
    }
    
    return return_value;

}

//--- Methodes ---

int update_som_parameters(som* const me, som_topology map_parameter, som_training_parameter map_training_parameter){

    /***********************************************************************************************************************
    *
    * Function name:                                        - update_net_parameters
    * 
    * Function purpose:                                     
    *                                                       - Setup/change the topology and training parameter of the neural net. The 
    *                                                         parameters will be checked by the setter functions. If one setter returns
    *                                                         a 1 this methode returns also a 1 signaling that something went wrong.
    * 
    * Input parameter:
    * 
    *   me                      [som* const]         - A pointer to the actual net object
    *   net_parameter           [cnn_topology]              - The parameters describing the net topology.
    *   net_training_parameter  [cnn_training_parameter]    - The training parameter.
    * 
    * Return parameter:
    * 
    *   ret_value               [int]                       - 0 = ok
    *                                                         1 = something went wrong
    *
    ***********************************************************************************************************************/

#ifdef DEBUG
    printf("\nInside update_net_parameter.\n");
#endif

    //--- Variables ---

	int return_value;

    //--- Initial settings ---

    return_value = 0;

    // ---

    me->set_width_of_input_map(me, map_parameter.width_of_input_map);
    me->set_height_of_input_map(me, map_parameter.height_of_input_map);
    me->set_width_of_cluster_map(me, map_parameter.width_of_cluster_map);

    //--- Set the training parameter

    me->set_number_of_epochs(me, map_training_parameter.number_of_epochs);
    me->set_neighborhood_size_r(me, map_training_parameter.neighborhood_size_r);
    me->set_number_of_training_maps(me, map_training_parameter.number_of_training_maps);
    me->set_number_of_test_maps(me, map_training_parameter.number_of_test_maps);
    //me->set_path_to_training_images(me, "test");
    //me->set_path_to_test_images(me, "test");
    me->set_learning_rate(me, map_training_parameter.learning_rate);
    
    
    return return_value;
}

int setup_som(som* const me, som_topology map_parameter, som_training_parameter map_training_parameter){
    
    /***********************************************************************************************************************
    *
    * Function name:                                        - setup_som
    * 
    * Function purpose:                                     
    * 
    *                                                       - Setup/change the topology of the neural net incl. memory
    *                                                         allocation. The net topology is checked against plausibility.
    *                                                         If a memory shortage is found all the previouse allocated 
    *                                                         memory is freed.
    * 
    * Input parameter:
    * 
    *   me                      [som* const]         -
    *   net_parameter           [cnn_topology]              -
    *   net_training_parameter  [cnn_training_parameter]    - 
    * 
    * Return parameter:
    * 
    *   ret_value               [int]                       -
    *
    ***********************************************************************************************************************/

#ifdef DEBUG
    printf("\nInside setup_som.\n");
#endif

    //--- Variables ---

	int return_value;

    //--- Initial settings ---

    return_value = 0;

    // ---
    
    if(me->check_if_som_topology_is_valid(me, map_parameter, map_training_parameter)!=0){
        return 1;   // Net topology is not valid
    }else{
        // Put the new net / training / parameter in the 
        me->update_som_parameters(me, map_parameter, map_training_parameter);
    }
    if((me->som_state & 0b00000010)!=0){
        me->free_allocated_memory(me);
    }

    //--- Allocate memory for the input map
    
    // Allocate memory for the numbers of rows of the map
    if((me->input_map = calloc(me->map_topology.height_of_input_map, sizeof *me->input_map))==NULL){
        me->free_allocated_memory(me);  // Free the memory that was allocatet untill now
        printf("Not enough memory.\n");
        return 1;
    }else{
        // Allocate memory for the columns of the map
        for (int i=0; i < me->map_topology.height_of_input_map; i++){
            if((me->input_map[i] = calloc(me->map_topology.width_of_input_map, sizeof **me->input_map))==NULL){
                me->free_allocated_memory(me);  // Free the memory that was allocatet untill now
                printf("Not enough memory for the columns of the input map.\n");
                return 1;
            }
        }
    }
    printf("Memory for the input map successfully allocated.\n");

    //--- Allocate memory for the weights
    
    if((me->weights = calloc(me->map_topology.width_of_cluster_map, sizeof *me->weights))==NULL){
        me->free_allocated_memory(me);  // Free the memory that was allocatet untill now
        printf("Not enough memory.\n");
        return 1;
    }else{
        for(int ci=0; ci < me->map_topology.width_of_cluster_map; ci++){
            if((me->weights[ci] = calloc(me->map_topology.width_of_cluster_map, sizeof **me->weights))==NULL){
                me->free_allocated_memory(me);  // Free the memory that was allocatet untill now
                printf("Not enough memory.\n");
                return 1;
            }else{
                for(int cj=0; cj < me->map_topology.width_of_cluster_map; cj++){
                    if((me->weights[ci][cj] = calloc(me->map_topology.height_of_input_map, sizeof ***me->weights))==NULL){
                        me->free_allocated_memory(me);  // Free the memory that was allocatet untill now
                        printf("Not enough memory.\n");
                        return 1;
                    }else{
                        for(int i=0; i < me->map_topology.height_of_input_map; i++){
                            if((me->weights[ci][cj][i] = calloc(me->map_topology.width_of_input_map, sizeof ****me->weights))==NULL){
                                me->free_allocated_memory(me);  // Free the memory that was allocatet untill now
                                printf("Not enough memory.\n");
                                return 1;
                            }
                        }
                    }
                }
            }
        }
    }
    
    printf("Went through all the memory allocations");
    me->som_state |= (1<<1);  // Memory allocated flag is set
    me->som_state &= ~(1<<2); // "Memory has to be allocated" - flag is deleted
    me->som_state &= ~(1<<0); // "Net topology changed flag is cleared
    

	return return_value;
}

int free_allocated_memory(som* const me){
    
    /***********************************************************************************************************************
    *
    * Function name:                    - free_allocated_memory
    * 
    * Function purpose:                 - Frees the before allocated memory of the SOM.
    * 
    * Input parameter:
    * 
    *   me              [som* const]    - A pointer to the actual som object.
    * 
    * Return parameter:
    * 
    *   return_value    [int]           - 0 = ok
    *                                     1 = something went wrong
    *
    ***********************************************************************************************************************/

#ifdef DEBUG
    printf("\nInside free_allocated_memory.\n");
#endif

    //--- Variables ---

	int return_value;

    //--- Initial settings ---

    return_value = 0;

    // ---

    //--- Free the memory for the input map

    for(int i=0; i < me->map_topology.height_of_input_map; i++){
        if(me->input_map[i]){
            free(me->input_map[i]);
        }
    }
    if(me->input_map){
        free(me->input_map);
    }

    //--- Free the memory for the weights
    
    for(int ci=0; ci < me->map_topology.width_of_cluster_map; ci++){
        for(int cj=0; cj < me->map_topology.width_of_cluster_map; cj++){
            for(int i=0; i < me->map_topology.height_of_input_map; i++){
                if(me->weights[ci][cj][i]){
                    free(me->weights[ci][cj][i]);
                }
            }
            if(me->weights[ci][cj]){
                free(me->weights[ci][cj]);
            }
        }
        if(me->weights[ci]){
            free(me->weights[ci]);
        }
    }
    if(me->weights){
        free(me->weights);
    }
    me->som_state &= ~(1<<1);  // Memory allocated flag is cleared

	return return_value;
}

int check_if_som_topology_is_valid(som* const me, som_topology map_topology, som_training_parameter map_training_parameter){

    /***********************************************************************************************************************
    *
    * Function name:                                        - check_if_som_topology_is_valid
    * 
    * Function purpose:                                     - Checks if the parameters are valid.
    * 
    * Input parameter:
    *   
    *   me                      [som* const]                -
    *   map_topology            [cnn_topology]              -
    *   map_training_parameter  [cnn_training_parameter]    -
    * 
    * Return parameter:
    * 
    *   return_value            [int] - (binary interpretation as a flag vector), bits are representing errors
    *                               bit 0 - WIDTH_OF_INPUT_MAP is to small. It should be 4 at min. to be meaningful
    *                               bit 1 - HEIGHT_OF_INPUT_MAP is to small. It should be 4 at min. to be meaningful
    *                               bit 2 - NUMBER_OF_INPUT_CHANNELS is too small (has to be 1 at min.),
    *                               bit 3 - WIDTH_OF_FILTER_KERNELS_FOR_THE_FIRST_CONVOLUTIONAL_LAYER is too small (min. size is 3 x 3),
    *                               bit 4 - WIDTH_OF_FILTER_KERNELS_FOR_THE_FIRST_CONVOLUTIONAL_LAYER is too big,
    *                               bit 5 - WIDTH_OF_FILTER_KERNELS_FOR_THE_OTHER_CONVOLUTIONAL_LAYER is too small (min. size is 3 x 3),
    *                               bit 6 - WIDTH_OF_FILTER_KERNELS_FOR_THE_OTHER_CONVOLUTIONAL_LAYER is too big,
    *                               bit 7 - NUMBER_OF_CONVOLUTIONAL_LAYERS is too big,
    *                               bit 8 - WIDTH_OF_POOLING_WINDOW is too small (min. size is 2 x 2),
    *                               bit 9 - WIDTH_OF_POOLING_WINDOW is too big,
    *                               bit 10 - NUMBER_OF_HIDDEN_LAYERS too small (min. is 1),
    *                               bit 11 - NUMBER_OF_NEURONS_IN_HIDDEN_LAYERS is too small (min. is 1),
    *                               bit 12 - NUMBER_OF_CLASSES is too small (min. is 1),
    *                               bit 13 - NUMBER_OF_CLASSES is too big (max. is 1)
    *
    ***********************************************************************************************************************/

#ifdef DEBUG
    printf("\nInside check_if_som_topology_is_valid.\n");
#endif

    //--- Variables ---

	int return_value;
    int actualized_value;

    //--- Initial settings ---

    return_value = 0;

    // ---
    
    //--- Until the rest of the methode is complete programmed the following code replaces it
    
    return 0;
    me->update_som_parameters(me, map_topology, map_training_parameter);
    
    //---
    
    switch(actualized_value){
        case WIDTH_OF_INPUT_MAP:
            if(me->map_topology.width_of_input_map<4){
                return_value |= (1<<0);
            }           
            break;
        case HEIGHTS_OF_INPUT_MAP:
            if(me->map_topology.height_of_input_map<4){
                return_value |= (1<<1);
            }           
            break;
    }
    
	return return_value;

}

int train_som(som* const me, int (*update_pixmap)(som *, int), void* chart_plot){

    /***********************************************************************************************************************
    *
    * Function name:                    - train_som
    * 
    * Function purpose:                 - Trains the som.
    * 
    * Input parameter:
    * 
    *   me              [som* const]    -
    *   update_pixmap   [int]           -
    * 
    * Return parameter:
    * 
    *   return_value    [int]           - int, if 1, the picture is too large
    *
    ***********************************************************************************************************************/

#ifdef DEBUG    
        printf("\nI am in train_som.\n");
#endif

    //--- Variables ---

	int return_value;
    mnist_data *d, *pd;
    unsigned int cnt;
    unsigned int start;
    unsigned int stop;
    int ret;
    int pixel_counter = 0;
    double actual_learning_rate;
    double actual_neighborhood_factor;
    int run_count;
    int total_runs;
    int show_count;

    //--- Initial settings ---

    start = 11;
    stop = me->map_training_parameter.number_of_training_maps;
    total_runs = me->map_training_parameter.number_of_epochs * me->map_training_parameter.number_of_training_maps - 11;
    show_count = 0;
    
    //---
    
    if (ret = mnist_load("/home/pi/projects/data/mnist/train-images-idx3-ubyte", "/home/pi/projects/data/mnist/train-labels-idx1-ubyte", &d, &cnt, &start, &stop)) {
        printf("An error occured: %d\n", ret);
    } else {
        
        // Train the map
        
        for(int e=0; e < me->map_training_parameter.number_of_epochs; e++){    
            if(me->state_of_training == 0){
                break;
            }            
            for (int k=11; k < me->map_training_parameter.number_of_training_maps; k++){
                pd = &d[k];
                for(int j=0; j < 28; j++){
                    for (int i=0; i < 28; i++){
                        me->input_map[i][j] = (255-(int)(pd->data[i][j]));
                    }
                }
                run_count++;
                find_the_winning_node(me);
                
                actual_learning_rate = me->map_training_parameter.learning_rate * pow(me->map_training_parameter.end_learning_rate / me->map_training_parameter.learning_rate, run_count / total_runs);
                
                actual_neighborhood_factor = me->map_training_parameter.neighborhood_size_r * pow(me->map_training_parameter.end_neighborhood_size_r / me->map_training_parameter.neighborhood_size_r, run_count / total_runs);
                
                update_weights(me, actual_learning_rate, actual_neighborhood_factor);
                if(show_count == me->weights_show_interval){
                    update_pixmap(me, 0);
                    show_count = 0;
                }
                update_pixmap(me, 1);
                show_count++;
            }
        }
    }

    return return_value;
}

int cluster_a_data_map(som* const me, void **map, int map_height, int map_width, int data_type){

    /***********************************************************************************************************************
    *
    * Function name:                    - cluster_a_data_map
    * 
    * Function purpose:                 - Clusters an input map
    * 
    * Input parameter:
    * 
    *   me              [som* const]    - A pointer to the actual som object
    *   map             [void**]        - The map to be clustered.
    *   map_height      [int]           - The height of the map
    *   map_width       [int]           - The width of the map
    *   data_type       [int]           - The type of the data (double, int etc.)
    * 
    * Return parameter:
    * 
    *   return_value    [int]           - 0 = ok
    *                                     1 = something went wrong
    *
    ***********************************************************************************************************************/

#ifdef DEBUG
    printf("\nNow I am in cluster_a_data_map.\n");
#endif

    //--- Variables ---

    double **picture_to_classify;
	int return_code;

    //--- Initial settings ---

    return_code = 0;

    // ---
    
    //--- Check if the picture is not too big
    
    
    //--- Classify the picture
    
    return return_code;
}

int fill_weights_randomly(som* const me){

    /***********************************************************************************************************************
    *
    * Function name:                        - fill_weights_randomly
    * 
    * Function purpose:                     - Fills the weights (incl. the filter kernels)
    * 
    * Input parameter:
    * 
    *   me              [som* const] -
    * 
    * Return parameter:
    * 
    *   return_value    [int]               - (binary interpretation as a flag vector), bits are representing errors
    *
    ***********************************************************************************************************************/

#ifdef DEBUG
    printf("\nNow I am in fill_weights_randomly.\n");
#endif

    //--- Variables ---

	int return_value;

    //--- Initial settings ---

    return_value = 0;

    // ---

    for(int ci=0; ci < me->map_topology.width_of_cluster_map; ci++){
        for(int cj=0; cj < me->map_topology.width_of_cluster_map; cj++){
            for(int i=0; i < me->map_topology.height_of_input_map; i++){
                for(int j=0; j < me->map_topology.width_of_input_map; j++){
                    me->weights[ci][cj][i][j] = (-1+2*((float)rand())/RAND_MAX);
                }
            }
        }
    }
    
    return return_value;
}

int reverse_int(som* const me, int i) {
    unsigned char c1, c2, c3, c4;

    c1 = i & 255;
    c2 = (i >> 8) & 255;
    c3 = (i >> 16) & 255;
    c4 = (i >> 24) & 255;

    return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
}

void read_mnist(som* const me, char * full_path){
    
    //ifstream file (*full_path);
    //if (file.is_open())
    //{
        //int magic_number=0;
        //int number_of_images=0;
        //int n_rows=0;
        //int n_cols=0;
        //file.read((char*)&magic_number,sizeof(magic_number));
        //magic_number= reverse_int(magic_number);
        //file.read((char*)&number_of_images,sizeof(number_of_images));
        //number_of_images= reverseInt(number_of_images);
        //file.read((char*)&n_rows,sizeof(n_rows));
        //n_rows= reverseInt(n_rows);
        //file.read((char*)&n_cols,sizeof(n_cols));
        //n_cols= reverseInt(n_cols);
        //for(int i=0;i<number_of_images;++i)
        //{
            //for(int r=0;r<n_rows;++r)
            //{
                //for(int c=0;c<n_cols;++c)
                //{
                    //unsigned char temp=0;
                    //file.read((char*)&temp,sizeof(temp));

                //}
            //}
        //}
    //}
}

int find_the_winning_node(som* const me){

    /***********************************************************************************************************************
    *
    * Function name:                        - find_the_winning_node
    * 
    * Function purpose:                     - Multiplies the general input vector with the weight matrix to the first 
    *                                         hidden layer and stores the result in the first hidden layer
    * 
    * Input parameter:
    * 
    *   me              [som* const] - The actual neuralnet
    * 
    * Return parameter:
    * 
    *   return_value    [int]               - 0 = ok, 
    *                                       - 1 = Somethng went wrong,
    *
    ***********************************************************************************************************************/

#ifdef DEBUG
    printf("\nNow I am in find_the_winning_node.\n");
#endif

    //--- Variables ---

	int return_value;
    double D;           //Actual distance
    double min_D;       //Minimal distance

    //--- Initial settings ---

    return_value = 0;
    me->winning_node[0] = 0;
    me->winning_node[1] = 0;
    min_D = -1;

    //---
        
    for(int ci=0; ci < me->map_topology.width_of_cluster_map; ci++){
        for(int cj=0; cj < me->map_topology.width_of_cluster_map; cj++){
            D = 0;
            for(int i=0; i < me->map_topology.height_of_input_map; i++){
                for(int j=0; j < me->map_topology.width_of_input_map; j++){
                    D += pow(me->weights[ci][cj][i][j] - me->input_map[i][j], 2);
                }
            }
            D = sqrt(D);
            if(min_D == -1){
                min_D = D;
                me->winning_node[0] = ci;
                me->winning_node[1] = cj;
            }else if(D < min_D){
                min_D = D;
                me->winning_node[0] = ci;
                me->winning_node[1] = cj;
            }
        }
    }

 
#ifdef DEBUG

#endif   
    
    return return_value;
}

int update_weights(som* const me, double learning_rate, double neighborhood_factor){

    /***********************************************************************************************************************
    *
    * Function name:                        - update_weights
    * 
    * Function purpose:                     - Updates the weights to the output layer
    * 
    * Input parameter:
    * 
    *   me              [som* const] - The actual neural net
    *   deltas          [double **]         - The deltas
    * 
    * Return parameter:
    * 
    *   return_value    [int]               - 0 = ok, 
    *                                       - 1 = Somethng went wrong,
    *
    ***********************************************************************************************************************/

#ifdef DEBUG
    printf("\nNow I am in update_weights.\n");
#endif

    //--- Variables ---

	int return_value;
    double neighborhood_value;
    double distance;

    //--- Initial settings ---

    return_value = 0;

    //---
    
    for(int ci=0; ci < me->map_topology.width_of_cluster_map; ci++){
        for(int cj=0; cj < me->map_topology.width_of_cluster_map; cj++){
            for(int i=0; i < me->map_topology.height_of_input_map; i++){
                for(int j=0; j < me->map_topology.width_of_input_map; j++){
                    distance = -(((me->winning_node[0] - ci) * (me->winning_node[0] - ci) + (me->winning_node[1] - cj) * (me->winning_node[1] - cj)));
                    neighborhood_value = pow(M_E,distance/(2*pow(neighborhood_factor, 2)));
                    me->weights[ci][cj][i][j] += learning_rate * neighborhood_value * (me->input_map[i][j] - me->weights[ci][cj][i][j]);
                }
            }
        }
    }

#ifdef DEBUG
    // For test reasons
        printf("\n");
#endif

    return return_value;
}

int serialize_the_som(som* const me, FILE *file, int open_option){

    /***********************************************************************************************************************
    *
    * Function name: setup_som
    * Function purpose: Setup/change the topology of the neural net
    * Input parameter:
    *               me -
    *               v -
    * Return parameter:
    *               ret -
    *
    ***********************************************************************************************************************/

#ifdef DEBUG
    printf("\nNow I am in serialize_the_net.\n");
#endif

    //--- Definition of parameters ---

    int return_value;
    int c;
    double normalizing_factor;  // The dot product of filter and 255 (the biggest pixel value)

    //--- Initial settings ---
    
    //---
    
    if(open_option == LOAD_ONN_FILE){
        printf("Open a CNN\n");
        if (file){

            char line[256];
            char *start, *stop, *value_buffer;
            int setup_result;
            
            //---
            
            fgets(line, sizeof(line), file); // Read the first line without any action
            
            //--- Check if the file is a valid .onn file
            fgets(line, sizeof(line), file);
            if(strstr(line, "<!-- The Net 00001.0000.0000 -->\n")==NULL){
                //show_modal_info_dialog("Error", "Not a valid .onn file.", 300, 100);
                return 1;
            }
            while (fgets(line, sizeof(line), file)) {
                if(strstr(line, "number_of_input_channels")){
                    start = strchr(line, 62);
                    stop = strrchr(line, 60);
                    for(int i=(int)(stop-1); i>(int)(start); i--){
                        value_buffer = (char*)i;
                    }
                }else if(strstr(line, "width_of_input_map")){
                    start = strchr(line, 62);
                    stop = strrchr(line, 60);
                    for(int i=(int)(stop-1); i>(int)(start); i--){
                        value_buffer = (char*)i;
                    }
                    me->map_topology.width_of_input_map = atoi(value_buffer);
                }else if(strstr(line, "height_of_input_map")){
                    start = strchr(line, 62);
                    stop = strrchr(line, 60);
                    for(int i=(int)(stop-1); i>(int)(start); i--){
                        value_buffer = (char*)i;
                    }
                    me->map_topology.height_of_input_map = atoi(value_buffer);
               }
            }
            fclose(file);
            //--- Setup the net by allocating memory
            setup_result = me->setup_som(me, me->map_topology, me->map_training_parameter);
            switch(setup_result){
                case 1:
                    break;
            }
        }
    }else{  // Save SOM to file
        printf("Save a CNN\n");
        if (file){
            
            fprintf(file, "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n");
            fprintf(file, "<!-- The Net 00001.0000.0000 -->\n");
            
            //--- The CNN topology
            
            fprintf(file, "<object class=\"SOM\" id=\"cnn\">\n");
            fprintf(file, "<object class=\"NetParameter\" id=\"NetParameter\">\n");
            fprintf(file, "<child cnn_topology=\"net_topology\">\n");
            fprintf(file, "<property name=\"width_of_input_map\">%i</property>\n", me->map_topology.width_of_input_map);
            fprintf(file, "<property name=\"height_of_input_map\">%i</property>\n", me->map_topology.height_of_input_map);
            fprintf(file, "</child>\n");
            
            //--- The training parameters
            
            fprintf(file, "<child cnn_training_parameter=\"cnn_training_parameter\">\n");
            fprintf(file, "<property name=\"number_of_epochs\">%i</property>\n", me->map_training_parameter.number_of_epochs);
            fprintf(file, "<property name=\"batch_size\">%i</property>\n", me->map_training_parameter.neighborhood_size_r);
            fprintf(file, "<property name=\"number_of_training_maps\">%i</property>\n", me->map_training_parameter.number_of_training_maps);
            fprintf(file, "<property name=\"number_of_test_maps\">%i</property>\n", me->map_training_parameter.number_of_test_maps);
            fprintf(file, "<property name=\"path_to_training_maps\">%i</property>\n", me->map_training_parameter.path_to_training_maps);
            fprintf(file, "<property name=\"path_to_test_maps\">%i</property>\n", me->map_training_parameter.path_to_test_maps);
            fprintf(file, "<property name=\"learning_rate\">%i</property>\n", me->map_training_parameter.learning_rate);
            fprintf(file, "</child>\n");
            fprintf(file, "</object>\n");
            
            //--- The kernel weights for the first convolutional layer
            printf("The kernel weights for the first convolutional layer");
            
            fprintf(file, "<object class=\"cnn_weights\" id=\"cnn_weights\">\n");
            fprintf(file, "<child filter_kernel_weights=\"filter_kernel_weights\">\n");
            
            fprintf(file, "</child>\n");
            
            
            fprintf(file, "<child hidden_layer_weights=\"hidden_layer_weights\">\n");
            
             

            fprintf(file, "</child>\n");
            fprintf(file, "</object>\n");
#ifdef DEBUG

#endif
            fprintf(file, "</object>\n");
        }
        fclose(file);
    }

    return return_value;
}

