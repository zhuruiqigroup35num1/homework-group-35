# SM3 Naive Birthday Attack  

## 利用生日攻击攻击SM3  
### 背景引入： 哈希碰撞：两个不同的输入值通过哈希后得到相同的哈希值，这对碰撞在伪造等密码学攻击中起到重要作用。 生日攻击：生日攻击是一种密码学攻击手段，所利用的是概率论中生日问题的数学原理。这种攻击手段可用于滥用两个或多个集团之间的通信。此攻击依赖于在随机攻击中的高碰撞概率和固定置换次数（鸽巢原理）。 经典案例：需要统计多少学生才有50%以上的概率找到两个学生同一天生，答案是23人，而达到70人的统计数我们将达到99.9%以上的概率。由此，我们利用这样的生日攻击原理寻求哈希碰撞。我们统计1.17*根号n（n为哈希值的空间大小）数量的输入值，就有50%以上的概率找到一对哈希碰撞
#### 运行环境：硬件环境：处理器：AMD Ryzen 7 5800H with Radeon Graphics  CPU： 3.20 GHz内存：16.0 GB (15.9 GB 可用)软件环境：操作系统：win11 编译器：python 3.7  

### 代码实现：
from gmssl import sm4,sm3  
#用国密库实现SM3  
import time  
#寻求碰撞  
def naive_birthday_attack(bitnumber:int):  
    #number为本次搜索空间的大小  
    space = int(2**(bitnumber/2))  
    Hashtable = [0]*2**bitnumber  
    #存储一侧，计算另一侧从而寻找碰撞  
    for i in range(space):  
        res = int(sm3.sm3_hash(str(i))[0:int(bitnumber/4)],16)  
        #加密计算另一侧，尝试碰撞  
        if Hashtable[res] == 0:  
            Hashtable[res] = i  
            continue  
        else:  
            return True  
  
if __name__ == '__main__':  
    bitnumber = 20  
    start_time = time.time()  
    print(naive_birthday_attack(bitnumber))  
    end_time = time.time()  
    print("\n")  
    print("caculate time is",(end_time-start_time))  


运行结果测试：
Bit长度是： 20
sum_time = 1.2739466278159378
Bit长度为哈希值长度，也就是其空间大小为2^20
其中sum_time为总时长
