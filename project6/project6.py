import hashlib
import random

def range_proof(value, lower, upper):
    #范围证明
    r = random.randint(0, 2**128)
    #随机数r
    h = hashlib.sha256(str(value).encode() + str(r).encode()).digest()
    bits = ''.join(f"{x:08b}" for x in h)
    # 置位，选择哈希值的前k位（k = m+1）
    m = (upper-lower).bit_length()  # 差异单元数
    k = m + 1
    commitment_bits = bits[:k]

    proof_bits = bits[k:k+m]
    commitment = int(commitment_bits, 2)
    proof = int(proof_bits, 2)
    return proof, r
#返回了证明proof和随机数r

def verify_range_proof(value, lower, upper, proof, r):
    h = hashlib.sha256(str(value).encode() + str(r).encode()).digest()

    bits = ''.join(map(lambda x: "{:08b}".format(x), h))
    n = len(bits)  
    m = (upper-lower).bit_length()

    k = m + 1
    commitment_bits = bits[:k]
    proof_bits = bits[k:k+m]
    #重构
    # 验证哈希值的前k位是否与证明一致
    if int(commitment_bits, 2) != proof >> 1:
        return False

    if proof >= (upper-lower) or proof < 0:
        return False
    #范围验证
    # 验证哈希值的后m个比特是否与上限lower一致
    mask = (1 << m) - 1
    if int(proof_bits, 2) & mask != (lower ^ (proof << 1)):
        return False

    return True

