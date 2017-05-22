#include <iostream>
#include "perceptron.cc"
int main()
{
   Perceptron<2> or_percep;
   //answer x0 x1
   std::vector<std::bitset<3>> and_train = {
       std::bitset<3>("000"),
       std::bitset<3>("010"),
       std::bitset<3>("001"),
       std::bitset<3>("111")
   };
   bool result = or_percep.DoTrain(and_train);
   if(result)
       std::cout << "traind" << std::endl;
   else
       std::cout << "not trained" <<std::endl;
}
