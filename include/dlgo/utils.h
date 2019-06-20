#ifndef _UTIL_H
#define _UTIL_H
#include <string>
#include <map>
#include <iostream>

char COLS[] = "ABCDEFGHJKLMNOPQRST";

std::map<Color,  std::string> STONE_TO_CHAR= {{Color::none,  " . "},
                                              {Color::black,  " x "},
                                              {Color::white,  " o "}};

void print_move(Player * player, Move * move){
    std::string move_str;
    if (move->is_pass)
        move_str = "passes";
    else if (move->is_resign)
        move_str = "resigns";
    else {
        move_str = COLS[move->point.col - 1] ;
        move_str += std::to_string(move->point.row);
	//std::cout << "row : " << move->point.row << std::endl;
    }
    std::cout << player->print() <<  move_str << std::endl;
}

void print_board(Board * board) {
 //   std::cout << "no. of rows : " << board->num_rows << std::endl;
    for (int row = board->num_rows; row >= 1; row--){
      //  std::cout << board->num_cols ;
     //   std::cout << "row : "   << row << std::endl;
        std::string bump = row <= 9?  " " : "";
      //  std::cout << bump;
        std::string line ;
     //   std::cout <<"hi";
        for (int col=1; col < board->num_cols + 1; col++){
     //       std::cout << "col : " << col << " "<< std::endl;
            Point p(row, col);
           // std::cout <<  "get started" << std::endl;
            Color stone = board->get(p);
       //     std::cout <<  "get finished" << std::endl;
            line+= STONE_TO_CHAR[stone];
        }
        std::cout  << bump << row << line << std::endl;
        
    }
    std::cout << "   "  ;
    for (int col=0; col < board->num_cols; col++){
        std::cout  << COLS[col] << "  ";
    }
    std::cout << std::endl;
}

/*
Point * point_from_coords(coords){
    col = COLS.index(coords[0]) + 1
    row = int(coords[1:])
    return gotypes.Point(row=row, col=col)
}
*/

#endif
