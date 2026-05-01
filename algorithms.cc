#include "algorithms.h"
using namespace std;

bool all_distinct(const vector<int>& A, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        if (A[i] == A[i - 1]) {
            return false;
        }
    }
    return true;
}

int find_missing_linear(const vector<int>& A) {
    for (int i = 0; i < (int)A.size() - 1; i++) {
        if (A[i + 1] > A[i] && A[i + 1] - A[i] > 1) {
            return A[i] + 1;
        }
    }
    return -1;
}

int binary_missing_distinct(const vector<int>& A, int left, int right) {
    int offset = A[left] - left;

    while (left < right) {
        int mid = left + (right - left) / 2;
        int expected = offset + mid;

        if (A[mid] == expected) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    return offset + left;
}

int general_missing_recursive(const vector<int>& A, int left, int right) {
    if (left >= right) {
        return -1;
    }

    if (right - left == 1) {
        if (A[right] > A[left] && A[right] - A[left] > 1) {
            return A[left] + 1;
        }
        return -1;
    }

    if (all_distinct(A, left, right)) {
        return binary_missing_distinct(A, left, right);
    }

    int mid = left + (right - left) / 2;

    int left_result = general_missing_recursive(A, left, mid);
    if (left_result != -1) {
        return left_result;
    }

    if (A[mid + 1] > A[mid] && A[mid + 1] - A[mid] > 1) {
        return A[mid] + 1;
    }

    return general_missing_recursive(A, mid + 1, right);
}

int find_missing_distinct(const vector<int>& A) {
    return binary_missing_distinct(A, 0, (int)A.size() - 1);
}

int find_missing_general(const vector<int>& A) {
    return general_missing_recursive(A, 0, (int)A.size() - 1);
}

int find_missing_element(const vector<int>& A) {
    if (all_distinct(A, 0, (int)A.size() - 1)) {
        return find_missing_distinct(A);
    }
    return find_missing_general(A);
}
