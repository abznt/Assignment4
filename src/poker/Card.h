#ifndef ASSIGNMENT4_CARD_H
#define ASSIGNMENT4_CARD_H

#include "Suit.h"
#include <map>
#include <string>
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace poker {
    /**
     * @brief This class encapsulates a poker card. The card has a rank (value) and a suit.
     */
    class Card {
    // ---------- Members ----------
    private:
        int m_value;
        Suit m_suit;
        /** @brief Maps card string ranks to numeric value */
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
        /** @brief Maps card string suit to enumerated Suit */
        static inline const std::map<std::string, Suit> m_suitMap{std::make_pair("S", Suit::SPADES),
                                                                  std::make_pair("C", Suit::CLUBS),
                                                                  std::make_pair("H", Suit::HEARTS),
                                                                  std::make_pair("D", Suit::DIAMONDS)};

    // ---------- Methods ----------
    public:
        /**
         * Default constructor. Initializes value to -1 and suit to Suit::NONE.
         */
        Card();

        /**
         * @brief Constructs a Card from a value and a suit
         * @param val Card value represented as a string
         * @param suit Card suit represented as a string
         */
        Card(const std::string& val, const std::string& suit);

        /**
         * @brief Gets the card value
         * @return The numeric card value
         */
        [[nodiscard]] int getValue() const;

        /**
         * @brief Gets the card suit
         * @return The enumerated card suit
         */
        [[nodiscard]] Suit getSuit() const;

        /**
         * @brief Converts the card value to an int
         * @return The numeric card value
         */
        operator int() const;

        friend bool operator< (const Card &card1, const Card &card2);

        friend bool operator> (const Card &card1, const Card &card2);

        friend bool operator== (const Card &card1, const Card &card2);

        friend std::ostream& operator<< (std::ostream &out, const Card &card);
    };
}


#endif //ASSIGNMENT4_CARD_H
