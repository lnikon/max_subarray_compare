#include <vector>
#include <iostream>
#include <tuple>
#include <cstdint>
#include <limits>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <chrono>

using ValueType = int64_t;
using IndexType = uint64_t;
using MaxTuple = std::tuple<IndexType, IndexType, ValueType>;

MaxTuple maxCorssingSubArray(std::vector<ValueType> vec, IndexType low, IndexType mid, IndexType high)
{
    ValueType leftSum = std::numeric_limits<ValueType>::min();
    ValueType sum = ValueType{};

    IndexType maxLeft = IndexType{};
    for (IndexType i = mid; i != low - 1; i--)
    {
        sum += vec[i];
        if (sum > leftSum)
        {
            leftSum = sum;
            maxLeft = i;

        }

    }

    ValueType rightSum = std::numeric_limits<ValueType>::min();
    sum = 0;

    IndexType maxRight = IndexType{};
    for (IndexType i = mid + 1; i <= high; i++)
    {
        sum += vec[i];

        if (sum > rightSum)
        {
            rightSum = sum;
            maxRight = i;

        }
    }

    return MaxTuple{ maxLeft, maxRight, leftSum + rightSum  };

}

MaxTuple maxSubarray(std::vector<ValueType> vec, IndexType low, IndexType high)
{
    if (low == high)
    {
        return MaxTuple{ low, high, vec[low]  };

    }
    else
    {
        IndexType mid = (low + high) / 2;

        MaxTuple leftPart = maxSubarray(vec, low, mid);
        ValueType lowLeft = std::get<0>(leftPart);
        ValueType highLeft = std::get<1>(leftPart);
        ValueType sumLeft = std::get<2>(leftPart);

        MaxTuple rightPart = maxSubarray(vec, mid + 1, high);
        ValueType lowRight = std::get<0>(rightPart);
        ValueType highRight = std::get<1>(rightPart);
        ValueType sumRight = std::get<2>(rightPart);

        MaxTuple crossPart = maxCorssingSubArray(vec, low, mid, high);
        ValueType lowCross = std::get<0>(crossPart);
        ValueType highCross = std::get<1>(crossPart);
        ValueType sumCross = std::get<2>(crossPart);

        if (sumLeft >= sumRight && sumLeft >= sumCross)
        {
            return MaxTuple{ lowLeft, highLeft, sumLeft  };

        }
        else if (sumRight >= sumLeft && sumRight >= sumCross)
        {
            return MaxTuple{ lowRight, highRight, sumRight  };

        }
        else
        {
            return MaxTuple{ lowCross, highCross, sumCross  };
        }

    }
}

int main(int argc, char *argv[])
{
    const std::string filename = "input_numbers.txt";
    std::ifstream csv("input_numbers.txt");
    if(!csv.is_open())
    {
        std::cerr << "Unable to open " << filename << std::endl;
        return -1;
    }
    std::istreambuf_iterator<char> iter(csv);

    std::vector<ValueType> numbers;
    std::copy(iter, std::istreambuf_iterator<char>{}, std::back_inserter(numbers));

    const auto now = std::chrono::high_resolution_clock::now();
    auto result = maxSubarray(numbers, 0, numbers.size() - 1);
    const auto after = std::chrono::high_resolution_clock::now();

    const auto elapsed_time = std::chrono::duration<double>(after - now).count();
    // const auto elapsed_time = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::duration<double>(after - now)).count();

    std::cout << "[size: " << numbers.size() << "; elapsed time: " << elapsed_time << "];" << std::endl;

    return 0;
}

