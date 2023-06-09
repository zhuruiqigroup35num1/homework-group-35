# length extension attack for SM3, SHA256  
## 背景引入：  
长度拓展攻击是一种密码学攻击技术，它利用已知消息与其哈希值，伪造出具有相同哈希值的新消息，而无需知道原始消息的内容。  
在哈希函数的计算过程中，消息的长度是一个重要的输入。攻击者可以根据已知消息的哈希值和长度，构造出一个新的消息，并利用哈希函数的可拓展性，直接计算出新消息的哈希值，从而伪造出一个合法的签名或认证信息，从而达到欺骗的目的。  
该攻击方法可以利用哈希函数的可预测性和在计算哈希值时不会改变消息长度的特性，在不知道原始消息的情况下，利用已知哈希值计算出指定长度的哈希值，以此来伪造消息或者篡改消息。  
理论步骤：  
计算M的哈希值H(M)，得到H(M) = A || B || C || D || E || F || G || H。  
选择一个任意长度的字符串S并计算其哈希值H(S)，得到H(S) = A' || B' || C' || D' || E' || F' || G' || H'。  
将新字符串构造为M' = M || Padding || S，其中Padding为填充使得M'满足64-byte分组长度的值，具体填充方式与SM3算法的填充方式相同。  
重新计算哈希值H(M')，计算方式为将M'分组成64-byte块，然后按照SM3算法计算哈希值，得到H(M') = A || B || C || D || E || F || G || H || H(S)。  
此时得到了M'的哈希值，即可进行伪造和篡改等攻击。  

# 运行环境：  
硬件环境：  
处理器：AMD Ryzen 7 5800H with Radeon Graphics   
CPU： 3.20 GHz内存：16.0 GB (15.9 GB 可用)  
软件环境：  
操作系统：win11   
编译器：Visual Studio2022  

# 核心代码实现：  
![Image_test](https://github.com/zhuruiqigroup35num1/homework-group-35/blob/main/image/project_3.png)  
# 运行结果示例：  
![Image_test](https://github.com/zhuruiqigroup35num1/homework-group-35/blob/main/image/project3_2.png)
