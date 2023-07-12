import binascii
import random
from stringprep import c22_specials
import hashlib
import math
import SM3


p =0x8542D69E4C044F18E8B92435BF6FF7DE457283915C45517D722EDB8B08F1DFC3
a = 0x787968B4FA32C3FD2417842E73BBFEFF2F3C848B6831D7E0EC65228B3937E498
b = 0x63E4C6D3B23B0C849CF84241484BFE48F61D59A5B16BA06E6E12D1DA27C5249A
G=(0x421DEBD61B62EAB6746434EBC3CC315E32220B3BADD50BDC4C4E6C147FEDD43D,
    0x0680512BCBB42C07D47349D2153B70C4E5D7FDFCBFA36EA1A85841B9E46E09A2)
n=0x8542D69E4C044F18E8B92435BF6FF7DD297720630485628D5AE74EE7C32E79B7
h = 1
Fp = 256

def inverse_mod(a, p):
    old_s, s = 1, 0
    old_t, t = 0, 1
    old_r, r = a, p
    if p == 0:
        return 1, 0, a
    else:
        while r != 0:
            q = old_r // r
            old_r, r = r, old_r - q * r
            old_s, s = s, old_s - q * s
            old_t, t = t, old_t - q * t
    return (old_s%p+p)%p

def On_curve(point):
    #无穷远点
    if point is None:
        return True
    else:
        x,y = point
        return (y*y-x*x*x-a*x-b)%p == 0


def point_add(point1,point2):
    assert On_curve(point1) and On_curve(point2)
    if point1 == None:
        return point2
    if point2  == None:
        return point1
    x1,y1 = point1
    x2,y2 = point2
    if x1 == x2 :
        if y1 !=y2:
            return None
        else:
            return double(point1)
    else:
        lamb = (y2-y1)*inverse_mod((x2-x1)%p,p)%p
        x3 = (lamb**2-x1-x2)%p
        y3 = (lamb*(x1-x3)-y1)%p
    point3 = (x3,y3)
    return point3


def double(point):
    assert On_curve(point)
    if point == None:
        return point
    x,y = point
    lamb = (3*(x**2)+a)*inverse_mod((2*y)%p,p)%p
    x3 = (lamb**2-2*x)%p
    y3 = (lamb*(x-x3)-y)%p
    point3 = (x3,y3)
    return point3


def Scalar_mult(k,point):
    assert On_curve(point)
    flag = 1<<255
    acc = None
    for i in range(255):
        if 0!=k&flag:
            acc = point_add(point,acc)
        acc = double(acc)
        flag>>=1
    if 0!=k&flag:
        acc = point_add(acc,point)
    return acc

def Key_gen():
    sK = random.randrange(1,n)
    pK = Scalar_mult(sK,G)
    return sK,pK

IDA = 'ida'
IDB = 'idb'
klen= 128
da,Pka = Key_gen()
db,Pkb = Key_gen()
Za = '{:04x}'.format(len(IDA)*4)+str(a)+str(b)+str(G[0])+str(G[1])+str(Pka[0])+str(Pka[1])
Zb = '{:04x}'.format(len(IDA)*4)+str(a)+str(b)+str(G[0])+str(G[1])+str(Pkb[0])+str(Pkb[1])


def Alice(Ra,Rb,ra):
    w = math.ceil(math.log2(n)/2)-1
    _x1=((1<<w)+(Ra[0]&((1<<w)-1)))%(1<<128)
    ta=(da+_x1*ra)%n
    _x2=((1<<w)+(Rb[0]&((1<<w)-1)))%(1<<128)
    X2Rb = Scalar_mult(_x2,Rb)
    temp = point_add(Pkb,X2Rb)
    U=Scalar_mult(h*ta,temp)
    Xu,Yu = U
    m=str(Xu)+str(Yu) +Za+Zb
    Ka = SM3.KDF(m,klen)
    print("Alice计算的K",Ka)
    S1msg = "0x02"+str(Yu)+hashlib.sha256((str(Xu)+Za+Zb+str(Ra)+str(Rb)).encode()).hexdigest()
    S1 = hashlib.sha256(S1msg.encode()).hexdigest()
    print("Alice计算的S1：",S1)
    Samsg = "0x03"+str(Yu)+hashlib.sha256((str(Xu)+Za+Zb+str(Ra)+str(Rb)).encode()).hexdigest()
    SA = hashlib.sha256(Samsg.encode()).hexdigest()
    print("Alice计算的SA：",SA)
    return 

