#pragma once
#include <iostream>
#include <memory>
#include "IInputGenerator.h"
#include "IScoringRule.h"
#include "IRewardRule.h"
#include "ShopSystem.h"

// ============================================================
//  RunSession — Controls the game loop
//  INVARIANT: Phase order 1-6 must NEVER change
//
//  1. Generate input
//  2. Compute base score
//  3. Compute reward
//  4. Update money
//  5. Shop phase
//  6. Advance round
//
//  RunSession does NOT contain:
//  - Scoring logic
//  - Reward logic
//  - Input generation logic
// ============================================================
class RunSession {
public:
    RunSession(
        std::shared_ptr<IInputGenerator> inputGen,
        std::shared_ptr<IScoringRule>    scoringRule,
        std::shared_ptr<IRewardRule>     rewardRule
    )
        : inputGen_(inputGen),
          scoringRule_(scoringRule),
          rewardRule_(rewardRule),
          money_(0),
          totalRounds_(3)
    {}

    void run() {
        std::cout << "=== RUN START ===\n";

        for (int round = 1; round <= totalRounds_; ++round) {
            std::cout << "\nRound " << round << "\n";

            // Phase 1 — Generate input
            TurnInput input = inputGen_->generate();
            std::cout << "[PLAY] input generated: " << input.value << "\n";

            // Phase 2 — Compute base score
            int baseScore = scoringRule_->compute(input);
            std::cout << "[SCORE] base score: " << baseScore << "\n";

            // Phase 3 — Compute reward
            int reward = rewardRule_->compute(baseScore, round);

            // Phase 4 — Update money
            money_ += reward;
            std::cout << "[REWARD] gain: " << reward
                      << " | money: " << money_ << "\n";

            // Phase 5 — Shop phase
            shop_.offerAndProcess(money_);

            // Phase 6 — Advance round (implicit via loop)
        }

        std::cout << "\n=== RUN END ===\n";
        std::cout << "Final money: " << money_ << "\n";
    }

private:
    std::shared_ptr<IInputGenerator> inputGen_;
    std::shared_ptr<IScoringRule>    scoringRule_;
    std::shared_ptr<IRewardRule>     rewardRule_;
    ShopSystem shop_;
    int money_;
    int totalRounds_;
};
