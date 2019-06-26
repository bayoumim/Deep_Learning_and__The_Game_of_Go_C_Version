#include "scoring.h"


    Territory::Territory(std::map<Point, std::string> * territory_map){
        num_black_territory = 0;
        num_white_territory = 0;
        num_black_stones = 0;
        num_white_stones = 0;
        num_dame = 0;

        for (auto itr = territory_map->begin(); itr != territory_map->end(); itr ++){
            Point point = itr->first;
            std::string status = itr->second;
            if (status == "b")
                num_black_stones += 1;
            else if( status == "w")
                num_white_stones += 1;
            else if( status == "territory_b")
                num_black_territory += 1;
            else if (status == "territory_w")
                num_white_territory += 1;
            else if( status == "dame") {
                num_dame += 1;
                dame_points.push_back(point);
            }
        }
        delete territory_map;
    }

void _collect_region(Point & start_pos, Board * board, std::set<Point> & all_points, std::set<Point> & all_borders, std::set<Point> * visited){
    bool FirstCall = false;
    if (visited == NULL) {
        visited = new std::set<Point>();
        FirstCall = true;
    }
    if (visited->find(start_pos) != visited->end()) {
        return;
    }
    all_points.insert(start_pos);
    //all_borders = set()
    visited->insert(start_pos);
    Color here = board->get(start_pos);
    std::vector< std::pair<int, int> > deltas = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    for (int i = 0; i < (int) deltas.size(); i++){
        int delta_r = deltas[i].first;
        int delta_c = deltas[i].second; 
        Point next_p(start_pos.row + delta_r, start_pos.col + delta_c);
        if (! board->is_on_grid(next_p))
            continue;
        Color neighbor = board->get(next_p);
        if (neighbor == here) {
             _collect_region(next_p, board, all_points,all_borders , visited);
        }
        else
            all_borders.insert(next_p);
    }

    if(FirstCall) delete visited;

}

Territory * evaluate_territory(Board * board){

    std::map<Point, std::string> * status = new std::map<Point, std::string> ();
    for(int r =1; r < board->num_rows + 1; r++){
        for(int c =1; c < board->num_cols + 1; c++){
            Point p(r, c); 
            if( status->find(p) != status->end() )
                continue;
            Color stone = board->get(p);
            if (stone != Color::none)  
                (*status)[p] = stone == Color::black ? "b" : "w";
            else{
                std::set<Point> group;
                std::set<Point> neighbors;
                _collect_region(p, board, group, neighbors);
                 std::string fill_with;
                if (neighbors.size() == 1){ 
                    Point neighbor_stone = *(neighbors.begin());
                    std::string stone_str = board->get(neighbor_stone) == Color::black ? "b" : "w";
                    fill_with = "territory_" + stone_str;
                }
                else
                    fill_with = "dame";
                for(auto itr = group.begin(); itr != group.end(); itr++){
                    Point pos  = *itr;
                    (*status)[pos] = fill_with;
                }
            }
        }
    }
    return new Territory(status);
}

    GameResult::GameResult(int b, int w, int komi){
        this->b = b;
        this->w = w;
        this->komi = komi;
    }
    Color GameResult::winner(){
        if(b > w + komi)
            return Color::black;
        return Color::white;
    }

    int GameResult::winning_margin(){
        w = w + komi;
        return abs(b - w);
    }
/*    def __str__():
        w = w + komi
        if b > w:
            return 'B+%.1f' % (b - w,);
        return 'W+%.1f' % (w - b);*/


GameResult*  compute_game_result(GameState * game_state){
    Territory * territory = evaluate_territory(game_state->board);
    return new GameResult(
        territory->num_black_territory + territory->num_black_stones,
        territory->num_white_territory + territory->num_white_stones,
        7.5);
}

