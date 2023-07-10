# Implement SM2 2P Sign with Real Network Communication  
# 背景引入：  
SM2双方签名是指使用SM2算法进行双方身份认证和消息完整性验证的过程。在这个过程中，通信双方各自生成一对公私钥，并将自己的公钥发送给对方。然后，当一方需要向另一方发送消息时，它使用自己的私钥对消息进行签名，并将签名信息发送给对方。接收方使用发件人的公钥进行验签，以确保收到的消息是完整的、未被篡改过的，并确认发件人的身份  
SM2双方签名采用基于椭圆曲线离散对数问题的公钥密码学算法，具有高强度、高安全性、高效性等特点，适用于各种网络通信环境。双方签名的过程安全可靠，能够有效地防止假冒和信息被篡改的情况  
具体步骤如下：  
1.生成密钥对：通信双方各自生成自己的公私钥对。其中，私钥是一串随机的数值，只有持有者才能访问；公钥是由私钥生成的一串数值，可以公开  
2.公钥交换：通信双方将自己的公钥发送给对方，以进行身份验证和消息完整性验证。在发送公钥的过程中，通信双方需要进行认证，以确保对方收到的公钥是真实有效的  
3.消息签名：当一方需要向另一方发送消息时，它使用自己的私钥对消息进行签名。签名的过程主要是对消息进行哈希运算，并使用私钥生成数字签名  
4.消息验签：接收方在收到消息后，使用发件人的公钥对消息进行验签。验签的过程主要是对消息进行哈希运算，并验证数字签名与哈希值是否匹配，以确保消息的完整性和真实性  
![Image_test](https://github.com/zhuruiqigroup35num1/homework-group-35/blob/main/image/project15_1.png)  

# 运行环境：  
硬件环境：  
处理器：AMD Ryzen 7 5800H with Radeon Graphics   
CPU： 3.20 GHz内存：16.0 GB (15.9 GB 可用)  
软件环境：  
操作系统：win11   
编译器：IDLE 3.8  

# 核心代码：  
![Image_test](https://github.com/zhuruiqigroup35num1/homework-group-35/blob/main/image/project15_2.png)  

# 运行示例：  
## 以学号为例：  
![Image_test](https://github.com/zhuruiqigroup35num1/homework-group-35/blob/main/image/project15_3.png)  
