# SM3 Implementation(software)  
# 背景引入：  
## SM3的实现流程为：  
1.初始化变量 初始化8个32位的寄存器（A、B、C、D、E、F、G、H）为固定的初始值。  
2.数据填充 将待哈希的消息按照规定的填充方式进行数据填充。填充方式包括在消息末尾添加一个"1"和若干个"0"，以及将消息长度表示为64位的大端序整数添加到消息的末尾。  
3.处理消息分组 将填充后的消息划分为若干个分组，每个分组512位，对每个分组进行处理。  
4.压缩函数 压缩函数是SM3算法的核心部分，对每个消息分组进行处理，包括消息扩展、消息搅乱和结果混合。  
  a. 消息扩展：将512位的消息分组扩展为132个32位字的消息扩展序列。  
  b. 消息搅乱：对消息扩展序列进行迭代搅乱，包括有限域上的位运算、非线性变换和轮置换。  
  c. 结果混合：将搅乱后的消息分组结果与寄存器的值进行异或运算，得到新的寄存器值。  
5.更新寄存器值 更新8个寄存器的值，将当前循环的寄存器的值赋给下一个循环。  
6.循环处理 对每个消息分组进行循环处理，直到处理完所有消息分组。  
7.输出结果 将最终的8个寄存器的值按顺序连接起来，得到最终的哈希结果。  
### 效果图示意：
![Image_test](https://github.com/zhuruiqigroup35num1/homework-group-35/blob/main/image/project4_1.png)  

# 核心代码实现（主要加速了迭代函数的部分和消息扩展搅乱部分）
![Image_test](https://github.com/zhuruiqigroup35num1/homework-group-35/blob/main/image/project4_2.png)  
# 运行示例（以GROUP为例进行哈希运算）  
![Image_test](https://github.com/zhuruiqigroup35num1/homework-group-35/blob/main/image/project4_3.png)  
共计0.068s
