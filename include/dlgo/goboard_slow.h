#ifndef _GOBOARD_SLOW_H
#define _GOBOARD_SLOW_H
#include "gotypes.h"
#include <cassert>
#include <set>
#include <vector>
#include <map>
#include <algorithm>


class Move {
public:
    Point point;
    bool is_play;
    bool is_resign;
    bool is_pass;

    Move(Point * point = NULL, bool is_pass = false, bool is_resign = false){
        assert(! point->isNone() || is_pass || is_resign);
        this->point = *point;
        Move(is_pass, is_resign);
    }
    Move(bool is_pass = false, bool is_resign = false){
        assert(!point.isNone() || is_pass || is_resign);
        this->is_pass = is_pass;
        this->is_resign = is_resign;
        this->is_play = !point.isNone();
    }
        
    static Move* play(Point & point){ 
        Point p = point;   
        return new Move(&p);
    }    
        
    static Move* pass_turn(){ 
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
    GoString(Color & color, std::set< Point > * stones, std::set<Point> * liberties, int lcount){    
        this->color = color;
        this->stones = stones;
        this->liberties = liberties;
        this->lcount = lcount;
    }

    ~GoString (){
        stones->clear();
        delete stones;
        liberties->clear();
        delete liberties;
    }   
    void remove_liberty(Point & point) {  
        assert(lcount >0);  
        liberties->erase(point);
        lcount --;
    }   
    void add_liberty(Point & point) {    
        liberties->insert(point);
        lcount++;
    }   
    int num_liberties() {    
        return lcount;
    }    

    bool operator== (const GoString& rhs) const {
        return (this->color == rhs.color) && 
               *(this->stones) == *(rhs.stones) && 
               *(this->liberties) == *(rhs.liberties);
    }
    static GoString * merged_with(GoString * go_string1, GoString * go_string2){
        assert(go_string1->color == go_string2->color);

        std::set< Point > *us = go_string1->stones;
        us->insert(go_string2->stones->begin(), go_string2->stones->end());
        
        std::set< Point > * ul;
        ul = go_string1->liberties;
        int cnt = go_string1->lcount;
        for (auto itr = go_string2->liberties->begin(); itr != (go_string2->liberties)->end(); itr++){
            if(ul->find(*itr) != ul->end()){
                cnt++;
                ul->insert(*itr);
            }
            if(us->find(*itr) != us->end()){
                cnt--;
                ul->erase(*itr);
            }
        }

        GoString *st = new GoString(go_string1->color,us,ul,cnt);
        return st;
    }

    GoString * deepcopy(){

        std::set< Point > * us = new std::set< Point > ();
        std::set< Point > * ul = new std::set< Point >  ();
        *us = *stones;
        *ul = *liberties;
    	GoString * gs =  new GoString(color, us, ul, lcount);
         
        return gs;
    }
};

class Board{
private:

public:
    int num_rows;
    int num_cols;
    std::map< Point, GoString * > * _grid;

    Board(int num_rows, int num_cols){    
        this->num_rows = num_rows;
        this->num_cols = num_cols;
        
        
    }    

     ~Board(){
         for(auto itr = _grid->begin() ; itr != _grid->end(); itr++){
             delete itr->second;
         }
         delete _grid;
     }    
  
    void place_stone(Player * player, Point & point){    
        assert(is_on_grid(point));
        assert(_grid->find(point) != _grid->end());
         

        std::set< GoString * > adjacent_same_color;
        std::set< GoString * > adjacent_opposite_color;
        std::set<Point> *liberties = new  std::set<Point>();
        int ucount =0; 

        Point * nl = point.neighbors();
        for(int i = 0; i < 4; i++){
            Point neighbor = nl[i];

            if (!is_on_grid(neighbor)) continue;
            
            auto itr = _grid->find(neighbor);
            GoString * neighbor_string = NULL; 

            if(itr != _grid->end()) {
                neighbor_string = (itr -> second);
                
                if(neighbor_string->color == player->color) 
                    adjacent_same_color.insert(neighbor_string);
                else
                    adjacent_opposite_color.insert(neighbor_string);
            }
            else { 
                liberties->insert(neighbor);
                ucount++;
            }
        }
        delete nl;

        std::set<Point> * s = new std::set<Point>();
        s->insert(point);
        GoString *new_string = new GoString(player->color, s, liberties,ucount);
        
        for(auto itr = adjacent_same_color.begin(); itr != adjacent_same_color.end(); itr++)
            new_string = GoString::merged_with(*itr, new_string );

        for(auto itr = new_string->stones->begin(); itr != new_string->stones->end(); itr++)
            (*_grid)[ *itr ] = new_string; 

        for(auto itr = adjacent_opposite_color.begin(); itr != adjacent_opposite_color.end(); itr++)
            (*itr)->remove_liberty(point); 
        
        for(auto itr = adjacent_opposite_color.begin(); itr != adjacent_opposite_color.end(); itr++) {
            if ( (*itr)->num_liberties() == 0) _remove_string(*itr); 
        }
    }    

