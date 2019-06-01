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


MaxTuple bruteForceMaxSubArray(std::vector<ValueType> vec, IndexType low, IndexType high)
{
    ValueType maximum = std::numeric_limits<ValueType>::min();
    ValueType sum = ValueType{};

    IndexType lowIdx = IndexType{};
    IndexType highIdx = IndexType{};
    for (int i = 0; i <= high; i++)
    {
        sum = ValueType{};
        for (int j = i; j <= high; j++)
        {
            sum += vec[j];

            if (sum > maximum)
            {
                maximum = sum;
                lowIdx = i;
                highIdx = j;

            }

        }

    }

    return MaxTuple{ lowIdx, highIdx, maximum  };
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

    const auto now = std::chrono::system_clock::now();
    auto result = bruteForceMaxSubArray(numbers, 0, numbers.size() - 1);
    const auto after = std::chrono::system_clock::now();

    const auto elapsed_time = std::chrono::duration<double>(after - now).count();
    //const auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::duration<double>(after - now)).count();

    std::cout << "[size: " << numbers.size() << "; elapsed time: " << elapsed_time << "];" << std::endl;

    return 0;
}

