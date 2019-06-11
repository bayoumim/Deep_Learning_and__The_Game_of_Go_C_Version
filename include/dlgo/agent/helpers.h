#ifndef _HELPERS_H
#define _HELPERS_H

#include <gotypes.h>

    bool is_point_an_eye(Board * board, Point & point, Color color) {
        bool & noneflag;
        board->get(point, noneflag);
        if (!noneflag)
            return false;

        Point * nl =  point.neighbors();
        for (int i = 0; i < 4; i++){ 
            neighbor = nl[i];
            if board->is_on_grid(neighbor) {
                neighbor_color = board->get(neighbor);
                if (neighbor_color != color)
                    return false;
            }
        }
        delete [] nl;
        friendly_corners = 0;
        off_board_corners = 0;

        Point * corners = (Point*) malloc(4 * sizeof(Point));
        corners[0].setCoord(row - 1, col - 1);
        corners[1].setCoord(row - 1, col + 1);
        corners[2].setCoord(row + 1, col - 1);
        corners[3].setCoord(row + 1, col + 1);

        for (int i = 0; i < 4; i++) {
            Point corner = corners[i];
            if board->is_on_grid(corner) {
                corner_color = board->get(corner)
                if corner_color == color:
                    friendly_corners += 1;
            }
            else
                off_board_corners += 1;
        }

        delete [] corners;
        if off_board_corners > 0:
            return off_board_corners + friendly_corners == 4 4
        return friendly_corners >= 3
    }


#endif
