# Impl SM2 with RFC6979  
# 背景引入：  
## RFC6979文档：www.gmbz.org.cn/main/viewfile/20180108015515787986.html  
![Image_test](https://github.com/zhuruiqigroup35num1/homework-group-35/blob/main/image/project11_1.jpg)  
## SM2算法：  
SM2算法是我国自主研发的一种椭圆曲线公钥密码算法，也是我国首个自主拥有完全自主知识产权的公钥密码算法。SM2算法被广泛应用于数字签名、密钥交换等安全领域，是我国在国际密码领域首次发表的公钥密码算法标准。  
SM2算法基于椭圆曲线密码体制（ECC），使用国家密码管理局公布的SM2曲线作为基础曲线，具有很高的安全性和效率。SM2算法可以实现数字签名、密钥协商和密钥交换等功能，还可以应用于密码卡、智能卡等硬件设备。  
### 算法步骤：  
1.密钥生成：  
（1）选择SM2椭圆曲线系统参数  
（2）选取一个随机数作为私钥，并通过椭圆曲线方程计算出公钥  
（3）输出私钥和公钥  
2.加密：  
（1）选择一个随机数作为临时私钥  
（2）使用SM2椭圆曲线方程计算出临时公钥  
（3）将明文转换成一个点，并加上随机数生成的点作为加密数据  
（4）计算出密文  
3.解密：  
（1）使用私钥计算出临时公钥  
（2）使用SM2椭圆曲线方程计算出加密数据中随机数生成的点  
（3）使用加密数据中的点减去临时生成的点得到明文  
4.数字签名：  
（1）计算出消息的哈希值  
（2）选择一个随机数作为临时私钥  
（3）计算出临时公钥  
（4）计算出签名值  

![Image_test](https://github.com/zhuruiqigroup35num1/homework-group-35/blob/main/image/project11_2.png)  

# 运行环境：   
硬件环境：  
处理器：AMD Ryzen 7 5800H with Radeon Graphics   
CPU： 3.20 GHz内存：16.0 GB (15.9 GB 可用)  
软件环境：  
操作系统：win11   
编译器：IDLE 3.8  

# 核心代码：  
![Image_test](https://github.com/zhuruiqigroup35num1/homework-group-35/blob/main/image/project11_4.png)  

# 运行示例：  
## 以加密学号为例：  
![Image_test](https://github.com/zhuruiqigroup35num1/homework-group-35/blob/main/image/project11_5.png)  
