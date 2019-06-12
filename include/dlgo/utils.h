#ifndef _UTIL_H
#define _UTIL_H
#include <string>
#include <map>
#include <iostream>

char COLS[] = "ABCDEFGHJKLMNOPQRST";

std::map<Color,  std::string> STONE_TO_CHAR= {{Color::none,  " . "},
                                              {Color::black,  " . "},
                                              {Color::white,  " . "}};

void print_move(Player * player, Move * move){
    std::string move_str;
    if (move->is_pass)
        move_str = "passes";
    else if (move->is_resign)
        move_str = "resigns";
    else
        move_str = COLS[move->point.col - 1] + move->point.row;
    std::cout << player->print() <<  move_str << std::endl;
}

void print_board(Board * board) {
    for (int row = board->num_rows; row >= 0; row--){
        std::string bump = row <= 9?  " " : "";
        std::cout << bump;
        std::string line ;
        for (int col=1; col < board->num_cols + 1; col++){
            Point p(row, col);
            Color stone = board->get(p);
            std::cout <<  row;
            line+= STONE_TO_CHAR[stone];
        }
        std::cout << COLS[board->num_cols] << " ";
    }
    std::cout << std::endl;
}
#endif
