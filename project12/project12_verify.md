# Verify the Above Pitfalls with Proof-of-concept Code  
# 背景引入：  
![Image_test](https://github.com/zhuruiqigroup35num1/homework-group-35/blob/main/image/project12_4.png)  
用代码验证上述陷阱  
## 泄露K  

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
