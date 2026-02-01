#include <iostream>
#include <vector>
#include <cmath>
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
        del_theta *= (M_PI/180);
        del_phi *= (M_PI/180);

        for (Point3D &p: points3d) {
            double rho = sqrt(p.x*p.x + p.y*p.y + p.z*p.z);
            double theta = atan2(p.y, p.x)+ del_theta;
            double phi = acos(p.z/rho)+ del_phi;

            if (isnan(phi)) phi = 0;

            p.x = rho * sin(phi) * cos(theta);
            p.y = rho * sin(phi) * sin(theta);
            p.z = rho * cos(phi);

            cout << rho << " " << theta  << " " << phi << "\n";
            cout << p.x << " " <<p.y  << " " << p.z << "\n";
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
    g.rotate(30,30);
    g.update_graph();
    g.draw_graph();
}