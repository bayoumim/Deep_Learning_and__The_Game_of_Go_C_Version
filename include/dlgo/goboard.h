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

    Move(Point * point = NULL, bool is_pass = false, bool is_resign = false){
        assert(! (point != NULL && point->isNone() ) || is_pass || is_resign);
        this->point = *point;
        this->is_play = !point->isNone();
        this->is_pass = is_pass;
        this->is_resign = is_resign;

    }
    Move(bool is_pass = false, bool is_resign = false){
        assert( is_pass || is_resign);
        this->is_pass = is_pass;
        this->is_resign = is_resign;
        this->is_play = false;
    }
        
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
    GoString(Color & color, std::set< Point > * stones, std::set<Point> * liberties, int lcount){    
        this->color = color;
        this->stones = stones;
        this->liberties = liberties;
        this->lcount = lcount;

        int tmplcount = 0;
        for (auto itr = liberties->begin(); itr != liberties->end(); itr++){
           // std::cout << "point ( " <<  itr->row << ", " << itr->col << " )";
            tmplcount ++;
            
        }
      //  std::cout << std::endl;
       // assert(tmplcount == lcount);
        if(tmplcount != lcount) {
            std::cout << "error" << std::endl;
            std::cout << "lcount : " << lcount << std::endl;
            std::cout << "tmplcount : " << tmplcount << std::endl;
            printliberties();
            assert(tmplcount == lcount);
        }
    }

    ~GoString (){
        stones->clear();
        delete stones;
        liberties->clear();
        delete liberties;
    }   

    int num_liberties() {    
        return lcount;
    }    

    bool operator== (const GoString& rhs) const {
        return (this->color == rhs.color) && 
               *(this->stones) == *(rhs.stones) && 
               *(this->liberties) == *(rhs.liberties);
    }
    static GoString * merged_with(GoString * go_string1, GoString * go_string2, bool verbose = false){
        assert(go_string1->color == go_string2->color);
        if (verbose) std::cout << "Merging two string" << std::endl;

        if (verbose) {
            std::cout << "Printing two string liberities...." << std::endl;
            go_string1->printliberties();
            go_string2->printliberties();
            std::cout << "Printing two string stones...." << std::endl;
            go_string1->printstones();
            go_string2->printstones();
        }

        std::set< Point > *us = new std::set< Point >();
        us->insert(go_string1->stones->begin(), go_string1->stones->end());
        us->insert(go_string2->stones->begin(), go_string2->stones->end());
        
        std::set< Point > * ul;
        ul = go_string1->liberties;
        int cnt = go_string1->lcount;
        for (auto itr = go_string1->liberties->begin(); itr != (go_string1->liberties)->end(); itr++){
            if(us->find(*itr) != us->end()){
                cnt--;
                ul->erase(*itr);
                if (verbose) std::cout << "liberity point (" << itr->row << "," << itr->col << ") in string 1 is in new stone set. Point will not be added. cnt : " << cnt << std::endl;
            }
        }

        for (auto itr = go_string2->liberties->begin(); itr != (go_string2->liberties)->end(); itr++){
            if(ul->find(*itr) == ul->end()){
                cnt++;
                ul->insert(*itr);
                if (verbose) std::cout << "liberity point (" << itr->row << "," << itr->col << ") add to liberty list. cnt : " << cnt << std::endl;
            }
            if(us->find(*itr) != us->end()){
                cnt--;
                ul->erase(*itr);
                if (verbose) std::cout << "liberity point (" << itr->row << "," << itr->col << ") in string 2 is in new stone set. Point will not be added. cnt : " << cnt << std::endl;
            }
        }

        GoString *st = new GoString(go_string1->color,us,ul,cnt);
        return st;
    }

    GoString * deepcopy(){

        std::set< Point > * us = new std::set< Point > ();
        std::set< Point > * ul = new std::set< Point >  ();

        for (auto itr = stones->begin(); itr != stones->end(); itr++){
            Point * p = new Point(*itr);
            us->insert(p);
        }

        for (auto itr = liberties->begin(); itr != liberties->end(); itr++){
            Point * p = new Point(*itr);
            ul->insert(p);
        }

        //us->insert() *us = *stones;
    //    *ul = *liberties;
    	GoString * gs =  new GoString(color, us, ul, lcount);
         
        return gs;
    }

    void printliberties(){
        std::cout << "string color : " << ((color == Color::black)? "black" : "white") << ". liberities";
        for (auto itr = liberties->begin(); itr != liberties->end(); itr++){
            std::cout << "point ( " <<  itr->row << ", " << itr->col << " ). ";
            
        }
        std::cout << std::endl;
        std::cout << "lcount : " << lcount << std::endl;
    }
    void printstones(){
        std::cout << "string color : " << ((color == Color::black)? "black" : "white") << ". stones .. ";
        for (auto itr = stones->begin(); itr != stones->end(); itr++){
            std::cout << "point ( " <<  itr->row << ", " << itr->col << " ). ";
            
        }
        std::cout << std::endl;
    }

    std::set< Point > *  Poinsdeepcopy(std::set< Point > * original){

        std::set< Point > * us = new std::set< Point > ();

        for (auto itr = original->begin(); itr != original->end(); itr++){
            Point * p = new Point(*itr);
            us->insert(p);
        }
         
        return us;
    }

    GoString * without_liberty(Point & point){ 
        assert(liberties->find(point) != liberties->end());
        std::set< Point > *  new_liberties = Poinsdeepcopy(liberties);
        assert(new_liberties->find(point) != new_liberties->end());
        new_liberties->erase(point);

        assert(new_liberties->find(point) == new_liberties->end());
        std::set< Point > *  new_stones = Poinsdeepcopy(stones);

        int nc  = lcount;
        nc --;

        return new GoString(color, new_stones, new_liberties, nc);
    }

    GoString * with_liberty(Point & point){
        assert(liberties->find(point) == liberties->end());
        std::set< Point > *  new_liberties = Poinsdeepcopy(liberties);
        new_liberties->insert(point);
        std::set< Point > *  new_stones = Poinsdeepcopy(stones);
        int nc  = lcount;
        nc ++;
        return new GoString(color, new_stones, new_liberties,nc);
    }

};