    void  _remove_string(GoString * string) {
        for(auto itr = string->stones->begin(); itr != string->stones->end(); itr++) {
            Point point = *itr; 
            Point * nl = point.neighbors();
            for(int i = 0; i < 4; i++){
                Point neighbor = nl[i];
                GoString * neighbor_string = (*_grid)[neighbor];
                if(neighbor_string != string) neighbor_string->add_liberty(point);
            }
            delete nl;
            _grid->erase(point);
        }
    }

    bool is_on_grid(Point & point){
        return 1 <= point.row && point.row <= this->num_rows &&
               1 <= point.col && point.col <= this->num_cols;
    }
    void add_grid(std::map< Point, GoString * > * next_grid){
        _grid = next_grid;
    }
    Board * deepcopy(){
        std::map< Point, GoString * > * next_grid = new std::map< Point, GoString * > ();
        for(auto itr = _grid->begin(); itr != _grid->end(); itr++) {
            GoString * gs = itr->second->deepcopy();
            (*next_grid)[ itr->first ] = gs;
        }

        Board * next_board = new Board(num_rows, num_cols);
        next_board->add_grid( next_grid);
        
        return next_board;
    }

    GoString *get_go_string(Point & point) {
        auto itr = _grid->find(point);
        if (itr == _grid->end())
            return NULL;
        return itr->second;
    }

    Color get(Point & point){
        auto itr = _grid->find(point);
        if (itr != _grid->end() )
            return Color::none;
        return itr->second->color;
    }
};


class GameState {
public:
    Board * board;
    Player * next_player;
    GameState * previous_state;
    Move* last_move;

    GameState(Board * board, Player * next_player, GameState * previous, Move* move){
        this->board = board;
        this->next_player = next_player;
        this->previous_state = previous;
        this->last_move = move;
    }
    ~GameState(){
        delete next_player;
        delete board;
     //   if(previous_state != NULL)
      //      delete previous_state;
        delete last_move;
    }
    GameState * apply_move(Move* move) {
        Board * next_board;
        if(move->is_play ) {
            next_board = board->deepcopy();
            next_board->place_stone(next_player, move->point);
        }
        else
            next_board = board;
        return new GameState(next_board, next_player->other(), this, move);
    }

    static GameState * new_game(int board_size){
        Board * board = new Board(board_size,board_size);
        Player * p = new Player(Color::black);
        return new GameState(board, p, NULL, NULL);
    }

    bool is_over(){ 
        if (last_move == NULL)
            return false;
        if (last_move->is_resign)
            return true;
        Move * second_last_move = previous_state->last_move;
        if (second_last_move == NULL)
            return false;
        return last_move->is_pass && second_last_move->is_pass;
    }

    bool is_move_self_capture(Player * player, Move* move){
        if (move->is_play)
            return false;
        Board * next_board = board->deepcopy();
        next_board->place_stone(player, move->point);
        GoString * new_string = next_board->get_go_string(move->point);
        bool flag = new_string->num_liberties() == 0;
        delete next_board;
        assert(new_string != NULL);
        return flag;
    }

    std::pair < Player * , Board* > * situation(){
        return new std::pair < Player * , Board* >(next_player, board);
    }

    bool does_move_violate_ko(Player * player, Move * move){
        if (!move->is_play)
            return false;
        Board * next_board = board->deepcopy();
        next_board->place_stone(player, move->point);
        std::pair < Player * , Board* > * next_situation = new std::pair < Player * , Board* >(player->other(), next_board);
        GameState * past_state = previous_state;
        std::pair < Player * , Board* > * tmp;

        while (past_state != NULL) {
            if ( *(tmp = past_state->situation()) == * next_situation ) {
                delete next_situation;
                delete tmp;
                return true;
            }
            delete tmp;
            past_state = past_state->previous_state;

        }
        delete next_situation;
        return false;
    }

    bool is_valid_move(Move * move){
        if (is_over())
            return false;
        if (move->is_pass && move->is_resign)
            return true;
        Color c = board->get(move->point);
        return (
            c == Color::none &&
            ! is_move_self_capture(next_player, move) &&
            ! does_move_violate_ko(next_player, move));
    }


};
#endif
