/*
 * command.c
 *
 * Created: 03.07.2016 14:27:49
 *  Author: Boss
 */ 

#include "/home/pi/projects/som/command.h"


volatile int Flags= 0b00000000;
volatile int * CommandFlags= &Flags;
char ActualCmd[25];
char * Buffer = ActualCmd;

const struct commandStruct commands[]={
	{"cmdGetVersion", cmdGetVersion, "Makes the software version available"},
	{"cmdTrainTheSOM", cmdTrainTheSOM, "Trains the SOM"},
	{"cmdSetupTheSOM", cmdSetupTheSOM, "Shows the setup dialog and sets up the SOM on ok."},
    {"cmdClusterAnInput", cmdClusterAnInput, "Clusters an input"},
    {"cmdAbout", cmdAbout, "Shows the about dialog."},
    {"cmdNewSOM", cmdNewSOM, "Establishes a new SOM and deletes parameter of an existing net if existing."},
    {"cmdLoadSOM", cmdLoadSOM, "Loads a SOM from a file."},
    {"cmdSaveSOM", cmdSaveSOM, "Saves a SOM to a file."},
    {"cmdSaveSOMAs", cmdSaveSOMAs, "Saves a SOM to a file as."},
    {"cmdShowResultScreen", cmdShowResultScreen, "Show the result screen."},
    {"cmdSetProgramOptions", cmdSetProgramOptions, "Set options for program look and feel like colors."},
    {"cmdPauseTrainTheSOM", cmdPauseTrainTheSOM, "Pause training the SOM."},
    {"cmdStopTrainTheSOM", cmdStopTrainTheSOM, "Stop training the SOM."},
    {"cmdContinueTrainTheSOM", cmdContinueTrainTheSOM, "Continue training the SOM."},
    {"cmdHelpContent", cmdHelpContent, "Show help."},
	{"",0,""}
};
	


void on_command(GtkWidget* sender, gpointer user_data){

    /************************************************************************************************************************
    *
    * Function name: on_command
    * 
    * Function purpose: This methodes connects the commands with the according methodes
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
    ***********************************************************************************************************************/

#ifdef DEBUG
    printf("\nInside on_command.\n");
#endif

    //--- Variables ---

    struct cmd_to_execute * cmd = (struct cmd_to_execute*)user_data;

    //--- Initial settings ---


    // ---

    if (strcmp(cmd->function_to_execute, "cmdGetVersion") == 0) {
        commands[0].execute(cmd);
    }else if (strcmp(cmd->function_to_execute, "cmdTrainTheSOM") == 0) {
        commands[1].execute(cmd);
    }else if (strcmp(cmd->function_to_execute, "cmdSetupTheSOM") == 0) {
        commands[2].execute(cmd);
    }else if (strcmp(cmd->function_to_execute, "cmdClusterAnInput") == 0){
        commands[3].execute(cmd);
    }else if (strcmp(cmd->function_to_execute, "cmdAbout") == 0){
        commands[4].execute(cmd);
    }else if (strcmp(cmd->function_to_execute, "cmdNewSOM") == 0){
        commands[5].execute(cmd);
    }else if (strcmp(cmd->function_to_execute, "cmdLoadSOM") == 0){
        commands[6].execute(cmd);
    }else if (strcmp(cmd->function_to_execute, "cmdSaveSOM") == 0){
        commands[7].execute(cmd);
    }else if (strcmp(cmd->function_to_execute, "cmdSaveSOMAs") == 0){
        commands[8].execute(cmd);
    }else if (strcmp(cmd->function_to_execute, "cmdShowResultScreen") == 0){
        commands[9].execute(cmd);
    }else if (strcmp(cmd->function_to_execute, "cmdSetProgramOptions") == 0){
        commands[10].execute(cmd);
    }else if (strcmp(cmd->function_to_execute, "cmdPauseTrainTheSOM") == 0){
        commands[11].execute(cmd);
    }else if (strcmp(cmd->function_to_execute, "cmdStopTrainTheSOM") == 0){
        commands[12].execute(cmd);
    }else if (strcmp(cmd->function_to_execute, "cmdContinueTrainTheSOM") == 0){
        commands[13].execute(cmd);
    }else if (strcmp(cmd->function_to_execute, "cmdHelpContent") == 0){
        commands[14].execute(cmd);
    }
       
}

//--- Commands ---