class Board{
private:

public:
    int num_rows;
    int num_cols;
    std::map< Point, GoString * > * _grid;
    unsigned long long int _hash;

    Board(int num_rows, int num_cols){    
        this->num_rows = num_rows;
        this->num_cols = num_cols;
        _grid = new std::map< Point, GoString * >();
        _hash = EMPTY_BOARD;
    }    

     ~Board(){
         for(auto itr = _grid->begin() ; itr != _grid->end(); itr++){
             delete itr->second;
         }
         delete _grid;
     }    
  
    void place_stone(Player * player, Point & point, bool verbose = false){   
        if (verbose) std::cout << "place_stone started. Point( " << point.row << "," << point.col << ")." << std::endl; 

        assert(is_on_grid(point));
        assert(_grid->find(point) == _grid->end());
         

        std::set< GoString * > adjacent_same_color;
        std::set< GoString * > adjacent_opposite_color;
        std::set<Point> *liberties = new  std::set<Point>();
        int ucount =0; 

        // std::cout << "place_stone: for loop." << std::endl; 
        Point * nl = point.neighbors();
        if (verbose) std::cout << "place_stone : get neighbors" << std::endl; 
        for(int i = 0; i < 4; i++){
            Point neighbor = nl[i];
            if (verbose) std::cout << "neighbor no. " << i << ". Point( " << neighbor.row << "," << neighbor.col << ")." << std::endl; 
            if (!is_on_grid(neighbor)){
                if (verbose) std::cout << "Not in the grid, skipped!" << std::endl; 
                continue;
            }
            auto itr = _grid->find(neighbor);
            GoString * neighbor_string = NULL; 

            if(itr != _grid->end()) {
                if (verbose) std::cout << "a stone is in the neighbor point..." << std::endl; 

                neighbor_string = (itr -> second);

                if(neighbor_string->liberties->find(point) == neighbor_string->liberties->end()){
	            std::cout << "place_stone: error, try to remove point not in liberity: P( " << point.row << "," << point.col << " ) . String is : " << neighbor_string << std::endl;
	        }

                assert( neighbor_string->liberties->find(point) != neighbor_string->liberties->end());

                if(neighbor_string->color == player->color)  {
                    if (verbose) std::cout << "neighbor stone is the same color, store in the adjacent_same_color..." << std::endl; 
                    adjacent_same_color.insert(neighbor_string);
                }
                else {
                    if (verbose) std::cout << "neighbor stone is different color, store in the adjacent_opposite_color..." << std::endl; 
                    adjacent_opposite_color.insert(neighbor_string);
                }
            }
            else { 
                liberties->insert(neighbor);
                ucount++;
                if (verbose) std::cout << "neighbor is empty, add to liberties list. ucount : " << ucount << std::endl; 
           }
        }
        delete [] nl;

        std::set<Point> * s = new std::set<Point>();
        s->insert(point);
        GoString *new_string = new GoString(player->color, s, liberties,ucount);
        
        // std::cout << "place_stone: for loop 2." << std::endl; 
        if (verbose && adjacent_same_color.begin() != adjacent_same_color.end()) std::cout << "Call Merge with function..." << std::endl; 
        for(auto itr = adjacent_same_color.begin(); itr != adjacent_same_color.end(); itr++) {
            new_string = GoString::merged_with(*itr, new_string, verbose );
        }
        // std::cout << "place_stone: for loop 3." << std::endl; 
        for(auto itr = new_string->stones->begin(); itr != new_string->stones->end(); itr++)
            (*_grid)[ *itr ] = new_string; 

        _hash ^= HASH_CODE[point][ player->color]; 


        // std::cout << "place_stone: for loop 4." << std::endl; 
        for(auto itr = adjacent_opposite_color.begin(); itr != adjacent_opposite_color.end(); itr++) {
            GoString * other_color_string = *itr;
            GoString * replacement = other_color_string->without_liberty(point);
            if (replacement->num_liberties() > 0 )
                _replace_string(other_color_string, replacement);
            else{
                _remove_string(other_color_string);
                delete replacement;
            }
        }
        assert(_grid->find(point) != _grid->end());
        VerifyStrings();
    }

