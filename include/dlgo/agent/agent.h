#ifndef _AGENT_H
#define _AGENT_H
#include <goboard_slow.h>
class Agent{
     virtual Move * select_move(GameState * game_state);
};
#endif
