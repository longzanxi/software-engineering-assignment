import random
import os

def generate_number(min_num, max_num):
    """
    生成指定范围内的随机数
    
    :param min_num: 随机数的最小值
    :param max_num: 随机数的最大值
    :return: 生成的随机数
    """
    return random.randint(min_num, max_num)

def generate_operator(operators):
    """
    从运算符列表中随机选择一个运算符
    
    :param operators: 运算符列表
    :return: 随机选择的运算符
    """
    return random.choice(operators)

def generate_expression(grade):
    """
    根据年级生成四则运算表达式
    
    :param grade: 年级(1-6)
    :return: 生成的表达式字符串
    """
    if grade == 1:
        # 一年级:20以内加减法,结果小于20
        a = generate_number(0, 20)
        b = generate_number(0, 20)
        if a < b:
            a, b = b, a  # 确保a大于等于b,避免减法结果为负数
        op = generate_operator(['+', '-'])
        return f"{a} {op} {b}"
    elif grade == 2:
        # 二年级:50以内加减法,结果小于50
        a = generate_number(0, 50) 
        b = generate_number(0, 50)
        if a < b:
            a, b = b, a  # 确保a大于等于b,避免减法结果为负数
        op = generate_operator(['+', '-'])
        return f"{a} {op} {b}"
    elif grade == 3:
        # 三年级:1000以内加减乘法  
        a = generate_number(0, 1000)
        b = generate_number(0, 1000)
        op = generate_operator(['+', '-', '*'])
        if op == '-' and a < b:
            a, b = b, a  # 确保减法结果非负
        return f"{a} {op} {b}"
    else:  
        # 四到六年级:带括号和三个以上运算符的非负整数、小数四则运算
        ops = ['+', '-', '*', '/']
        exp = ""
        num_ops = random.randint(3, 5)  # 随机生成3到5个运算符
        for i in range(num_ops):
            a = generate_number(0, 100)
            b = generate_number(1, 100)  # 除数不能为0
            op = generate_operator(ops)
            if op == '/':
                exp += f"({a} {op} {b:.1f})"  # 除法保留1位小数
            else:
                exp += f"({a} {op} {b})"
            if i < num_ops - 1:
                exp += " " + generate_operator(ops) + " "
        return exp

def generate_unique_filename(filename):
    """
    生成唯一的文件名
    
    :param filename: 原始文件名
    :return: 唯一的文件名
    """
    base_name, extension = os.path.splitext(filename)
    counter = 1
    while os.path.exists(os.path.join("exercise_question", filename)):
        filename = f"{base_name}-{counter}{extension}"
        counter += 1
    return filename

def generate_exercises(grade, num, homework_name):
    """
    生成指定数量的练习题并写入文件
    
    :param grade: 年级(1-6)
    :param num: 题目数量
    :param homework_name: 作业名称
    """
    current_dir = os.path.dirname(os.path.abspath(__file__))
    folder_path = os.path.join(current_dir, "exercise_question")
    os.makedirs(folder_path, exist_ok=True)
    filename = f"{homework_name}.txt"
    filename = generate_unique_filename(filename)
    file_path = os.path.join(folder_path, filename)
    
    # 打开文件,如果文件不存在则创建
    with open(file_path, "w", encoding="utf-8") as file:
        # 生成并写入练习题
        for i in range(num):
            expression = generate_expression(grade)
            file.write(f"{i+1}. {expression} = \n")
    print(f"练习题已生成并保存到文件: {file_path}")

# 获取用户输入
while True:
    try:
        # 提示用户输入年级,并将输入转换为整数
        grade = int(input("请输入年级(1-6): "))
        # 判断年级是否在合法范围内
        if grade < 1 or grade > 6:
            raise ValueError
        break
    except ValueError:
        # 如果输入的年级不合法,提示用户重新输入
        print("无效的年级,请输入1到6之间的整数")

while True:        
    try:
        # 提示用户输入题目数量,并将输入转换为整数
        num = int(input("请输入题目数量: "))
        # 判断题目数量是否为正整数
        if num <= 0:
            raise ValueError
        break
    except ValueError:
        # 如果输入的题目数量不合法,提示用户重新输入
        print("无效的题目数量,请输入正整数")
        
# 提示用户输入作业名称        
homework_name = input("请输入作业名称: ")

# 调用generate_exercises函数生成练习题并写入文件
generate_exercises(grade, num, homework_name)