    void  _remove_string(GoString * string) {
        // std::cout << "_remove_string started." << std::endl; 
        std::set< GoString* > processedNeighbor;
        for(auto itr = string->stones->begin(); itr != string->stones->end(); itr++) {
            Point point = *itr; 
            Point * nl = point.neighbors();
            for(int i = 0; i < 4; i++){
                // std::cout << "i " << i << std::endl;
                Point neighbor = nl[i];
                if (!is_on_grid(neighbor)) continue;
                // std::cout << "get string " << std::endl;
                if(_grid->find(neighbor) == _grid->end() ) continue;
                GoString * neighbor_string = (*_grid)[neighbor];
                if(processedNeighbor.find(neighbor_string) != processedNeighbor.end()) continue;
                // std::cout << "if statement. neighbor row : " << neighbor.row << " . col : " << neighbor.col << std::endl;
                if(neighbor_string != string) {
                    // std::cout << "_remove_string :: neighbor_string: " << neighbor_string << std::endl;
                    GoString * newString = neighbor_string->with_liberty(point);
                    processedNeighbor.insert(newString);
                    _replace_string(neighbor_string,newString);
                }
            }
            // std::cout << "_remove_string : delete nl." << std::endl; 
            _hash ^= HASH_CODE[point][string->color];
            delete [] nl;
            // // std::cout << "_remove_string : erase point." << std::endl; 
         //   _grid->erase(point);
        }

        for(auto itr = string->stones->begin(); itr != string->stones->end(); itr++) {
            Point point = *itr; 
            _grid->erase(point);
        }
        // std::cout << "_remove_string ended." << std::endl; 
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
            if(next_grid->find(itr->first) == next_grid->end()){
                GoString * gs = itr->second->deepcopy();
               // (*next_grid)[ itr->first ] = gs;
                for(auto itr2 = gs->stones->begin(); itr2 != gs->stones->end(); itr2++) {
                    (*next_grid)[ *itr2 ] = gs;
                }
            }
        }

        Board * next_board = new Board(num_rows, num_cols);
        next_board->add_grid(next_grid);
        
