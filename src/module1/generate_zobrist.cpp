#include <random>
#include <iostream>
#include <map>
#include "gotypes.h"



int main(){
    long long int MAX63 = 0x7fffffffffffffff;
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0,MAX63);
    std::map<Point, std::map<Color, int> > table;

    for ( int row = 1; row < 20; row++){
        for(int col = 1; col < 20; col++){
            for (int i = 0 ; i < 2; i++){
                Color state = i ==0? Color::black : Color::white;
                int code = distribution(generator);
                Point p(row, col);
                table[p][state] = code;
            }
        }
    }
    std::cout << "#include <map> " << std::endl;
    std::cout << "#include \"gotypes.h\" " << std::endl;
    std::cout <<  std::endl;
    std::cout << "constant std::map<Point, std::map<Color, int> > HASH_CODE = {";
    for ( int row = 1; row < 20; row++){
        for(int col = 1; col < 20; col++){
            for (int i = 0 ; i < 2; i++){
                Color state = i ==0? Color::black : Color::white;
                Point p(row, col);
                std::cout <<"{Point(" << row<< ", " << col << "), {"<< i << "," << table[p][state] << "}}";
                if(!( (row ==19) && (col == 19) && (i == 1) ) ) std::cout <<",";
            }
        }
    }

    std::cout <<"};" << std::endl;
    std::cout <<  std::endl;

//print('EMPTY_BOARD = %d' % (empty_board,))

}

//empty_board = 0


