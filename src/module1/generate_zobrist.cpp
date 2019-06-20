#include <random>
#include <iostream>
#include <map>
#include "gotypes.h"



int main(){
    unsigned long long int MAX63 = 0x7fffffffffffffff;
    std::default_random_engine generator;
    std::uniform_int_distribution< unsigned long long int> distribution(0,MAX63);
    std::map<Point, std::map<Color, unsigned long long  int> > table;

    for ( int row = 1; row < 20; row++){
        for(int col = 1; col < 20; col++){
            for (int i = 0 ; i < 2; i++){
                Color state = i ==0? Color::black : Color::white;
                unsigned long long int code = distribution(generator);
                Point p(row, col);
                table[p][state] = code;
            }
        }
    }
    std::cout << "#include <map> " << std::endl;
    std::cout << "#include \"gotypes.h\" " << std::endl;
    std::cout <<  std::endl;
    std::cout << "const std::map<Point , std::map<Color, unsigned long long int> >  HASH_CODE = {";
    for ( int row = 1; row < 20; row++){
        for(int col = 1; col < 20; col++){
            std::cout <<"{ { " << row<< " , " << col << " } , {" ;
            for (int i = 0 ; i < 2; i++){
                Color state = i ==0? Color::black : Color::white;
                std::string str = i ==0? "Color::black" : "Color::white";
                Point p(row, col);
                std::cout <<"{"<< str << "," << table[p][state] << "}";
                if( i == 0 ) std::cout << "," ;
            }
            std::cout << "} }" ;
            if(!( (row ==19) && (col == 19) ) ) std::cout <<"," << std::endl;
        }
    }

    std::cout <<"};" << std::endl;
    std::cout <<  std::endl;

    std::cout << "unsigned long long int EMPTY_BOARD = " << distribution(generator) << ";" << std::endl;

}

//empty_board = 0


