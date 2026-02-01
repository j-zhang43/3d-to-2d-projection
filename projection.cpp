#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

struct Point2D {
    double x;
    double y;
};

class Graph {
public:
    void draw_graph() {
        for (size_t i = 0; i < size_x+2; ++i) {
            cout << '-';
        }
        cout << '\n';
        for (size_t i = 0; i<size_x; ++i) {
            cout << '|';
            for (size_t j = 0; j<size_y; ++j) {
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
    int MIN_X = 0;
    int MAX_X = 10;
    int MIN_Y = 0;
    int MAX_Y = 10;

    size_t size_x = static_cast<size_t>(MAX_X-MIN_X);
    size_t size_y = static_cast<size_t>(MAX_Y-MIN_Y);

    vector<vector<char>> graph = vector<vector<char>>(size_x, vector<char>(size_y, ' '));
    vector<Point2D> points2d = {{0,1}, {5.5,5}};
    vector<pair<int, int>> edges = {{0,1}};
};

int main () {
    Graph g();
}