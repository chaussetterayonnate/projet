#include <stdio.h>
#include <stdlib.h>
#include "NeuronalNetwork.h"

#define random() (float)rand()/(RAND_MAX)

NeuralNetworkInit *net;

net->_input = 2;
net->_output = 1;
net->_hidden = 4;

net->bias = random();

net->weight_1a  = malloc(4 * sizeof(float));
net->weight_1b = malloc(4 * sizeof(float));
net->weight_2 = malloc(4 * sizeof(float));

for(size_t i = 0; i < 4; i++)
  {
    *(net->weight_1a + i) = random();
    *(net->weight_1b + i) = random();
    *(net->weight_2 + i) = random();
  }

printf("bias = %f.2\n", net->bias); 

printf("weight_1a = =")
for(size_t j = 0; j < 4; j++)
  {
    printf("%f ", *(net->weight_1a + j));
  }