void cmdGetVersion(void * dat){

    /***********************************************************************************************************************
    *
    * Function name: cmdGetVersion
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
    ***********************************************************************************************************************/

    //--- Variables ---

    struct cmd_to_execute *cmd = (struct cmd_to_execute *) dat;

    //--- Initial settings ---


    // ---

    printf("Inside cmdGetVersion.\n");

}

void cmdTrainTheSOM(void * dat){

    /************************************************************************************************************************
    * 
    * Function name:    - cmdTrainTheSOM
    * 
    * Function purpose: - Start training the SOM
    * 
    * Input parameter:
    * 
    *   dat [void *]    -
    *        
    * Return parameter:
    *
    ***********************************************************************************************************************/

#ifdef DEBUG
    printf("\nInside cmdTrainTheSOM.\n");
#endif
    //--- Variables ---

    struct cmd_to_execute *cmd = (struct cmd_to_execute *) dat;

    //--- Initial settings ---


    // ---
    
    //--- Check if the SOM is ready to train ---
    
    if((cmd->the_map->som_state & 0b00000100)==4){
        show_modal_info_dialog("Info!", "SOM isn't ready to train yet.\n It has to be setted up before using.", 300, 100, (GdkWindow*) cmd->data_2);
    }else{
        
        // Setup the weight images
        
        setup_weight_images(cmd->the_map);
        organize_weight_image_grid(cmd->the_map);

        cmd->the_map->state_of_training = 2;
        cmd->the_map->fill_weights_randomly(cmd->the_map);
        cmd->the_map->train_som(cmd->the_map, update_pixmap, graph_window);
    }
}

void cmdPauseTrainTheSOM(void * dat){
    
    /************************************************************************************************************************
    *
    * Function name:    - cmdPauseTrainTheSOM
    * 
    * Function purpose: - Pause training the SOM
    * 
    * Input parameter:
    * 
    *   dat [void *]    -
    *        
    * Return parameter:
    *
    ***********************************************************************************************************************/

#ifdef DEBUG
    printf("\nInside cmdPauseTrainTheSOM.\n");
#endif

    //--- Variables ---

    struct cmd_to_execute *cmd = (struct cmd_to_execute *) dat;

    //--- Initial settings ---


    // ---


}

void cmdStopTrainTheSOM(void * dat){

    /************************************************************************************************************************
    * Function name:    - cmdStopTrainTheSOM
    * 
    * Function purpose: - Stop training of the SOM
    * 
    * Input parameter:
    * 
    *   dat [void *]    -
    *        
    * Return parameter:
    *
    ***********************************************************************************************************************/

#ifdef DEBUG
    printf("\nInside cmdStopTrainTheSOM.\n");
#endif

    //--- Variables ---

    struct cmd_to_execute *cmd = (struct cmd_to_execute *) dat;

    //--- Initial settings ---

    // ---

    cmd->the_map->state_of_training = 0;
}

void cmdContinueTrainTheSOM(void * dat){

    /************************************************************************************************************************
    * 
    * Function name:    - cmdContinueTrainTheSOM
    * 
    * Function purpose: - Continues the training of the SOM
    * 
    * Input parameter:
    * 
    *   dat [void *]    -
    *        
    * Return parameter:
    *
    ***********************************************************************************************************************/

#ifdef DEBUG
    printf("\nInside cmdContinueTrainTheSOM.\n");
#endif

    //--- Variables ---

    struct cmd_to_execute *cmd = (struct cmd_to_execute *) dat;

    //--- Initial settings ---

    // ---
    
}

