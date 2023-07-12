from gmssl import sm3
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
