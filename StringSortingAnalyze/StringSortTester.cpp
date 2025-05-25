#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include "StandardSorters.cpp"
#include "StringSorters.cpp"
#include "StringGenerator.cpp"
#include <fstream>
#include <iomanip>

class StringSortTester {
public:
    struct TestResult {
        std::string algorithm;
        std::string data_type;
        size_t size;
        double time_ms;
        size_t comparisons;
    };

    static TestResult run_quick_sort_test(const std::vector<std::string>& arr, const std::string& data_type) {
        TestResult result;
        result.algorithm = "QuickSort";
        result.data_type = data_type;
        result.size = arr.size();

        std::vector<std::string> arr_copy = arr;
        StandardSorters::reset_comparisons();

        auto start = std::chrono::high_resolution_clock::now();
        StandardSorters::quickSort(arr_copy, 0, arr_copy.size() - 1);
        auto end = std::chrono::high_resolution_clock::now();

        result.time_ms = std::chrono::duration<double, std::milli>(end - start).count();
        result.comparisons = StandardSorters::comparisons;

        if (!std::is_sorted(arr_copy.begin(), arr_copy.end())) {
            std::cerr << "QuickSort failed for size " << arr.size() << std::endl;
        }

        return result;
    }

    static TestResult run_merge_sort_test(const std::vector<std::string>& arr, const std::string& data_type) {
        TestResult result;
        result.algorithm = "MergeSort";
        result.data_type = data_type;
        result.size = arr.size();

        std::vector<std::string> arr_copy = arr;
        StandardSorters::reset_comparisons();

        auto start = std::chrono::high_resolution_clock::now();
        StandardSorters::mergeSort(arr_copy, 0, arr_copy.size() - 1);
        auto end = std::chrono::high_resolution_clock::now();

        result.time_ms = std::chrono::duration<double, std::milli>(end - start).count();
        result.comparisons = StandardSorters::comparisons;

        if (!std::is_sorted(arr_copy.begin(), arr_copy.end())) {
            std::cerr << "MergeSort failed for size " << arr.size() << std::endl;
        }

        return result;
    }

    static TestResult run_string_quick_sort_test(const std::vector<std::string>& arr, const std::string& data_type) {
        TestResult result;
        result.algorithm = "StringQuickSort";
        result.data_type = data_type;
        result.size = arr.size();

        std::vector<std::string> arr_copy = arr;
        StringSorters::reset_comparisons();

        auto start = std::chrono::high_resolution_clock::now();
        StringSorters::stringQuickSort(arr_copy, 0, arr_copy.size() - 1, 0);
        auto end = std::chrono::high_resolution_clock::now();

        result.time_ms = std::chrono::duration<double, std::milli>(end - start).count();
        result.comparisons = StringSorters::comparisons;

        if (!std::is_sorted(arr_copy.begin(), arr_copy.end())) {
            std::cerr << "StringQuickSort failed for size " << arr.size() << std::endl;
        }

        return result;
    }

    static TestResult run_string_merge_sort_test(const std::vector<std::string>& arr, const std::string& data_type) {
        TestResult result;
        result.algorithm = "StringMergeSort";
        result.data_type = data_type;
        result.size = arr.size();

        std::vector<std::string> arr_copy = arr;
        std::vector<int> lcp(arr.size(), 0);
        StringSorters::reset_comparisons();

        auto start = std::chrono::high_resolution_clock::now();
        StringSorters::stringMergeSort(arr_copy, lcp, 0, arr_copy.size() - 1);
        auto end = std::chrono::high_resolution_clock::now();

        result.time_ms = std::chrono::duration<double, std::milli>(end - start).count();
        result.comparisons = StringSorters::comparisons;

        if (!std::is_sorted(arr_copy.begin(), arr_copy.end())) {
            std::cerr << "StringMergeSort failed for size " << arr.size() << std::endl;
        }

        return result;
    }

