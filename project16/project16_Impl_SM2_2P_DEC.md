# Implement SM2 2P Decrypt with Real Network Communication  
# 背景引入：  
SM2双方加密是一种基于椭圆曲线密码算法的加密方式，可用于对称加密密钥的安全交换  
在SM2双方加密中，通信双方各自生成一对公私钥，然后进行密钥交换。交换过程中，使用对方的公钥加密自己的对称加密密钥，并将加密后的密文发送给对方  
接收方从收到的密文中解密出对称加密密钥，并使用该密钥进行后续通信的加密和解密  
由于双方的对称加密密钥是通过非对称加密算法交换的，因此可以避免密钥被中间人窃取或篡改的风险  
在SM2算法中，一方拥有一对非对称密钥，即公钥和私钥。公钥用于加密数据，私钥用于解密加密后的数据  
当一方需要向另一方发送加密数据时，首先需要获取对方的公钥。然后，使用对方的公钥对原始数据进行加密。加密后的数据只能使用对应的私钥进行解密，其他人无法获得明文数据  
当接收方收到加密数据后，使用自己的私钥对加密数据进行解密，得到原始的明文数据  
![Image_test](https://github.com/zhuruiqigroup35num1/homework-group-35/blob/main/image/project16_1.png)  

# 运行环境：  
硬件环境：  
处理器：AMD Ryzen 7 5800H with Radeon Graphics   
CPU： 3.20 GHz内存：16.0 GB (15.9 GB 可用)  
软件环境：  
操作系统：win11   
编译器：IDLE 3.8  

# 核心代码：  
![Image_test](https://github.com/zhuruiqigroup35num1/homework-group-35/blob/main/image/project16_2.png)  

# 运行示例：  
## 以加密学号为例：  
![Image_test](https://github.com/zhuruiqigroup35num1/homework-group-35/blob/main/image/project16_3.png)  
