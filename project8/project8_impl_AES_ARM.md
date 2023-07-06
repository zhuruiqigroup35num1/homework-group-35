# Impl AES With ARM Instruction
# 背景引入：  
## ARM指令集：  
ARM指令集是一种被广泛应用于嵌入式系统和移动设备的低功耗处理器架构。ARM指令集被设计为简洁、高效和灵活，能够满足不同类型的应用需求。  
ARM指令集包含多种指令，可以执行基本的算术和逻辑操作，访问和操作内存，进行控制流转移等。ARM指令可以分为数据处理指令、加载/存储指令、分支和跳转指令等。具体的指令格式和操作方式可以根据不同的ARM架构进行扩展和变化。  
ARM指令集的特点包括紧凑、低功耗和高性能。紧凑的指令表示形式可以减小指令存储空间和流量，并提高指令缓存的命中率。低功耗的设计使得ARM处理器在电池供电设备中具有较长的续航时间。高性能的特点则使得ARM处理器适用于许多计算密集型和实时应用。  
ARM指令集还具有可扩展性和可移植性。不同的ARM处理器可以支持不同的指令集扩展和优化，以满足特定应用领域的需求。同时，ARM处理器可以使用不同的编译器和开发工具链进行开发，使得代码在不同的ARM架构上具有良好的移植性和兼容性。  
总而言之，ARM指令集是一种用于嵌入式系统和移动设备的低功耗处理器架构，具有高性能、低功耗和可扩展性的特点。  
## AES：  
AES是SPN结构的对称加密算法，其步骤为：  
1.密钥生成：根据安全要求，生成一个128、192或256位的密钥  
2.明文填充：如果明文长度不是块长度的整数倍，则需要进行填充  
3.初始轮加：将明文分为块，使用密钥进行第一次加密，得到密文  
4.四轮变换：循环执行四轮变换，每一轮由四个步骤组成：
a.字节代替（SubBytes）：将每个字节替换为预定义的值  
b.行移位（ShiftRows）：按照特定规则移动每行中的字节位置  
c.列混淆（MixColumns）：对每列进行逐位乘和加操作  
d.轮密钥加（AddRoundKey）：将每个字节与该轮使用的密钥相关联的值进行异或操作  
最后一轮：执行最后一轮变换，但不包括列混淆步骤  
密文输出：将最后一轮得到的密文输出  

# 注：此project基于Keil仿真环境  
# 核心代码：  
![Image_test](https://github.com/zhuruiqigroup35num1/homework-group-35/blob/main/image/project8_1.png)  
![Image_test](https://github.com/zhuruiqigroup35num1/homework-group-35/blob/main/image/project8_2.png)  

# 运行示例：  
![Image_test](https://github.com/zhuruiqigroup35num1/homework-group-35/blob/main/image/project8_3.png)  
