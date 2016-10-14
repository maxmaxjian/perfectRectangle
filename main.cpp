#include <iostream>
#include <vector>
#include <utility>
#include <climits>
#include <cmath>
#include <unordered_set>
#include <cassert>
#include <functional>

using std::vector;
using std::pair;

struct myHasher {
    size_t operator()(const vector<int> & v) const {
        size_t result = 1;
        for (auto i : v)
            result ^= std::hash<int>()(i);
        return result;
    }
};

class solution {
  public:
    bool isRectangleCover(const vector<vector<int>> & rectangles) {
        pair<int,int> botleft(INT_MAX/2, INT_MAX/2), topright(0, 0);
        for (auto rec : rectangles) {
            if (pow(rec[0],2)+pow(rec[1],2) < pow(botleft.first,2)+pow(botleft.second,2)) {
                botleft.first = rec[0];
                botleft.second = rec[1];
            }
            if (pow(rec[2],2)+pow(rec[3],2) > pow(topright.first,2)+pow(topright.second,2)) {
                topright.first = rec[2];
                topright.second = rec[3];
            }
        }

        // std::cout << "botleft = (" << botleft.first << "," << botleft.second << ")\n";
        // std::cout << "topright = (" << topright.first << "," << topright.second << ")\n";
        std::unordered_set<vector<int>, myHasher> recSet;
        for (int i = botleft.first; i < topright.first; ++i) {
            for (int j = botleft.second; j < topright.second; ++j) {
                // std::cout << "(" << i << "," << j << "," << i+1 << "," << j+1 << ")\n";
                recSet.emplace(vector<int>{i,j, i+1, j+1});
            }
        }

        // for (auto it = recSet.begin(); it != recSet.end(); ++it) {
        //     std::cout << "(" << (*it)[0] << "," << (*it)[1] << "," << (*it)[2] << "," << (*it)[3] << ")\n";
        // }

        if (recSet.empty()) {
            std::cerr << "Not a valid rectangle\n";
            return false;
        }
        
        for (auto rec : rectangles) {
            for (int i = rec[0]; i < rec[2]; ++i) {
                for (int j = rec[1]; j < rec[3]; ++j) {
                    vector<int> curr{i,j,i+1,j+1};
                    if (recSet.find(curr) == recSet.end()) {
                        std::cerr << "One unit not found\n";
                        // std::cout << "(" << curr[0] << "," << curr[1] << "," << curr[2] << "," << curr[3] << ")\n";
                        return false;
                    }
                    // std::cout << "before = " << recSet.size() << std::endl;
                    recSet.erase(curr);
                    // std::cout << "after = " << recSet.size() << std::endl;
                }
            }
        }

        std::cout << std::endl;
        for (auto it = recSet.begin(); it != recSet.end(); ++it) {
            std::cout << "(" << (*it)[0] << "," << (*it)[1] << "," << (*it)[2] << "," << (*it)[3] << ")\n";
        }
        if (!recSet.empty()) {
            std::cerr << "Unit not covered\n";
            return false;
        }
        return true;
    }
};

int main() {
    // vector<vector<int>> rectangles{
    //     {1,1,2,3},
    //     {1,3,2,4},
    //     {3,1,4,2},
    //     {3,2,4,4}
    // };

    // vector<vector<int>> rectangles{
    //     {1,1,3,3},
    //     {3,1,4,2},
    //     {3,2,4,4},
    //     {1,3,2,4},
    //     {2,3,3,4}
    // };

    // vector<vector<int>> rectangles{
    //     {1,1,2,3},
    //     {3,1,4,2},
    //     {1,3,2,4},
    //     {3,2,4,4}
    // };

    vector<vector<int>> rectangles{
        {1,1,3,3},
        {3,1,4,2},
        {1,3,2,4},
        {2,2,4,4}
    };
    
    solution soln;
    bool isRectangle = soln.isRectangleCover(rectangles);
    std::cout << std::boolalpha
              << isRectangle << std::endl;
}
