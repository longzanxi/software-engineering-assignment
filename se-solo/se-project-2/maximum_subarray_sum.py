def max_subarray_sum(arr):
    """
    求最大连续子数组和（最大子段和）
    
    :param arr: 输入的整数序列
    :return: 最大连续子数组和
    """
    n = len(arr)  # 序列长度
    
    # 特殊情况：序列为空
    if n == 0:
        return 0
    
    max_sum = float("-inf")  # 初始化最大和为负无穷
    current_sum = 0  # 当前子数组和
    
    for num in arr:
        # 如果当前子数组和小于0，则丢弃之前的子数组，从当前元素重新开始
        if current_sum < 0:
            current_sum = 0
        
        current_sum += num  # 将当前元素加入子数组
        max_sum = max(max_sum, current_sum)  # 更新最大和
    
    # 如果最大和为负数，说明所有元素均为负，则返回0
    return max_sum if max_sum > 0 else 0

# 测试
arr = [-2, 11, -4, 13, -5, -2]
result = max_subarray_sum(arr)
print("最大连续子数组和为:", result)  