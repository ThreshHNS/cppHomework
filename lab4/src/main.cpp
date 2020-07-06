#include <memory>

#include "game.h"
#include "human.h"
#include "computer.h"
#include "computer_smart.h"

int main() {
	
    auto player1 = std::make_shared<computer_strategy_t>("Basic");
    auto player2 = std::make_shared<computer_smart_strategy_t>("Genius");

    for (int i = 0; i < 1337; i++) {
        game_t game(player1, player2);
        game.play();
    }
    player1->print_stat();
    player2->print_stat();
	
	
    // auto player1 = std::make_shared<human_strategy_t>("Andrey");
    // auto player2 = std::make_shared<computer_smart_strategy_t>("Genius");

    game_t game(player1, player2);
    game.play();
	
    return 0;
}
