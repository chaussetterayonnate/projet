#ifndef NEURONAL_NETWORK_H_
# define NEURONAL_NETWORK_H_

typedef struct __attribute__((packed))
{
  /*Hyperparameters */
  int                 _input;
  int                 _output;
  int                 _hidden;

  float                *bias_1a;
  float                *bias_1b;
  float                *bias_2;

  /*list of weights of synapses between
    input a and the hidden layer
   */
  float               *weight_1a;

  /*list of weights of synapses between
   input b and the hidden layer*/
  float               *weight_1b;

  /*list of weights of synapses between
   the hidden layer and the output*/
  float               *weight_2;

  float               *z1_00;
  float               *z1_01;
  float               *z1_10;
  float               *z1_11;

  float               *z2;

}                     NeuralNetworkInit;

//FUNCTIONS PROTOTYPES

NeuralNetworkInit            *init_network(void);

#endif /* !NEURONAL_NETWORK_H_ */
