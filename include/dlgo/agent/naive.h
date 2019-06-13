#ifndef _naive_H
#define _naive_H
#include "goboard_slow.h"
#include <vector>
#include "helpers.h"
#include <stdlib.h>
#include "agent.h"


class RandomBot /* : public Agent*/ {
public:
    Move * select_move(GameState * game_state){
        // """Choose a random valid move that preserves our own eyes."""
        std::vector< Point * > candidates;
        for (int r =1 ; r < game_state->board->num_rows + 1; r++) {
            for (int c = 1; c < game_state->board->num_cols + 1; c++) {
                Point *candidate = new Point(r, c);
                Move* p = Move::play(*candidate);
                if ( game_state->is_valid_move(p) && 
                        ! is_point_an_eye(game_state->board,
                                            *candidate,
                                            game_state->next_player->color))
                    candidates.push_back(candidate);
                else delete candidate;
                delete p;
            }
        }

        if (candidates.size() == 0 )
            return Move::pass_turn();
        int r = rand() % candidates.size();
        Point * choice = candidates[r];
        candidates.erase(candidates.begin()+r);

        for(int i = 0; i < (int) candidates.size(); i++ ){
            delete candidates[i];
        }
        return Move::play(*choice);
    }





};


#endif
