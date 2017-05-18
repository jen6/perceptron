#include <iostream>
#include <array>
#include <bitset>
#include <cstdlib>
#include <vector>
#include <ctime>

const int kDefaultTrainMax = 2000;

float FloatRand() {
    static bool flag = false;
    if(!flag) {
        std::srand(static_cast<unsigned>(std::time(0)));
        flag = true;
    }
    float r = 
        static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX/0.5f);
    return r;
}

template<std::size_t SIZE>
class Perceptron {
private:
    float learning_rate = 0.05f;
    std::array<float, SIZE> weights;
    const int x0 = -1;
public:
    Perceptron() { 
        for(auto i = 0; i < SIZE; ++i){
            weights[i] = FloatRand();
            std::cout << "w" << i << " : " << weights[i] << std::endl;
        }
        std::cout << "---init---" << std::endl;
    }
    
    /*
     * bitset 1 ~ SIZE-2 are variables
     * bitset 0 is result
    */
    bool DoTrain(const std::vector<std::bitset<SIZE>> &testCase){ 
        return DoTrain(kDefaultTrainMax, testCase); 
    }
    bool DoTrain(int maxcount, 
                 const std::vector<std::bitset<SIZE>> &train_data){
        auto ExceptAnswer = [](const std::bitset<SIZE> &data){
            std::bitset<SIZE -1> buf; 
            for(auto i = 0; i < data.size() - 1; ++i) 
                buf[i] = data[i];

            return buf;
        };

        while(maxcount) {
            bool break_flag = true;
                std::cout << "------round" << maxcount <<"----------" << std::endl;
            for(const auto &d : train_data) {
                std::cout << "----------------" << std::endl;
                bool result = Run(ExceptAnswer(d));
                std::cout << weights[0] <<", " << weights[1] << ", " <<
                    weights[2] << std::endl;
                std::cout << d[0] <<", " << d[1] << " : " << result << std::endl;
                if(result == d[SIZE-1]) 
                    continue;

                break_flag = false;
                int retsign = (d[SIZE-1] - result);
                weights[0] += learning_rate * x0 * retsign;
                //w0-x0, w1-d0, w2-d1, .... , wn-d(n-1)
                for(auto j = 1; j < SIZE-1; ++j) {
                    weights[j] += learning_rate * d[j-1] * retsign;
                }
            }

            //if result is all right
            if(break_flag)
                break;

            --maxcount;
        }

        std::cout << "-----final weights------" << std::endl;
        for(auto i = 0; i < SIZE; ++i){
            std::cout << "w" << i << " : " << weights[i] << std::endl;
        }
        if (maxcount == 0)
            return false;
    }

    bool Run(const std::bitset<SIZE-1> &data) const {
        float net = 0.0f;
        net += x0 * weights[0];
        for(auto i = 0; i < data.size(); ++i) {
            net += data[i] * weights[i+1];
        }

        if(net > 0.00f) 
            return true;
        else
            return false;
    }
};

int main()
{
   Perceptron<3> or_percep;
   //answer x0 x1
   std::vector<std::bitset<3>> and_train = {
       std::bitset<3>("000"),
       std::bitset<3>("010"),
       std::bitset<3>("001"),
       std::bitset<3>("111")
   };
   bool result = or_percep.DoTrain(and_train);
   if(result)
       std::cout << "Oh yea!" << std::endl;
   else
       std::cout << "fuck" <<std::endl;
}
