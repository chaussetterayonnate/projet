#include <stdio.h>
#include <stdlib.h>

#include "NeuronalNetwork.h"

#define random() (float)rand()/(float)(RAND_MAX)

NeuralNetworkInit     *init_network(void)
{
NeuralNetworkInit *net;

net = malloc(sizeof(NeuralNetworkInit));

 if(net == NULL)
   {
     perror("init_network :");
     return NULL;
   }

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

printf("bias = %.2f\n", net->bias);

 printf("weight_1a = =");
for(size_t j = 0; j < 4; j++)
  {
    printf("%.2f\n", *(net->weight_1a + j));
  }
 return net;
}

int main(void)
{
  NeuralNetworkInit    *ne = init_network();
  if (!ne)
    return -1;
  free(ne);
  return EXIT_SUCCESS;
}
