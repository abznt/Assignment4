#include "Hand.h"
#include <stdexcept>
#include <algorithm>

namespace poker {
    Hand::Hand() : m_cardIndex{0} {}

    void Hand::addCard(const Card &card) {
        if (m_cardIndex < m_cards.size()) {
            m_cards.at(m_cardIndex) = card;
            ++m_cardIndex;
        } else {
            throw std::runtime_error("Hand::addCard cannot add card since the hand is already full");
        }
    }

    void Hand::emplaceCard(const std::string &val, const std::string &suit) {
        if (m_cardIndex < m_cards.size()) {
            m_cards.at(m_cardIndex) = Card{val, suit};
            ++m_cardIndex;
        } else {
            throw std::runtime_error("Hand::emplaceCard cannot add card since the hand is already full");
        }
    }

    unsigned int Hand::evaluateHand() const {
        if (m_cardIndex < m_cards.size()) {
            throw std::runtime_error("Hand::evaluateHand() - hand does not have a full set of cards");
        }
        // Count the occurances of each card rank
        std::array<int, 13> countByRank{0};
        for (int i = 0; i < m_cards.size(); ++i) {
            countByRank[m_cards[i]-2]++;
        }

        spdlog::debug("Count by rank: [{}] [{}] [{}] [{}] [{}] [{}] [{}] [{}] [{}] [{}] [{}] [{}] [{}]",
                      countByRank[0], countByRank[1], countByRank[2], countByRank[3], countByRank[4], countByRank[5],
                      countByRank[6], countByRank[7], countByRank[8], countByRank[9], countByRank[10], countByRank[11],
                      countByRank[12]);

        // Tests for the various hand types
        std::array<int, 5> straight{1, 1, 1, 1, 1};
        bool isFlush = (m_cards[0].getSuit() == m_cards[1].getSuit()) &&
                (m_cards[1].getSuit() == m_cards[2].getSuit()) &&
                (m_cards[2].getSuit() == m_cards[3].getSuit()) &&
                (m_cards[3].getSuit() == m_cards[4].getSuit());
        auto isStraight = std::search(countByRank.begin(), countByRank.end(), straight.begin(), straight.end());
        auto isFourOfKind = std::find(countByRank.begin(), countByRank.end(), 4);
        auto isTriple = std::find(countByRank.begin(), countByRank.end(), 3);
        auto firstPair = std::find(countByRank.begin(), countByRank.end(), 2);
        std::array<int, 13>::iterator secondPair;
        if (firstPair != countByRank.end()) {
            secondPair = std::find(firstPair + 1, countByRank.end(), 2);
        }
        else {
            secondPair = countByRank.end();
        }

        // Evaluate the hand type and score it
        if ((isStraight != countByRank.end()) && isFlush) {
            // Straight flush
            unsigned int handValue = 8;
            for (int i = countByRank.size() - 1; i >= 0; --i) {
                if (countByRank.at(i) == 1) {
                    handValue = (handValue << 4) + i;
                }
            }
            spdlog::debug("Straight flush identified");
            return handValue;
        }
        else if (isFourOfKind != countByRank.end()) {
            // Four of a kind
            unsigned int handValue = 7;
            int fourIndex = int(isFourOfKind - countByRank.begin());
            for (int i = 0; i < 4; ++i) { handValue = (handValue << 4) + fourIndex; }
            for (int i = countByRank.size() - 1; i >= 0; --i) {
                if (countByRank.at(i) == 1) {
                    handValue = (handValue << 4) + i;
                }
            }
            spdlog::debug("Four of a kind identified");
            return handValue;
        }
        else if ((isTriple != countByRank.end()) && (firstPair != countByRank.end())) {
            // Full house
            unsigned int handValue = 6;
            int tripleIndex = int(isTriple - countByRank.begin());
            int pairIndex = int(firstPair - countByRank.begin());
            for (int i = 0; i < 3; ++i){ handValue = (handValue << 4) + tripleIndex; }
            for (int i = 0; i < 2; ++i){ handValue = (handValue << 4) + pairIndex; }
            spdlog::debug("Full house identified");
            return handValue;
        }
        else if (isFlush) {
            // Flush
            unsigned int handValue = 5;
            for (int i = countByRank.size() - 1; i >= 0; --i) {
                if (countByRank.at(i) == 1) {
                    handValue = (handValue << 4) + i;
                }
            }
            spdlog::debug("Flush identified");
            return handValue;
        }
        else if (isStraight != countByRank.end()) {
            // Straight
            unsigned int handValue = 4;
            for (int i = countByRank.size() - 1; i >= 0; --i) {
                if (countByRank.at(i) == 1) {
                    handValue = (handValue << 4) + i;
                }
            }
            spdlog::debug("Straight identified at {}", isStraight - countByRank.begin());
            return handValue;
        }
        else if (isTriple != countByRank.end()) {
            // Three of a kind
            unsigned int handValue = 3;
            int tripleIndex = int(isTriple - countByRank.begin());
            for (int i = 0; i < 3; ++i){ handValue = (handValue << 4) + tripleIndex; }
            for (int i = countByRank.size() - 1; i >= 0; --i) {
                if (countByRank.at(i) == 1) {
                    handValue = (handValue << 4) + i;
                }
            }
            spdlog::debug("Three of a kind identified");
            return handValue;
        }
        else if ((firstPair != countByRank.end()) && (secondPair != countByRank.end())) {
            // Two pair
            unsigned int handValue = 2;
            int pair1Index = int(firstPair - countByRank.begin());
            int pair2Index = int(secondPair - countByRank.begin());
            for (int i = 0; i < 2; ++i) { handValue = (handValue << 4) + pair2Index; }
            for (int i = 0; i < 2; ++i) { handValue = (handValue << 4) + pair1Index; }
            for (int i = countByRank.size() - 1; i >= 0; --i) {
                if (countByRank.at(i) == 1) {
                    handValue = (handValue << 4) + i;
                }
            }
            spdlog::debug("Two pairs identified");
            return handValue;
        }
        else if (firstPair != countByRank.end()) {
            // One pair
            unsigned int handValue = 1;
            int pairIndex = int(firstPair - countByRank.begin());
            for (int i = 0; i < 2; ++i) { handValue = (handValue << 4) + pairIndex; }
            for (int i = countByRank.size() - 1; i >= 0; --i) {
                if (countByRank.at(i) == 1) {
                    handValue = (handValue << 4) + i;
                }
            }
            spdlog::debug("Pair identified");
            return handValue;
        }
        else {
            // High card
            unsigned int handValue = 0;
            for (int i = countByRank.size() - 1; i >= 0; --i) {
                if (countByRank.at(i) == 1) {
                    handValue = (handValue << 4) + i;
                }
            }
            spdlog::debug("High card identified");
            return handValue;
        }

    }

    int Hand::compareTo(const Hand &hand) const {
        unsigned int myValue = evaluateHand();
        unsigned int otherValue = hand.evaluateHand();
        if (myValue < otherValue) {
            return -1;
        }
        else if (myValue > otherValue) {
            return 1;
        }
        else {
            return 0;
        }
    }

    std::ostream &operator<<(std::ostream &out, const Hand &hand) {
        for (auto &card : hand.m_cards) {
            out << card << " ";
        }
        return out;
    }
}
