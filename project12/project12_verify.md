# Verify the Above Pitfalls with Proof-of-concept Code  
# 背景引入：  
![Image_test](https://github.com/zhuruiqigroup35num1/homework-group-35/blob/main/image/project12_4.png)  
用代码验证上述陷阱  
## 泄露K  
直接利用公式恢复即可  
![Image_test](https://github.com/zhuruiqigroup35num1/homework-group-35/blob/main/image/project12_5.png)  
## Reusing K  
### 重复使用K的时候，直接用下图公式即可恢复对应私钥  
![Image_test](https://github.com/zhuruiqigroup35num1/homework-group-35/blob/main/image/project12_1.png)  
## Reusing K by Different Users  
### 不同使用者使用相同K的时候，可以根据签名值恢复私钥  
攻击原理如下图所示：  
![Image_test](https://github.com/zhuruiqigroup35num1/homework-group-35/blob/main/image/project12_3.png)  
## Same d and K with ECDSA  
### 和ECDSA使用相同的私钥d和K的时候，可以根据两者的签名进行私钥恢复  
攻击原理如下图所示：  
![Image_test](https://github.com/zhuruiqigroup35num1/homework-group-35/blob/main/image/project12_2.png)  

# 运行环境：   
硬件环境：  
处理器：AMD Ryzen 7 5800H with Radeon Graphics   
CPU： 3.20 GHz内存：16.0 GB (15.9 GB 可用)  
软件环境：  
操作系统：win11   
编译器：IDLE 3.8  

# 核心代码：  
## 处理泄露K的方案：  
![Image_test](https://github.com/zhuruiqigroup35num1/homework-group-35/blob/main/image/project12_6.png)  
## 处理Reusing K的方案：  
![Image_test](https://github.com/zhuruiqigroup35num1/homework-group-35/blob/main/image/project12_7.png)  
## 处理Reusing K by Different Users的方案：  
![Image_test](https://github.com/zhuruiqigroup35num1/homework-group-35/blob/main/image/project12_8.png)  
## 处理Same d and K with ECDSA的方案：  
![Image_test](https://github.com/zhuruiqigroup35num1/homework-group-35/blob/main/image/project12_8.png)  

# 运行示例：  
## 以签名消息为学号为例：  
![Image_test](https://github.com/zhuruiqigroup35num1/homework-group-35/blob/main/image/project12_10.png)  
