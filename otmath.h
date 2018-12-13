#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifndef OTMATH_H_
#define OTMATH_H_

#define AVERAGE_POOLING                                             14
#define MAX_POOLING                                                 15
#define RELU                                                        16
#define TANH                                                        17
#define SIGMOID                                                     18


int dot_product(double *v1, int size_of_v1, double *v2,  int size_of_v2, double * result);
int convolve(double ***map, int map_number_of_columns, int map_number_of_rows, double ***filter_kernel, int size_of_filter_kernel, double ***map_convolved, int padding, int stride);
int normalize_map(double ***map, int map_number_of_columns, int map_number_of_rows, double lower_normalization_limit, double upper_normalization_limit, double min_map_value, double max_map_value);
int convolve_a_matrix_2(double ***matrix_to_convolve, double ***filter_kernel, double ***convolved_matrix, int options, int border_values[2], int matrix_to_convolve_width, int matrix_to_convolve_height, int width_of_filter_kernel, int kind_of_activation, double gradient_for_relu);

#endif /* OTMATH_H_ */
