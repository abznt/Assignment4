//
// Created by berge on 9/23/2020.
//

#include "Card.h"
#include <stdexcept>

namespace poker {
    Card::Card() : m_value{-1}, m_suit{Suit::NONE} {}

    Card::Card(const std::string& val, const std::string& suit) {
        auto mappedVal = Card::m_valueMap.find(val);
        if (mappedVal != Card::m_valueMap.end()) {
            m_value = mappedVal->second;
        } else {
            throw std::invalid_argument("Invalid card value passed to constructor");
        }
        auto mappedSuit = Card::m_suitMap.find(suit);
        if (mappedSuit != Card::m_suitMap.end()) {
            m_suit = mappedSuit->second;
        } else {
            throw std::invalid_argument("Invalid card suit passed to constructor");
        }
    }

    int Card::getValue() const {
        return m_value;
    }

    Suit Card::getSuit() const {
        return m_suit;
    }

    Card::operator int() const {
        return m_value;
    }

    bool operator<(const Card &card1, const Card &card2) {
        return card1.m_value < card2.m_value;
    }

    bool operator>(const Card &card1, const Card &card2) {
        return card1.m_value > card2.m_value;
    }

    bool operator==(const Card &card1, const Card &card2) {
        return card1.m_value == card2.m_value;
    }

    std::ostream& operator<< (std::ostream &out, const Card &card) {
        out << "[";
        if (2 <= card.m_value && card.m_value <= 10) {
            out << card.m_value;
        } else {
            switch (card.m_value) {
                case 11: out << "J"; break;
                case 12: out << "Q"; break;
                case 13: out << "K"; break;
                case 14: out << "A"; break;
            }
        }
        out << static_cast<char>(card.m_suit);
        out << "]";
        return out;
    }
}