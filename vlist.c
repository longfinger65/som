#include "/home/pi/projects/filter_test_002/vlist.h"

/* constructors and destructors */

void init_vlist (vlist* const me,
                        int (*function_set_node_value)(vlist* const me, int, double),
                        double(*function_get_node_value)(vlist* const me,int),
                        int (*function_set_node_count)(vlist* const me,int),
                        int (*function_get_node_count)(vlist* const me),
                        int (*function_add_node)(vlist* const me, int),
                        int (*function_add_first_node)(vlist* const me),
                        int (*function_add_last_node)(vlist* const me),
                        int (*function_remove_node)(vlist* const me, int),
                        int (*function_remove_first_node)(vlist* const me),
                        int (*function_remove_last_node)(vlist* const me),
                        int (*function_rotate_and_add_last)(vlist* const me, double)){

    /*******************************************************************************************************************************
    *
    * Function name:        - init_vlist
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
    *   return_value [int]-
    *
    ********************************************************************************************************************************/

    //--- Initial settings ---
    
    //--- Setting the methodes
    
    me->set_node_value = function_set_node_value;
    me->get_node_value = function_get_node_value;
    me->set_node_count = function_set_node_count;
    me->get_node_count = function_get_node_count;
    me->add_node = function_add_node;
    me->add_first_node = function_add_first_node;
    me->add_last_node = function_add_last_node;
    me->remove_node = function_remove_node;
    me->remove_first_node = function_remove_first_node;
    me->remove_last_node = function_remove_last_node;
    me->rotate_and_add_last = function_rotate_and_add_last;
    
    //--- Setting the member variables
    
	me->node_count = 0;
    //me->first_node->next = NULL;
    //me->first_node->previouse = NULL;
    me->first_node = NULL;

}

/* Constructor and destructor */

vlist * create_vlist(void){
	vlist * me = (vlist *)malloc(sizeof(vlist));
	if(me!=NULL){
		init_vlist( me,
                    set_node_value,
                    get_node_value,
                    set_node_count,
                    get_node_count,
                    add_node,
                    add_first_node,
                    add_last_node,
                    remove_node,
                    remove_first_node,
                    remove_last_node,
                    rotate_and_add_last);
		printf("Vlist was successfully created.\n");
	}else{
		printf("Not enough memory to create the vlist object.\n");
	}
	return me;
}

void destroy_vlist(vlist* const me){
	if(me!=NULL){
		cleanup_vlist(me);
		free(me);
	}
}

void cleanup_vlist(vlist* const me){
    
}

//--- Getter and setter ---

int set_node_value(vlist* const me, int node_number, double node_value){

    /********************************************************************************************************************************
    *
    * Function name:                        - set_node_value
    * 
    * Function purpose:                     - Updates the weights to the first hidden layer
    * 
    * Input parameter:
    * 
    *   me              [neural_net* const] - The actual neuralnet
    * 
    * Return parameter:
    * 
    *   return_value    [int]               - 0 = ok, 
    *                                       - 1 = Somethng went wrong,
    *
    ********************************************************************************************************************************/

#ifdef DEBUG
    printf("\nNow I am in set_node_value.\n");
#endif

    //--- Variables ---

    int return_value;
    vlist_node *buffer_node;

    //--- Initial settings ---

    return_value = 0;
    buffer_node = me->first_node;
    
    //---
    
    if(node_number >= me->node_count){
        return 1;
    }else{
        for(int i=0; i < node_number; i++){
            buffer_node = buffer_node->next;
        }
        buffer_node->node_value = node_value;
    }
    
    return return_value;
}

double get_node_value(vlist* const me, int node_number){

    /************************************************************************************************************************
    *
    * Function name:               - calculate_deltas_for_general_inputs
    * 
    * Function purpose:            - Updates the weights to the first hidden layer
    * 
    * Input parameter:
    * 
    *   me          [vlist* const] - The actual vlist
    * 
    * Return parameter:
    * 
    *   node_value  [double]
    *
    ************************************************************************************************************************/

#ifdef DEBUG
    printf("\nNow I am in get_node_value.\n");
#endif

    //--- Variables ---

    vlist_node * actual_node;
    
    //--- Initial settings ---
    
    actual_node = me->first_node;
    
    //---
    
    if(node_number >= me->node_count){
        return 1;
    }else{
        for(int i=0; i < node_number; i++){
            actual_node = actual_node->next;
        }
    }
        
    return actual_node->node_value;
}

