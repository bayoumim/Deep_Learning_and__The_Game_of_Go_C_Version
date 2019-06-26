#ifndef _GOBOARD_H
#define _GOBOARD_H
#include "gotypes.h"
#include <cassert>
#include <set>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
#include "zobrist.h"
#include <utility>


class Move {
public:
    Point point;
    bool is_play;
    bool is_resign;
    bool is_pass;

    Move(Point * point = NULL, bool is_pass = false, bool is_resign = false);
    Move(bool is_pass = false, bool is_resign = false);
        
    static Move* play(Point * point, bool verbose = false){ 
        if(verbose) std::cout << "Move is selected at point (" << point->row << "," << point->col << ")." << std::endl;
        return new Move(point);
    }    

    static Move* pass_turn(){ 
       // std::cout << "pass_turn : started";
        return new Move(true);
    }    
        
    static Move* resign(){ 
        return new Move(false,true);
    }    
        
};


class GoString{
public:
    Color color;
    std::set< Point > * stones;
    std::set< Point > * liberties;
    int lcount;
    GoString(Color & color, std::set< Point > * stones, std::set<Point> * liberties, int lcount);

    ~GoString ();

    int num_liberties() ;

    bool operator== (const GoString& rhs) const ;
    void merged_with(GoString * go_string2, bool verbose);
    GoString * deepcopy();

    void printliberties();
    void printstones();


    void without_liberty(Point & point);

    void with_liberty(Point & point);

    void print();
};

class Board{
private:

public:
    int num_rows;
    int num_cols;
    std::map< Point, GoString * > * _grid;
    unsigned long long int _hash;

    Board(int num_rows, int num_cols);
    ~Board();
  
    void place_stone(Player * player, Point & point, bool );

    void  _remove_string(GoString * string);

    bool is_on_grid(Point & point);
    void add_grid(std::map< Point, GoString * > * next_grid);

    void add_hash(unsigned long long int _hash);
    Board * deepcopy();

    GoString *get_go_string(Point & point) ;

    Color get(Point & point);

    void printStrings();

    void VerifyStrings();

    void compareBoard(Board * nextboard);

    void _replace_string(GoString * old_string, GoString * new_string);

    unsigned long long int zobrist_hash();
};


class GameState {
public:
    Board * board;
    Player * next_player;
    GameState * previous_state;
    std::set< std::pair<Color, unsigned long long int> > previous_states;
    Move* last_move;

    GameState(Board * board, Player * next_player, GameState * previous, Move* move);
    ~GameState();
    GameState * apply_move(Move* move) ;

    static GameState * new_game(int board_size){
        Board * board = new Board(board_size,board_size);
        Player * p = new Player(Color::black);
        return new GameState(board, p, NULL, NULL);
    }

    bool is_over();

    bool is_move_self_capture(Player * player, Move* move);

    std::pair < Player * , Board* > * situation();

    bool does_move_violate_ko(Player * player, Move * move);

    bool is_valid_move(Move * move);

    std::vector<Move* > * legal_moves();

    void printStrings();

    Color winner();

    bool is_point_an_eye(Point & point, Color color) ;

};
#endif
