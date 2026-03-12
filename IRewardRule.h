#pragma once

// ============================================================
//  IRewardRule — Interface untuk hitung reward dari base score
//  Mutable: bisa diganti tanpa ubah RunSession
// ============================================================
class IRewardRule {
public:
    virtual ~IRewardRule() = default;
    virtual int compute(int baseScore, int round) const = 0;
};

// ============================================================
//  EqualRewardRule — Reward = base score (default)
// ============================================================
class EqualRewardRule : public IRewardRule {
public:
    int compute(int baseScore, int round) const override {
        return baseScore;
    }
};

// ============================================================
//  BonusRewardRule — Modification 2: reward berbeda dari score
//  - Round genap: reward = baseScore * 2
//  - Round ganjil: reward = baseScore + 2
//  RunSession TIDAK berubah sama sekali
// ============================================================
class BonusRewardRule : public IRewardRule {
public:
    int compute(int baseScore, int round) const override {
        if (round % 2 == 0) {
            return baseScore * 2;   // round genap: double
        } else {
            return baseScore + 2;   // round ganjil: +2 bonus
        }
    }
};