int set_node_count(vlist* const me, int node_count){

    /********************************************************************************************************************************
    *
    * Function name:                      - set_node_count
    * 
    * Function purpose:                   - Sets the node_count
    * 
    * Input parameter:
    * 
    *   me              [vlist* const me] - The actual vlist
    *   node_count      [int]
    * 
    * Return parameter:
    * 
    *   return_value    [int]             - 0 = ok, 
    *                                     - 1 = Somethng went wrong,
    *
    ********************************************************************************************************************************/

#ifdef DEBUG
    printf("\nNow I am in set_node_count.\n");
#endif

    //--- Variables ---

    int return_value;


    //--- Initial settings ---

    return_value = 0;
    
    //---
    
    me->node_count = node_count;
    
    return return_value;
}

int get_node_count(vlist* const me){

    /********************************************************************************************************************************
    *
    * Function name:                      - get_node_count
    * 
    * Function purpose:                   - Returns the node_count
    * 
    * Input parameter:
    * 
    *   me              [vlist* const me] - The actual vlist
    * 
    * Return parameter:
    * 
    *   me->node_count  [int]
    *
    ********************************************************************************************************************************/

#ifdef DEBUG
    printf("\nNow I am in get_node_count.\n");
#endif

    //--- Variables ---

    //--- Initial settings ---
    
    //---
    
    return me->node_count;
}

	//--- Methodes ---

int add_node(vlist* const me, int node_number){

    /********************************************************************************************************************************
    *
    * Function name:                        - add_node
    * 
    * Function purpose:                     - Add a new node to the end of the vlist.
    * 
    * Input parameter:
    * 
    *   me              [vlist* const me]   - The actual vlist
    *   node_number     [int]               -
    * 
    * Return parameter:
    * 
    *   return_value    [int]               - 0 = ok, 
    *                                       - 1 = Somethng went wrong,
    *
    ********************************************************************************************************************************/

#ifdef DEBUG
    printf("\nNow I am in add_node.\n");
#endif

    //--- Variables ---

    int return_value;
    vlist_node *new_list_node;
    vlist_node *buffer_node;

    //--- Initial settings ---

    return_value = 0;
    new_list_node = NULL;
    buffer_node = NULL;
    if(me->node_count == 0){
        if((me->first_node = calloc(1, sizeof *me->first_node))==NULL){
            printf("Not enough memory to add a list_node.\n");
            return 1;
        }else{
            printf("Memory for the first_node successfully allocated.\n");
            me->set_node_count(me, 1);
            me->first_node->next = me->first_node;
            me->first_node->previouse = me->first_node;
            return 0;
        }
    }else{
        // Allocate memory for a new list_node other than the first one
        if((new_list_node = calloc(1, sizeof *new_list_node ))==NULL){
            printf("Not enough memory to add a new_list_node.\n");
            return 1;
        }else{
            printf("Memory for a new_list_node successfully allocated.\n");
        }
        // Initialize the new_list_node
        new_list_node->previouse = NULL;
        new_list_node->next = NULL;
        buffer_node = me->first_node;
        for(int i=0; i < me->node_count; i++){
            if(buffer_node->next == me->first_node){
                new_list_node->previouse = buffer_node;
                new_list_node->next = me->first_node;
                buffer_node->next = new_list_node;
                me->first_node->previouse = new_list_node;
                return 0;
            }else{
                buffer_node = buffer_node->next;
            }
        }
    }
    
    return return_value;
}

int add_first_node(vlist* const me){

    /********************************************************************************************************************************
    *
    * Function name:                        - add_first_node
    * 
    * Function purpose:                     - Updates the weights to the first hidden layer
    * 
    * Input parameter:
    * 
    *   me              [neural_net* const] - The actual neuralnet
    * 
    * Return parameter:
    * 
    *   return_value    [int]               - 0 = ok, 
    *                                       - 1 = Somethng went wrong,
    *
    ********************************************************************************************************************************/

#ifdef DEBUG
    printf("\nNow I am in add_first_node.\n");
#endif

    //--- Variables ---

    int return_value;


    //--- Initial settings ---

    return_value = 0;
    
    //---
    
    return return_value;
}

