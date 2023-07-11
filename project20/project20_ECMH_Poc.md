# ECMH Poc  
# 背景引入：  
## 参考网址：  
https://github.com/tomasvdw/secp256k1  
## ECMH：  
ECMH（Elliptic Curve Menezes-Qu-Vanstone Hash）是一种基于椭圆曲线密码学的哈希算法。ECMH 的基本思想是将消息和随机数通过某种方法映射到椭圆曲线上作为椭圆曲线点，然后对这些点进行加法和乘法运算，最终得到一个椭圆曲线点作为哈希值  
ECMH 由三位密码学家 Menezes、Qu 和 Vanstone 在 1993 年提出，是一种比较简单和高效的哈希算法。ECMH 与传统的哈希算法相比，具有更好的安全性和更快的计算速度，因此在某些场景下具有优势  
## ECMH Poc：  
ECMH PoC 指的是 ECMH (Ethereum Crosslink Implementation for Multiple Heterogeneous Blockchains) 技术的 "Proof of Concept"，即概念验证、原型验证的过程  
在 ECMH PoC 的过程中，利用已有的技术和资源，来验证 ECMH 技术在可行性、可用性、安全性等方面的表现，以便在系统实际投入使用之前，确定 ECMH 技术的可行性和有效性，规避投入大量人力物力之后才发现系统存在的问题和风险 
在 PoC 过程中，通常会进行模拟环境测试，以证明 ECMH 能够实现连接和交互多个异构区块链的功能  
这意味着，通过 ECMH 技术，不同的区块链系统可以相互协作，完成交易和数据共享，从而促进整个区块链生态系统的发展  

![Image_test](https://github.com/zhuruiqigroup35num1/homework-group-35/blob/main/image/project20_2.png)

# 运行环境：  
硬件环境：  
处理器：AMD Ryzen 7 5800H with Radeon Graphics   
CPU： 3.20 GHz内存：16.0 GB (15.9 GB 可用)  
软件环境：  
操作系统：win11   
编译器：Visual Studio2022  
IDLE 3.8

# 核心代码：  
![Image_test](https://github.com/zhuruiqigroup35num1/homework-group-35/blob/main/image/project20_1.png)  

# 运行示例：  
## 以处理学号为例：  
![Image_test](https://github.com/zhuruiqigroup35num1/homework-group-35/blob/main/image/project20_3.png)  
