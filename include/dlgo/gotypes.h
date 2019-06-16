#ifndef _GO_TYPES_H
#define _GO_TYPES_H

#include <stdlib.h>
#include <string>
#include <iostream>

enum class Color{none=0,black=1, white = 2};

class Player{
public:
    Color color;
    Player(Color color){
        this->color = color;
    }

    Player * other(){
        Color c = color == Color::black ? Color::white : Color::black;
        Player * player = new Player(c);
        return player;
    }

    std::string print(){
        std::string s;
        s = color == Color::black ? "Black player " : "white player ";
        return s;
    }
};

class Point{
public:
    int row;
    int col;

    Point(){
        setCoord(-1, -1);
    }

    Point(int row, int col){
        setCoord(row, col);
    }
    Point(Point * point){
        setCoord(point->row, point->col);
    }


    bool isNone(){
     //   std::cout << "row : " << row << ". col : " << col << std::endl;
        return row < 0 || col < 0;
    }

    void setCoord(int row, int col){
        this->row = row;
        this->col = col;
    }

    Point * neighbors(){
        Point * r = (Point*) malloc(4 * sizeof(Point));
        r[0].setCoord(row - 1, col);
        r[1].setCoord(row , col - 1);
        r[2].setCoord(row + 1, col);
        r[3].setCoord(row , col + 1);
        return r;
    }

    bool operator< (const Point& rhs) const
    {
        if(rhs.row < this->row)
            return true;
        else if (rhs.row == this->row) return rhs.col < this->col;
        else return false;
    }

    bool operator==(const Point & rhs) const
    {
        return rhs.row == this->row && rhs.col == this->col;
    }

};

#endif