        return next_board;
    }

    GoString *get_go_string(Point & point) {
        auto itr = _grid->find(point);
        if (itr == _grid->end())
            return NULL;
        return itr->second;
    }

    Color get(Point & point){
   //     std::cout << "get started"<< std::endl;
   //     std::cout << "point row : " << point.row << " . col : " << point.col << std::endl;

        auto itr = _grid->find(point);
     //   std::cout << "find finished!"<< std::endl;
        if (itr == _grid->end() ) {
    //        std::cout << "return none"<< std::endl;
            return Color::none;
        }
   //     std::cout << "return color"<< std::endl;
        return itr->second->color;
    }

    void printStrings(){
        std::cout << "Printing Strings ..." << std::endl;
        for(auto itr = _grid->begin(); itr != _grid->end(); itr++) {
            std::cout << "Point (" << itr->first.row << "," << itr->first.col << ")" << " belongs to string " << itr->second << std::endl;
            itr->second->printliberties();
            itr->second->printstones ();

        }


    }

    void VerifyStrings(){
        for(auto itr = _grid->begin(); itr != _grid->end(); itr++) {
            Point p = itr->first;
            GoString * gs = itr->second;
            assert(gs->stones->find(p) != gs->stones->end());
          //  assert(p.row )

            for(auto itr2 = gs->stones->begin(); itr2 != gs->stones->end(); itr2++) {
                auto itr3 = _grid->find(*itr2);
                assert( itr3 != _grid->end());
                assert( itr3->second == gs);
                
            }

            for(auto itr2 = gs->liberties->begin(); itr2 != gs->liberties->end(); itr2++) {
                auto itr3 = _grid->find(*itr2);
                assert( itr3 == _grid->end());
                
            }
            
            for(auto itr2 = gs->stones->begin(); itr2 != gs->stones->end(); itr2++) {
                Point point = * itr2;
                Point * nl = point.neighbors();

                for(int i = 0; i < 4; i++){
                    Point neighbor = nl[i];
                    if (!is_on_grid(neighbor)) continue;
                  //  if ( _grid->find(neighbor) == _grid->end() ) continue;
                    bool inStones = gs->stones->find(neighbor) != gs->stones->end();
                    bool inliberities = gs->liberties->find(neighbor) != gs->liberties->end();
                    bool ingrid =  _grid->find(neighbor) != _grid->end();
                    bool sameColor = false;
                    if(ingrid) {
                         sameColor = _grid->find(neighbor)->second->color == gs->color;
                    } 
                    assert( (inStones && !inliberities && ingrid && sameColor) || (inliberities && !ingrid) || (ingrid && !sameColor) );
                }
                delete [] nl;
            }

        }
    }

    void _replace_string(GoString * old_string, GoString * new_string){
       // GoString * old_string;

        for (auto itr = old_string->stones->begin(); itr != old_string->stones->end(); itr++) {
           Point point = *(itr); 
           auto itr2 = _grid->find(point);
           assert( itr2->second == old_string);
           assert( itr2 != _grid->end());
            _grid->erase(point);
        }

        for (auto itr = new_string->stones->begin(); itr != new_string->stones->end(); itr++) {
           Point point = *(itr); 
           assert(_grid->find(point) == _grid->end());
           (*_grid)[point] = new_string;
        }
        delete old_string;
    }

    unsigned long long int zobrist_hash() {
        return _hash;
    }

};


class GameState {
public:
    Board * board;
    Player * next_player;
    GameState * previous_state;
    std::set< std::pair<Color, unsigned long long int> > previous_states;
    Move* last_move;

    GameState(Board * board, Player * next_player, GameState * previous, Move* move){
        this->board = board;
        this->next_player = next_player;
        this->previous_state = previous;

        if (previous_state ==NULL) {
           // do nothing
           ; 
        }
        else {
            previous_states.insert(std::make_pair(next_player->color,board->zobrist_hash()));
        }
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
            next_board->VerifyStrings();
         //   next_board->printStrings();
            next_board->place_stone(next_player, move->point, false);
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
        // std::cout << "is_move_self_capture started" << std::endl;
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
        // std::cout << "does_move_violate_ko is started" << ". move->is_play:" << move->is_play << std::endl;
        if (!move->is_play)
            return false;
        // std::cout << "1." << std::endl;
        Board * next_board = board->deepcopy();
        // std::cout << "2." << std::endl;
        next_board->VerifyStrings();
        next_board->place_stone(player, move->point,false);

        // std::cout << "3." << std::endl;
        std::pair < Color , unsigned long long int >  next_situation =  std::make_pair(player->other()->color, next_board->zobrist_hash() );

        // std::cout << "while loop started." << std::endl;
        bool flag = previous_states.find(next_situation) != previous_states.end();
        return flag;
    }

    bool is_valid_move(Move * move){
        // std::cout << "is_valid_move started" << std::endl;
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

    void printStrings(){
        std::cout << "Printing Strings ..." << std::endl;
        for(auto itr = board->_grid->begin(); itr != board->_grid->end(); itr++) {
            std::cout << "Point (" << itr->first.row << "," << itr->first.col << ")" << " belongs to string " << itr->second << std::endl;
            itr->second->printliberties();
            itr->second->printstones ();

        }
    }
};
#endif