def Bob(Ra,Rb,rb):
    w = math.ceil(math.log2(n)/2)-1
    x2 = Rb[0]
    _x2 = ((1<<w)+(x2&((1<<w)-1)))%(1<<128)
    tb = (db+_x2*rb)%n
    _x1 = ((1<<w)+(Ra[0]&((1<<w)-1)))%(1<<128)
    x1Ra = Scalar_mult(_x1,Ra)
    temp = point_add(x1Ra,Pka)
    V = Scalar_mult(h*tb,temp)
    Xv,Yv = V
    msg = str(Xv)+str(Yv)+Za+Zb
    Kb = SM3.KDF(msg,klen)
    print("Bob计算的K",Kb)
    Sbmsg = "0x02"+str(Yv)+hashlib.sha256((str(Xv)+Za+Zb+str(Ra)+str(Rb)).encode()).hexdigest()
    SB = hashlib.sha256(Sbmsg.encode()).hexdigest()
    print("Bob计算的SB:",SB)
    S2msg = "0x03"+str(Yv)+hashlib.sha256((str(Xv)+Za+Zb+str(Ra)+str(Rb)).encode()).hexdigest()
    S2 = hashlib.sha256(S2msg.encode()).hexdigest()
    print("Bob计算的S2:",S2)
    return 

import random
from stringprep import c22_specials
# SM3
import math
from typing import ByteString


IV = [0x7380166F, 0x4914B2B9, 0x172442D7, 0xDA8A0600, 0xA96F30BC, 0x163138AA, 0xE38DEE4D, 0xB0FB0E4E]
T = [0x79cc4519, 0x7a879d8a]

def AsToByte(string):
    BString = ''
    for i in string:
        BString += hex(ord(i))[2:]
    return BString


def FF(X, Y, Z, j):
    if j >= 0 and j <= 15:
        return X ^ Y ^ Z
    else:
        return ((X & Y) | (X & Z) | (Y & Z))


def RoundS(X, i):
    i = i % 32
    return ((X << i) & 0xFFFFFFFF) | ((X & 0xFFFFFFFF) >> (32 - i))


def GG(X, Y, Z, j):
    if j >= 0 and j <= 15:
        return X ^ Y ^ Z
    else:
        return ((X & Y) | (~X & Z))


def P0(X):
    return X ^ RoundS(X, 9) ^ RoundS(X, 17)


def P1(X):
    return X ^ RoundS(X, 15) ^ RoundS(X, 23)


def T_(j):
    if j >= 0 and j <= 15:
        return T[0]
    else:
        return T[1]


def Pad(message):
    m = bin(int(message, 16))[2:]
    if len(m) != len(message) * 4:
        m = '0' * (len(message) * 4 - len(m)) + m
    l = len(m)
    Pad_len = '0' * (64 - len(bin(l)[2:])) + bin(l)[2:]
    m = m + '1'
    if len(m) % 512 > 448:
        m = m + '0' * (512 - len(m) % 512 + 448) + Pad_len
    else:
        m = m + '0' * (448 - len(m) % 512) + Pad_len
    m = hex(int(m, 2))[2:]
    return m


def Group(m):
    n = len(m) / 128
    M = []
    for i in range(int(n)):
        M.append(m[0 + 128 * i:128 + 128 * i])
    return M


def Ex_msg(M, n):
    W = []
    _W = []
    for j in range(16):
        W.append(int(M[n][0 + 8 * j:8 + 8 * j], 16))
    for j in range(16, 68):
        W.append(P1(W[j - 16] ^ W[j - 9] ^ RoundS(W[j - 3], 15)) ^ RoundS(W[j - 13], 7) ^ W[j - 6])
    for j in range(64):
        _W.append(W[j] ^ W[j + 4])
    return W, _W


