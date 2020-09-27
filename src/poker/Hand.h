#ifndef ASSIGNMENT4_HAND_H
#define ASSIGNMENT4_HAND_H

#include "Card.h"
#include <array>
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace poker {
    class Hand {
    // ---------- Members ----------
    private:
        int m_cardIndex;
        int m_highCard;
        std::array<Card, 5> m_cards;
    // ---------- Methods ----------
    public:
        Hand();

        void addCard(const Card &card);

        void emplaceCard(const std::string &val, const std::string &suit);

        int evaluateHand();

        friend bool operator< (const Hand &hand1, const Hand &hand2);

        friend std::ostream& operator<< (std::ostream &out, const Hand &hand);
    };
}


#endif //ASSIGNMENT4_HAND_H
