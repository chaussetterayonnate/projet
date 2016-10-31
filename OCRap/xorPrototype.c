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

float sigDer ( float z)
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

 net->z1_00 = malloc(4 * sizeof(float));
 net->z1_01 = malloc(4 * sizeof(float));
 net->z1_10 = malloc(4 * sizeof(float));
 net->z1_11 = malloc(4 * sizeof(float));

 net->z2 = malloc(4 * sizeof(float));
 
for(size_t i = 0; i < 4; i++)
  {
    *(net->weight_1a + i) = random();
    *(net->weight_1b + i) = random();
    *(net->weight_2 + i) = random();

    *(net->bias_1a + i) = random()*2 - 1;
    *(net->bias_1b + i) = random()*2 - 1;
    *(net->bias_2 + i) = random()*2 - 1;

    *(net->z1_00 +i) = 0;
    *(net->z1_01 +i) = 0;
    *(net->z1_10 +i) = 0;
    *(net->z1_11 +i) = 0;

    *(net->z2 +i) = 0;
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
  float        *a1_00;
  //same for different a & b
  float        *a1_01;
  float        *a1_10;
  float        *a1_11;
  
  float        *output;

  a1_00 = malloc(4*sizeof(float));
  a1_01 = malloc(4*sizeof(float));
  a1_10 = malloc(4*sizeof(float));
  a1_11 = malloc(4*sizeof(float));

  output = malloc(4*sizeof(float));

  for(size_t i = 0; i < 4; i++)
    {
      
      *(net->z1_00 + i) = (*(net->bias_1a +i) + *(net->bias_1b +i));
      *(a1_00 +i) = sigmoid(*(net->z1_00 +i));
	
      *(net->z1_01 + i) = (*(net->bias_1a +i)
			      + *(net->weight_1b + i)
			     + *(net->bias_1b + i));
      *(a1_01 +i) = sigmoid(*(net->z1_01 +i));
			    
      *(net->z1_10 + i) = (*(net->weight_1a + i)
			     + *(net->bias_1a + i)
			     + *(net->bias_1b + i));
      *(a1_10 +i) = sigmoid(*(net->z1_10 +i));
      
      *(net->z1_11 + i) = (*(net->weight_1a + i)
			     + *(net->bias_1a + i)
			     + *(net->weight_1b + i)
	                     + *(net->bias_1b + i));
      *(a1_11 +i) = sigmoid(*(net->z1_11 +i));
      
    }
  
  printf("\na1_00 = ");
  for(size_t j = 0; j < 4; j++)
      printf("%.2f, ",*(a1_00+j));

  printf("\na1_01 = ");
  for (size_t j = 0; j < 4; j++)
    printf("%.2f, ",*(a1_01+j));

  printf("\na1_10 = ");
  for (size_t j = 0; j < 4; j++)
    printf("%.2f, ",*(a1_01+j));

  printf("\na1_11 = ");
  for (size_t j = 0; j < 4; j++)
    printf("%.2f, ",*(a1_11+j));

  for(size_t i = 0; i < 4; i++)
    {
      *net->z2 += *(net->z1_00 +i)*(*(net->weight_2 +i))
      +  *(net->bias_2 +i);
      *(net->z2 + 1) += *(net->z1_01 +i)*(*(net->weight_2 +i))
	+ *(net->bias_2 +i);
      *(net->z2 + 2) += *(net->z1_10 +i)*(*(net->weight_2 +i))
	+ *(net->bias_2 +i);
      *(net->z2 + 3) += *(net->z1_11 +i)*(*(net->weight_2 +i))
	+ *(net->bias_2 +i);
    }

  *output   = sigmoid(*(net->z2));
  *(output+1)= sigmoid(*(net->z2+1));
  *(output +2) = sigmoid(*(net->z2+2));
  *(output +3) = sigmoid(*(net->z2+3));
  
  printf("\n00 : %.2f \n", *output);
printf("01 : %.2f \n", *(output+1));
printf("10 : %.2f \n", *(output+2));
printf("11 : %.2f \n", *(output+3));

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

float *deriv_w2(NeuralNetworkInit *net, float *output)
{
  float *w2;

  w2 = malloc(4 * sizeof(float));
  *w2 = 0;
  *(w2+1) = 0;
  *(w2+2) = 0;
  *(w2+3) = 0;
  for(size_t i  = 0; i<4; i++)
    {
      *w2 += sigmoid(*(net->z1_00 +i)) * -(*output) * sigDer(*(net->z2));

      *(w2+1) += sigmoid(*(net->z1_01 + i))
	* (-(1 - *(output + 1)))
	* sigDer(*(net->z2+1));

      *(w2+2) += sigmoid(*(net->z1_10 + i))
	* (-(1 - *(output + 2)))
	* sigDer(*(net->z2+2));

      *(w2+3) += sigmoid(*(net->z1_11 + i))
	* (-(*(output + 3)))
	* sigDer(*(net->z2+3));
    }
return w2;
}

float * deriv_b2(NeuralNetworkInit *net, float *output)
{
  float *b2;

  b2 = malloc(4 * sizeof(float));

  *b2= -(*output) * sigDer(*net->z2);
  *(b2+1) = -(1 - *(output+1)) * sigDer(*(net->z2+1));
  *(b2+2) = -(1 - *(output+2)) * sigDer(*(net->z2+2));
  *(b2+3) = -(*(output+3)) * sigDer(*(net->z2+3));
  return b2;
}

float * deriv_w1(NeuralNetworkInit *net, float *output)
{
  float *w1;

  w1 = malloc(4 * sizeof(float));
  *w1 = 0;
  *(w1+1) = 0;
  *(w1+2) = 0;
  *(w1+3) = 0;

  for(size_t i = 0; i <4; i++)
    {
      *(w1+1) += -(1-(*(output+1))) * sigDer(*(net->z1_01 + i));
      *(w1+2) += -(1-(*(output+2))) * sigDer(*(net->z1_10 + i)); 
    }
return w1;
}

float * deriv_b1(NeuralNetworkInit *net, float *output)
{
  float *b1;
  b1 = malloc(4 * sizeof(float));
  *b1 = 0;
  *(b1+1) = 0;
  *(b1+2) = 0;
  *(b1+3) = 0;

  for(size_t i = 0; i < 4; i++)
    {
      *b1 += -(*(output)) * (*(net->weight_2 + i)) * sigDer(*(net->z1_00 + i));
      *(b1+1) += -(1 - (*(output+1)))
	* (*(net->weight_2 + i))
	* sigDer(*(net->z1_01 +i));
      *(b1+2) += -(1 - (*(output+2)))
	* (*(net->weight_2 + i))
	* sigDer(*(net->z1_10 +i));
      *(b1+3) += -(*(output+3))
	* (*(net->weight_2 + i))
	* sigDer(*(net->z1_11 +i));
    }
  return b1;
}



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
