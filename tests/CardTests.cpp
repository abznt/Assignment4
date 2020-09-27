#include "gtest/gtest.h"
#include "Card.h"
#include "Suit.h"
#include <stdexcept>
#include <array>

namespace poker {
    TEST(CardTests, TestDefaultConstructor) {
        Card card;
        EXPECT_EQ(card.getValue(), -1);
        EXPECT_EQ(card.getSuit(), Suit::NONE);
    }

    TEST(CardTests, TestValueSuitConstructor) {
        // Test all valid card permutations
        std::array<std::string, 13> values{"2", "3", "4", "5", "6", "7",
                                           "8", "9", "10", "J", "Q", "K", "A"};
        std::array<std::string, 4> suits{"H", "C", "D", "S"};
        for (auto &value : values) {
            for (auto &suit : suits) {
                EXPECT_NO_THROW(Card(value, suit));
            }
        }
        // Test some invalid cards
        EXPECT_THROW(Card("-1", "D"), std::invalid_argument);
        EXPECT_THROW(Card("5", "B"), std::invalid_argument);
    }

    TEST(CardTests, TestOperatorLessThan) {
        Card card1{"5", "H"};
        Card card2{"5", "D"};
        Card card3{"A", "S"};
        EXPECT_TRUE(card1 < card3);
        EXPECT_TRUE(card2 < card3);
        EXPECT_FALSE(card1 < card2);
        EXPECT_FALSE(card2 < card1);
    }

    TEST(CardTests, TestOperatorEquals) {
        Card card1{"7", "C"};
        Card card2{"7", "H"};
        Card card3{"10", "D"};
        Card card4{"J", "S"};
        EXPECT_FALSE(card1 == card3);
        EXPECT_TRUE(card1 == card2);
        EXPECT_FALSE(card3 == card4);
    }
}