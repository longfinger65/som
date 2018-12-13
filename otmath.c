#include "/home/pi/projects/filter_test_002/otmath.h"


int dot_product(double *v1, int size_of_v1, double *v2, int size_of_v2, double * result){

    /****************************************************************
    *
    * Function name: mnist_bin_to_int
    * Function purpose:
    * Input parameter:
    *               me -
    *               v -
    * Return parameter:
    *               ret -
    *
    *****************************************************************/

    //--- Variables ---

	int return_code;

    //--- Initial settings ---

    return_code = 0;

    // ---



	return return_code;
}

int convolve(double ***map, int map_number_of_columns, int map_number_of_rows, double ***filter_kernel, int width_of_filter_kernel, double ***map_convolved, int padding, int stride){

    /****************************************************************
    *
    * Function name: mat_mul
    * Function purpose: Multiplies to matrixes and stores the result where mat_result is pointing to.
    * Input parameter:
    *               me -
    *               padding - 	0 if no padding,
    * 							1 if padded with zeros
    * Return parameter:
    *               return_code - type = int,
    * 									0 = "ok",
    * 									1 = "filter kernel too big for map",
    *                               	2 = "Not a valid image file",
    *                               	3 = "Not a valid label file"
    *
    *****************************************************************/

    //--- Confirmation of parameters ---
    printf("red value = test");
	switch(padding) {
		case 0:
			if(width_of_filter_kernel>(map_number_of_columns-stride-1)||width_of_filter_kernel>(map_number_of_rows-stride-1)||stride==0){
				return 1;
			}
		break;
		case 1:
			if(width_of_filter_kernel>(map_number_of_columns-stride)||width_of_filter_kernel>(map_number_of_rows-stride)||stride==0){
				return 1;
			}
		break;
	}

    //--- Variables ---

	int return_code;
    int size_of_padding;
    double **filter = *filter_kernel;
    double **map_unconv = *map;
    double **map_conv = *map_convolved;

    //--- Initial settings ---

    return_code = 0;
    size_of_padding = width_of_filter_kernel / 2;

    //---

	switch(padding) {
		case 0:
			for(int y=0; y<(map_number_of_rows-width_of_filter_kernel); y+=stride){
				for(int x=0; x<(map_number_of_columns-width_of_filter_kernel); x+=stride){
					for(int j=0; j<(width_of_filter_kernel); j++){
						for(int i=0; i<(width_of_filter_kernel); i++){
							*map_convolved[x][y] += (*map[x][y]) * (*filter_kernel[i][j]);
						}
					}
				}
			}
		break;
		case 1:
            //printf("red value = test");
			for(int y=0; y<map_number_of_rows; y+=stride){
				for(int x=0; x<map_number_of_columns; x+=stride){
					for(int j=0; j<width_of_filter_kernel; j++){
						for(int i=0; i<width_of_filter_kernel; i++){
                            if(((x-size_of_padding+i)>=0)&&((y-size_of_padding+j)>=0)&&((x-size_of_padding+i)<map_number_of_columns)&&((y-size_of_padding+j)<map_number_of_rows)){
                                map_conv[x][y] += map_unconv[x-size_of_padding+i][y-size_of_padding+j] * filter[i][j];
                                //printf("Filter value = %f",filter[i][j]);
                            }
						}
					}
				}
			}
		break;
	}

    return return_code;
}

int normalize_map(double ***map, int map_number_of_columns, int map_number_of_rows, double lower_normalization_limit, double upper_normalization_limit, double min_map_value, double max_map_value){

	    /****************************************************************
    *
    * Function name: mat_mul
    * Function purpose: Multiplies to matrixes and stores the result where mat_result is pointing to.
    * Input parameter:
    *               me -
    *               padding - 	0 if no padding,
    * 							1 if padded with zeros
    * Return parameter:
    *               return_code - type = int,
    * 									0 = "ok",
    * 									1 = "filter kernel too big for map",
    *                               	2 = "Not a valid image file",
    *                               	3 = "Not a valid label file"
    *
    *****************************************************************/

    //--- Confirmation of parameters ---


    //--- Variables ---

	int return_code;
    double **map_to_normalize = *map;
    
    //--- Initial settings ---

    return_code = 0;

    //---
    
    for (int x=0; x<map_number_of_columns; x++){
        for (int y=0; y<map_number_of_rows; y++){
            map_to_normalize[x][y] = (map_to_normalize[x][y] - min_map_value) * upper_normalization_limit / max_map_value;
        }
    }

    return return_code;
}

