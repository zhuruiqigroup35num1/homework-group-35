# Impl this Protocol with Actual Network Communication  
# 背景引入：  
"Range Proofs from Hash Functions" 是一种加密学术语汇，指的是使用哈希函数构建范围证明的技术。范围证明是指，对于一个公钥和一个承诺（通常是一种加密方式，用于标识某些内容的哈希值），证明某个值是否落在指定区间内，同时又不暴露任何有关该值的信息。  
范围证明（Range Proof）是一种加密技术，用于证明某个值是否落在指定区间内，同时又不暴露任何有关该值的信息。例如，在加密货币领域中，范围证明技术可用于证明一个交易的输出值是否落在指定区间内，以确保交易不会超出指定范围。但是，由于范围证明需要证明是否在特定范围内，因此需要更多的证明信息，这会增加交易的复杂性和计算成本。  
在这种情况下，使用哈希函数构建范围证明就成为了比较流行的选择。哈希函数（Hash Function）是将任意长度的消息压缩成固定长度消息摘要的函数，通常用于加密、完整性验证和签名等应用。将哈希函数用于范围证明可以提供高效性、简洁性和安全性，这使得它成为构建加密货币或隐私保护应用程序的强大技术工具。使用哈希函数构建范围证明的基本思想是，将哈希函数的输入值与随机数进行混淆并取哈希值进行证明。  
Range Proofs:  
1.选择一个随机数r  
2.计算哈希值h（v | r），其中v是要证明的值  
3.将哈希值h拆分为n个比特（bit）  
4.将h的前k个比特进行公开声明。这些比特称为“置位（commitment）”，用于在后续的阶段中证明单元比特值正确  
5.对于h的其余比特，将它们用来构建证明。例如，可以证明v是否在区域（2m, 2m+1）内，其中m是差异的单元数，其余n-m bits用于构建证明  
6.将证明信息提供给验证者（可能是一个加密货币网络中的节点），验证者可以使用哈希函数和随机数r来重构哈希值h，并检查所提供的证明信息是否正确。  
本协议引入以Alice向Bob证明其age>=21为引入例子  

![Image_test](https://github.com/zhuruiqigroup35num1/homework-group-35/blob/main/image/project6_2.png)  
# 运行环境：  
硬件环境：  
处理器：AMD Ryzen 7 5800H with Radeon Graphics   
CPU： 3.20 GHz内存：16.0 GB (15.9 GB 可用)  
软件环境：  
操作系统：win11   
编译器：IDLE 3.8  

# 核心代码：  
![Image_test](https://github.com/zhuruiqigroup35num1/homework-group-35/blob/main/image/project6_1.png)  

# 运行示例：  
![Image_test](https://github.com/zhuruiqigroup35num1/homework-group-35/blob/main/image/project6_3.png)  
