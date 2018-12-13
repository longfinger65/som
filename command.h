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
#include <math.h>
#include <string.h>
#include "/home/pi/projects/som/read_mnist.h"
#include "/home/pi/projects/som/menubar.h"
#include "/home/pi/projects/som/otmath.h"
#include "/home/pi/projects/som/utilities.h"

extern int setup_weight_images(som *the_map);
extern int organize_weight_image_grid(som *the_map);
extern chart_plotter *graph_window;


#ifndef COMMAND_H_
#define COMMAND_H_

#define DEBUG

#define AVERAGE_POOLING                                             14
#define MAX_POOLING                                                 15
#define RELU                                                        16
#define TANH                                                        17
#define SIGMOID                                                     18
#define ONE_OUT_OF_MANY                                             19
#define MANY_OUT_OF_ONE                                             20


typedef void (*functionPointerType)(void *);

struct commandStruct {
	char const *name;
	functionPointerType execute;
	char const *help;
};

struct cmd_to_execute{
    char  function_to_execute[30];
    void *data;
    void *data_2;
    som *the_map;
};

struct map_data{
    void **data;
};

struct command_system_state{
    
    int show_weight_images;                                    // 1 = show
    int number_of_rows_in_grid_of_weight_images;         // 1 = created
    int number_of_columns_in_grid_of_weight_images;      // 1 = created
    int weight_images_are_created;                       // 1 = created
    
    
};

extern const struct commandStruct commands[];
extern mnist_data image_data;
extern unsigned char char_pixel[28][28];
extern char about_text[];


void on_command(GtkWidget* sender, gpointer user_data);

//--- Begin commands ---

void cmdGetVersion(void * dat);
void cmdTrainTheSOM(void * dat);
void cmdPauseTrainTheSOM(void * dat);
void cmdStopTrainTheSOM(void * dat);
void cmdContinueTrainTheSOM(void * dat);
void cmdSetupTheSOM(void * dat);
void cmdClusterAnInput(void * dat);
void cmdHelpContent(void * dat);
void cmdAbout (void * dat);
void cmdNewSOM(void *dat);
void cmdLoadSOM(void *dat);
void cmdSaveSOM(void *dat);
void cmdSaveSOMAs(void *dat);
void cmdShowResultScreen(void *dat);
void cmdSetProgramOptions(void *dat);

//--- End commands ---

#endif //--- COMMAND_H_ ---
