#include <string>
#include <vector>
#include <ctime>

class StandardSorters {
public:
    static size_t comparisons;

    static void reset_comparisons() {
        comparisons = 0;
    }

    static int compare_strings(const std::string& a, const std::string& b) {
        comparisons++;
        if (a < b) return -1;
        if (a > b) return 1;
        return 0;
    }

    // QuickSort реализация
    static void quickSort(std::vector<std::string>& arr, int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high);
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }

    static int partition(std::vector<std::string>& arr, int low, int high) {
        std::string pivot = arr[high];
        int i = low - 1;

        for (int j = low; j < high; j++) {
            if (compare_strings(arr[j], pivot) <= 0) {
                i++;
                std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[high]);
        return i + 1;
    }

    // MergeSort реализация
    static void mergeSort(std::vector<std::string>& arr, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSort(arr, left, mid);
            mergeSort(arr, mid + 1, right);
            merge(arr, left, mid, right);
        }
    }

    static void merge(std::vector<std::string>& arr, int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        std::vector<std::string> L(n1), R(n2);

        for (int i = 0; i < n1; i++)
            L[i] = arr[left + i];
        for (int j = 0; j < n2; j++)
            R[j] = arr[mid + 1 + j];

        int i = 0, j = 0, k = left;

        while (i < n1 && j < n2) {
            if (compare_strings(L[i], R[j]) <= 0) {
                arr[k] = L[i];
                i++;
            } else {
                arr[k] = R[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            arr[k] = L[i];
            i++;
            k++;
        }

        while (j < n2) {
            arr[k] = R[j];
            j++;
            k++;
        }
    }
};

size_t StandardSorters::comparisons = 0;