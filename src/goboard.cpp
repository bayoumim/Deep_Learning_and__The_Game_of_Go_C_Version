#include "gotypes.h"
#include <cassert>
#include <set>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
#include <utility>
#include "goboard.h"
#include "scoring.h"
#include "zobrist.h"

  //  Move::Move(Point * point = NULL, bool is_pass = false, bool is_resign = false){
    Move::Move(Point * point , bool is_pass , bool is_resign){
        assert(! (point != NULL && point->isNone() ) || is_pass || is_resign);
        this->point = *point;
        this->is_play = !point->isNone();
        this->is_pass = is_pass;
        this->is_resign = is_resign;

    }
//    Move::Move(bool is_pass = false, bool is_resign = false){
    Move::Move(bool is_pass , bool is_resign){
        assert( is_pass || is_resign);
        this->is_pass = is_pass;
        this->is_resign = is_resign;
        this->is_play = false;
    }
        
        


    GoString::GoString(Color & color, std::set< Point > * stones, std::set<Point> * liberties, int lcount){    
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

    GoString::~GoString (){
        stones->clear();
        delete stones;
        liberties->clear();
        delete liberties;
    }   

    int GoString::num_liberties() {    
        return lcount;
    }    

    bool GoString::operator== (const GoString& rhs) const {
        return (this->color == rhs.color) && 
               *(this->stones) == *(rhs.stones) && 
               *(this->liberties) == *(rhs.liberties);
    }

    void GoString::merged_with(GoString * go_string2, bool verbose = false){
        assert(this->color == go_string2->color);
        if (verbose) std::cout << "Merging two string" << std::endl;

        if (verbose) {
            std::cout << "Printing two string liberities...." << std::endl;
            this->printliberties();
            go_string2->printliberties();
            std::cout << "Printing two string stones...." << std::endl;
            this->printstones();
            go_string2->printstones();
        }

        stones->insert(go_string2->stones->begin(), go_string2->stones->end());
        
        for (auto itr = this->liberties->begin(); itr != (this->liberties)->end(); itr++){
            if(stones->find(*itr) != stones->end()){
                lcount--;
                liberties->erase(*itr);
                if (verbose) std::cout << "liberity point (" << itr->row << "," << itr->col << ") in string 1 is in new stone set. Point will not be added. lcount : " << lcount << std::endl;
            }
        }

        for (auto itr = go_string2->liberties->begin(); itr != (go_string2->liberties)->end(); itr++){
            if(liberties->find(*itr) == liberties->end()){
                lcount++;
                liberties->insert(*itr);
                if (verbose) std::cout << "liberity point (" << itr->row << "," << itr->col << ") add to liberty list. lcount : " << lcount << std::endl;
            }
            if(stones->find(*itr) != stones->end()){
                lcount--;
                liberties->erase(*itr);
                if (verbose) std::cout << "liberity point (" << itr->row << "," << itr->col << ") in string 2 is in new stone set. Point will not be added. lcount : " << lcount << std::endl;
            }
        }
        assert( liberties->size() == (unsigned int) lcount);
    }

    GoString * GoString::deepcopy(){

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

    	GoString * gs =  new GoString(color, us, ul, lcount);
         
        return gs;
    }

    void GoString::printliberties(){
        std::cout << "string color : " << ((color == Color::black)? "black" : "white") << ". liberities";
        for (auto itr = liberties->begin(); itr != liberties->end(); itr++){
            std::cout << "point ( " <<  itr->row << ", " << itr->col << " ). ";
            
        }
        std::cout << std::endl;
        std::cout << "lcount : " << lcount << std::endl;
    }
    void GoString::printstones(){
        std::cout << "string color : " << ((color == Color::black)? "black" : "white") << ". stones .. ";
        for (auto itr = stones->begin(); itr != stones->end(); itr++){
            std::cout << "point ( " <<  itr->row << ", " << itr->col << " ). ";
            
        }
        std::cout << std::endl;
    }


    void GoString::without_liberty(Point & point){ 
        assert(liberties->find(point) != liberties->end());
        liberties->erase(point);
        lcount--;
    }

    void GoString::with_liberty(Point & point){
        assert(liberties->find(point) == liberties->end());
        liberties->insert(point);
        lcount++;
    }

    void GoString::print(){
        std::cout <<  "string : " << this << std::endl;
        printliberties();
        printstones ();
    }

    Board::Board(int num_rows, int num_cols){    
        this->num_rows = num_rows;
        this->num_cols = num_cols;
        _grid = new std::map< Point, GoString * >();
        _hash = EMPTY_BOARD;
    }    

     Board::~Board(){
         for(auto itr = _grid->begin() ; itr != _grid->end(); itr++){
             delete itr->second;
         }
         delete _grid;
     }    
  
    void Board::place_stone(Player * player, Point & point, bool verbose = false){   
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
            GoString * old_string = new_string;
            //new_string = GoString::merged_with(*itr, new_string, verbose );
            (*itr)->merged_with(new_string, verbose );
            new_string = *itr;
            delete old_string;
        }

        // std::cout << "place_stone: for loop 3." << std::endl; 
    //    std::cout << "stones size : " << new_string->stones->size() << std::endl;
        for(auto itr = new_string->stones->begin(); itr != new_string->stones->end(); itr++) {
         //   std::cout << "update string for point(" << itr->row << "," << itr->col << ")"  << std::endl;
            if(*itr == point)
                assert(_grid->find(point) == _grid->end());
            else
                assert(_grid->find(*itr) != _grid->end());

            (*_grid)[ *itr ] = new_string; 
        }
     //   std::cout << "grid size : " << _grid->size()  << std::endl;
        _hash ^= HASH_CODE[point][ player->color]; 


        // std::cout << "place_stone: for loop 4." << std::endl; 
        for(auto itr = adjacent_opposite_color.begin(); itr != adjacent_opposite_color.end(); itr++) {
            GoString * other_color_string = *itr;
            /*GoString * replacement = */
            other_color_string->without_liberty(point);
     //       if (replacement->num_liberties() > 0 )
            if (other_color_string->num_liberties() > 0 ) {
                assert(_grid->find(point) != _grid->end());
;// _replace_string(other_color_string /*, replacement*/);
            }
            else{
              //  std::cout << "removing string : " << other_color_string << std::endl;
             //   other_color_string->print();
                assert(other_color_string->num_liberties() == 0);
                _remove_string(other_color_string);
             //   assert(0);
             //   delete replacement;
            }
        }
        assert(_grid->find(point) != _grid->end());
        VerifyStrings();
      //  std::cout << "place_stone : ended " << std::endl;
    }

    void  Board::_remove_string(GoString * string) {
      //   std::cout << "_remove_string started." << std::endl; 
      //   string->print();
     //   std::set< GoString* > processedNeighbor;
     //   std::set<Point> processedPoint;

        for(auto itr = string->stones->begin(); itr != string->stones->end(); itr++) {
            Point point = *itr; 
            Point * nl = point.neighbors();

            std::set<GoString*> processedStrings;
            for(int i = 0; i < 4; i++){
          //       std::cout << "i " << i << std::endl;
                Point neighbor = nl[i];
                if (!is_on_grid(neighbor)) continue;
          //      std::cout << "get string " << std::endl;
                if(_grid->find(neighbor) == _grid->end() ) continue;
                GoString * neighbor_string = (*_grid)[neighbor];
           //     if(processedNeighbor.find(neighbor_string) != processedNeighbor.end()) continue;
         //       std::cout << "if statement. neighbor row : " << neighbor.row << " . col : " << neighbor.col << std::endl;
                if(neighbor_string != string) {
          //          std::cout << "_remove_string :: neighbor_string: " << neighbor_string << std::endl;
                    /*GoString * newString = */ 
                    if(processedStrings.find(neighbor_string) == processedStrings.end()){
                        neighbor_string->with_liberty(point);
                        processedStrings.insert(neighbor_string);
                    }

                }
            }
        //    std::cout << "_remove_string : delete nl." << std::endl; 
            _hash ^= HASH_CODE[point][string->color];
            delete [] nl;
        }

        for(auto itr = string->stones->begin(); itr != string->stones->end(); itr++) {
            assert(_grid->find(*itr) != _grid->end());
            _grid->erase(*itr);
        }
        delete string;
        // std::cout << "_remove_string ended." << std::endl; 
    }

    bool Board::is_on_grid(Point & point){
        return 1 <= point.row && point.row <= this->num_rows &&
               1 <= point.col && point.col <= this->num_cols;
    }
    void Board::add_grid(std::map< Point, GoString * > * next_grid){
        _grid = next_grid;
    }

    void Board::add_hash(unsigned long long int _hash){
        this->_hash=_hash;
    }
    Board * Board::deepcopy(){
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
        next_board->add_hash(_hash);
        compareBoard(next_board);
        next_board-> VerifyStrings();
        return next_board;
    }

    GoString *Board::get_go_string(Point & point) {
        auto itr = _grid->find(point);
        if (itr == _grid->end())
            return NULL;
        return itr->second;
    }

    Color Board::get(Point & point){
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

    void Board::printStrings(){
        std::cout << "Printing Strings ..." << std::endl;
        for(auto itr = _grid->begin(); itr != _grid->end(); itr++) {
            std::cout << "Point (" << itr->first.row << "," << itr->first.col << ")" << " belongs to string " << itr->second << std::endl;
            itr->second->printliberties();
            itr->second->printstones ();

        }


    }

    void Board::VerifyStrings(){
        for(auto itr = _grid->begin(); itr != _grid->end(); itr++) {
            Point p = itr->first;
            GoString * gs = itr->second;
            assert(gs->stones->find(p) != gs->stones->end());


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

    void Board::compareBoard(Board * nextboard){
        assert(_grid->size() == nextboard->_grid->size());

        for(auto itr = _grid->begin(); itr != _grid->end(); itr++) {
            Point p = itr->first;
            auto nxtItr = nextboard->_grid->find(p);
            assert(nxtItr != nextboard->_grid->end() );
            assert(nxtItr->first == p);
            GoString * gs = itr->second;
            GoString * nxtgs = nxtItr->second;

            assert(gs->stones->size() == nxtgs->stones->size() );
            assert(gs->liberties->size() == nxtgs->liberties->size() );


            for(auto itr2 = gs->stones->begin(); itr2 != gs->stones->end(); itr2++) {
                auto itr3 =nxtgs->stones->find(*itr2);
                assert( itr3 != nxtgs->stones->end());
                
            }

            for(auto itr2 = gs->liberties->begin(); itr2 != gs->liberties->end(); itr2++) {
                auto itr3 =nxtgs->liberties->find(*itr2);
                assert( itr3 != nxtgs->liberties->end());
                
            }
        }

    }

    void Board::_replace_string(GoString * old_string, GoString * new_string){
       // GoString * old_string;
       // std::cout << "_replace_string started" << std::endl;
       // std::cout << "new string..." << std::endl;
       // new_string->print();
        for (auto itr = old_string->stones->begin(); itr != old_string->stones->end(); itr++) {
           Point point = *(itr); 
           auto itr2 = _grid->find(point);
           assert( itr2->second == old_string);
           assert( itr2 != _grid->end());
            _grid->erase(point);
       //    std::cout << "remove string for point(" << point.row << "," << point.col << ")" << std::endl;
        }

        for (auto itr = new_string->stones->begin(); itr != new_string->stones->end(); itr++) {
           Point point = *(itr); 
           assert(_grid->find(point) == _grid->end());
           (*_grid)[point] = new_string;
       //    std::cout << "add new string for point(" << point.row << "," << point.col << ")"  << std::endl;
        }
      //  std::cout << "_replace_string ended" << std::endl;
        delete old_string;
    }

    unsigned long long int Board::zobrist_hash() {
        return _hash;
    }



    GameState::GameState(Board * board, Player * next_player, GameState * previous, Move* move){
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
    GameState::~GameState(){
        delete next_player;
        delete board;
     //   if(previous_state != NULL)
      //      delete previous_state;
        delete last_move;
    }
    GameState * GameState::apply_move(Move* move) {
        Board * next_board;
        if(move->is_play ) {
            next_board = board->deepcopy();
            next_board->VerifyStrings();

            next_board->place_stone(next_player, move->point, false);
        }
        else
            next_board = board;
        return new GameState(next_board, next_player->other(), this, move);
    }



    bool GameState::is_over(){ 
        if (last_move == NULL)
            return false;
        if (last_move->is_resign)
            return true;
        Move * second_last_move = previous_state->last_move;
        if (second_last_move == NULL)
            return false;
        return last_move->is_pass && second_last_move->is_pass;
    }

    bool GameState::is_move_self_capture(Player * player, Move* move){
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

    std::pair < Player * , Board* > * GameState::situation(){
        return new std::pair < Player * , Board* >(next_player, board);
    }

    bool GameState::does_move_violate_ko(Player * player, Move * move){
        // std::cout << "does_move_violate_ko is started" << ". move->is_play:" << move->is_play << std::endl;
        if (!move->is_play)
            return false;
        // std::cout << "1." << std::endl;
        Board * next_board = board->deepcopy();
        // std::cout << "2." << std::endl;
       // next_board->VerifyStrings();
        next_board->place_stone(player, move->point,false);

        // std::cout << "3." << std::endl;
        std::pair < Color , unsigned long long int >  next_situation =  std::make_pair(player->other()->color, next_board->zobrist_hash() );

        // std::cout << "while loop started." << std::endl;
        bool flag = previous_states.find(next_situation) != previous_states.end();
        return flag;
    }

    bool GameState::is_valid_move(Move * move){
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

    std::vector<Move* > * GameState::legal_moves() {
        std::vector<Move* > * moves = new std::vector<Move* > ();

        for (int r =1 ; r < board->num_rows + 1; r++) {
            // std::cout << "r: " << r << std::endl;
            for (int c = 1; c < board->num_cols + 1; c++) {
                // std::cout << "c: " << c << std::endl;
                Point candidate(r, c);
                if(board->_grid->find(candidate) != board->_grid->end() ) {
                    continue; 
                }

                Move* p = Move::play(&candidate);
                if ( is_valid_move(p) && 
                        ! is_point_an_eye(candidate,
                                          next_player->color)) {
                    // std::cout << "add candidate to the list" << std::endl;
                    moves->push_back(p);
                }
                else {
                    delete p;
                }
            }
        }

        return moves;
    }

    void GameState::printStrings(){
        std::cout << "Printing Strings ..." << std::endl;
        for(auto itr = board->_grid->begin(); itr != board->_grid->end(); itr++) {
            std::cout << "Point (" << itr->first.row << "," << itr->first.col << ")" << " belongs to string " << itr->second << std::endl;
            itr->second->printliberties();
            itr->second->printstones ();

        }
    }

    Color GameState::winner(){
        if (!is_over())
            return Color::none;
        if (last_move->is_resign)
            return next_player->color;
        GameResult* game_result = compute_game_result(this);
        return game_result->winner();
    }

    bool GameState::is_point_an_eye(Point & point, Color color) {
        Color c = board->get(point);
        if (c != Color::none)
            return false;

        Point * nl =  point.neighbors();
        for (int i = 0; i < 4; i++){ 
            Point neighbor = nl[i];
            if (board->is_on_grid(neighbor)) {
                Color neighbor_color = board->get(neighbor);
            //    assert(neighbor_color != Color::none);
                if (neighbor_color != color)
                    return false;
            }
        }
        delete [] nl;
        int friendly_corners = 0;
        int off_board_corners = 0;

        Point * corners = (Point*) malloc(4 * sizeof(Point));
        corners[0].setCoord(point.row - 1, point.col - 1);
        corners[1].setCoord(point.row - 1, point.col + 1);
        corners[2].setCoord(point.row + 1, point.col - 1);
        corners[3].setCoord(point.row + 1, point.col + 1);

        for (int i = 0; i < 4; i++) {
            Point corner = corners[i];
            if (board->is_on_grid(corner)) {
                Color corner_color = board->get(corner);
              //  assert(corner_color != Color::none);
                if (corner_color == color)
                    friendly_corners += 1;
            }
            else
                off_board_corners += 1;
        }

        delete [] corners;
        if (off_board_corners > 0)
            return off_board_corners + friendly_corners == 4;
        return friendly_corners >= 3;
    }