void cmdSetupTheSOM(void * dat){

    /***********************************************************************************************************************
    *
    * Function name:    - cmdSetupTheSOM
    * 
    * Function purpose: - Setup/change the topology of the SOM
    * 
    * Input parameter:
    * 
    *   dat [void *]    -
    *              
    * Return parameter:
    *
    ***********************************************************************************************************************/

#ifdef DEBUG
    printf("\nInside cmdSetupTheSOM.\n");
#endif

    //--- Variables ---
    
    GtkWidget *dialog;
    GtkLabel *widget;
    GtkBuilder *b;
    GObject *adjust;
    GObject *r_button;
    GObject *grid_1;
    gint knopf;
    struct command_system_state * the_state;
    som_topology temp_som_topology;
    som_training_parameter temp_som_training_parameters;
    struct cmd_to_execute *cmd = (struct cmd_to_execute *) dat;
    
    //--- Initial settings ---

    the_state = (struct command_system_state *)cmd->data_2;
    b = (GtkBuilder*)cmd->data;
    dialog = GTK_WIDGET(gtk_builder_get_object (b, "cnn_setup_dialog"));
 
    g_signal_connect_swapped (dialog, "response", G_CALLBACK (gtk_widget_hide), dialog);

    //---
    
    grid_1 = gtk_builder_get_object (b, "grid-1-1");
    gtk_widget_set_name ((GtkWidget*)grid_1,"net_topology");
    grid_1 = gtk_builder_get_object (b, "grid-2-1");
    gtk_widget_set_name ((GtkWidget*)grid_1,"net_topology");
    grid_1 = gtk_builder_get_object (b, "grid-3-1");
    gtk_widget_set_name ((GtkWidget*)grid_1,"net_topology");

    //--- Actualize the adjusts with the actual SOM parameters
    
    //--- Page 1 settings (topology parameter)
    
    adjust = gtk_builder_get_object (b, "adjustment-2-2-3-1-0");
    gtk_adjustment_set_value ((GtkAdjustment*)adjust, cmd->the_map->map_topology.width_of_input_map);
    adjust = gtk_builder_get_object (b, "adjustment-2-2-3-1-1");
    gtk_adjustment_set_value ((GtkAdjustment*)adjust, cmd->the_map->map_topology.height_of_input_map);
    adjust = gtk_builder_get_object (b, "adjustment-2-2-3-1");
    gtk_adjustment_set_value ((GtkAdjustment*)adjust, cmd->the_map->map_topology.width_of_cluster_map);
        
    //--- Page 2 settings (training parameter)
    
    adjust = gtk_builder_get_object (b, "adjustment-2-1");
    gtk_adjustment_set_value ((GtkAdjustment*)adjust, cmd->the_map->map_training_parameter.number_of_epochs);
    adjust = gtk_builder_get_object (b, "adjustment-2-2");
    gtk_adjustment_set_value ((GtkAdjustment*)adjust, cmd->the_map->map_training_parameter.neighborhood_size_r);
    adjust = gtk_builder_get_object (b, "adjustment-2-3");
    gtk_adjustment_set_value ((GtkAdjustment*)adjust, cmd->the_map->map_training_parameter.number_of_training_maps);
    adjust = gtk_builder_get_object (b, "adjustment-2-4");
    gtk_adjustment_set_value ((GtkAdjustment*)adjust, cmd->the_map->map_training_parameter.number_of_test_maps);
    adjust = gtk_builder_get_object (b, "adjustment-2-5");
    gtk_adjustment_set_value ((GtkAdjustment*)adjust, cmd->the_map->map_training_parameter.learning_rate);
    adjust = gtk_builder_get_object (b, "adjustment-2-6");
    gtk_adjustment_set_value ((GtkAdjustment*)adjust, cmd->the_map->map_training_parameter.end_learning_rate);
        
    //--- Page 3 settings (other parameter)

    r_button = gtk_builder_get_object (b, "checkbutton-1");
    printf("the checkbutton 1 is %d", (int)gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (r_button)));
    if((the_state->show_weight_images == 1) && (int)gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (r_button))==0){
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (r_button), TRUE);
    }
    adjust = gtk_builder_get_object (b, "adjustment-3-2");
    gtk_adjustment_set_value ((GtkAdjustment*)adjust, cmd->the_map->weights_show_interval);
    adjust = gtk_builder_get_object (b, "adjustment-3-33");
    gtk_adjustment_set_value ((GtkAdjustment*)adjust, cmd->the_map->weights_image_scaling_factor);
        
    // Evaluate the action
    
    gtk_widget_show_all (dialog);
    knopf = gtk_dialog_run (GTK_DIALOG(dialog));
    if(knopf==2){
        
        //--- Take over the parameters from page 1
        
        adjust = gtk_builder_get_object (b, "adjustment-2-2-3-1-0");
        temp_som_topology.width_of_input_map = gtk_adjustment_get_value ((GtkAdjustment*)adjust);
        adjust = gtk_builder_get_object (b, "adjustment-2-2-3-1-1");
        temp_som_topology.height_of_input_map = gtk_adjustment_get_value ((GtkAdjustment*)adjust);
        adjust = gtk_builder_get_object (b, "adjustment-2-2-3-1");
        temp_som_topology.width_of_cluster_map = gtk_adjustment_get_value ((GtkAdjustment*)adjust);

        //--- Take over the parameters from page 2
        
        adjust = gtk_builder_get_object (b, "adjustment-2-1");
        temp_som_training_parameters.number_of_epochs = gtk_adjustment_get_value ((GtkAdjustment*)adjust);
        adjust = gtk_builder_get_object (b, "adjustment-2-2");
        temp_som_training_parameters.neighborhood_size_r = gtk_adjustment_get_value ((GtkAdjustment*)adjust);
        adjust = gtk_builder_get_object (b, "adjustment-2-3");
        temp_som_training_parameters.number_of_training_maps = gtk_adjustment_get_value ((GtkAdjustment*)adjust);
        adjust = gtk_builder_get_object (b, "adjustment-2-4");
        temp_som_training_parameters.number_of_test_maps = gtk_adjustment_get_value ((GtkAdjustment*)adjust);
        adjust = gtk_builder_get_object (b, "adjustment-2-5");
        temp_som_training_parameters.learning_rate = gtk_adjustment_get_value ((GtkAdjustment*)adjust);
        adjust = gtk_builder_get_object (b, "adjustment-2-6");
        temp_som_training_parameters.end_learning_rate = gtk_adjustment_get_value ((GtkAdjustment*)adjust);
        
        //--- Take over the parameters from page 3
        
        r_button = gtk_builder_get_object (b, "checkbutton-1");
        if(gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (r_button))==TRUE){
            the_state->show_weight_images = 0;
        }else{
            the_state->show_weight_images = 1;
        }
        adjust = gtk_builder_get_object (b, "adjustment-3-2");
        cmd->the_map->weights_show_interval = gtk_adjustment_get_value ((GtkAdjustment*)adjust);
        adjust = gtk_builder_get_object (b, "adjustment-3-33");
        cmd->the_map->weights_image_scaling_factor = gtk_adjustment_get_value ((GtkAdjustment*)adjust);

        cmd->the_map->setup_som(cmd->the_map, temp_som_topology, temp_som_training_parameters);
        printf("Som state = %d\n", cmd->the_map->som_state);

    }

}

