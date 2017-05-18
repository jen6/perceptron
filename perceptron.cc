#include <iostream>
#include <array>
#include <bitset>
#include <cstdlib>
#include <vector>
#include <ctime>

const int kDefaultTrainMax = 2000;
const float kWeightUpdate = 0.005f;

float FloatRand() {
    static bool flag = false;
    if(!flag) {
        std::srand(static_cast<unsigned>(std::time(0)));
        flag = true;
    }
    float r = 
        static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
    r = r/1.0f;
    r -= 0.5f;
    return r;
}

template<std::size_t SIZE>
class Perceptron {
private:
    std::array<float, SIZE> weights;
    const int x0 = -1;
    float w0;
public:
    Perceptron() { 
         
    }
    /*
     * bitset 0 ~ SIZE-2 are variables
     * bitset SIZE-1 is result
    */
    bool DoTrain(const std::vector<std::bitset<SIZE>> &testCase){ 
        return DoTrain(kDefaultTrainMax, testCase); 
    }
    bool DoTrain(int maxcount, 
                 const std::vector<std::bitset<SIZE>> &train_data){
        auto ExceptAnswer = [](const std::bitset<SIZE> &data){
            std::bitset<SIZE -1> buf; 
            for(auto i = 0; i < data.size - 1; ++i) 
                buf[i] = data[i];

            return buf;
        };

        while(maxcount) {
            for(const auto &d : train_data) {
                bool result = Run(ExceptAnswer(d));
                if(result == d[SIZE-1]) 
                    continue;
                int retsign = (d[SIZE-1] - result);
                weights[0] += kWeightUpdate * x0 * retsign;

                //w0-x0, w1-d0, w2-d1, .... , wn-d(n-1)
                for(auto j = 1; j < SIZE-1; ++j) 
                    weights[j] += kWeightUpdate * d[j-1] * retsign;
            }
            --maxcount;
        }
        if (maxcount == 0)
            return false;
    }

    bool Run(const std::bitset<SIZE> &data) const {
        float net = 0.0f;
        for(auto i = 0; i < data.size(); ++i) {
            net += data[i] * weights[i];
        }
        
        if(net > 0.000000f) 
            return true;
        else
            return false;
    }
};

int main()
{
}
