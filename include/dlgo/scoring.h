#ifndef _SCORING_H
#define _SCORING_H
#include<map>
#include<vector>
#include<set>
#include"gotypes.h"
#include"goboard.h"

class Territory {
public:
    int num_black_territory;
    int num_white_territory;
    int num_black_stones;
    int num_white_stones;
    int num_dame;
    std::vector<Point>  dame_points;

    Territory(std::map<Point, std::string> * territory_map);
};

void _collect_region(Point & start_pos, Board * board, std::set<Point> & all_points, std::set<Point> & all_borders, std::set<Point> * visited=NULL);

Territory * evaluate_territory(Board * board);

class GameResult{
public:
    int b;
    int w;
    int komi;

    GameResult(int b, int w, int komi);
    Color winner();

    int winning_margin();
/*    def __str__():
        w = w + komi
        if b > w:
            return 'B+%.1f' % (b - w,);
        return 'W+%.1f' % (w - b);*/
};


GameResult*  compute_game_result(GameState * game_state);

#endif
