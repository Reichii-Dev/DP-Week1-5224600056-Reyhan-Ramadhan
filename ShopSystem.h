#pragma once
#include <iostream>

// ============================================================
//  ShopSystem — Tampilkan tawaran shop, player bisa skip
// ============================================================
class ShopSystem {
public:
    void offerAndProcess(int& money) const {
        int cost = 2;
        int bonus = 2;
        std::cout << "[SHOP] offered: Bonus(+" << bonus
                  << ") cost " << cost << "\n";

        if (money >= cost) {
            std::cout << "[SHOP] Enter 'buy' to purchase or anything to skip: ";
            std::string input;
            std::cin >> input;

            if (input == "buy") {
                money -= cost;
                money += bonus;
                std::cout << "[SHOP] purchased! money: " << money << "\n";
                return;
            }
        }
        std::cout << "[SHOP] skipped\n";
    }
};
