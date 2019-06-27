#ifndef _PRUNED_GO_H
#define _PRUNED_GO_H
#include "goboard.h"
#include <vector>
//#include "helpers.h"
#include <stdlib.h>
#include "agent.h"

int MAX_SCORE = 999999;
int MIN_SCORE = -999999;

int best_result(GameState *game_state, int max_depth, int (*eval_fn)(GameState *game_state) ){
    if (game_state->is_over()) {                              
        if (game_state->winner() == game_state->next_player->color)  
            return MAX_SCORE ;                              
        else                                              
            return MIN_SCORE ;  
    }                            

    if (max_depth == 0)                                     
        return eval_fn(game_state) ;                        

    int best_so_far = MIN_SCORE;
    std::vector<Move* > * lm = game_state->legal_moves();
    for (int i = 0 ; i < (int) lm->size(); i++ ) {
        Move* candidate_move =(*lm)[i];       
        GameState * next_state = game_state->apply_move(candidate_move); 
        int opponent_best_result = best_result(                
            next_state, max_depth - 1, eval_fn) ;           
        int our_result = -1 * opponent_best_result ;            
        if (our_result > best_so_far)                       
            best_so_far = our_result;                       
    }
    for (int i = 0 ;  i < (int) lm->size(); i++ ) {
        delete (*lm)[i];       
    }
    lm->clear();
    delete lm;
    return best_so_far;
}


class DepthPrunedAgent /* : public Agent*/ {
public:
    int max_depth;
    int (*eval_fn)(GameState *game_state);

    void setParam(int max_depth, int  (*eval_fn)(GameState *game_state) ){
        this->max_depth = max_depth;
        this->eval_fn = eval_fn;
    }

    Move * select_move(GameState * game_state){
        // """Choose a random valid move that preserves our own eyes."""
        std::cout << "find candidates" << std::endl;
        int best_score = MIN_SCORE;
        std::vector< Move * > * legal_moves = game_state->legal_moves();
        assert(legal_moves->size() > 0);
        std::vector<Move* > * best_moves = new std::vector<Move* > ();
        std::cout << "legal_moves size : " << legal_moves->size() << std::endl;
        for (unsigned int i = 0 ; i < legal_moves->size(); i++) {
            std::cout << "legal move no. " << i << std::endl;
            Move * possible_move = (*legal_moves)[i];
            GameState* next_state = game_state->apply_move(possible_move);
            int opponent_best_outcome = best_result(next_state, max_depth, eval_fn);
            int our_best_outcome = -1 * opponent_best_outcome;
            if ((best_moves->size() == 0) || (our_best_outcome > best_score) ) {
                best_moves->clear();
                best_moves->push_back(possible_move);
                best_score = our_best_outcome;
            }
            else if (our_best_outcome == best_score)
                best_moves->push_back(possible_move);
        }

        // std::cout << "choice one candidate." << std::endl;
   //     std::cout << "best move size : " << best_moves->size() << std::endl;
        assert(best_moves->size() > 0);
        int r = rand() % best_moves->size();
        Move * choice = (*best_moves)[r];
        best_moves->erase(best_moves->begin()+r);
   //     std::cout << "choice move:" << std::endl;
   //     choice->print();
        
        for (unsigned int i = 0 ; i < legal_moves->size(); i++) {
            auto tmp = (*legal_moves)[i];
            if(tmp != choice)
                delete tmp;
            else
                legal_moves->erase(legal_moves->begin()+i);
        }
        legal_moves->clear();
        delete legal_moves;

        best_moves->clear();
        delete best_moves;

        std::cout << "choice move:" << std::endl;
        choice->print();

        return choice;
    }





};


#endif
