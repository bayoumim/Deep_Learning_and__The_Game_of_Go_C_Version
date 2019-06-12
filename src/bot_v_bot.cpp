
#include "naive.h"
#include <chrono>
#include "utils.h"
#include <thread>

int main(){
    int board_size = 9;
    GameState * game = GameState::new_game(board_size);
    RandomBot bots [3] ;
    while(!game->is_over()) {
        std::this_thread::sleep_for (std::chrono::milliseconds(300));
        char c = 27;
        std::cout << c << "[2J" << std::endl;
        print_board(game->board);
        Move *bot_move = bots[(int)game->next_player->color].select_move(game);
        print_move(game->next_player, bot_move);
        game = game->apply_move(bot_move);
        delete bot_move;
    }


}