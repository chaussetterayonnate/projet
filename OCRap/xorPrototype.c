#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "NeuronalNetwork.h"

#define random()         (float)rand()/(float)(RAND_MAX)
//#define sigmoid(z)       (1. / (1. + expo(z))
//#define sigmoidDer(z)    ((float)(z)*(1.-z))

float expo (float z)
{
  double  x = (double)z;
  return (float)exp(x);
}

float sigmoid (float z)
{
  double x = (double)z;
  return (float) (1 / (1 + expo(x)));
}

float sigmoidDer ( float z)
{
  double x = (double) z;
  return (float) (x * (1 - x));
}

//double exp


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

 net->bias_1a = malloc(4 * sizeof(float));
 net->bias_1b = malloc(4 * sizeof(float));
 net->bias_2 = malloc(4 * sizeof(float));

net->weight_1a  = malloc(4 * sizeof(float));
net->weight_1b = malloc(4 * sizeof(float));
net->weight_2 = malloc(4 * sizeof(float));

for(size_t i = 0; i < 4; i++)
  {
    *(net->weight_1a + i) = random();
    *(net->weight_1b + i) = random();
    *(net->weight_2 + i) = random();

    *(net->bias_1a + i) = random()*2 - 1;
    *(net->bias_1b + i) = random()*2 - 1;
    *(net->bias_2 + i) = random()*2 - 1;
    
  }

printf("bias_1a = ");
 for(size_t j = 0; j < 4; j++)
   printf("%.2f, ", *(net->bias_1a + j));
 
 printf("bias_1b = ");
 for(size_t j = 0; j < 4; j++)
   printf("%.2f, ", *(net->bias_1b + j));

 printf("bias_2 = ");
 for(size_t j = 0; j < 4; j++)
   printf("%.2f, ", *(net->bias_2 + j));
 
 printf("weight_1a = ");
for(size_t j = 0; j < 4; j++)
    printf("%.2f, ", *(net->weight_1a + j));

 printf("\nweight_1b = ");
 for(size_t j = 0; j <4; j++)
   printf("%.2f, ", *(net->weight_1b + j));
 
 return net;
}

void forward(NeuralNetworkInit *net)
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
      
      *(z1_00 + i) = sigmoid(*(net->bias_1a +i) + *(net->bias_1b +i));

      *(z1_01 + i) = sigmoid(*(net->bias_1a +i)
			      + *(net->weight_1b + i)
			     + *(net->bias_1b + i));
      *(z1_10 + i) = sigmoid(*(net->weight_1a + i)
			     + *(net->bias_1a + i)
			     + *(net->bias_1b + i));

      *(z1_11 + i) = sigmoid(*(net->weight_1a + i)
			     + *(net->bias_1a + i)
			     + *(net->weight_1b + i)
	                     + *(net->bias_1b + i));
    }
  printf("\nz1_00 = ");
  for(size_t j = 0; j < 4; j++)
      printf("%.2f, ",*(z1_00+j));

  printf("\nz1_01 = ");
  for (size_t j = 0; j < 4; j++)
    printf("%.2f, ",*(z1_01+j));

  printf("\nz1_10 = ");
  for (size_t j = 0; j < 4; j++)
    printf("%.2f, ",*(z1_01+j));

  printf("\nz1_11 = ");
  for (size_t j = 0; j < 4; j++)
    printf("%.2f, ",*(z1_11+j));

}

int main(void)
{
  NeuralNetworkInit    *ne = init_network();
  if (!ne)
    return -1;


  forward(ne);

  free(ne);
  return EXIT_SUCCESS;
}
