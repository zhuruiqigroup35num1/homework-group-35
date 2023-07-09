# Implement a PGP Scheme with SM2  
# 背景引入：  
PGP (Pretty Good Privacy) 是一种加密系统，它采用对称加密和非对称加密的结合来实现安全通信。PGP 最初由 Phil Zimmermann 开发，并于1991年发布  
PGP 使用非对称加密来创建密钥对，包括公钥和私钥。公钥是可以公开分享的，可以用来加密消息和验证数字签名。私钥只有持有者知道，用于解密消息和生成数字签名  
PGP 还使用对称加密来加密实际的消息。在对称加密中，发送方使用同一个密钥加密和解密消息。这个密钥也被称为会话密钥。通常，发送方使用对方的公钥来加密会话密钥，并将其发送给接收方。接收方使用自己的私钥来解密会话密钥，然后使用该密钥来解密消息  
最后，PGP 还支持数字签名，在消息上添加数字签名后，就可以确保消息的真实性和完整性。这是通过使用发送方的私钥来生成数字签名来实现的，任何拥有发送方公钥的人都可以验证该数字签名  
### 本次使用SM2作为非对称加密部分用来创建密钥对，使用AES作为对称加密部分  
![Image_test](https://github.com/zhuruiqigroup35num1/homework-group-35/blob/main/image/project14_1.png)  

# 运行环境：  
硬件环境：  
处理器：AMD Ryzen 7 5800H with Radeon Graphics   
CPU： 3.20 GHz内存：16.0 GB (15.9 GB 可用)  
软件环境：  
操作系统：win11   
编译器：IDLE 3.8  

# 核心代码：  
## 加解密部分：  
![Image_test](https://github.com/zhuruiqigroup35num1/homework-group-35/blob/main/image/project14_2.png)  
## 发送与接收方：  
![Image_test](https://github.com/zhuruiqigroup35num1/homework-group-35/blob/main/image/project14_3.png)  

# 运行示例：  
## 以加密学号为例：  
![Image_test](https://github.com/zhuruiqigroup35num1/homework-group-35/blob/main/image/project14_4.png)  
