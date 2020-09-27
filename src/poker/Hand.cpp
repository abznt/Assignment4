//
// Created by berge on 9/26/2020.
//

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

    int Hand::evaluateHand() {
        std::sort(m_cards.begin(), m_cards.end());
        std::array<int, 13> countByRank{0};
        for (auto &card : m_cards) {
            countByRank[card-2]++;
        }
        spdlog::debug("Count by rank: [{}] [{}] [{}] [{}] [{}] [{}] [{}] [{}] [{}] [{}] [{}] [{}] [{}]",
                      countByRank[0], countByRank[1], countByRank[2], countByRank[3], countByRank[4], countByRank[5],
                      countByRank[6], countByRank[7], countByRank[8], countByRank[9], countByRank[10], countByRank[11],
                      countByRank[12]);
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
        if ((isStraight != countByRank.end()) && isFlush) {
            spdlog::debug("Straight flush identified at {}", isStraight - countByRank.begin());
        }
        else if (isFourOfKind != countByRank.end()) {
            spdlog::debug("Four of a kind identified at {}", isFourOfKind - countByRank.begin());
        }
        else if ((isTriple != countByRank.end()) && (firstPair != countByRank.end())) {
            spdlog::debug("Full house identified at {}, {}", isTriple - countByRank.begin(), firstPair - countByRank.begin());
        }
        else if (isFlush) {
            spdlog::debug("Flush identified");
        }
        else if (isStraight != countByRank.end()) {
            spdlog::debug("Straight identified at {}", isStraight - countByRank.begin());
        }
        else if (isTriple != countByRank.end()) {
            spdlog::debug("Three of a kind identified at {}", isTriple - countByRank.begin());
        }
        else if ((firstPair != countByRank.end()) && (secondPair != countByRank.end())) {
            spdlog::debug("Two pairs identified at {}, {}", firstPair - countByRank.begin(), secondPair - countByRank.begin());
        }
        else if (firstPair != countByRank.end()) {
            int pairValue = int(firstPair - countByRank.begin() + 2);
            countByRank.at(*firstPair) = 0;
            spdlog::debug("Pair identified at {}", firstPair - countByRank.begin());
            return 1000 + 50*pairValue;
        }
        else {
            auto kickerValue = (countByRank.rend() - std::find(countByRank.rbegin(), countByRank.rend(), 1) - 1) + 2;
            spdlog::debug("High card identified: {}", kickerValue);
            return kickerValue;
        }
        return 0;
    }

    bool operator<(const Hand &hand1, const Hand &hand2) {
        if (hand1.m_cardIndex < hand1.m_cards.size()) {
            throw std::runtime_error("Hand::operator< hand 1 does not have a full set of cards");
        }
        if (hand2.m_cardIndex < hand2.m_cards.size()) {
            throw std::runtime_error("Hand::operator< hand 2 does not have a full set of cards");
        }
        return false;
    }

    std::ostream &operator<<(std::ostream &out, const Hand &hand) {
        for (auto &card : hand.m_cards) {
            out << card << " ";
        }
        return out;
    }
}
