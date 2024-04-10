#include "OptimalSubsequenceSum.h"
#include "minunit.h"
#include <stdio.h>

// ��¼�����еĲ�������
int tests_run = 0;

// ����ȫ��������
static const char* test_all_positive() {
    int sequence[] = { 1, 2, 3, 4 };
    int result = maximalSubsequenceSum(sequence, 4);
    mu_assert("error, maximalSubsequenceSum != 10", result == 10);
    return 0;
}

// ����ȫ��������
static const char* test_all_negative() {
    int sequence[] = { -1, -2, -3, -4 };
    int result = maximalSubsequenceSum(sequence, 4);
    mu_assert("error, maximalSubsequenceSum != 0", result == 0);
    return 0;
}

// ����������������
static const char* test_alternating_positive_negative() {
    int sequence[] = { -2, 3, -1, 2, -3 };
    int result = maximalSubsequenceSum(sequence, 5);
    mu_assert("error, maximalSubsequenceSum != 4", result == 4);
    return 0;
}

// ���԰����������
static const char* test_array_with_zero() {
    int sequence[] = { 0, -1, 2, 3, -2, 0 };
    int result = maximalSubsequenceSum(sequence, 6);
    mu_assert("error, maximalSubsequenceSum != 5", result == 5);
    return 0;
}

// ���Ե�������
static const char* test_single_positive() {
    int sequence[] = { 5 };
    int result = maximalSubsequenceSum(sequence, 1);
    mu_assert("error, maximalSubsequenceSum != 5", result == 5);
    return 0;
}

// ���Ե�������
static const char* test_single_negative() {
    int sequence[] = { -5 };
    int result = maximalSubsequenceSum(sequence, 1);
    mu_assert("error, maximalSubsequenceSum != 0", result == 0);
    return 0;
}

// ����ȫ������
static const char* test_all_zero() {
    int sequence[] = { 0, 0, 0, 0 };
    int result = maximalSubsequenceSum(sequence, 4);
    mu_assert("error, maximalSubsequenceSum != 0", result == 0);
    return 0;
}

// ���Ե�ǰ��ʼ�մ�������
static const char* test_current_sum_always_greater_than_max_sum() {
    int sequence[] = { 1, 2, 3, 4, 5 };
    int result = maximalSubsequenceSum(sequence, 5);
    mu_assert("error, maximalSubsequenceSum != 15", result == 15);
    return 0;
}

// �������в���
static const char* all_tests() {
    mu_run_test(test_all_positive);
    mu_run_test(test_all_negative);
    mu_run_test(test_alternating_positive_negative);
    mu_run_test(test_array_with_zero);
    mu_run_test(test_single_positive);
    mu_run_test(test_single_negative);
    mu_run_test(test_all_zero);
    mu_run_test(test_current_sum_always_greater_than_max_sum);
    return 0;
}

int main(int argc, char** argv) {
    const char* result = all_tests();

    if (result != 0) {
        printf("%s\n", result);
    }
    else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);
    return result != 0;
}