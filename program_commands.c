#include "/home/pi/projects/filter_test_002/program_commands.h"

extern GtkWidget *my_image;
extern GdkPixbuf *pixbufImage;
extern mnist_data image_data;
extern unsigned char char_pixel[28][28];
extern char about_text[];
extern void filter_image(GdkPixbuf *pixbuf, int x, int y, guchar red, guchar green, guchar blue, guchar alpha);


int setup_neural_net(mnist_data **dat){

    /****************************************************************
    *
    * Function name: setup_neural_net
    * Function purpose: Setup/change the topology of the neural net
    * Input parameter:
    *               me -
    *               v -
    * Return parameter:
    *               ret -
    *
    *****************************************************************/

    //--- Variables ---

    int i, j;
    unsigned char ***input_maps;
	int return_code;

    //--- Initial settings ---

    return_code = 0;

    // ---

    //input_maps = calloc(4, sizeof *input_maps);
    if((input_maps = calloc(4, sizeof *input_maps))==NULL){
        return 1;
    }else{
        for (i=0; i<4; i++){
            //input_maps[i] = calloc(28, sizeof **input_maps);
            if((input_maps[i] = calloc(28, sizeof **input_maps))==NULL){
                // Free the memory that was allocatet untill now
                for(int k=0; k<i; k++){
                    free(input_maps[k]);
                }
                free(input_maps);
                return 1;
            }
        }
        for (i=0; i<4; i++){
            for (j=0; j<28; j++){
                //input_maps[i][j] = calloc(28, sizeof ***input_maps);
                if((input_maps[i][j] = calloc(28, sizeof ***input_maps))==NULL){
                    // Free the memory that was allocatet untill now
                    for(int k=0; k<28; k++){
                        for(int l=0; l<j; l++){
                            free(input_maps[k][l]);
                        }
                        free(input_maps[k]);
                    }
                    free(input_maps);
                    return 1;
                }
            }
        }
    }
    //return 2;
     for (int k=0; k<4; k++){
        for(int l=0; l<28; l++){
            for(int m=0; m<28; m++){
                input_maps[k][l][m] = dat[k]->data[l][m];
            }
        }
    }
   
    for (int k=0; k<4; k++){
        for(int l=0; l<28; l++){
            for(int m=0; m<28; m++){
                printf(", %u", input_maps[k][l][m]);
            }
        }
    }
    //return 3;
    for(int k=0; k<4; k++){
        for(int l=0; l<28; l++){
            free(input_maps[k][l]);
        }
        free(input_maps[k]);
    }
    free(input_maps);

    

	return return_code;

}