    static TestResult run_msd_radix_sort_test(const std::vector<std::string>& arr, const std::string& data_type) {
        TestResult result;
        result.algorithm = "MSDRadixSort";
        result.data_type = data_type;
        result.size = arr.size();

        std::vector<std::string> arr_copy = arr;
        StringSorters::reset_comparisons();

        auto start = std::chrono::high_resolution_clock::now();
        StringSorters::msdRadixSort(arr_copy, 0, arr_copy.size() - 1, 0);
        auto end = std::chrono::high_resolution_clock::now();

        result.time_ms = std::chrono::duration<double, std::milli>(end - start).count();
        result.comparisons = StringSorters::comparisons;

        if (!std::is_sorted(arr_copy.begin(), arr_copy.end())) {
            std::cerr << "MSDRadixSort failed for size " << arr.size() << std::endl;
        }

        return result;
    }

    static TestResult run_msd_radix_sort_with_switch_test(const std::vector<std::string>& arr, const std::string& data_type) {
        TestResult result;
        result.algorithm = "MSDRadixSortWithSwitch";
        result.data_type = data_type;
        result.size = arr.size();

        std::vector<std::string> arr_copy = arr;
        StringSorters::reset_comparisons();

        auto start = std::chrono::high_resolution_clock::now();
        StringSorters::msdRadixSortWithSwitch(arr_copy, 0, arr_copy.size() - 1, 0);
        auto end = std::chrono::high_resolution_clock::now();

        result.time_ms = std::chrono::duration<double, std::milli>(end - start).count();
        result.comparisons = StringSorters::comparisons;

        if (!std::is_sorted(arr_copy.begin(), arr_copy.end())) {
            std::cerr << "MSDRadixSortWithSwitch failed for size " << arr.size() << std::endl;
        }

        return result;
    }

    static void save_results_to_csv(const std::vector<TestResult>& results, const std::string& filename) {
        std::ofstream out(filename);
        if (!out.is_open()) {
            std::cerr << "Failed to open file " << filename << " for writing" << std::endl;
            return;
        }

        // Заголовок CSV
        out << "Algorithm,Data Type,Size,Time (ms),Comparisons\n";

        // Запись данных
        for (const auto& res : results) {
            out << std::quoted(res.algorithm) << ","
                << std::quoted(res.data_type) << ","
                << res.size << ","
                << res.time_ms << ","
                << res.comparisons << "\n";
        }

        out.close();
        std::cout << "Results saved to " << filename << std::endl;
    }

    static void run_tests() {
        StringGenerator generator;
        std::vector<size_t> sizes;
        for (size_t i = 100; i <= 3000; i += 100) {
            sizes.push_back(i);
        }

        std::vector<std::string> test_types = {"random", "reverse_sorted", "almost_sorted"};
        std::vector<TestResult> all_results;

        for (const auto& type : test_types) {
            std::cout << "Generating " << type << " base array..." << std::endl;

            // Генерируем максимальный массив
            std::vector<std::string> base_array;
            if (type == "random") {
                base_array = generator.generate_random_array(3000);
            } else if (type == "reverse_sorted") {
                base_array = generator.generate_reverse_sorted_array(3000);
            } else if (type == "almost_sorted") {
                base_array = generator.generate_almost_sorted_array(3000);
            }

            for (size_t size : sizes) {
                std::cout << "Testing size " << size << " for " << type << " arrays..." << std::endl;

                // Берем подмассив нужного размера
                std::vector<std::string> arr(base_array.begin(), base_array.begin() + size);

                // Тестируем все алгоритмы
                all_results.push_back(run_quick_sort_test(arr, type));
                all_results.push_back(run_merge_sort_test(arr, type));
                all_results.push_back(run_string_quick_sort_test(arr, type));
                all_results.push_back(run_string_merge_sort_test(arr, type));
                all_results.push_back(run_msd_radix_sort_test(arr, type));
                all_results.push_back(run_msd_radix_sort_with_switch_test(arr, type));
            }
        }

        // Сохраняем результаты
        save_results_to_csv(all_results, "sorting_results_5.csv");
    }
};