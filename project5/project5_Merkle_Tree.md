# Merkle Tree Implementation  
# 背景引入：  
![Image_test](https://github.com/zhuruiqigroup35num1/homework-group-35/blob/main/image/project5_5.png)  
Merkle树是一种哈希树，它是由计算机科学家Ralph Merkle于1987年发明的，并以他的名字命名。Merkle树具有一些独特的特点，使它在网络和加密领域中被广泛使用。  
Merkle树的基本思想是将多个哈希值组合成一个树形结构，使得任何一个哈希值都可以通过计算出它所在的叶节点，并由其它的哈希值逐一地向根节点计算哈希值。这个根节点是一个单一的哈希值，它可以被用作校验这个哈希树上任何一条路径的完整性。  
为了实现这种哈希树结构，需要一些规则：  
1.所有的叶子节点都是数据块的哈希值；  
2.从叶节点开始，每个节点都是其子节点哈希值的哈希值。这样，它们向上成为树的父节点，并重复了同样的计算过程，直到达到根节点，即Merkle树的根哈希值；  
3.如果树的节点数不是2的幂，那么可以使用虚拟节点（选择一个可预期的值，例如0或空哈希值）来填充Merkle树的最后一层。  
Merkle树的特点：  
1.安全：由于哈希函数是不可逆的，因此Merkle树的校验和可以有效的保证数据完整性；  
2.高效：Merkle树的校验和可以在不需要下载所有数据块的情况下快速计算得出，这对于需要快速验证数据完整性的应用程序非常有用。  

## 交易核心：（不）存在性证明
### 存在性证明：  
当有全节点收到这个MSG_MERKLEBLOCK请求之后，利用传过来的交易信息在自己的区块链数据库中进行查询，并把验证路径返回给请求源，SPV节点拿到验证路径之后，再做一次merkle校验  
Alice要证明自己的一笔transaction属于某一区块，需要给出该transcation在某一区块中的序号，然后由叶节点由主链计算回Root节点，并验证Root节点的value  
### 不存在性证明：  
不存在性证明基于交易是排序的，通过对比pre与next确定Merkle根进行存在性证明，并锁定pre和next在Merkle Tree TXID Nodes中的位置，并对相应区块进行不确定性证明  
![Image_test](https://github.com/zhuruiqigroup35num1/homework-group-35/blob/main/image/project5_4.png)  

# 核心代码：  

