#ifndef ASSIGNMENT4_HAND_H
#define ASSIGNMENT4_HAND_H

#include "Card.h"

#include <array>
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace poker {
    /**
     * @brief This class encapsulates a poker hand. The hand contains 5 cards.
     */
    class Hand {
    // ---------- Members ----------
    private:
        int m_cardIndex;
        int m_highCard;
        std::array<Card, 5> m_cards;
    // ---------- Methods ----------
    public:
        /**
         * @brief Hand default constructor. Initializes an empty array of cards.
         */
        Hand();

        /**
         * @brief Adds an existing card to the hand
         * @param card Card to be added
         * @throws std::runtime_error if the hand is already full
         */
        void addCard(const Card &card);

        /**
         * @brief Constructs a card in plance and adds it to the hand
         * @param val Card value
         * @param suit Card suit
         * @throws std::runtime_error if the hand is already full
         */
        void emplaceCard(const std::string &val, const std::string &suit);

        /**
         * @brief Computes the numeric score of the hand.
         * @return The score of the current hand
         * @throws std::runtime_error if the hand has less than 5 cards
         */
        [[nodiscard]] unsigned int evaluateHand() const;

        /**
         * @brief Compares one hand to another
         * @param hand The hand to compare with
         * @return 1 if this hand beats the other hand, 0 if the hands are equal, or -1 if the other hand beats this hand
         */
        [[nodiscard]] int compareTo(const Hand &hand) const;

        friend std::ostream& operator<< (std::ostream &out, const Hand &hand);
    };
}


#endif //ASSIGNMENT4_HAND_H
