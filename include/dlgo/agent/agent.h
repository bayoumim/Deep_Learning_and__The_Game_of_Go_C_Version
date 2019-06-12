#ifndef _AGENT_H
#define _AGENT_H

class Agent{
     virtual Move * select_move(GameState * game_state);
};
#endif
