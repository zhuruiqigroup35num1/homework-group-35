import math
import secrets
from hashlib import sha256

DEBUG = 0       
FORGE_DEBUG = 1 
A = 0
B = 7
G_x = 0x79BE667EF9DCBBAC55A06295CE870B07029BFCDB2DCE28D959F2815B16F81798
G_y = 0x483ADA7726A3C4655DA4FBFC0E1108A8FD17B448A68554199C47D08FFB10D4B8
G = (G_x, G_y)
P = 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2F
N = 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEBAAEDCE6AF48A03BBFD25E8CD0364141



def elliptic_add(p, q):
    if p == 0 and q == 0: return 0
    elif p == 0: return q
    elif q == 0: return p
    else:
        if p[0] > q[0]:
            temp = p
            p = q
            q = temp
        r = []

        slope = (q[1] - p[1])*pow(q[0] - p[0],-1, P) % P

        r.append((slope**2 - p[0] - q[0]) % P)
        r.append((slope*(p[0] - r[0]) - p[1]) % P)

        return (r[0], r[1])

if DEBUG:
    print(elliptic_add(0,(15,7)))
    print(elliptic_add((1,60),(15,7)))

def elliptic_double(p):
    r = []
    slope = (3*p[0]**2 + A)*pow(2*p[1],-1, P) % P

    r.append((slope**2 - 2*p[0])%P)
    r.append((slope*(p[0] - r[0]) - p[1])%P)

    return (r[0], r[1])
if DEBUG:
    print("elliptic_double((1,5))= " ,elliptic_double((1,5)))
    print("elliptic_double(G)= ",elliptic_double(G))


def elliptic_multiply(s, p):
    n = p
    r = 0 

    s_binary = bin(s)[2:] 
    s_length = len(s_binary)

    for i in reversed(range(s_length)):     
        if s_binary[i] == '1':
            r = elliptic_add(r, n)
        n = elliptic_double(n)

    return r

if DEBUG:
    print(elliptic_multiply(2, G) == elliptic_double(G))
    print(elliptic_multiply(4, G) == elliptic_add(elliptic_multiply(3, G), elliptic_multiply(1, G)))


def generate_private_key():
    return int(secrets.token_hex(32), 16)


def generate_public_key(private_key):
    return elliptic_multiply(private_key, G)


def generate_key_pair():
  
    private_key = generate_private_key()
    public_key = generate_public_key(private_key)

    return (private_key, public_key) 

if DEBUG:
    (sample_private_key, sample_public_key) = generate_key_pair()
    print("Private Key : ",sample_private_key)
    print("Public Key  : ",sample_public_key)


def double_hash(message):
    hashed_message = sha256(message.encode('utf-8')).hexdigest()
    hashed_message = sha256(hashed_message.encode('utf-8')).hexdigest()
    return int(hashed_message, 16)

if DEBUG:
    print(double_hash("202122202219"))


def sign(private_key, message):

    hashed_message = double_hash(message)
    k = secrets.randbelow(P)
    R = elliptic_multiply(k, G) 
    R_x = R[0] % N

    signature = pow(k,-1, N) * (hashed_message + R_x*private_key) % N

    return (R_x, signature)

if DEBUG:
    message = "Alice sends to Bob 12 Bitcoins"
    signature = sign(sample_private_key, message)

    print("Message: " + message)
    print("Signature: ", end="")
    print(signature)

def verify(public_key, message, signature,hashed_message=None):
    (R_x, s) = signature

    if not hashed_message:
        hashed_message = double_hash(message)

    s_inv = pow(s,-1, N)

    a = elliptic_multiply(hashed_message * s_inv % N, G)
    b = elliptic_multiply(R_x * s_inv % N, public_key)
    recovered_random_point = elliptic_add(a, b)

    return recovered_random_point[0] == R_x

if DEBUG:
    print(verify(sample_public_key, message, signature))


def forge_a_signature(pubk):

    u = secrets.randbelow(P)
    v = secrets.randbelow(P)
    v_inv = pow(v,-1,N)

    R = elliptic_add(elliptic_multiply(u,G),elliptic_multiply(v,pubk))
    if FORGE_DEBUG:
        print("u = {},v = {}".format(hex(u),hex(v)))
        print("R = ({},{})".format(hex(R[0]),hex(R[1])))
    forge_rx = R[0]
    forge_e = forge_rx*u*v_inv % N
    forge_s = forge_rx*v_inv % N
    forge_sig = (forge_rx,forge_s)
    if FORGE_DEBUG:
        print("e' = ", hex(forge_e))
        print("s' = ", hex(forge_s))
        print("伪造消息签名：sig = ({},{})".format(hex(forge_sig[0]),hex(forge_sig[1])))

    if verify(pubk,None,forge_sig,forge_e):
        print("伪造消息签名通过验证")
        print("\t")
        return True

if __name__ =="__main__":
    (testsk,testvk) = generate_key_pair()
    print("\t")
    print("public key: (x = {},y = {})".format(hex(testvk[0]),hex(testvk[1])))
    forge_a_signature(testvk)
