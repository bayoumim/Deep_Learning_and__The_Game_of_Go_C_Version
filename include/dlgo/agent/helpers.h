#ifndef _HELPERS_H
#define _HELPERS_H

    bool is_point_an_eye(Board * board, Point & point, Color color) {
        Color c = board->get(point);
        if (c != Color::none)
            return false;

        Point * nl =  point.neighbors();
        for (int i = 0; i < 4; i++){ 
            Point neighbor = nl[i];
            if (board->is_on_grid(neighbor)) {
                Color neighbor_color = board->get(neighbor);
            //    assert(neighbor_color != Color::none);
                if (neighbor_color != color)
                    return false;
            }
        }
        delete [] nl;
        int friendly_corners = 0;
        int off_board_corners = 0;

        Point * corners = (Point*) malloc(4 * sizeof(Point));
        corners[0].setCoord(point.row - 1, point.col - 1);
        corners[1].setCoord(point.row - 1, point.col + 1);
        corners[2].setCoord(point.row + 1, point.col - 1);
        corners[3].setCoord(point.row + 1, point.col + 1);

        for (int i = 0; i < 4; i++) {
            Point corner = corners[i];
            if (board->is_on_grid(corner)) {
                Color corner_color = board->get(corner);
                assert(corner_color != Color::none);
                if (corner_color == color)
                    friendly_corners += 1;
            }
            else
                off_board_corners += 1;
        }

        delete [] corners;
        if (off_board_corners > 0)
            return off_board_corners + friendly_corners == 4;
        return friendly_corners >= 3;
    }


#endif
