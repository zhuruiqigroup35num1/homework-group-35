# Impl AES SM4(software)  
# 背景引入：  
## AES：  
AES是一种基于SPN结构的对称加密算法，有128bit，192bit，256bit三种长度的工作模式  
其加密步骤为：  
1.密钥生成：根据安全要求，生成一个128、192或256位的密钥  
2.明文填充：如果明文长度不是块长度的整数倍，则需要进行填充  
3.初始轮加：将明文分为块，使用密钥进行第一次加密，得到密文  
4.四轮变换：循环执行四轮变换，每一轮由四个步骤组成：  
a.字节代替（SubBytes）：将每个字节替换为预定义的值  
b.行移位（ShiftRows）：按照特定规则移动每行中的字节位置  
c.列混淆（MixColumns）：对每列进行逐位乘和加操作  
d.轮密钥加（AddRoundKey）：将每个字节与该轮使用的密钥相关联的值进行异或操作  
最后一轮：执行最后一轮变换，但不包括列混淆步骤  
密文输出：将最后一轮得到的密文输出  
![Image_test](https://github.com/zhuruiqigroup35num1/homework-group-35/blob/main/image/project9_3.png)  

## SM4:  
M4 算法是一种基于Feistel结构的分组密码算法。其分组长度为 128bit，密钥长度也为 128bit  
加密算法与密钥扩展算法均采用 32 轮非线性迭代结构，以字（32 位）为单位进行加密运算，每一次迭代运算均为一轮变换函数F  
SM4 算法加/解密算法的结构相同，只是使用轮密钥相反，其中解密轮密钥是加密轮密钥的逆序  
![Image_test](https://github.com/zhuruiqigroup35num1/homework-group-35/blob/main/image/project9_1.png)  
![Image_test](https://github.com/zhuruiqigroup35num1/homework-group-35/blob/main/image/project9_2.png)  

# 运行环境：  
硬件环境：  
处理器：AMD Ryzen 7 5800H with Radeon Graphics   
CPU： 3.20 GHz内存：16.0 GB (15.9 GB 可用)  
软件环境：  
操作系统：win11   
编译器：Visual Studio2022  

# 核心代码：  
## AES:  
![Image_test]()  
![Image_test]()  