def CF(V, M, i):
    A, B, C, D, E, F, G, H = V[i]
    W, _W = Ex_msg(M, i)
    for j in range(64):
        SS1 = RoundS((RoundS(A, 12) + E + RoundS(T_(j), j % 32)) % (2 ** 32), 7)
        SS2 = SS1 ^ RoundS(A, 12)
        TT1 = (FF(A, B, C, j) + D + SS2 + _W[j]) % (2 ** 32)
        TT2 = (GG(E, F, G, j) + H + SS1 + W[j]) % (2 ** 32)
        D = C
        C = RoundS(B, 9)
        B = A
        A = TT1
        H = G
        G = RoundS(F, 19)
        F = E
        E = P0(TT2)
    a, b, c, d, e, f, g, h = V[i]
    V_ = [a ^ A, b ^ B, c ^ C, d ^ D, e ^ E, f ^ F, g ^ G, h ^ H]
    return V_


def Round_iter(M):
    n = len(M)
    V = []
    V.append(IV)
    for i in range(n):
        V.append(CF(V, M, i))
    return V[n]


def SM3(message):
    m = Pad(message)  
    M = Group(m)  
    Vn = Round_iter(M)  
    res = ''
    for x in Vn:
            res += hex(x)[2:]
    return res



def KDF(z,klen):
    klen = int(klen)
    ct = 0x00000001
    cnt = math.ceil(klen/32)
    Ha = ""
    for i in range(cnt):
        msg = z+hex(ct)[2:].rjust(8,'0')
        #print(msg)
        Ha  = Ha + SM3(msg)
        #print(Ha)
        ct += 1
    return Ha[0:klen*2]

import string
import base64
from Crypto.Cipher import AES

def Pad(value):
    while len(value) % 16 != 0:
        value += '\0'
    return str.encode(value)  

def AES_encrypt(key, text):
    #使用AES作为对称加密部分
    aes = AES.new(Pad(key), AES.MODE_ECB)  
    encrypt_aes = aes.encrypt(Pad(text))  
    text = str(base64.encodebytes(encrypt_aes), encoding='utf-8')  
    return text

def AES_decrypt(key, text):
    aes = AES.new(Pad(key), AES.MODE_ECB)  
    base64_text = base64.decodebytes(text.encode(encoding='utf-8'))  
    text = str(aes.decrypt(base64_text), encoding='utf-8').replace('\0', '')  
    return text

def Get_str(strlen):
    str = ''
    a = [random.choice(string.digits+'abcdef') for i in range(strlen)]
    str = "".join(a)
    return str

p =0x8542D69E4C044F18E8B92435BF6FF7DE457283915C45517D722EDB8B08F1DFC3
a = 0x787968B4FA32C3FD2417842E73BBFEFF2F3C848B6831D7E0EC65228B3937E498
b = 0x63E4C6D3B23B0C849CF84241484BFE48F61D59A5B16BA06E6E12D1DA27C5249A
G=(0x421DEBD61B62EAB6746434EBC3CC315E32220B3BADD50BDC4C4E6C147FEDD43D,
    0x0680512BCBB42C07D47349D2153B70C4E5D7FDFCBFA36EA1A85841B9E46E09A2)
n=0x8542D69E4C044F18E8B92435BF6FF7DD297720630485628D5AE74EE7C32E79B7
h = 1
Fp = 256

def inverse_mod(a, p):
    old_s, s = 1, 0
    old_t, t = 0, 1
    old_r, r = a, p
    if p == 0:
        return 1, 0, a
    else:
        while r != 0:
            q = old_r // r
            old_r, r = r, old_r - q * r
            old_s, s = s, old_s - q * s
            old_t, t = t, old_t - q * t
    return (old_s%p+p)%p

def On_curve(point):
    if point is None:
        return True
    else:
        x,y = point
        return (y*y-x*x*x-a*x-b)%p == 0


