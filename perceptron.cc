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
    std::array<float, SIZE+1> weights;
    const int x0 = -1;
public:
    Perceptron() { 
        for(auto i = 0; i < SIZE+1; ++i){
            weights[i] = FloatRand();
            std::cout << "w" << i << " : " << weights[i] << std::endl;
        }
        std::cout << "---init---" << std::endl;
    }
    
    /*
     * bitset 1 ~ SIZE-2 are variables
     * bitset 0 is result
    */
    bool DoTrain(const std::vector<std::bitset<SIZE+1>> &testCase){ 
        return DoTrain(kDefaultTrainMax, testCase); 
    }
    bool DoTrain(int maxcount, 
                 const std::vector<std::bitset<SIZE+1>> &train_data){
        auto ExceptAnswer = [](const std::bitset<SIZE+1> &data){
            std::bitset<SIZE> buf; 
            for(auto i = 0; i < data.size() - 1; ++i) 
                buf[i] = data[i];

            return buf;
        };

        while(maxcount) {
            bool break_flag = true;
            for(const auto &d : train_data) {
                bool result = Run(ExceptAnswer(d));
                if(result == d[SIZE-1]) 
                    continue;

                break_flag = false;
                int retsign = (d[SIZE] - result);
                weights[0] += learning_rate * x0 * retsign;
                //w0-x0, w1-d0, w2-d1, .... , wn-d(n-1)
                for(auto j = 1; j < SIZE; ++j) {
                    weights[j] += learning_rate * d[j-1] * retsign;
                }
            }

            //if result is all right
            if(break_flag)
                break;

            --maxcount;
        }

        std::cout << "-----final weights------" << std::endl;
        for(auto i = 0; i < SIZE+1; ++i){
            std::cout << "w" << i << " : " << weights[i] << std::endl;
        }
        if (maxcount == 0)
            return false;
    }

    bool Run(const std::bitset<SIZE> &data) const {
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

