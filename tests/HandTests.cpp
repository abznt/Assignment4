#include "gtest/gtest.h"
#include "spdlog/spdlog.h"
#include "Hand.h"

class HandTests : public ::testing::Test {
    void SetUp() override {
        spdlog::set_level(spdlog::level::debug);
    }
};

namespace poker {
    TEST_F(HandTests, TestRoyalFlush) {
        Hand hand{};
        hand.emplaceCard("10", "D");
        hand.emplaceCard("J", "D");
        hand.emplaceCard("Q", "D");
        hand.emplaceCard("K", "D");
        hand.emplaceCard("A", "D");
        EXPECT_EQ(hand.evaluateHand(), 9222808);
    }

    TEST_F(HandTests, TestStraightFlush) {
        Hand hand{};
        hand.emplaceCard("8", "D");
        hand.emplaceCard("9", "D");
        hand.emplaceCard("10", "D");
        hand.emplaceCard("J", "D");
        hand.emplaceCard("Q", "D");
        EXPECT_EQ(hand.evaluateHand(), 9082998);
    }

    TEST_F(HandTests, TestFourOfKind) {
        Hand hand{};
        hand.emplaceCard("5", "D");
        hand.emplaceCard("5", "S");
        hand.emplaceCard("5", "C");
        hand.emplaceCard("5", "H");
        hand.emplaceCard("9", "D");
        EXPECT_EQ(hand.evaluateHand(), 7549751);
    }

    TEST_F(HandTests, TestFullHouse) {
        Hand hand{};
        hand.emplaceCard("5", "D");
        hand.emplaceCard("5", "S");
        hand.emplaceCard("5", "C");
        hand.emplaceCard("9", "H");
        hand.emplaceCard("9", "D");
        EXPECT_EQ(hand.evaluateHand(), 6501239);
    }

    TEST_F(HandTests, TestFlush) {
        Hand hand{};
        hand.emplaceCard("5", "H");
        hand.emplaceCard("2", "H");
        hand.emplaceCard("6", "H");
        hand.emplaceCard("10", "H");
        hand.emplaceCard("9", "H");
        EXPECT_EQ(hand.evaluateHand(), 5796912);
    }

    TEST_F(HandTests, TestStraight) {
        Hand hand{};
        hand.emplaceCard("5", "D");
        hand.emplaceCard("6", "S");
        hand.emplaceCard("7", "C");
        hand.emplaceCard("8", "H");
        hand.emplaceCard("9", "D");
        EXPECT_EQ(hand.evaluateHand(), 4678979);
    }

    TEST_F(HandTests, TestThreeOfKind) {
        Hand hand{};
        hand.emplaceCard("5", "D");
        hand.emplaceCard("5", "S");
        hand.emplaceCard("5", "C");
        hand.emplaceCard("8", "H");
        hand.emplaceCard("9", "D");
        EXPECT_EQ(hand.evaluateHand(), 3355510);
    }

    TEST_F(HandTests, TestTwoPair) {
        Hand hand{};
        hand.emplaceCard("5", "D");
        hand.emplaceCard("5", "S");
        hand.emplaceCard("8", "C");
        hand.emplaceCard("8", "H");
        hand.emplaceCard("9", "D");
        EXPECT_EQ(hand.evaluateHand(), 2515767);
    }

    TEST_F(HandTests, TestPair) {
        Hand hand{};
        hand.emplaceCard("5", "D");
        hand.emplaceCard("5", "S");
        hand.emplaceCard("7", "C");
        hand.emplaceCard("8", "H");
        hand.emplaceCard("9", "D");
        EXPECT_EQ(hand.evaluateHand(), 1259365);
    }

    TEST_F(HandTests, TestHighCard) {
        Hand hand{};
        hand.emplaceCard("5", "D");
        hand.emplaceCard("2", "S");
        hand.emplaceCard("4", "C");
        hand.emplaceCard("8", "H");
        hand.emplaceCard("9", "D");
        EXPECT_EQ(hand.evaluateHand(), 484128);
    }
}