#ifndef RANGE_PROOF_H
#define RANGE_PROOF_H

#include <string>
#include <secp256k1.h>

class RangeProof {
public:
    RangeProof(int minRange, int maxRange, secp256k1_context* context);
    ~RangeProof();
    std::string generateCredential(int value);
    bool verifyCredential(std::string credential);

private:
    int m_minRange;
    int m_maxRange;
    secp256k1_context* m_context;
    std::string generateCommitment(int value);
    std::string generateProof(secp256k1_scalar value, secp256k1_scalar* blindingFactor, secp256k1_scalar* commitment);
    bool verifyProof(secp256k1_ge* value, secp256k1_ge* commitment, secp256k1_ge* blindingFactor, secp256k1_ge* generator, secp256k1_ge* h);

    secp256k1_scalar generateRandomScalar();

    secp256k1_scalar generateBlindingFactor(secp256k1_scalar* r, secp256k1_scalar* commitment, secp256k1_scalar* value);
    secp256k1_scalar generateProofValue(secp256k1_scalar* r, secp256k1_scalar* value, secp256k1_scalar* commitment, secp256k1_scalar* blindingFactor);
    secp256k1_ge getGeneratorPoint(int index);
    secp256k1_scalar hashValue(int value);
};

#endif
