#ifndef NEURONAL_NETWORK_H_
# define NEURONAL_NETWORK_H_

typedef struct __attribute__((packed))
{
  /*Hyperparameters */
  int                 _input;
  int                 _output;
  int                 _hidden;

  float                bias;
  
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
  
}                     NeuralNertworkInit;



#endif /* !NEURONAL_NETWORK_H_ */