int convolve_a_matrix_2(double ***matrix_to_convolve, double ***filter_kernel, double ***convolved_matrix, int options, int border_values[2], int matrix_to_convolve_width, int matrix_to_convolve_height, int width_of_filter_kernel, int kind_of_activation, double gradient_for_relu){

    /**************************************************************************************************************************************
    *
    * Function name:                                - convolve_a_matrix_2
    *                   
    * Function purpose:
    * 
    *                                               - Convolves a matrix by a given filter_kernel. The size of the convolved matrix
    *                                                 depends on the options (padded, not padded). If the convolved_matrix matrix should
    *                                                 be normalized the normalization factor is caculated out of the border_values[1] 
    *                                                 and the kernel values. 
    * 
    * Input parameter:
    * 
    *   matrix_to_convolve          [double ***]    - The matrix that will be convolved by the filter kernel
    *   filter_kernel               [double ***]    - The filter kernel to convolve the matrix_to_convolve with
    *   convolved_matrix            [double ***]    - The matrix that holds the result
    *   options                     [int]           - read as binary
    *                                                   [values] bit 0 -    If set the convolved_matrix is the same size as the
    *                                                                   matrix_to_convolve. Therefore the matrix_to_convolve is padded
    *                                                   [values] bit 1 -    If set the convolved_matrix is normalized
    *   bordervalues                [int]           - Only used if bit 1 of options is set. 
    *                                                   border_values[0] = absolute min of matrix_to_convolve,
    *                                                   border_values[1] = absolute max of matrix_to_convolve.
    *   matrix_to_convolve_width    [int]           - The width of the matrix_to_convolve.
    *   matrix_to_convolve_height   [int]           - The height of the matrix_to_convolve
    *   width_of_filter_kernel      [int]           - The width and height of the filter_kernel.
    * 
    * Return parameter:
    * 
    *   ret_value                   [int]           - 0 = ok,
    *                                                 1 = something went wrong.
    *
    **************************************************************************************************************************************/

    //--- Definition of parameters ---

    int return_value;
    int flag_result;
    int width_of_padded_matrix;
    int height_of_padded_matrix;
    int width_of_cm;
    int height_of_cm;
    double **mtc = *matrix_to_convolve;
    double **cm = *convolved_matrix;
    double **fk = *filter_kernel;
    double normalizing_factor;  // The dot product of filter and 255 (the biggest pixel value)
    double **padded_matrix = NULL;
    double conv_result;
    double min_conv_value;
    double max_conv_value;
    int test;
    if((options & 0b00000001)!=0){
        double padded_image[matrix_to_convolve_width + width_of_filter_kernel-1][matrix_to_convolve_height + width_of_filter_kernel-1];
    }else{
        double padded_image[1][1];
    }

    //--- Initial settings ---

    return_value = 0;
    
    //---
    
    /* Set elements of padded image to 0 */
    if((options & 0b00000001)!=0){
        padded_matrix = calloc(matrix_to_convolve_width + width_of_filter_kernel-1, sizeof *padded_matrix);
        if(padded_matrix != 0){
            for(int i=0; i<(matrix_to_convolve_height + width_of_filter_kernel-1); i++){
                padded_matrix[i] = calloc(matrix_to_convolve_width + width_of_filter_kernel-1, sizeof **padded_matrix);
                if(padded_matrix[i]==0){
                    for(int j=0; j<i; j++){
                        free(padded_matrix[j]);
                    }
                    free(padded_matrix);
                    return 1;
                }
            }
        }
        width_of_padded_matrix = matrix_to_convolve_width + width_of_filter_kernel-1;
        height_of_padded_matrix = matrix_to_convolve_height + width_of_filter_kernel-1;
        for(int x=0; x<matrix_to_convolve_width; x++){
            for(int y=0; y<matrix_to_convolve_height; y++){
                padded_matrix[x - width_of_filter_kernel/2][y - width_of_filter_kernel/2] = mtc[x][y];
            }
        }
    }

    //--- Convolve the map ---
    //printf("Now Iam here.\n");
    if((options & 0b00000001)!=0){
        for(int y = y = width_of_filter_kernel/2; y<(width_of_padded_matrix - width_of_filter_kernel/2); y++){
            for(int x=width_of_filter_kernel/2; x<(height_of_padded_matrix-width_of_filter_kernel/2); x++){
                conv_result = 0;
                for(int y2=0; y2 < width_of_filter_kernel; y2++){
                    for(int x2=0; x2 < width_of_filter_kernel; x2++){
                        conv_result += padded_matrix[y+y2-width_of_filter_kernel/2][x+x2-width_of_filter_kernel/2] * fk[y2][x2];
                    }
                }
                cm[y + width_of_filter_kernel/2][x + width_of_filter_kernel/2] = conv_result;
            }
        }
    }else{
        for(int i2 = 0; i2<(matrix_to_convolve_height - width_of_filter_kernel); i2++){
            for(int j2 = 0; j2<(matrix_to_convolve_width - width_of_filter_kernel); j2++){
                conv_result = 0;
                for(int i=0; i<width_of_filter_kernel; i++){
                    for(int j=0; j<width_of_filter_kernel; j++){
                        conv_result += mtc[i2+i][j2+j] * fk[i][j];
                    }
                }
                cm[i2][j2] = conv_result;
                test = i2;
                //printf("cm[i2][j2] = %f \n", cm[i2][j2]);
                //printf("width = %d \n", j2);
            }
        }
    }
    printf("height = %d \n", test);

    //--- If normalization is choosen, normalize the convolved_matrix ---

    if((options & 0b00000010)!=0){
        min_conv_value = 0;
        max_conv_value = 0;
        //--- Calculate the min. and max. filtered value
        for(int y=0; y<width_of_filter_kernel; y++){
            for(int x=0; x<width_of_filter_kernel; x++){
                min_conv_value += border_values[0] * fk[y][x];
                max_conv_value += border_values[1] * fk[y][x];
            }
        }
        normalizing_factor = (border_values[1] - border_values[0])/ (max_conv_value - min_conv_value);
        //--- Normalize the matrix
        if((options & 0b00000001)!=0){
            width_of_cm = matrix_to_convolve_width;
            height_of_cm = matrix_to_convolve_height;
        }else{
            width_of_cm = matrix_to_convolve_width - width_of_filter_kernel + 1;
            height_of_cm = matrix_to_convolve_height  - width_of_filter_kernel + 1;            
        }

        for(int y=1; y<width_of_cm; y++){
            for(int x=1; x<height_of_cm; x++){
                cm[y][x] = cm[y][x] * normalizing_factor + border_values[0] - min_conv_value;
            }
        }
    }
    
    return return_value;
}
