#ifndef _GO_TYPES
#define _GO_TYPES

enum class Color{black=1, white = 2};

class Player{
public:
    Color clr;
    Player(Color clr){
        this->clr = clr;
    }

    Color other(){
        return clr == Color::black ? Color::white : Color::black;
    }
};

class Point{
public:
    int x;
    int y;

    Point(int x, int y){
        this->x = x;
        this->y = y;
    }

    Point * neighbors(int & count){
        
    }
};
