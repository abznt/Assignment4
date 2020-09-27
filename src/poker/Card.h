#ifndef ASSIGNMENT4_CARD_H
#define ASSIGNMENT4_CARD_H

#include "Suit.h"
#include <map>
#include <string>
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace poker {
    class Card {
    // ---------- Members ----------
    private:
        int m_value;
        Suit m_suit;
        static inline const std::map<std::string, int> m_valueMap{std::make_pair("2",  2 ),
                                                                  std::make_pair("3",  3 ),
                                                                  std::make_pair("4",  4 ),
                                                                  std::make_pair("5",  5 ),
                                                                  std::make_pair("6",  6 ),
                                                                  std::make_pair("7",  7 ),
                                                                  std::make_pair("8",  8 ),
                                                                  std::make_pair("9",  9 ),
                                                                  std::make_pair("10", 10),
                                                                  std::make_pair("J",  11),
                                                                  std::make_pair("Q",  12),
                                                                  std::make_pair("K",  13),
                                                                  std::make_pair("A",  14)};
        static inline const std::map<std::string, Suit> m_suitMap{std::make_pair("S", Suit::SPADES),
                                                                  std::make_pair("C", Suit::CLUBS),
                                                                  std::make_pair("H", Suit::HEARTS),
                                                                  std::make_pair("D", Suit::DIAMONDS)};

    // ---------- Methods ----------
    public:
        Card();
        Card(const std::string& val, const std::string& suit);
        [[nodiscard]] int getValue() const;
        void setValue(int val);
        [[nodiscard]] Suit getSuit() const;
        void setSuit(Suit suit);

        operator int() const;
        friend bool operator< (const Card &card1, const Card &card2);
        friend bool operator> (const Card &card1, const Card &card2);
        friend bool operator== (const Card &card1, const Card &card2);
        friend std::ostream& operator<< (std::ostream &out, const Card &card);
    };
}


#endif //ASSIGNMENT4_CARD_H
