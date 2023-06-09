# Research Report on Merkle Patricia Trie  
MPT: Merkle Patricia Trie  
## MPT来源背景：  
Merkle Patricia Trie最初是由以太坊的创始人Vitalik Buterin等人在以太坊白皮书中提出的，其目的是为了提高以太坊区块链系统的效率和可扩展性。  
## MPT的构成：  
Merkle Patricia Trie是一种基于Merkle树和Patricia树的数据结构，常用于以太坊和其他区块链平台中存储账户和合约地址以及其它一些数据  
该数据结构将原始数据以字节的形式存储在树结构中的叶子节点上，同时使用哈希值来连接叶子节点和非叶子节点。由于哈希是一个固定长度的值，因此可以使用它来验证存储在叶子节点上的数据是否正确，从而保证了数据的完整性和安全性  
Merkle Patricia Trie中的每个节点都有一个前缀和后缀，前缀是其父节点的哈希，后缀是该节点本身存储的数据。这种结构让节点之间可以共用相同的前缀和哈希值，从而大大减少了存储空间的需求  
此外，由于哈希值的唯一性，Merkle Patricia Trie可以保证数据的防篡改性，使得区块链的数据安全可靠  
![Image_test](https://github.com/zhuruiqigroup35num1/homework-group-35/blob/main/image/project22_1.png)  
## 内部节点的特点与关系：  
### 内部节点通常是树结构中的非叶子节点，也称为父节点。其特点主要包括：  
1.内部节点有子节点：内部节点至少有一个子节点，且子节点可以是叶子节点或其他内部节点  
2.内部节点可以有多个子节点：多个子节点之间没有顺序关系，每个子节点可分别指向不同的节点  
3.内部节点通常保存数据：每个内部节点可以保存一些与树相关的信息或数据，如键值、权重等等  
### 其关系主要包括：
1.父节点与子节点之间的关系：  
将一个节点指向另一个节点的指针称为边，父节点与子节点之间的边是从父节点指向子节点的有向边  
2.兄弟节点之间的关系：  
如果两个节点拥有同一个父节点，且在同一级别上，则它们之间就是兄弟节点  
3.祖先节点与子孙节点之间的关系：  
一个节点的祖先节点是它所在路径上的所有父节点，而它的子孙节点包括它本身以及它的所有后代节点  
四个状态要存储在世界状态的MPT树中，需要存入的值是键值对的形式  
首先是根哈希，由keccak256生成的  
绿色的扩展节点Extension Node，其中共同前缀shared nibble是a7，采用了压缩前缀树的方式进行了合并  
蓝色的分支节点Branch Node，其中有表示十六进制的字符和一个value，最后的value是fullnode的数据部分  
紫色的叶子节点leadfNode，用来存储具体的数据，它也是对路径进行了压缩  
![Image_test](https://github.com/zhuruiqigroup35num1/homework-group-35/blob/main/image/project22_2.jpg)  
## MPT简要创建过程：  
1.创建空的Merkle Patricia Trie树，同时创建一个空的根节点  
2.将需要存储的数据按照某种方式进行编码，并将编码后的数据作为键值插入到树中  
3.对每个键值进行哈希运算，并保存哈希值作为节点的路径，在每个节点的数据域中保存键和值的对应关系  
4.在插入每个节点时，需要对节点的路径进行拆分，查找Merkle Patricia Trie树中与该路径最相似的节点，并将该节点作为该插入节点的父节点  
5.如果在查找过程中没有匹配到路径，则需要创建新的节点，并将其添加到树中作为父节点  
6.每次插入节点时需要维护根节点的哈希值，以保证数据不被篡改  
7.在查询数据时，首先对查询数据进行哈希运算，然后根据哈希值进行搜索，如果在Merkle Patricia Trie树中找到了对应的节点，则说明该数据存在  
8.如果需要删除数据，则需要首先对要删除的数据进行哈希运算，然后在树中找到对应节点并删除，同时需要更新父节点及其祖先节点的哈希值  
9.如果删除节点后父节点及其祖先节点没有其他子节点，则需要将其一并删除  
10.在对数据进行修改或删除操作后，需要重新计算根节点的哈希值，以保证数据不被篡改  
## MPT的持久化：  
MPT持久化是指在Merkle Patricia Trie树中对数据进行更改时，不会直接修改原始的树结构，而是通过创建一系列新的节点来表示新的状态，以避免修改原始数据，创建新的版本，并将新的版本链接到先前版本的子节点上，这种方式称为持久化数据结构，确保原始数据的不可变性，同时也方便进行历史记录的管理，从而更加安全和可靠  
以以太坊为例，Merkle Patricia Trie树在以太坊中被用来存储各个账户的状态信息  
当某个账户的状态发生变化时，原始数据不会被直接修改，而是通过创建新的节点来表示新的状态，这样做可以保证原始数据不被篡改，同时也方便对历史记录进行回溯和管理   
 MPT树最终持久化到LevelDB中是k-v的形式，还需要对value进行处理。在以太坊存储键值对之前会采用RLP(以太坊RLP编码)对键值对进行转码，将键值对编码后作为value，计算编码后数据的哈希（keccak256）作为key，存储在levelDB中  
​ 在具体的实现中，为了避免出现相同的key，以太坊会给key增加一些前缀用作区分  
## MPT的优点  
提高以太坊区块链系统的效率和可扩展性  
该结构能够高效地存储和检索数据，并且安全可靠，具有较少的存储空间和查询时间  
保证数据的防篡改性，使得区块链的数据安全可靠  


