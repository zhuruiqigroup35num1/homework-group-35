# Impl This Deduce Technique in Ethereum with ECDSA  
# 背景引入:  
ECDSA（Elliptic Curve Digital Signature Algorithm）是基于椭圆曲线密码学的数字签名算法  
ECDSA使用椭圆曲线上的点进行密钥生成、签名和验证  
## 具体步骤：  
密钥生成：选择一个椭圆曲线作为密码算法的基础，并随机选取一个私钥（一个整数）。接着，通过使用椭圆曲线上的点乘法来计算对应的公钥（一个曲线上的点）  
签名生成：在进行数字签名之前，需要先对原始数据进行哈希处理，以减小数据量并提高安全性。然后，选择一个随机数作为签名的私钥（一个整数），并使用该私钥和原始数据的哈希值来计算签名的数字。签名的数字由两个组成：一个称为r值，代表椭圆曲线上的点的x坐标；另一个称为s值，是根据私钥、哈希值和r值计算得出的  
签名验证：接收到签名的一方可以使用发送方的公钥、原始数据的哈希值以及签名的数字来验证签名的有效性。在验证过程中，将使用公钥和哈希值来重新计算r值，并将其与签名中的r值进行比较。如果两者相等，则表示签名有效  
## 优点  
ECDSA相对于其他签名算法的优势包括较小的密钥尺寸、较快的运算速度和较低的资源消耗。由于这些特点，ECDSA在资源受限的环境中得到了广泛应用，例如智能卡和物联网设备  
![Image_test](https://github.com/zhuruiqigroup35num1/homework-group-35/blob/main/image/project10_1.png)  

# 运行环境：    
硬件环境：  
处理器：AMD Ryzen 7 5800H with Radeon Graphics   
CPU： 3.20 GHz内存：16.0 GB (15.9 GB 可用)  
软件环境：  
操作系统：win11   
编译器：IDLE 3.7  

# 核心代码：  
![Image_test](https://github.com/zhuruiqigroup35num1/homework-group-35/blob/main/image/project10_2.png)  
![Image_test](https://github.com/zhuruiqigroup35num1/homework-group-35/blob/main/image/project10_3.png)  
![Image_test](https://github.com/zhuruiqigroup35num1/homework-group-35/blob/main/image/project10_4.png)  

# 运行示例：  
![Image_test](https://github.com/zhuruiqigroup35num1/homework-group-35/blob/main/image/project10_5.png)  
