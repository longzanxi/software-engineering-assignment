#include "OptimalSubsequenceSum.h"

int maximalSubsequenceSum(int sequence[], int length) {
    int maxSum = 0;
    int currentSum = 0;

    for (int i = 0; i < length; i++) {
        currentSum += sequence[i];
        if (currentSum < 0) {
            currentSum = 0;
        }
        if (maxSum < currentSum) {
            maxSum = currentSum;
        }
    }

    return maxSum;
}
