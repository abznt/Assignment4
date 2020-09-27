// Main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Card.h"
#include "Hand.h"

#include <iostream>
#include <sstream>
#include <libconfig.hh>
#include <iomanip>
#include "spdlog/spdlog.h"

/**
 * @brief Main entry point for the program
 */
int main()
{
    spdlog::set_level(spdlog::level::debug);
    // Load the config file
    libconfig::Config cfg;
    try
    {
        cfg.readFile("../input/assignment4.cfg");
    }
    catch (const libconfig::FileIOException &fioex)
    {
        std::cerr << "I/O error while reading file." << std::endl;
        return(EXIT_FAILURE);
    }
    catch(const libconfig::ParseException &pex)
    {
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
                  << " - " << pex.getError() << std::endl;
        return(EXIT_FAILURE);
    }
    // Parse the config file
    const libconfig::Setting& inputDeck = cfg.getRoot()["InputDeck"];
    // Play the configured games
    for (int iGame = 0; iGame < inputDeck.getLength(); ++iGame)
    {
        spdlog::info("Playing game {}", iGame);
        const libconfig::Setting& game = inputDeck[iGame];
        poker::Hand hand1;
        poker::Hand hand2;
        for (auto &card : game["hand1"])
        {
            hand1.emplaceCard(card[0], card[1]);
        }
        int val1 = hand1.evaluateHand();
        spdlog::info("Hand 1: {}", hand1);
        for (auto &card : game["hand2"])
        {
            hand2.emplaceCard(card[0], card[1]);
        }
        spdlog::info("Hand 2: {}", hand2);
    }
    return EXIT_SUCCESS;
}
