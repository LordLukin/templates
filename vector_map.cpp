// #include <complex>
#include <vector>
#include <iterator>
#include <iostream>
#include <algorithm>

// template <typename A, typename B>
// std::complex<A> makeComplex(A first, B second)
// {
//     return std::complex<A>(first, second);
// }

template <typename Key, typename Value>
class VectorMap
{
    std::vector<Key> keys;
    std::vector<Value> values;

public:
    void insert(Key key, Value value)
    {
        keys.emplace_back(key);
        values.emplace_back(value);
    }

    Value& operator[](Key key)
    {
        auto iterator = std::find(keys.begin(), keys.end(), key);
        if (iterator == keys.end())
        {
            keys.emplace_back(key);
            values.emplace_back(Value{});
            return values.back();
        }
        auto index = std::distance(keys.begin(), iterator);
        return values[index];
    }

    Value& at(Key key)
    {
        auto iterator = std::find(keys.begin(), keys.end(), key);
        if (iterator == keys.end())
        {
            throw std::invalid_argument("Key does not exist");
        }
        else
        {
            auto index = std::distance(keys.begin(), iterator);
            return values[index];
        }
    }
};

int main() {
    VectorMap<int, char> map;
    map.insert(1, 'c');
    map[1] = 'e';  // replaces value under 1
    map[10] = 'g';  // replaces value under 1
    std::cout << map[1];  // prints 'e'
    std::cout << map[10];  // prints 'e'
    map.at(2); // throw std::out_of_range
    return 0;
}