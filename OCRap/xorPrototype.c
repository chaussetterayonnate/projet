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

printf("\nbias_1a = ");
 for(size_t j = 0; j < 4; j++)
   printf("%.2f, ", *(net->bias_1a + j));
 
 printf("\nbias_1b = ");
 for(size_t j = 0; j < 4; j++)
   printf("%.2f, ", *(net->bias_1b + j));

 printf("\nbias_2 = ");
 for(size_t j = 0; j < 4; j++)
   printf("%.2f, ", *(net->bias_2 + j));
 
 printf("\nweight_1a = ");
for(size_t j = 0; j < 4; j++)
    printf("%.2f, ", *(net->weight_1a + j));

 printf("\nweight_1b = ");
 for(size_t j = 0; j <4; j++)
   printf("%.2f, ", *(net->weight_1b + j));

 printf("\nweight_2 = ");
 for(size_t j = 0; j <4; j++)
   printf("%.2f, ", *(net->weight_2 + j));
 
 
 return net;
}

float* forward(NeuralNetworkInit *net)
{
  /*list of hidden neurons for
   the test a = 0, b=0*/
  float        *z1_00;
  //same for different a & b
  float        *z1_01;
  float        *z1_10;
  float        *z1_11;

  float        output_00 = 0;
  float        output_01 = 0;
  float        output_10 = 0;
  float        output_11 = 0;
  
  float        *output;

  z1_00 = malloc(4*sizeof(float));
  z1_01 = malloc(4*sizeof(float));
  z1_10 = malloc(4*sizeof(float));
  z1_11 = malloc(4*sizeof(float));

  output = malloc(4*sizeof(float));

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

  for(size_t i = 0; i < 4; i++)
    {
      output_00 += *(z1_00 +i)*(*(net->weight_2 +i))
	+ *(net->bias_2 +i);
      output_01 += *(z1_01 +i)*(*(net->weight_2 +i))
	+ *(net->bias_2 +i);
      output_10 += *(z1_10 +i)*(*(net->weight_2 +i))
	+ *(net->bias_2 +i);
      output_11 += *(z1_11 +i)*(*(net->weight_2 +i))
	+ *(net->bias_2 +i);
    }

  *output   = sigmoid(output_00);
  *(output+1)= sigmoid(output_01);
  *(output +2) = sigmoid(output_10);
  *(output +3) = sigmoid(output_11);
  
  printf("\n00 : %.2f \n", output_00);
  printf("01 : %.2f \n", output_01);
  printf("10 : %.2f \n", output_10);
  printf("11 : %.2f \n", output_11);

  return output;
}

float * costFunction(float *output)
{
  float *cost;
  cost = malloc(4 * sizeof(float));

  *cost = pow(*output,2)/2;
  *(cost+1) = pow(1 - *(output+1),2)/2;
  *(cost+2) = pow(1 - *( output+2),2)/2;
  *(cost+3) = pow(*(output+3),2)/2;

  printf("\ncost = ");
  for(size_t i = 0; i <4; i++)
    printf("%.5f, ", *(cost+i));
  
  return cost;
}

/*float * deriv_w2(NeuralNetworkInit net, float *output)
{
  
}

float * deriv_b2(NeuralNetworkInit net, float *output)
{}

float * deriv_w1(NeuralNetworkInit net, float *output)
{}

float * deriv_b1(NeuralNetworkInit net, float *output)
{}*/



int main(void)
{
  NeuralNetworkInit    *ne = init_network();
  if (!ne)
    return -1;
  
  float *output;
  output = malloc(4*sizeof(float));

  output = forward(ne);
  costFunction(output);
  
  free(ne);
  free(output);
  return EXIT_SUCCESS;
}
