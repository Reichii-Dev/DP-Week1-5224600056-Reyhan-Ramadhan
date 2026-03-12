#pragma once
#include "TurnInput.h"
#include <cstdlib>

// ============================================================
//  IInputGenerator — Interface untuk generate input per ronde
//  Mutable: bisa diganti tanpa ubah RunSession
// ============================================================
class IInputGenerator {
public:
    virtual ~IInputGenerator() = default;
    virtual TurnInput generate() const = 0;
};

// ============================================================
//  FixedInputGenerator — Selalu return nilai tetap (3)
// ============================================================
class FixedInputGenerator : public IInputGenerator {
public:
    TurnInput generate() const override {
        return TurnInput{3};
    }
};

// ============================================================
//  RandomInputGenerator — Return nilai random 1-10
//  Modification 1: replace FixedInputGenerator dengan ini
//  RunSession TIDAK berubah sama sekali
// ============================================================
class RandomInputGenerator : public IInputGenerator {
public:
    TurnInput generate() const override {
        return TurnInput{(std::rand() % 10) + 1};
    }
};
