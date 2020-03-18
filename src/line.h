#ifndef __LINE__H
#define __LINE__H 

#include "enviro.h"
using namespace std;

typedef struct point {
        int x;
        int y;
} Point;

//! Line Class

//! Creates vectors of points that make letters or phrases
class Line {

    public:
    //! Produces a formation for "NO"
    //! \return A vector of Point values which create a "NO" formation
    vector<Point> get_no() {
        vector<Point> no = get_n();
        vector<Point> temp = get_o(30, -50);
        no.insert(no.end(), temp.begin(), temp.end());

        return no;
    }

    //! Produces a formation for "YA"
    //! \return A vector of Point values which create a "YA" formation
    vector<Point> get_ya() {
        vector<Point> ya = get_y(-200, 150);
        vector<Point> temp = get_a(-200 + width + 30, 150);
        ya.insert(ya.end(), temp.begin(), temp.end());

        return ya;
    }

    private:
    int height = 150;
    int width = 120;


    //! Given beginning and end coordinates, creates a vector of point_count Points between the two (inclusive)
    vector<Point> get_line (Point start, Point end, int point_count) {
        if (point_count < 2) {
            throw invalid_argument("Must have 2 or more points");
        }
        
        double rate_y = (end.y - start.y) / point_count;
        double rate_x = (end.x - start.x) / point_count;

        vector<Point> line = {};
        for (int i = 0; i < point_count; i++) {
            int x = (int) i*rate_x + start.x;
            int y = (int) i*rate_y + start.y; // inverted coordinate system
            
            std::cout << "x, y: " << x << " " << y << "\n";
            
            line.push_back(Point{x, y});
        }
        return line;
    }

    //! Produces a vector representation of "N." By default, starts at -100, -50
    //! \return vector representation of "N"
    vector<Point> get_n() {
        vector<Point> n = get_line(Point{-100, -50}, Point{-100, 50}, 5);
        vector<Point> n1 = get_line(Point{-100, -50}, Point{-20, 50}, 6);
        vector<Point> n2 = get_line(Point{-20, -50}, Point{-20, 50}, 5);

        n.insert(n.end(), n1.begin(), n1.end());
        n.insert(n.end(), n2.begin(), n2.end());

        return n;
    }

    //! Produces a vector representation of "O" given starting bottom left coordinates.
    //! \param left x coordinate of bottom left of letter
    //! \param bottom y coordinate of bottom left of letter
    //! \return vector representation of "O"
    vector<Point> get_o(int left, int bottom) {
        vector<Point> n = get_line(Point{left, bottom}, Point{left, bottom + height}, 5);
        vector<Point> n1 = get_line(Point{left, bottom}, Point{left + width, bottom}, 5);
        vector<Point> n2 = get_line(Point{left, bottom + height}, Point{left + width, bottom + height}, 5);
        vector<Point> n3 = get_line(Point{left + width, bottom}, Point{left + width, bottom + height}, 5);

        n.insert(n.end(), n1.begin(), n1.end());
        n.insert(n.end(), n2.begin(), n2.end());
        n.insert(n.end(), n3.begin(), n3.end());

        return n;
    }

    //! Produces a vector representation of "Y" given starting bottom left coordinates.
    //! \param left x coordinate of bottom left of letter
    //! \param bottom y coordinate of bottom left of letter
    //! \return vector representation of "Y"
    vector<Point> get_y(int left, int bottom) {
        int mid_height = bottom - (height/2);   // Inverted coordinate
        int mid_width = left + (width/2);

        vector<Point> n = get_line(Point{mid_width, bottom}, Point{mid_width, mid_height}, 3);
        vector<Point> n1 = get_line(Point{left, bottom-height}, Point{mid_width, mid_height}, 3);
        vector<Point> n2 = get_line(Point{left + width, bottom-height}, Point{mid_width, mid_height}, 3);

        n.insert(n.end(), n1.begin(), n1.end());
        n.insert(n.end(), n2.begin(), n2.end());

        return n;
    }

    //! Produces a vector representation of "A" given starting bottom left coordinates.
    //! \param left x coordinate of bottom left of letter
    //! \param bottom y coordinate of bottom left of letter
    //! \return vector representation of "A"
    vector<Point> get_a(int left, int bottom) {
        int mid_height = bottom - (height/2);   // Inverted coordinate
        double mid_width = left + (width/2);

        vector<Point> n = get_line(Point{left, bottom}, Point{mid_width, bottom - height}, 5);
        vector<Point> n1 = get_line(Point{left + width, bottom}, Point{mid_width, bottom - height}, 5);
        vector<Point> n2 = get_line(Point{left, mid_height+20}, Point{left + width, mid_height+20}, 5);

        n.insert(n.end(), n1.begin(), n1.end());
        n.insert(n.end(), n2.begin(), n2.end());

        return n;
    }    

};

#endif