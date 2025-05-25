#include <string>
#include <vector>
#include <algorithm>
#include <ctime>

class StringSorters {
public:
    static size_t comparisons;

    static void reset_comparisons() {
        comparisons = 0;
    }

    // Тернарный QuickSort для строк
    static void stringQuickSort(std::vector<std::string>& arr, int low, int high, int d = 0) {
        if (high <= low) return;

        int lt = low, gt = high;
        int v = charAt(arr[low], d);
        int i = low + 1;

        while (i <= gt) {
            int t = charAt(arr[i], d);
            comparisons++;

            if (t < v) {
                std::swap(arr[lt++], arr[i++]);
            } else if (t > v) {
                std::swap(arr[i], arr[gt--]);
            } else {
                i++;
            }
        }

        stringQuickSort(arr, low, lt - 1, d);
        if (v >= 0) stringQuickSort(arr, lt, gt, d + 1);
        stringQuickSort(arr, gt + 1, high, d);
    }

    static int charAt(const std::string& s, int d) {
        if (d < s.size()) return s[d];
        return -1;
    }

    // String MergeSort с использованием LCP
    static void stringMergeSort(std::vector<std::string>& arr, std::vector<int>& lcp, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            stringMergeSort(arr, lcp, left, mid);
            stringMergeSort(arr, lcp, mid + 1, right);
            stringMerge(arr, lcp, left, mid, right);
        }
    }

    static void stringMerge(std::vector<std::string>& arr, std::vector<int>& lcp, int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        std::vector<std::string> L(n1), R(n2);
        std::vector<int> lcpL(n1), lcpR(n2);

        for (int i = 0; i < n1; i++) {
            L[i] = arr[left + i];
            lcpL[i] = lcp[left + i];
        }

        for (int j = 0; j < n2; j++) {
            R[j] = arr[mid + 1 + j];
            lcpR[j] = lcp[mid + 1 + j];
        }

        int i = 0, j = 0, k = left;

        while (i < n1 && j < n2) {
            int cmp = compareStringsWithLCP(L[i], R[j], lcpL[i], lcpR[j]);
            comparisons++;

            if (cmp <= 0) {
                arr[k] = L[i];
                lcp[k] = lcpL[i];
                i++;
            } else {
                arr[k] = R[j];
                lcp[k] = lcpR[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            arr[k] = L[i];
            lcp[k] = lcpL[i];
            i++;
            k++;
        }

        while (j < n2) {
            arr[k] = R[j];
            lcp[k] = lcpR[j];
            j++;
            k++;
        }
    }

    static int compareStringsWithLCP(const std::string& a, const std::string& b, int lcp_a, int lcp_b) {
        int min_lcp = std::min(lcp_a, lcp_b);
        if (min_lcp < a.size() && min_lcp < b.size()) {
            if (a[min_lcp] < b[min_lcp]) return -1;
            if (a[min_lcp] > b[min_lcp]) return 1;
        }
        return a.compare(b);
    }

    // MSD Radix Sort
    static void msdRadixSort(std::vector<std::string>& arr, int low, int high, int d = 0) {
        if (high <= low) return;

        const int R = 256; // Размер алфавита ASCII
        std::vector<int> count(R + 2);
        std::vector<std::string> aux(high - low + 1);

        // Вычисление счетчиков
        for (int i = low; i <= high; i++) {
            int c = charAt(arr[i], d);
            count[c + 2]++;
        }

        // Преобразование счетчиков в индексы
        for (int r = 0; r < R + 1; r++) {
            count[r + 1] += count[r];
        }

        // Распределение
        for (int i = low; i <= high; i++) {
            int c = charAt(arr[i], d);
            aux[count[c + 1]++] = arr[i];
            comparisons++;
        }

        // Копирование обратно
        for (int i = low; i <= high; i++) {
            arr[i] = aux[i - low];
        }

        // Рекурсивная сортировка для каждого символа
        for (int r = 0; r < R; r++) {
            msdRadixSort(arr, low + count[r], low + count[r + 1] - 1, d + 1);
        }
    }

    // MSD Radix Sort с переключением на QuickSort
    static void msdRadixSortWithSwitch(std::vector<std::string>& arr, int low, int high, int d = 0) {
        if (high <= low) return;

        // Переключение на QuickSort для маленьких подмассивов
        if (high - low + 1 < 74) { // Мощность алфавита
            stringQuickSort(arr, low, high, d);
            return;
        }

        const int R = 256;
        std::vector<int> count(R + 2);
        std::vector<std::string> aux(high - low + 1);

        for (int i = low; i <= high; i++) {
            int c = charAt(arr[i], d);
            count[c + 2]++;
            comparisons++;
        }

        for (int r = 0; r < R + 1; r++) {
            count[r + 1] += count[r];
        }

        for (int i = low; i <= high; i++) {
            int c = charAt(arr[i], d);
            aux[count[c + 1]++] = arr[i];
        }

        for (int i = low; i <= high; i++) {
            arr[i] = aux[i - low];
        }

        for (int r = 0; r < R; r++) {
            msdRadixSortWithSwitch(arr, low + count[r], low + count[r + 1] - 1, d + 1);
        }
    }
};

size_t StringSorters::comparisons = 0;