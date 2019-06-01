#include <iostream>
#include <vector>
#include <tuple>
#include <cstdint>
#include <limits>

using ValueType = int64_t;
using IndexType = uint64_t;
using MaxTuple = std::tuple<IndexType, IndexType, ValueType>;

MaxTuple linearMaxSubArray(std::vector<ValueType> vec)
{
    const auto size = vec.size();

    auto maxSum = std::numeric_limits<int64_t>::min();
    auto currentSum = std::numeric_limits<int64_t>::min();

    auto maxLow = IndexType{};
    auto maxHigh = IndexType{};

    for(int i = 0; i < size; i++)
    {
        auto currSumEnd = i;
        auto currSumStart = IndexType{};
        if(currentSum > 0)
        {
            currentSum += vec[i];
        } 
        else
        {
            currSumStart = i;
            currentSum = vec[i];
        }

        if(currentSum > maxSum)
        {
            maxSum = currentSum;
            maxLow = currSumStart;
            maxHigh = currSumEnd;
        }
    }

    return MaxTuple{maxLow, maxHigh, maxSum};
}

int main()
{
    std::vector<ValueType> v = { 13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7  };

    auto result = linearMaxSubArray(v);

    auto leftIdx = std::get<0>(result);
    auto rightIdx = std::get<1>(result);
    auto sum = std::get<2>(result);

    std::cout << "Left index: " << leftIdx << std::endl;
    std::cout << "Right index: " << rightIdx << std::endl;
    std::cout << "Sum: " << sum << std::endl;

    return 0;
}
