# Scheme Implmentation（未完成）  
# 背景引入：  
Hyperefficient Credential-Based Range Proofs指的是一种用于验证数字范围证明的技术。简单来说，数字范围证明是一种保护隐私的技术，它允许用户在不透露实际数字的情况下证明某个数字在特定的范围内。这种证明在许多应用场景中非常有用，例如电子现金、匿名投票、身份验证等等。  
Hyperefficient Credential-Based Range Proofs的实现方式主要包括以下几个步骤：  
1.设置参数：在使用数字范围证明进行验证之前，需要首先设置一些参数，包括待证明的数字范围、公钥和私钥等。  
2.生成凭证：凭证是数字范围证明过程中的重要组成部分。利用一些密码学技术，可以生成一些凭证用于验证数字范围。在此过程中，生成的凭证可以用于多次验证，而不需要暴露实际数字。  
3.验证数字范围：使用生成的凭证和设置的参数，验证数字是否在给定的范围内。这个过程会返回一个结果，表明数字是否在指定范围内。  
Hyperefficient Credential-Based Range Proofs的实现方式主要基于以下技术实现：  
1.零知识证明技术：这是密码学中的一种技术，它可以在不泄露任何有关证明的信息的前提下，证明某个陈述是正确的。  
2.双线性配对技术：这是一种密码学技术，它将两个群之间的乘积映射到另一个群中，并且满足乘法和加法的性质，可以用于实现数字范围证明。  
3.承诺方案技术：这是一种密码学技术，可以将数字“承诺”到未来，并且只能在未来的某个时刻才能揭示数字的真实值，用于实现数字范围证明中的凭证生成。  
![Image_test](https://github.com/zhuruiqigroup35num1/homework-group-35/blob/main/image/project7_2.png)  

# 注：  
## 本问题没有完全完成，只能给出部分尝试写出的代码：  
## 利用种子生成哈希的部分可能的过程：  
![Image_test](https://github.com/zhuruiqigroup35num1/homework-group-35/blob/main/image/project7_1.png)  