void cmdClusterAnInput(void * dat){

    /************************************************************************************************************************
    *
    * Function name: cmdClusterAnInput
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

#ifdef DEBUG
    printf("\nInside cmdClusterAnInput.\n");
#endif

    //--- Variables ---

    struct cmd_to_execute *cmd = (struct cmd_to_execute *) dat;

    //--- Initial settings ---


    // ---


}

void cmdHelpContent(void * dat){
    
    /************************************************************************************************************************
    *
    * Function name: cmdHelpContent
    * 
    * Function purpose: Shows the program help
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
    ***********************************************************************************************************************/

#ifdef DEBUG    
    printf("\nInside cmdHelpContent.\n");
#endif

    //--- Variables ---

    struct cmd_to_execute *cmd = (struct cmd_to_execute *) dat;

    //--- Initial settings ---


    // ---


    system("xpdf odartec_cnn_help.pdf");

}

void cmdAbout(void * dat){
    
    /************************************************************************************************************************
    *
    * Function name: cmdTrainTheNet
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
    ***********************************************************************************************************************/

#ifdef DEBUG
    printf("\nInside cmdAbout.\n");
#endif

    //--- Variables ---

    struct cmd_to_execute *cmd = (struct cmd_to_execute *) dat;

    //--- Initial settings ---


    // ---

    show_modal_info_dialog("About OdarTec SOM", about_text, 400, 150, (GdkWindow*) cmd->data);
}

