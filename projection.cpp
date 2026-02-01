#include <iostream>
#include <vector>
#include <cmath>
#include <thread>
#include <chrono>
using namespace std;

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
    void process_input() {
        string junk;
        cin >> junk >> MIN_X >> 
               junk >> MAX_X >>
               junk >> MIN_Y >>
               junk >> MAX_Y;
        size_t size;
        cin >> size;
        points3d.resize(size);
        points2d.reserve(size);
        for (size_t i = 0; i<size; ++i) {
            Point3D p;
            cin >> p.x >> p.y >> p.z;
            points3d[i] = p;
        }
        cin >> size;
        edges.resize(size);
        for (size_t i = 0; i<size; ++i) {
            size_t idx_1, idx_2;
            cin >> idx_1 >> idx_2;
            edges[i] = {idx_1, idx_2};
        }

        size_x = static_cast<size_t>(MAX_X+1-MIN_X);
        size_y = static_cast<size_t>(MAX_Y+1-MIN_Y);

        graph = vector<vector<char>>(size_x, vector<char>(size_y, ' '));
    }

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
        convert_dim();

        for (const auto &edge: edges) {
            Point2D &p1 = points2d[edge.first];
            Point2D &p2 = points2d[edge.second];

            double angle = atan2(p2.y-p1.y, p2.x - p1.x) * (180.0/M_PI);
            double dist = sqrt(pow(p2.x-p1.x,2) + pow(p2.y-p1.y,2));
            char angle_char = get_char(angle);
            
            double cur_x = p1.x;
            double cur_y = p1.y;
            // int x = static_cast<int>(cur_x-MIN_X);
            // int y = static_cast<int>(cur_y-MIN_Y);

            for (size_t i = 0; i<= static_cast<size_t>(dist); ++i) {
                int x_new = static_cast<int>(cur_x-MIN_X);
                int y_new = static_cast<int>(cur_y-MIN_Y);

                // char angle_char = '.';
                // if (x_new-x == 0) angle_char = '|';
                // else if (y_new-y == 0) angle_char = '-';
                // else if (!((x_new-x)-(y_new-y))) angle_char = '/';
                // else angle_char = '\\';

                // x = x_new;
                // y = y_new;
                graph[static_cast<size_t>(x_new)][static_cast<size_t>(y_new)] = angle_char;

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

    void clear_graph() {
        for (size_t i = 0; i<size_x; ++i) {
            for (size_t j = 0; j<size_y; ++j) {
                graph[i][j] = ' ';
            }
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
    
    void convert_dim() {
        points2d.clear();

        for (Point3D &p3d: points3d) {
            Point2D p2d;
            p2d.x = 0.5*p3d.x + 1*p3d.y;
            p2d.y = 0.5*p3d.x + 1*p3d.z;
            points2d.push_back(p2d);
        }
    }

    void rotate(double del_theta, double del_phi) {
        double theta = del_theta * M_PI / 180.0;
        double phi   = del_phi   * M_PI / 180.0;

        for (Point3D &p : points3d) {
            double x1 = p.x * cos(theta) - p.y * sin(theta);
            double y1 = p.x * sin(theta) + p.y * cos(theta);
            double z1 = p.z;

            double y2 = y1 * cos(phi) - z1 * sin(phi);
            double z2 = y1 * sin(phi) + z1 * cos(phi);

            p.x = x1;
            p.y = y2;
            p.z = z2;
        }
        convert_dim();
    }

private: 
    int MIN_X;
    int MAX_X;
    int MIN_Y;
    int MAX_Y;

    size_t size_x;
    size_t size_y;

    vector<vector<char>> graph;
    vector<Point3D> points3d;
    vector<Point2D> points2d;
    vector<pair<size_t, size_t>> edges;
};

int main () {
    Graph g = Graph();
    g.process_input();

    while (true){
        this_thread::sleep_for(chrono::milliseconds(50));
        cout << "\x1B[2J\x1B[H";

        g.rotate(5,0);
        g.clear_graph();
        g.update_graph();
        g.draw_graph();
    }
}