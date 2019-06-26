#include "depthprune.h"
#include <chrono>
#include "utils.h"
#include <thread>

int BOARD_SIZE = 5;

int capture_diff(GameState *game_state){
    int black_stones = 0;
    int white_stones = 0;
    for(int r = 1; r < game_state->board->num_rows + 1; r++){
        for(int c = 1;c < game_state->board->num_cols + 1; c++){
            Point p (r, c);
            Color color = game_state->board->get(p);
            if( color == Color::black)
                black_stones += 1;
            else if (color == Color::white)
                white_stones += 1;
        }
    }
    int diff = black_stones - white_stones;                    
    if (game_state->next_player->color == Color::black)    
        return diff;                                       
    return -1 * diff;                                      

}

int main(){
 
 
    GameState * game = GameState::new_game(BOARD_SIZE);
    DepthPrunedAgent bots [3] ;

    for(int i =0; i <3; i++){
        bots[i].setParam(3, capture_diff);
        
    }
    while(!game->is_over()) {
      //  std::this_thread::sleep_for (std::chrono::milliseconds(300));
     //   char c = 27;
     //   std::cout << c << "[2J" << std::endl;
    //    std::cout << "print board" << std::endl;
        print_board(game->board);
      //  std::cout << "next move" << std::endl;
        Move *bot_move = bots[(int)game->next_player->color].select_move(game);
        print_move(game->next_player, bot_move);
        game = game->apply_move(bot_move);
      //  game->printStrings();
     //   game->board->VerifyStrings();
        
        delete bot_move;
    }

    return BOARD_SIZE;
}
