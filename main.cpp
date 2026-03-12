#include <iostream>
#include <memory>
#include <cstdlib>
#include <ctime>
#include "RunSession.h"
#include "IInputGenerator.h"
#include "IScoringRule.h"
#include "IRewardRule.h"

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // --------------------------------------------------------
    // Modification 1: swap FixedInputGenerator
    //                  -> RandomInputGenerator
    // Modification 2: swap EqualRewardRule
    //                  -> BonusRewardRule
    // RunSession code does NOT change at all.
    // --------------------------------------------------------

    auto inputGen    = std::make_shared<RandomInputGenerator>(); // Mod 1
    auto scoringRule = std::make_shared<SimpleScoring>();
    auto rewardRule  = std::make_shared<BonusRewardRule>();      // Mod 2

    RunSession session(inputGen, scoringRule, rewardRule);
    session.run();

    return 0;
}