def point_add(point1,point2):
    #椭圆曲线上点的加法
    assert On_curve(point1) and On_curve(point2)
    if point1 == None:
        return point2
    if point2  == None:
        return point1
    x1,y1 = point1
    x2,y2 = point2
    if x1 == x2 :
        if y1 !=y2:
            return None
        else:
            return double(point1)
    else:
        lamb = (y2-y1)*inverse_mod((x2-x1)%p,p)%p
        x3 = (lamb**2-x1-x2)%p
        y3 = (lamb*(x1-x3)-y1)%p
    point3 = (x3,y3)
    return point3


def double(point):
    assert On_curve(point)
    if point == None:
        return point
    x,y = point
    lamb = (3*(x**2)+a)*inverse_mod((2*y)%p,p)%p
    x3 = (lamb**2-2*x)%p
    y3 = (lamb*(x-x3)-y)%p
    point3 = (x3,y3)
    return point3


def Scalar_mult(k,point):
    assert On_curve(point)
    flag = 1<<255
    acc = None
    for i in range(255):
        if 0!=k&flag:
            acc = point_add(point,acc)
        acc = double(acc)
        flag>>=1
    if 0!=k&flag:
        acc = point_add(acc,point)
    return acc

def Key_gen():
    sK = random.randrange(1,n)
    pK = Scalar_mult(sK,G)
    return sK,pK


def encryption(M, Pk):
    #加密部分
    msg = M.encode('utf-8')
    msg = msg.hex()  
    k,c = Key_gen()
    C1 = str(c[0])+str(c[1]) 
    #print(C1)
    lenx = len(str(c[0]))
    length  = len(C1)
    if Pk == None:
        print("Infinite point!")
        exit(1)

    x2,y2  = Scalar_mult(k,Pk)

    xy = str(x2)+str(y2)
    lenMsg = len(msg)

    t = SM3.KDF(xy, lenMsg / 2)

    if int(t, 16) == 0:
        temp = encryption(M, Pk)
        return temp
    else:
        form = '%%0%dx' % lenMsg
        C2 = form % (int(msg, 16) ^ int(t, 16))
        C3 = SM3.SM3(str(x2) + msg + str(y2))


        return C1 + C3 + C2,length,lenx


def decryption(C, Sk, length,lenx):
    #解密部分
    length2 = length+64
    C1 = C[0:length]

    x = int(C1[:lenx], 10)
    y = int(C1[lenx:], 10)
    if pow(y, 2) % p != (pow(x, 3) + a * x + b) % p:
        print("C1不满足方程")
        exit(1)
    if C1 == None:
        print("Infinite point!")
        exit(1)
    C3 = C[length:length2]
    C2 = C[length2:]
    x2,y2 = Scalar_mult(Sk,(x,y))
    xy = str(x2)+str(y2)
    cl = len(C2)

    t = SM3.KDF(xy, cl / 2)

    if int(t, 16) == 0:
        return None
    else:
        form = '%%0%dx' % cl
        M = form % (int(C2, 16) ^ int(t, 16))

        u = SM3.SM3(str(x2) + M + str(y2))
        if u == C3:
            return M
        else:
            return None

def PGP_Send(pK,data,Com_key):
    #发送方
    ciphertext =AES_encrypt(Com_key,data)
    cipherkey,length,lenx = encryption(Com_key,pK)
    print("加密消息: ",ciphertext)
    return ciphertext,cipherkey,length,lenx


def PGP_Receive(d,ciphertext,cipherkey,length,lenx):
    #接收方
    temp = decryption(cipherkey,d,length,lenx)
    temp = bytes.fromhex(temp)
    Com_key = temp.decode()
    plaintext = AES_decrypt(Com_key,ciphertext)
    print("解密消息: ",plaintext)
    return 

if __name__ == "__main__":
    len_para = int(Fp/4)
    sK,pK = Key_gen()
    data = '202122202219'
    ra,Ra = Key_gen()
    rb,Rb = Key_gen()
    Ka = SM2_KeyEx.Alice(Ra,Rb,ra)
    Kb = SM2_KeyEx.Bob(Ra,Rb,rb)
    if Ka == Kb:
        Ka = Ka[:32] 
        print("消息： 202122202219")
        ciphertext,cipherkey,length,lenx = PGP_Send(pK,data,Ka)
        PGP_Receive(sK,ciphertext,cipherkey,length,lenx)
