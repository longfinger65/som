#include "/home/pi/projects/som/menubar.h"
#include "/home/pi/projects/som/som.h"
#include "/home/pi/projects/som/command.h"


extern void on_command(GtkWidget* sender, gpointer user_data);


gboolean statusbar_hint(GtkMenuItem * menuitem, GdkEventProximity *event, GtkStatusbar *statusbar){
	gchar *hint;
	guint id = gtk_statusbar_get_context_id(statusbar, "MenuItemHints");
	if (event->type == GDK_ENTER_NOTIFY){
		hint = (gchar*) g_object_get_data(G_OBJECT (menuitem), "menuhint");
		gtk_statusbar_push(statusbar, id, hint);
    } else if (event->type == GDK_LEAVE_NOTIFY){
        gtk_statusbar_pop(statusbar, id);
    }

    return FALSE;
}

GtkWidget* make_menubar (GtkWidget* statusbar, GtkBuilder *builder, som *the_map, GtkWidget* image_grid, void * the_program_state, chart_plotter *graph_window, GtkWindow *main_window){
    
    /*----------------------------------------------------------------------------*/
    /*                                                                            */
    /* Methode "create_menubar" creates the menu for the program                  */
    /*                                                                            */
    /*----------------------------------------------------------------------------*/
    
	GtkWidget *box;
    GtkWidget *menubar;
    GtkWidget *file, *filemenu, *new, *open, *save_som, *save_som_as, *exit_program;
    GtkWidget *edit, *editmenu, *cut, *copy, *paste;
    GtkWidget *selforganizingmap, *sommenu, *sep2, *setup, *train, *pause_training, *stop_training, *continue_training, *sep1, *cluster;
    GtkWidget *utilities, *utilitymenu;
    GtkWidget *extras, *extrasmenu, *set_program_options;
    GtkWidget *windows, *windowsmenu, *show_error_diagram;
    GtkWidget *help, *helpmenu, *contents, *about;
    GtkAccelGroup *group;
    struct cmd_to_execute * cmdDataForTrainTheSOM = malloc(sizeof (struct cmd_to_execute));
    struct cmd_to_execute * cmdDataForPauseTrainTheSOM = malloc(sizeof (struct cmd_to_execute));
    struct cmd_to_execute * cmdDataForStopTrainTheSOM = malloc(sizeof (struct cmd_to_execute));
    struct cmd_to_execute * cmdDataForContinueTrainTheSOM = malloc(sizeof (struct cmd_to_execute));
    struct cmd_to_execute * cmdDataForSetupTheSOM = malloc(sizeof (struct cmd_to_execute));
    struct cmd_to_execute * cmdDataForTestTheSOM = malloc(sizeof (struct cmd_to_execute));
    struct cmd_to_execute * cmdDataForClusterAnInput = malloc(sizeof (struct cmd_to_execute));
    struct cmd_to_execute * cmdDataForHelpContent = malloc(sizeof (struct cmd_to_execute));
    struct cmd_to_execute * cmdDataForAbout = malloc(sizeof (struct cmd_to_execute));
    struct cmd_to_execute * cmdDataForNewSOM = malloc(sizeof (struct cmd_to_execute));
    struct cmd_to_execute * cmdDataForLoadSOM = malloc(sizeof (struct cmd_to_execute));
    struct cmd_to_execute * cmdDataForSaveSOM = malloc(sizeof (struct cmd_to_execute));
    struct cmd_to_execute * cmdDataForSaveSOMAs = malloc(sizeof (struct cmd_to_execute));
    struct cmd_to_execute * cmdDataForShowResultScreen = malloc(sizeof (struct cmd_to_execute));
    struct cmd_to_execute * cmdDataForSetProgramOptions = malloc(sizeof (struct cmd_to_execute));
    
    //--- Initialization

    strcpy( (*cmdDataForTrainTheSOM).function_to_execute, "cmdTrainTheSOM");
    cmdDataForTrainTheSOM->data = image_grid;
    cmdDataForTrainTheSOM->data_2 = main_window;
    cmdDataForTrainTheSOM->the_map = the_map;
    strcpy( (*cmdDataForPauseTrainTheSOM).function_to_execute, "cmdPauseTrainTheSOM");
    cmdDataForPauseTrainTheSOM->data = image_grid;
    cmdDataForPauseTrainTheSOM->data_2 = main_window;
    cmdDataForPauseTrainTheSOM->the_map = the_map;
    strcpy( (*cmdDataForStopTrainTheSOM).function_to_execute, "cmdStopTrainTheSOM");
    cmdDataForStopTrainTheSOM->data = image_grid;
    cmdDataForStopTrainTheSOM->data_2 = main_window;
    cmdDataForStopTrainTheSOM->the_map = the_map;
    strcpy( (*cmdDataForContinueTrainTheSOM).function_to_execute, "cmdContinueTrainTheSOM");
    cmdDataForContinueTrainTheSOM->data = image_grid;
    cmdDataForContinueTrainTheSOM->data_2 = main_window;
    cmdDataForContinueTrainTheSOM->the_map = the_map;
    strcpy( (*cmdDataForSetupTheSOM).function_to_execute, "cmdSetupTheSOM");
    cmdDataForSetupTheSOM->data = builder;
    cmdDataForSetupTheSOM->data_2 = the_program_state;
    cmdDataForSetupTheSOM->the_map = the_map;
    strcpy( (*cmdDataForTestTheSOM).function_to_execute, "cmdTestTheSOM");
    cmdDataForTestTheSOM->data = the_program_state;
    cmdDataForTestTheSOM->the_map = the_map;
    strcpy( (*cmdDataForClusterAnInput).function_to_execute, "cmdClusterAnInput" );
    cmdDataForClusterAnInput->data = the_program_state;
    cmdDataForClusterAnInput->the_map = the_map;
    strcpy( (*cmdDataForHelpContent).function_to_execute, "cmdHelpContent" );
    cmdDataForHelpContent->data = main_window;
    cmdDataForHelpContent->the_map = the_map;
    strcpy( (*cmdDataForAbout).function_to_execute, "cmdAbout" );
    cmdDataForAbout->data = main_window;
    cmdDataForAbout->the_map = the_map;
    strcpy( (*cmdDataForNewSOM).function_to_execute, "cmdNewSOM" );
    cmdDataForNewSOM->data = builder;
    cmdDataForNewSOM->the_map = the_map;
    strcpy( (*cmdDataForLoadSOM).function_to_execute, "cmdLoadSOM" );
    cmdDataForLoadSOM->data = the_program_state;
    cmdDataForLoadSOM->the_map = the_map;
    strcpy( (*cmdDataForSaveSOM).function_to_execute, "cmdSaveSOM" );
    cmdDataForSaveSOM->data = main_window;
    cmdDataForSaveSOM->the_map = the_map;
    strcpy( (*cmdDataForSaveSOMAs).function_to_execute, "cmdSaveSOMAs" );
    cmdDataForSaveSOMAs->data = the_program_state;
    cmdDataForSaveSOMAs->the_map = the_map;
    strcpy( (*cmdDataForShowResultScreen).function_to_execute, "cmdShowResultScreen" );
    cmdDataForShowResultScreen->data = graph_window;
    cmdDataForShowResultScreen->the_map = the_map;
    strcpy( (*cmdDataForSetProgramOptions).function_to_execute, "cmdSetProgramOptions" );
    cmdDataForSetProgramOptions->data = the_program_state;
    cmdDataForSetProgramOptions->the_map = the_map;
    
    //--- Create the menu bar. ---
    
    group = gtk_accel_group_new();
    menubar = gtk_menu_bar_new();
    file = gtk_menu_item_new_with_label("File");
    edit = gtk_menu_item_new_with_label("Edit");
    selforganizingmap = gtk_menu_item_new_with_label("SOM");
    utilities = gtk_menu_item_new_with_label("Utilities");
    extras = gtk_menu_item_new_with_label("Extras");
    windows = gtk_menu_item_new_with_label("Windows");
    help = gtk_menu_item_new_with_label("Help");
    filemenu = gtk_menu_new();
    editmenu = gtk_menu_new();
    sommenu = gtk_menu_new();
    utilitymenu = gtk_menu_new();
    extrasmenu = gtk_menu_new();
    windowsmenu = gtk_menu_new();
    helpmenu = gtk_menu_new();

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(file), filemenu);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(edit), editmenu);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(selforganizingmap), sommenu);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(utilities), utilitymenu);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(extras), extrasmenu);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(windows), windowsmenu);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(help), helpmenu);

    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), edit);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), selforganizingmap);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), utilities);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), extras);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), windows);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), help);

    /* Create the File menu content. */

    new = gtk_menu_item_new_with_label("new");
    g_object_set_data(G_OBJECT(new), "menuhint",(gpointer) "Establishes a new SOM");
    open = gtk_menu_item_new_with_label("open");
    g_object_set_data(G_OBJECT(open), "menuhint",(gpointer) "Opens an existing SOM");
    save_som = gtk_menu_item_new_with_label("save the net");
    g_object_set_data(G_OBJECT(save_som), "menuhint",(gpointer) "Saves the actual SOM to file");
    save_som_as = gtk_menu_item_new_with_label("save the SOM as ...");
    g_object_set_data(G_OBJECT(save_som_as), "menuhint",(gpointer) "Saves the actual SOM to file");
    sep1 = gtk_separator_menu_item_new ();
    exit_program = gtk_menu_item_new_with_label("exit");
    g_object_set_data(G_OBJECT(exit_program), "menuhint",(gpointer) "Leaves and close the program");
    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), new);
    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), open);
    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), save_som);
    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), save_som_as);
    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), exit_program);

    /* Create the Edit menu content. */

    cut = gtk_menu_item_new_with_label("cut");
    copy = gtk_menu_item_new_with_label("copy");
    paste = gtk_menu_item_new_with_label("paste");
    gtk_menu_shell_append(GTK_MENU_SHELL(editmenu), cut);
    gtk_menu_shell_append(GTK_MENU_SHELL(editmenu), copy);
    gtk_menu_shell_append(GTK_MENU_SHELL(editmenu), paste);

    /* Create the Neural-Net menu content. */

    setup = gtk_menu_item_new_with_label("Setup SOM");
    g_object_set_data(G_OBJECT(setup), "menuhint",(gpointer) "setup the SOM");
    //---
    sep2 = gtk_separator_menu_item_new ();
    train = gtk_menu_item_new_with_label("Train SOM");
    g_object_set_data(G_OBJECT(train), "menuhint",(gpointer) "train the SOM");
    pause_training = gtk_menu_item_new_with_label("Pause Training");
    g_object_set_data(G_OBJECT(pause_training), "menuhint",(gpointer) "pause training");
    stop_training = gtk_menu_item_new_with_label("Stop Training");
    g_object_set_data(G_OBJECT(stop_training), "menuhint",(gpointer) "stop training");
    continue_training = gtk_menu_item_new_with_label("Continue Training");
    g_object_set_data(G_OBJECT(continue_training), "menuhint",(gpointer) "continue training");
    //---
    sep1 = gtk_separator_menu_item_new ();
    cluster = gtk_menu_item_new_with_label("Cluster an input");
    g_object_set_data(G_OBJECT(cluster), "menuhint",(gpointer) "cluster an input");
    gtk_menu_shell_append(GTK_MENU_SHELL(sommenu), setup);
    gtk_menu_shell_append(GTK_MENU_SHELL(sommenu), sep2);
    gtk_menu_shell_append(GTK_MENU_SHELL(sommenu), train);
    gtk_menu_shell_append(GTK_MENU_SHELL(sommenu), pause_training);
    gtk_menu_shell_append(GTK_MENU_SHELL(sommenu), stop_training);
    gtk_menu_shell_append(GTK_MENU_SHELL(sommenu), continue_training);
    gtk_menu_shell_append(GTK_MENU_SHELL(sommenu), sep1);
    gtk_menu_shell_append(GTK_MENU_SHELL(sommenu), cluster);
    
    // Create the Utility-Net menu content.

    // Create the Extras menu content.

    set_program_options = gtk_menu_item_new_with_label("Set Program Options");
    g_object_set_data(G_OBJECT(set_program_options), "menuhint",(gpointer) "sets options for the behaviore of the program");
    gtk_menu_shell_append(GTK_MENU_SHELL(extrasmenu), set_program_options);

    // Create the Windows menu content.

    show_error_diagram = gtk_menu_item_new_with_label("Show Diagram");
    g_object_set_data(G_OBJECT(show_error_diagram), "menuhint",(gpointer) "show result screen");
    gtk_menu_shell_append(GTK_MENU_SHELL(windowsmenu), show_error_diagram);
    
    // Create the Help menu content.

    contents = gtk_menu_item_new_with_label("contents");
    g_object_set_data(G_OBJECT(contents), "menuhint",(gpointer) "show the help content");
    about = gtk_menu_item_new_with_label("about");
    g_object_set_data(G_OBJECT(about), "menuhint",(gpointer) "show about dialog");
    gtk_menu_shell_append(GTK_MENU_SHELL(helpmenu), contents);
    gtk_menu_shell_append(GTK_MENU_SHELL(helpmenu), about);

	//--- Connect signals

	// Show open dialog when opening a file

    g_signal_connect (new, "activate", G_CALLBACK (on_command), cmdDataForNewSOM);
    g_signal_connect (new, "enter-notify-event", G_CALLBACK (statusbar_hint), statusbar);
    g_signal_connect (new, "leave-notify-event", G_CALLBACK (statusbar_hint), statusbar);
    g_signal_connect (open, "activate", G_CALLBACK (on_command), cmdDataForLoadSOM);
    g_signal_connect (open, "enter-notify-event", G_CALLBACK (statusbar_hint), statusbar);
    g_signal_connect (open, "leave-notify-event", G_CALLBACK (statusbar_hint), statusbar);
    g_signal_connect (save_som, "activate", G_CALLBACK (on_command), cmdDataForSaveSOM);
    g_signal_connect (save_som, "enter-notify-event", G_CALLBACK (statusbar_hint), statusbar);
    g_signal_connect (save_som, "leave-notify-event", G_CALLBACK (statusbar_hint), statusbar);
    g_signal_connect (save_som_as, "activate", G_CALLBACK (on_command), cmdDataForSaveSOMAs);
    g_signal_connect (save_som_as, "enter-notify-event", G_CALLBACK (statusbar_hint), statusbar);
    g_signal_connect (save_som_as, "leave-notify-event", G_CALLBACK (statusbar_hint), statusbar);
    
    // SOM signals
    
    g_signal_connect (setup, "activate", G_CALLBACK (on_command), cmdDataForSetupTheSOM);
    g_signal_connect (setup, "enter-notify-event", G_CALLBACK (statusbar_hint), statusbar);
    g_signal_connect (setup, "leave-notify-event", G_CALLBACK (statusbar_hint), statusbar);
    g_signal_connect (train, "activate", G_CALLBACK (on_command), cmdDataForTrainTheSOM);
    g_signal_connect (train, "enter-notify-event", G_CALLBACK (statusbar_hint), statusbar);
    g_signal_connect (train, "leave-notify-event", G_CALLBACK (statusbar_hint), statusbar);
    g_signal_connect (pause_training, "activate", G_CALLBACK (on_command), cmdDataForPauseTrainTheSOM);
    g_signal_connect (pause_training, "enter-notify-event", G_CALLBACK (statusbar_hint), statusbar);
    g_signal_connect (pause_training, "leave-notify-event", G_CALLBACK (statusbar_hint), statusbar);
    g_signal_connect (stop_training, "activate", G_CALLBACK (on_command), cmdDataForStopTrainTheSOM);
    g_signal_connect (stop_training, "enter-notify-event", G_CALLBACK (statusbar_hint), statusbar);
    g_signal_connect (stop_training, "leave-notify-event", G_CALLBACK (statusbar_hint), statusbar);
    g_signal_connect (continue_training, "activate", G_CALLBACK (on_command), cmdDataForContinueTrainTheSOM);
    g_signal_connect (continue_training, "enter-notify-event", G_CALLBACK (statusbar_hint), statusbar);
    g_signal_connect (continue_training, "leave-notify-event", G_CALLBACK (statusbar_hint), statusbar);
    
    // Utilities menu signals
    
    // Extras menu signals
    
    g_signal_connect (set_program_options, "activate", G_CALLBACK (on_command), cmdDataForSetProgramOptions);
    g_signal_connect (set_program_options, "enter-notify-event", G_CALLBACK (statusbar_hint), statusbar);
    g_signal_connect (set_program_options, "leave-notify-event", G_CALLBACK (statusbar_hint), statusbar);

    // Window menu signals
    
    g_signal_connect (show_error_diagram, "activate", G_CALLBACK (on_command), cmdDataForShowResultScreen);
    g_signal_connect (show_error_diagram, "enter-notify-event", G_CALLBACK (statusbar_hint), statusbar);
    g_signal_connect (show_error_diagram, "leave-notify-event", G_CALLBACK (statusbar_hint), statusbar);

    // Help menu signals
    
    g_signal_connect (contents, "activate", G_CALLBACK (on_command), cmdDataForHelpContent);
    g_signal_connect (contents, "enter-notify-event", G_CALLBACK (statusbar_hint), statusbar);
    g_signal_connect (contents, "leave-notify-event", G_CALLBACK (statusbar_hint), statusbar);
    g_signal_connect (about, "activate", G_CALLBACK (on_command), cmdDataForAbout);
    g_signal_connect (about, "enter-notify-event", G_CALLBACK (statusbar_hint), statusbar);
    g_signal_connect (about, "leave-notify-event", G_CALLBACK (statusbar_hint), statusbar);
   

	// Exit when the window is closed

    g_signal_connect (exit_program, "activate", G_CALLBACK (gtk_main_quit), NULL);
    g_signal_connect (exit_program, "enter-notify-event", G_CALLBACK (statusbar_hint), statusbar);
    g_signal_connect (exit_program, "leave-notify-event", G_CALLBACK (statusbar_hint), statusbar);

	return menubar;
}
