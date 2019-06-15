
#include "naive.h"
#include <chrono>
#include "utils.h"
#include <thread>

#include <stdio.h>
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void handler(int sig) {
  void *array[10];
  size_t size;

  // get void*'s for all entries on the stack
  size = backtrace(array, 10);

  // print out all the frames to stderr
  fprintf(stderr, "Error: signal %d:\n", sig);
  backtrace_symbols_fd(array, size, STDERR_FILENO);
  exit(1);
}

int main(){
    signal(SIGSEGV, handler);   // install our handler
    signal(SIGABRT, handler);   // install our handler

 
    int board_size = 9;
    GameState * game = GameState::new_game(board_size);
    RandomBot bots [3] ;
    while(!game->is_over()) {
        std::this_thread::sleep_for (std::chrono::milliseconds(300));
        char c = 27;
        std::cout << c << "[2J" << std::endl;
        std::cout << "print board" << std::endl;
        print_board(game->board);
        std::cout << "next move" << std::endl;
        Move *bot_move = bots[(int)game->next_player->color].select_move(game);
        print_move(game->next_player, bot_move);
        game = game->apply_move(bot_move);
        delete bot_move;
    }

    return board_size;
}
