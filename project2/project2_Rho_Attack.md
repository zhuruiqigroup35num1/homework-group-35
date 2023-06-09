# SM3 Rho环路攻击  
# 背景引入：  
Rho是一种寻找哈希碰撞的算法方案，其思路如下：  
1.选择两个不同的随机输入值，分别为x1和x2。  
2.使用哈希函数h进行迭代计算，即x1 = h(x1)和x2 = h(h(x2))。  
3.检查x1和x2是否相等，如果相等，则找到了一个碰撞。  
4.如果不相等，则重复步骤2和步骤3，直到找到碰撞或者遇到一个循环。  
Rho算法的关键在于探测循环。通过设置快慢指针方法，即慢指针每次进行一次哈希运算，快指针每次进行两次哈希运算，当两个指针相遇时，就检测到了一个循环。在循环中，通过使用迭代函数h进行计算，可以得到相同的结果。  
如果能通过可接受的迭代次数寻找到一个环路，也就是碰撞达成，我们就说对其Rho攻击成功  
# 运行环境：  
硬件环境：  
处理器：AMD Ryzen 7 5800H with Radeon Graphics   
CPU： 3.20 GHz内存：16.0 GB (15.9 GB 可用)  
软件环境：  
操作系统：win11   
编译器：Visual Studio2022  

# 核心代码实现：  
![Image_test](https://github.com/zhuruiqigroup35num1/homework-group-35/blob/main/image/0704project2.png)
# 运行示例：  
![Image_test](https://github.com/zhuruiqigroup35num1/homework-group-35/blob/main/image/5R5CIU%2470YDGL%60CB499SCZB.png)
