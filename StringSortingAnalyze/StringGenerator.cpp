#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <ctime>

class StringGenerator {
private:
    const std::string charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#%:;^&*()-.";
    std::mt19937 gen;

public:
    StringGenerator() : gen(std::random_device{}()) {}

    // Генерация случайной строки заданной длины
    std::string generate_random_string(size_t length) {
        std::uniform_int_distribution<> dist(0, charset.size() - 1);
        std::string result;
        for (size_t i = 0; i < length; ++i) {
            result += charset[dist(gen)];
        }
        return result;
    }

    // Генерация массива случайных строк
    std::vector<std::string> generate_random_array(size_t count, size_t min_len = 10, size_t max_len = 200) {
        std::uniform_int_distribution<size_t> len_dist(min_len, max_len);
        std::vector<std::string> result;
        for (size_t i = 0; i < count; ++i) {
            result.push_back(generate_random_string(len_dist(gen)));
        }
        return result;
    }

    // Генерация отсортированного массива
    std::vector<std::string> generate_sorted_array(size_t count, size_t min_len = 10, size_t max_len = 200) {
        auto arr = generate_random_array(count, min_len, max_len);
        std::sort(arr.begin(), arr.end());
        return arr;
    }

    // Генерация обратно отсортированного массива
    std::vector<std::string> generate_reverse_sorted_array(size_t count, size_t min_len = 10, size_t max_len = 200) {
        auto arr = generate_random_array(count, min_len, max_len);
        std::sort(arr.begin(), arr.end(), std::greater<std::string>());
        return arr;
    }

    // Генерация почти отсортированного массива
    std::vector<std::string> generate_almost_sorted_array(size_t count, size_t min_len = 10, size_t max_len = 200, size_t swaps = 10) {
        auto arr = generate_sorted_array(count, min_len, max_len);
        std::uniform_int_distribution<size_t> dist(0, count - 1);

        for (size_t i = 0; i < swaps; ++i) {
            size_t a = dist(gen);
            size_t b = dist(gen);
            std::swap(arr[a], arr[b]);
        }
        return arr;
    }
};