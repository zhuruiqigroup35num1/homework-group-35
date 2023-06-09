# Forge a Signature to Pretend that You are Satoshi  
# 背景引入：  
ECDSA (Elliptic Curve Digital Signature Algorithm) 是一种基于椭圆曲线密码学的数字签名算法。它使用了椭圆曲线的数学性质来实现数字签名的生成和验证  
然而，ECDSA 签名算法也存在可能被伪造的风险。以下是一些可能的 ECDSA 签名伪造情况：  
1.私钥泄露：私钥是用于生成签名的关键部分。如果私钥意外泄露，攻击者可以使用该私钥来生成有效的签名，伪装成合法的数字签名  
2.随机数生成问题：在生成 ECDSA 签名时，需要使用一个随机数作为签名的一部分。如果随机数的生成不安全或可预测，攻击者可以通过分析签名中的随机数，推测出私钥和其他签名参数，从而伪造签名  
3.侧信道攻击：侧信道攻击是一种通过分析实现的物理特性，如电流、功耗等来获取敏感信息的攻击方式。侧信道攻击可能泄露 ECDSA 签名算法中的相关信息，从而有可能被用于伪造签名  
为了防止 ECDSA 签名伪造，可以采取以下措施：  
1.保护私钥的安全性：确保私钥的安全存储，例如使用安全的硬件钱包或安全存储设备，避免私钥的泄露风险  
2.使用安全的随机数生成器：选择安全的随机数生成器来生成签名需要的随机数，确保生成的随机数具有足够的随机性和不可预测性  
3.防止侧信道攻击：对实现 ECDSA 签名算法的设备进行物理安全措施，如防止侧信道攻击的硬件设计、物理隔离等  
4.定期更新密钥：为了降低私钥泄露风险，定期更新签名密钥是一个常用的做法  
## 本问题中利用一个已知的消息签名，伪造一个消息签名：  
![Image_test](https://github.com/zhuruiqigroup35num1/homework-group-35/blob/main/image/project19_1.png)  

# 运行环境：  
硬件环境：  
处理器：AMD Ryzen 7 5800H with Radeon Graphics   
CPU： 3.20 GHz内存：16.0 GB (15.9 GB 可用)  
软件环境：  
操作系统：win11   
编译器：IDLE 3.8  

# 核心代码：  
![Image_test](https://github.com/zhuruiqigroup35num1/homework-group-35/blob/main/image/project19_2.png)  
![Image_test](https://github.com/zhuruiqigroup35num1/homework-group-35/blob/main/image/project19_3.png)  
![Image_test](https://github.com/zhuruiqigroup35num1/homework-group-35/blob/main/image/project19_4.png)  

# 运行示例：  
## 以学号为例：  
![Image_test](https://github.com/zhuruiqigroup35num1/homework-group-35/blob/main/image/project19_5.png)  
