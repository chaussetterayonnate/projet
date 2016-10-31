#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "NeuronalNetwork.h"

#define random()         (float)rand()/(float)(RAND_MAX)
#define expo(z)          exp(-(double)z)
#define sigmoid(z)       (1. / (1. + expo(z))
#define sigmoidDer(z)    ((float)(z)*(1.-z))

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

void forward(NeuralNetworkInit *net, int *a, int *b)
{
  /*list of hidden neurons for
   the test a = 0, b=0*/
  float        *z1_00;
  //same for different a & b
  float        *z1_01;
  float        *z1_10;
  float        *z1_11;

  z1_00 = malloc(4*sizeof(float));
  z1_01 = malloc(4*sizeof(float));
  z1_10 = malloc(4*sizeof(float));
  z1_11 = malloc(4*sizeof(float));

  
  for(size_t i = 0; i < 4; i++)
    {
      *(z1_00 + i) = sigmoid(((*(a+i)) * (*(net->weight_1a + i)) + net->bias) +
			     ((*(b+i)) * (*(net->weight_1b + i)) + net->bias)));
      *(z1_01 + i) = sigmoid(((*(a+i)) * (*(net->weight_1a + i)) + net->bias) +
			     ((*(b+i)) * (*(net->weight_1b + i)) + net->bias)));
      *(z1_10 + i) = sigmoid(((*(a+i)) * (*(net->weight_1a + i)) + net->bias) +
			     ((*(b+i)) * (*(net->weight_1b + i)) + net->bias)));
      *(z1_11 + i) = sigmoid(((*(a+i)) * (*(net->weight_1a + i)) + net->bias) +
			     ((*(b+i)) * (*(net->weight_1b + i)) + net->bias)));
    }
  printf("z1_00 = ");
  for(size_t j = 0; j < 4; j++)
    {
      printf("%.2f, ",*(z1_00+j));
    }
}

int main(void)
{
  NeuralNetworkInit    *ne = init_network();
  if (!ne)
    return -1;
  
  int *a;
  int *b;
  a = malloc(4*sizeof(int));
  b = malloc(4*sizeof(int));

  *a = 0;
  *b = 0;
  *(a+1) = 0;
  *(b+1) = 1;
  *(a+2) = 1;
  *(b+2) = 0;
  *(a+3) = 1;
  *(b+3) = 1;

  forward(ne,a,b);
  
  free(ne);
  free(a);
  free(b);
  return EXIT_SUCCESS;
}