int add_last_node(vlist* const me){

    /********************************************************************************************************************************
    *
    * Function name:                        - add_last_node
    * 
    * Function purpose:                     - Updates the weights to the first hidden layer
    * 
    * Input parameter:
    * 
    *   me              [neural_net* const] - The actual neuralnet
    * 
    * Return parameter:
    * 
    *   return_value    [int]               - 0 = ok, 
    *                                       - 1 = Somethng went wrong,
    *
    ********************************************************************************************************************************/

#ifdef DEBUG
    printf("\nNow I am in add_last_node.\n");
#endif

    //--- Variables ---

    int return_value;
    vlist_node *new_list_node;
    vlist_node *buffer_node;

    //--- Initial settings ---

    return_value = 0;
    new_list_node = NULL;
    buffer_node = NULL;
    if(me->node_count == 0){
        if((me->first_node = calloc(1, sizeof *me->first_node))==NULL){
            printf("Not enough memory to add a list_node.\n");
            return 1;
        }else{
            printf("Memory for the first_node successfully allocated.\n");
            me->set_node_count(me, 1);
            me->first_node->next = me->first_node;
            me->first_node->previouse = me->first_node;
            return 0;
        }
    }else{
        // Allocate memory for a new list_node other than the first one
        if((new_list_node = calloc(1, sizeof *new_list_node ))==NULL){
            printf("Not enough memory to add a new_list_node.\n");
            return 1;
        }else{
            printf("Memory for a new_list_node successfully allocated.\n");
        }
        // Initialize the new_list_node
        new_list_node->previouse = NULL;
        new_list_node->next = NULL;
        buffer_node = me->first_node;
        for(int i=0; i < me->node_count; i++){
            if(buffer_node->next == me->first_node){
                new_list_node->previouse = buffer_node;
                new_list_node->next = me->first_node;
                buffer_node->next = new_list_node;
                me->first_node->previouse = new_list_node;
                me->set_node_count(me, me->get_node_count(me) + 1);
                return 0;
            }else{
                buffer_node = buffer_node->next;
            }
        }
    }
    
    return return_value;
}

int remove_node(vlist* const me, int node_number){

    /********************************************************************************************************************************
    *
    * Function name:                        - remove_node
    * 
    * Function purpose:                     - Updates the weights to the first hidden layer
    * 
    * Input parameter:
    * 
    *   me              [neural_net* const] - The actual neuralnet
    * 
    * Return parameter:
    * 
    *   return_value    [int]               - 0 = ok, 
    *                                       - 1 = Somethng went wrong,
    *
    ********************************************************************************************************************************/

#ifdef DEBUG
    printf("\nNow I am in remove_node.\n");
#endif

    //--- Variables ---

    int return_value;


    //--- Initial settings ---

    return_value = 0;
    
    //---
    
    return return_value;
}

int remove_first_node(vlist* const me){

    /********************************************************************************************************************************
    *
    * Function name:                        - remove_first_node
    * 
    * Function purpose:                     - Updates the weights to the first hidden layer
    * 
    * Input parameter:
    * 
    *   me              [neural_net* const] - The actual neuralnet
    * 
    * Return parameter:
    * 
    *   return_value    [int]               - 0 = ok, 
    *                                       - 1 = Somethng went wrong,
    *
    ********************************************************************************************************************************/

#ifdef DEBUG
    printf("\nNow I am in remove_first_node.\n");
#endif

    //--- Variables ---

    int return_value;


    //--- Initial settings ---

    return_value = 0;
    
    //---
    
    return return_value;
}

int remove_last_node(vlist* const me){

    /********************************************************************************************************************************
    *
    * Function name:                        - remove_last_node
    * 
    * Function purpose:                     - Updates the weights to the first hidden layer
    * 
    * Input parameter:
    * 
    *   me              [neural_net* const] - The actual neuralnet
    * 
    * Return parameter:
    * 
    *   return_value    [int]               - 0 = ok, 
    *                                       - 1 = Somethng went wrong,
    *
    ********************************************************************************************************************************/

#ifdef DEBUG
    printf("\nNow I am in remove_last_node.\n");
#endif

    //--- Variables ---

    int return_value;


    //--- Initial settings ---

    return_value = 0;
    
    //---
    
    return return_value;
}

int rotate_and_add_last(vlist* const me, double node_value){

    /********************************************************************************************************************************
    *
    * Function name:                      - rotate_and_add_last
    * 
    * Function purpose:                   - Makes the first node the last and put the node_value in the lasts node value.
    * 
    * Input parameter:
    * 
    *   me              [vlist* const me] - The actual vlist
    *   node_value      [double]          - The value the value of the new last node is set to.
    * 
    * Return parameter:
    * 
    *   return_value    [int]             - 0 = ok, 
    *                                     - 1 = Somethng went wrong,
    *
    ********************************************************************************************************************************/

#ifdef DEBUG
    printf("\nNow I am in rotate_and_add_last.\n");
#endif

    //--- Variables ---

    int return_value;

    //--- Initial settings ---

    return_value = 0;
    
    //---
    
    me->first_node->node_value = node_value;
    me->first_node = me->first_node->next;
    
    
    return return_value;
}
