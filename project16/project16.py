import random
from stringprep import c22_specials
import math
#SM3实现
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
        Ha  = Ha + SM3(msg)
        ct += 1
    return Ha[0:klen*2]

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

print("\t")


def P2_enc_dec(M): 
    d1 = random.randrange(1,n)
    print("A私钥d1:",d1)
    d2 = random.randrange(1,n)
    print("B私钥d2:",d2)
    msg = M.encode('utf-8')
    msg = msg.hex() 
    k = random.randrange(1,n)
    c = Scalar_mult(k,G)
    C1 = str(c[0])+str(c[1])
    ned = inverse_mod((d1*d2)%p,p)-1
    P = Scalar_mult(ned,G)
    x2,y2 = Scalar_mult(k,P)
    lenMsg = len(msg)
    t = KDF(str(x2)+str(y2), lenMsg / 2)
    form = '%%0%dx' % lenMsg
    C2 = form % (int(msg, 16) ^ int(t, 16))
    C3 = SM3(str(x2) + msg + str(y2))
    C = C1+C2+C3
    print("加密得密文：",C)
    T1 = Scalar_mult(inverse_mod(d1%p,p)%p,c)
    print("A得到密文，计算T1:",T1)
    T2 = Scalar_mult(inverse_mod(d2%p,p)%p,T1)
    print("B得到T1计算T2：",T2)

    print("A得到T2，计算明文：")
    _c = (c[0],p-c[1])
    _P = point_add(T2,_c)
    _x2,_y2 = _P
    _x2,_y2 = Scalar_mult(k,P)
    t = KDF(str(_x2)+str(_y2), lenMsg / 2)
    form = '%%0%dx' % lenMsg
    _M = form % (int(C2, 16) ^ int(t, 16))
    u = SM3(str(_x2) + _M +str(_y2))
    if u == C3:
        return _M
    else:
        return None


if __name__ == "__main__":
    print("明文: 202122202219.")
    a = P2_enc_dec('202122202219')
    print(bytes.fromhex(a).decode())
    print("\t")
