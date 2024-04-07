#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <windows.h>

/**
 * 求最大连续子数组和
 *
 * @param arr 输入的整数序列
 * @param n 序列的长度
 * @return 最大连续子数组和
 */
int max_subarray_sum(int arr[], int n) {
    // 特殊情况：序列为空
    if (n == 0) {
        return 0;
    }
    
    int max_sum = INT_MIN;  // 初始化最大和为INT_MIN
    int current_sum = 0;    // 当前子数组和
    
    for (int i = 0; i < n; i++) {
        // 如果当前子数组和小于0，则丢弃之前的子数组，从当前元素重新开始
        if (current_sum < 0) {
            current_sum = 0;
        }
        
        current_sum += arr[i];  // 将当前元素加入子数组
        
        // 更新最大和
        if (current_sum > max_sum) {
            max_sum = current_sum;
        }
    }
    
    // 如果最大和为负数，说明所有元素均为负，则返回0
    return max_sum > 0 ? max_sum : 0;
}

/**
 * 测试样例：
 * 1. 输入：6 -2 1 -3 4 -1 2
 *    输出：5
 *    连续子数组 [4, -1, 2, 1] 的和最大，为 5。
 *
 * 2. 输入：1 1
 *    输出：1
 *
 * 3. 输入：5 5 4 -1 7 8
 *    输出：23
 *    整个数组的和最大，为 23。
 *
 * 4. 输入：5 -1 -2 -3 -4 -5
 *    输出：0
 *    所有元素均为负数，返回 0。
 *
 * 5. 输入：0
 *    输出：0
 *    空数组，返回 0。
 */

int main() {
    SetConsoleOutputCP(65001);  
    
    int n;
    printf("请输入序列的长度和序列内容，用空格分隔：");
    scanf("%d", &n);
    
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    int result = max_subarray_sum(arr, n);  // 调用函数求最大连续子数组和
    printf("最大连续子数组和为：%d\n", result); 
    
    system("pause");
    return 0;  
}
