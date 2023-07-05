import hashlib
from multiprocessing.dummy import Value
import random
import string
import math
from numpy import block



def Generate_data_block(blocknumber):
    blocks = []  
    for i in range(blocknumber):
        number = [random.choice(string.digits) for _ in range(10)]
        blocks.append(''.join(number))
        #合并迭代数据
    return blocks


def generate_Tree(blocks):
    #迭代生成Merkle_Tree
    depth = math.ceil(math.log2(len(blocks)+1))
    Treenode = [[hashlib.sha256(('0x00'+data).encode()).hexdigest() for data in blocks]]
    assert Treenode[0][-1] != Treenode[0][-2]

    for i in range(depth):
        lay_number = len(Treenode[i])
        #每层个数
        Treenode.append([hashlib.sha256(('0x01'+Treenode[i][j*2]).encode()+('0x01'+Treenode[i][j*2+1]).encode()).hexdigest() for j in range(int(lay_number/2))])
        if lay_number%2!=0:
            Treenode[i+1].append(Treenode[i][-1]) 
    
    return Treenode


def Inclusion_Proof(element,Treenode):
    value = (hashlib.sha256(('0x00'+element).encode())).hexdigest()
    #判断是不是一个单独的数据块
    depth = len(Treenode)
    path = []
    if value in Treenode[0]:
        index = Treenode[0].index(value)
    else:
        print("The element not in the merkle tree.")
        return
    for i in range(depth):
        if index%2 ==  0:
            if index+1 != len(Treenode[i]):
                path.append(['left',Treenode[i][index+1]])
            #置入Mekle树
        else:
            path.append(['right',Treenode[i][index-1]])
        index = int(index/2)



    for w in path:
        if w[0] == 'left':
            value = hashlib.sha256(('0x01'+value).encode()+('0x01'+w[1]).encode()).hexdigest()
        else:
            value = hashlib.sha256(('0x01'+w[1]).encode()+('0x01'+value).encode()).hexdigest()
    if value == Treenode[depth-1][0]:
        print("Inclusion proof correct.")
    else:
        print("Inclusion proof false.")



def Exclusion_proof(element,Treenode,blocks):
    #不存在性证明
    Value = hashlib.sha256(element.encode()).hexdigest()
    if Value in Treenode[0]:
        print('element exist.')
    else:
        length = len(Treenode[0])
        for i in range(length-1):
            #基于排序，进行遍历
            if blocks[i]<element and blocks[i+1]>element:
                print('Pre:',blocks[i])
                Inclusion_Proof(blocks[i],Treenode)
                print('Next:',blocks[i+1])
                Inclusion_Proof(blocks[i+1],Treenode)
                print("Exclusion proof correct.")
            else:
                continue
    return 

if __name__ == "__main__":
    #运行示例尝试
    # blocks = Generate_data_block(10)
    #可以调整规模进行生成
    blocks = ['4','7','6','10','5','1']
    for i in blocks:
        print("TX{} value:{}".format(blocks.index(i),i))
    Treenode = generate_Tree(blocks)
    print("对TX7的存在性证明")
    Inclusion_Proof('7',Treenode)

    Sort_blocks = sorted(blocks)
    Treenode2 = generate_Tree(Sort_blocks)
    print("证明一笔交易不存在性 value:2")
    Exclusion_proof('2',Treenode2,Sort_blocks)

