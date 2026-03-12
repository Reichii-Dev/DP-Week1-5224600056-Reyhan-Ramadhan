#pragma once
#include "TurnInput.h"

// ============================================================
//  IScoringRule — Interface untuk hitung base score dari input
//  Mutable: bisa diganti tanpa ubah RunSession
// ============================================================
class IScoringRule {
public:
    virtual ~IScoringRule() = default;
    virtual int compute(const TurnInput& input) const = 0;
};

// ============================================================
//  SimpleScoring — Base score = nilai input langsung
// ============================================================
class SimpleScoring : public IScoringRule {
public:
    int compute(const TurnInput& input) const override {
        return input.value;
    }
};
