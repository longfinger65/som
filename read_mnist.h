#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef READ_MNIST_H_
#define READ_MNIST_H_

#ifdef MNIST_DOUBLE
#define MNIST_DATA_TYPE double
#else
#define MNIST_DATA_TYPE unsigned char
#endif

typedef struct mnist_data {
    
	MNIST_DATA_TYPE data[28][28]; /* 28x28 data for the image */
	unsigned int label; /* label : 0 to 9 */
    
} mnist_data;

static unsigned int mnist_bin_to_int(char *v);
int mnist_load(const char *image_filename, const char *label_filename, mnist_data **data, unsigned int *count, unsigned int *start, unsigned int *stop);

#endif /* READ_MNIST_H_ */
