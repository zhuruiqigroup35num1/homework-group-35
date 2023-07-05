#include "range_proof.h"
#include <openssl/sha.h>

RangeProof::RangeProof(int minRange, int maxRange, secp256k1_context* context) {
    m_minRange = minRange;
    m_maxRange = maxRange;
    m_context = context;
}

RangeProof::~RangeProof() {}

std::string RangeProof::generateCommitment(int value) {
    secp256k1_scalar r;
    secp256k1_scalar_set_b32(&r, (const unsigned char*)"r"); 
    secp256k1_scalar_normalize(&r);

    secp256k1_scalar valueScalar;
    secp256k1_scalar_set_int(&valueScalar, value);
    secp256k1_gej valueJacobian, commitmentJacobian;
    secp256k1_ge_set_gej(&valueJacobian, secp256k1_gej_const_g);
    secp256k1_scalar_mul(&valueScalar, &valueScalar, &m_context->blindingGen);
    secp256k1_scalar_mul(&r, &r, &m_context->blindingGen);
    secp256k1_gej_add_ge_var(&commitmentJacobian, &valueJacobian, &m_context->blindingGen, &r, NULL);
    secp256k1_ge commitment;
    secp256k1_ge_set_gej(&commitment, &commitmentJacobian);

    unsigned char commitmentBytes[33];
    secp256k1_fe_normalize(&commitment.x);
    secp256k1_fe_normalize(&commitment.y);
    secp256k1_ge_set_xy(&commitment, &commitment.x, &commitment.y);
    secp256k1_ge_pubkey_serialize(m_context, commitmentBytes, &commitment, SECP256K1_EC_COMPRESSED);
    return std::string(reinterpret_cast<char*>(commitmentBytes), 33);
}


secp256k1_scalar RangeProof::generateRandomScalar() {
    secp256k1_scalar scalar;
    unsigned char sha256sum[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, (const void*)m_context, sizeof(secp256k1_context));
    SHA256_Final(sha256sum, &sha256);
    secp256k1_scalar_set_b32(&scalar, sha256sum);
    secp256k1_scalar_normalize(&scalar);
    return scalar;
}


secp256k1_scalar RangeProof::generateBlindingFactor(secp256k1_scalar* r, secp256k1_scalar* commitment, secp256k1_scalar* value) {
    secp256k1_scalar blindingFactor;
    unsigned char sha256sum[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);


    unsigned char commitmentBytes[33];
    secp256k1_ge commitmentPoint;
    secp256k1_pubkey_parse(m_context, &commitmentPoint, (const unsigned char*)commitment->data, 33);
    secp256k1_fe_normalize(&commitmentPoint.x);
    secp256k1_fe_normalize(&commitmentPoint.y);
    secp256k1_ge_set_xy(&commitmentPoint, &commitmentPoint.x, &commitmentPoint.y);
    secp256k1_ge_pubkey_serialize(m_context, commitmentBytes, &commitmentPoint, SECP256K1_EC_COMPRESSED);
    SHA256_Update(&sha256, commitmentBytes, 33);

    unsigned char blindingGenBytes[33];
    secp256k1_fe_normalize(&m_context->blindingGen.x);
    secp256k1_fe_normalize(&m_context->blindingGen.y);
    secp256k1_ge_set_xy(&m_context->blindingGen, &m_context->blindingGen.x, &m_context->blindingGen.y);
    secp256k1_ge_pubkey_serialize(m_context, blindingGenBytes, &m_context->blindingGen, SECP256K1_EC_COMPRESSED);
    SHA256_Update(&sha256, blindingGenBytes, 33);

    unsigned char valueBytes[33];
    secp256k1_scalar_get_b32(valueBytes, value);
    SHA256_Update(&sha256, valueBytes, 32);

    unsigned char rBytes[33];
    secp256k1_scalar_get_b32(rBytes, r);
    SHA256_Update(&sha256, rBytes, 32);

    SHA256_Final(sha256sum, &sha256);
    secp256k1_scalar_set_b32(&blindingFactor, sha256sum);
    secp256k1_scalar_normalize(&blindingFactor);
    return blindingFactor;
}


secp256k1_scalar RangeProof::generateProofValue(secp256k1_scalar* r, secp256k1_scalar* value, secp256k1_scalar* commitment, secp256k1_scalar* blindingFactor) {
    secp256k1_scalar proofValue;
    secp256k1_scalar valueMinusMinRange;
    secp256k1_scalar_set_int(&valueMinusMinRange, std::abs(m_minRange));
    secp256k1_scalar_negate(&valueMinusMinRange, &valueMinusMinRange);
    secp256k1_scalar_add(&valueMinusMinRange, value, &valueMinusMinRange);
    secp256k1_scalar_mul(&proofValue, &blindingFactor[0], value);
    secp256k1_scalar_mul(&proofValue, &r[1], &proofValue);
    secp256k1_scalar_mul(&proofValue, &valueMinusMinRange, &proofValue);
    secp256k1_scalar_add(&proofValue, &proofValue, &blindingFactor[1]);
    return proofValue;
}


std::string RangeProof::generateProof(secp256k1_scalar value, secp256k1_scalar* blindingFactor, secp256k1_scalar* commitment) {
   
    secp256k1_scalar r;
    do {
        r = generateRandomScalar();
    } while (secp256k1_scalar_is_zero(&r));
    secp256k1_scalar_normalize(&r);
    secp256k1_scalar commitmentY, blindingFactorY;
    secp256k1_scalar_mul(&commitmentY, &r, &m_context->blindingGen);
    secp256k1_scalar_add(&commitmentY, &commitmentY, &value);