void cmdNewSOM(void *dat){

    /************************************************************************************************************************
    *
    * Function name: cmdNewSOM
    * 
    * Function purpose: Creates a new SOM
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

#ifdef DEBUG
    printf("\nInside cmdNewSOM.\n");
#endif

    //--- Variables ---

    struct cmd_to_execute *cmd = (struct cmd_to_execute *) dat;

    //--- Initial settings ---


    // ---
    
}

void cmdLoadSOM(void *dat){

    /************************************************************************************************************************
    *
    * Function name: cmdLoadSOM
    * 
    * Function purpose: Loads an existing SOM from a file
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

#ifdef DEBUG
    printf("\nInside cmdLoadSOM.\n");
#endif

    //--- Variables ---

    struct cmd_to_execute *cmd = (struct cmd_to_execute *) dat;
	GtkFileFilter *filter = gtk_file_filter_new ();
	GtkWidget *toplevel = gtk_widget_get_toplevel (cmd->data);
    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    gint res;
    FILE *file;
    int c;
    
    //--- Initial settings ---

    gtk_file_filter_set_name (filter, "OdarTec SOM");
    gtk_file_filter_add_pattern (filter, "*.onn");
    gtk_file_filter_add_mime_type(filter, "som");

    // ---

    dialog = gtk_file_chooser_dialog_new ("Open File",
                                      GTK_WINDOW (toplevel),
                                      action,
                                      _("_Cancel"),
                                      GTK_RESPONSE_CANCEL,
                                      _("_Open"),
                                      GTK_RESPONSE_ACCEPT,
                                      NULL);
    
	gtk_file_chooser_add_filter (GTK_FILE_CHOOSER (dialog),
	                             filter);
    res = gtk_dialog_run (GTK_DIALOG (dialog));
    if (res == GTK_RESPONSE_ACCEPT){
        char *filename;
        GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
        filename = gtk_file_chooser_get_filename (chooser);
        file = fopen(filename, "r");
        cmd->the_map->serialize_the_som(cmd->the_map, file, LOAD_ONN_FILE);

        g_free (filename);
    }

    gtk_widget_destroy (dialog);    //setup_neural_net();

}

void cmdSaveSOM(void *dat){

    /************************************************************************************************************************
    *
    * Function name: cmdSaveSOM
    * 
    * Function purpose: Saves the SOM to a file
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

#ifdef DEBUG
    printf("\nInside cmdSaveSOM.\n");
#endif

    //--- Variables ---

    struct cmd_to_execute *cmd = (struct cmd_to_execute *) dat;
    GtkWidget *dialog;
	GtkFileFilter *filter = gtk_file_filter_new ();
    GtkFileChooser *chooser;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
	GtkWidget *toplevel = gtk_widget_get_toplevel (cmd->data);
    gint res;
    FILE *file;
    int c;
    int is_new;
    
    //--- Initial settings ---

    is_new = 1;
    gtk_file_filter_set_name (filter, "OdarTec SOM");
    gtk_file_filter_add_pattern (filter, "*.onn");
    gtk_file_filter_add_mime_type(filter, "som");

    // ---

    dialog = gtk_file_chooser_dialog_new ("Save the SOM",
                                      GTK_WINDOW (toplevel),
                                      action,
                                      _("_Cancel"),
                                      GTK_RESPONSE_CANCEL,
                                      _("_Save"),
                                      GTK_RESPONSE_ACCEPT,
                                      NULL);
    
    chooser = GTK_FILE_CHOOSER (dialog);

    gtk_file_chooser_set_do_overwrite_confirmation (chooser, TRUE);

    if (is_new == 1){
        gtk_file_chooser_set_current_name (chooser,_("Untitled document"));
    }else{
        gtk_file_chooser_set_filename (chooser, "test.onn");
    }
    res = gtk_dialog_run (GTK_DIALOG (dialog));
    if (res == GTK_RESPONSE_ACCEPT){
        char *filename;

        filename = gtk_file_chooser_get_filename (chooser);
        file = fopen(filename, "w");
        cmd->the_map->serialize_the_som(cmd->the_map, file, SAVE_ONN_FILE );

        g_free (filename);
    }

    gtk_widget_destroy (dialog);    //setup_neural_net();
}

void cmdSaveSOMAs(void *dat){

    /************************************************************************************************************************
    *
    * Function name: cmdSaveSOMAs
    * 
    * Function purpose: Saves the SOM as
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

#ifdef DEBUG
    printf("\nInside cmdSaveSOMAs.\n");
#endif

    //--- Variables ---

    struct cmd_to_execute *cmd = (struct cmd_to_execute *) dat;

    //--- Initial settings ---


    // ---
    
}

void cmdShowResultScreen(void *dat){

    /************************************************************************************************************************
    *
    * Function name: cmdShowReultScreen
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
    ***********************************************************************************************************************/

#ifdef DEBUG
    printf("\nInside cmdShowResultScreen.\n");
#endif

    //--- Variables ---

    chart_plotter *graph_window;
    struct cmd_to_execute *cmd = (struct cmd_to_execute *) dat;

    //--- Initial settings ---

    graph_window = (chart_plotter *)cmd->data;

    // ---

    int is_visible = 1;
    graph_window->set_chart_options(graph_window, &is_visible, "is_visible");
    
}

void cmdSetProgramOptions(void *dat){
    
    /************************************************************************************************************************
    *
    * Function name: cmdSetProgramOptions
    * 
    * Function purpose: Sets the program options
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

#ifdef DEBUG
    printf("\nInside cmdSetProgramOptions.\n");
#endif

    //--- Variables ---

    struct cmd_to_execute *cmd = (struct cmd_to_execute *) dat;

    //--- Initial settings ---


    // ---

}
