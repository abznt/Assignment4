#include "Card.h"
#include "Hand.h"

#include <iostream>
#include <libconfig.hh>
#include "spdlog/spdlog.h"

/**
 * @brief Main entry point for the program
 */
int main()
{
    // Set logging level
    spdlog::set_level(spdlog::level::info);
    // Load the config file
    libconfig::Config cfg;
    try {
        cfg.readFile("../input/assignment4.cfg");
    }
    catch (const libconfig::FileIOException &fioex) {
        std::cerr << "I/O error while reading file." << std::endl;
        return(EXIT_FAILURE);
    }
    catch(const libconfig::ParseException &pex) {
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
                  << " - " << pex.getError() << std::endl;
        return(EXIT_FAILURE);
    }
    // Parse the config file and get the input deck
    const libconfig::Setting& inputDeck = cfg.getRoot()["InputDeck"];
    // Play the configured games
    for (int iGame = 0; iGame < inputDeck.getLength(); ++iGame)
    {
        spdlog::info("Playing game {}", iGame);
        const libconfig::Setting& game = inputDeck[iGame];
        poker::Hand hand1;
        poker::Hand hand2;
        // Populate the first hand
        for (auto &card : game["hand1"])
        {
            hand1.emplaceCard(card[0], card[1]);
        }
        spdlog::info("Hand 1: {}", hand1);
        // Populate the second hand
        for (auto &card : game["hand2"])
        {
            hand2.emplaceCard(card[0], card[1]);
        }
        spdlog::info("Hand 2: {}", hand2);
        // Compare hands and log the results
        switch (hand1.compareTo(hand2)) {
            case -1:
                spdlog::info("Hand 2 wins");
                break;
            case 1:
                spdlog::info("Hand 1 wins");
                break;
            case 0:
                spdlog::info("Tie");
                break;
        }
    }
    return EXIT_SUCCESS;
}
