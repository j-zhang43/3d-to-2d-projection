#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

struct Point2D {
    double x;
    double y;
};
struct Point3D {
    double x;
    double y;
    double z;
};

class Graph {
public:
    char get_char(double angle) {
        char angle_char;  
        if (angle < -150) {
            angle_char = '-';
        } else if (angle < -120) {
            angle_char = '/';
        } else if (angle < -60) {
            angle_char = '|';
        } else if (angle < -30) {
            angle_char = '\\';
        } else if (angle < 30) {
            angle_char = '-';
        } else if (angle < 60) {
            angle_char = '/';
        } else if (angle < 120) {
            angle_char = '|';
        } else if (angle < 150) {
            angle_char = '\\';
        } else {
            angle_char = '-';
        }
        return angle_char;
    }
    void update_graph() {
        for (const auto &edge: edges) {
            Point2D &p1 = points2d[edge.first];
            Point2D &p2 = points2d[edge.second];

            double angle = atan2(p2.y-p1.y, p2.x - p1.x) * (180.0/M_PI);
            double dist = sqrt(pow(p2.x-p1.x,2) + pow(p2.y-p1.y,2));
            cout << edge.first << " " << edge.second << " "<< angle << '\n';
            char angle_char = get_char(angle);
            double cur_x = p1.x;
            double cur_y = p1.y;

            for (size_t i = 0; i<= static_cast<size_t>(dist); ++i) {
                size_t x = static_cast<size_t>(cur_x-MIN_X);
                size_t y = static_cast<size_t>(cur_y-MIN_Y);
                graph[x][y] = angle_char;
                cur_x += cos(angle * (M_PI/180.0));
                cur_y += sin(angle * (M_PI/180.0));
            }
        }
        for (Point2D &p: points2d) {
            size_t x = static_cast<size_t>(p.x-MIN_X);
            size_t y = static_cast<size_t>(p.y-MIN_Y);

            graph[x][y] = 'o';
        }
    }
    void draw_graph() {
        for (size_t i = 0; i < size_x+2; ++i) {
            cout << '-';
        }
        cout << '\n';
        for (size_t j = size_y; j>0;) {
            --j;
            cout << '|';
            for (size_t i = 0; i<size_x; ++i) {
                cout << graph[i][j];
            }
            cout << "|\n";
        }
        for (size_t i = 0; i < size_x+2; ++i) {
            cout << '-';
        }
        cout << '\n';
    }
    

private: 
    int MIN_X = -10;
    int MAX_X = 10;
    int MIN_Y = -10;
    int MAX_Y = 10;

    size_t size_x = static_cast<size_t>(MAX_X+1-MIN_X);
    size_t size_y = static_cast<size_t>(MAX_Y+1-MIN_Y);

    vector<vector<char>> graph = vector<vector<char>>(size_x, vector<char>(size_y, ' '));
    vector<Point3D> points3d = {{0,0,0}, {5,0,0}, {0,5,0}};
    vector<Point2D> points2d = {{0,0}, {-5,10}, {0, 10}};
    vector<pair<size_t, size_t>> edges = {{0,1}, {0,2}, {1,2}};
};

int main () {
    Graph g = Graph();
    g.update_graph();
    g.draw_graph();
}