/*
 * vlist.h
 *
 * Created: 02.07.2018 15:36:22
 *  Author: Boss
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifndef VLIST_H_
#define VLIST_H_

//typedef struct vlist_node vlist_node;

typedef struct vlist_node{

	double node_value;
    struct vlist_node *previouse;
    struct vlist_node *next;
    
}vlist_node;

//--- Begin class vlist ---

    typedef struct vlist vlist;

    struct vlist{

        //--- Vlist options ---

        int node_count;
        /* The node count if only one node is in the list is 1 */
        
        vlist_node *first_node;

        //--- Getters and setters ---

        int (*set_node_value)(vlist* const me, int, double);
        double (*get_node_value)(vlist* const me, int);
        int (*set_node_count)(vlist* const me, int);
        int (*get_node_count)(vlist* const me);

        //--- Methodes ---

        int (*add_node)(vlist* const me, int);
        int (*add_first_node)(vlist* const me);
        int (*add_last_node)(vlist* const me);
        int (*remove_node)(vlist* const me, int);
        int (*remove_first_node)(vlist* const me);
        int (*remove_last_node)(vlist* const me);
        int (*rotate_and_add_last)(vlist* const me, double);
        
	};

	/* constructors and destructors */

	vlist * create_vlist(void);
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
                        int (*function_rotate_and_add_last)(vlist* const me, double));
    void destroy_vlist (vlist* const me);
    void cleanup_vlist(vlist* const me);

    //--- Getter and setter ---

    int set_node_value(vlist* const me, int, double node_value);
    double get_node_value(vlist* const me, int node_number);
    int set_node_count(vlist* const me, int node_count);
    int get_node_count(vlist* const me);

	//--- Methodes ---

    int add_node(vlist* const me, int node_number);
    int add_first_node(vlist* const me);
    int add_last_node(vlist* const me);
    int remove_node(vlist* const me, int node_number);
    int remove_first_node(vlist* const me);
    int remove_last_node(vlist* const me);
    int rotate_and_add_last(vlist* const me, double node_value);

#endif //--- VLIST_H_ ---
