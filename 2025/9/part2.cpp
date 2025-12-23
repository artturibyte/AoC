#include    <iostream>
#include    <fstream>
#include    <string>
#include    <vector>
#include    <array>
#include    <sstream>
#include    <math.h>
#include    <map>
#include    <algorithm>
#include    <set>


typedef long long int lli;
typedef std::pair<long long int, long long int> tile;
typedef std::pair<int,int> intpair;
typedef std::pair<tile, tile> tile_pair;


lli area_between(const tile &p1, const tile &p2) {
    return (abs(p2.first - p1.first) + 1) * (abs(p2.second - p1.second) + 1); 
}

std::pair<lli, lli> min_max(const lli &i1, const lli &i2) {
    if (i1 > i2) {
        return std::make_pair(i2, i1);
    } else {
        return std::make_pair(i1, i2);
    }
}

int main(int argc, char const *argv[])
{
    std::ifstream file("input.txt");
    std::string str;
    std::vector<tile> tiles;

    while (std::getline(file, str)) {
        tile p;
        std::string delimiter = ",";
        p.first = stoi(str.substr(0, str.find(delimiter)));
        p.second = stoi(str.substr(str.find(delimiter) + 1, -1));
        tiles.push_back(p);
    }

    std::vector<intpair> combinations;
    for (int i = 0; i < tiles.size() ; i++)
    {
        for (int j = i; j < tiles.size() ; j++)
        {
            if (i != j) {
                int id = 10 * i + j;
                combinations.push_back({std::make_pair(i, j)});
            }
        }
    }

    lli biggest_int = 0;
    lli area;
    bool success;
    tile t1;
    tile t2;
    for (auto p : combinations)
    {
        // calculate every box
        area = area_between(tiles.at(p.first), tiles.at(p.second));
        // if size is bigger than last biggest, start checking boundaries

        if (area > biggest_int) {
            // find if any point exists in the rectangle area
            auto [x_smaller, x_upper] = min_max(tiles.at(p.first).first, tiles.at(p.second).first);
            auto [y_smaller, y_upper] = min_max(tiles.at(p.first).second, tiles.at(p.second).second);
            
            success = true;

            // some point exists in the area of the rectangle
            for (auto t : tiles) {
                if (t.first > x_smaller && t.first < x_upper &&
                    t.second > y_smaller && t.second < y_upper) {
                    success = false;
                    break;
                }
            }

            // check if previous step was successful
            if (success) {
            // find if line of two sequential tiles crosses boundaries
            
            for (size_t i = 0; i < tiles.size() - 1; i++)
            {
                t1 = tiles.at(i);
                t2 = tiles.at(i + 1);
                // check if tiles are the same as rectangle corners
                if (t1 == tiles.at(p.first) || (t1 == tiles.at(p.second))
                    || t2 == tiles.at(p.first) || (t2 == tiles.at(p.second))) {
                    continue;
                }

                // check if line between t1 and t2 crosses the rectangle
                auto [line_x_start, line_x_end] = min_max(t1.first, t2.first);
                auto [line_y_start, line_y_end] = min_max(t1.second, t2.second);

                bool x_overlap = !(line_x_end <= x_smaller || line_x_start >= x_upper);
                bool y_overlap = !(line_y_end < y_smaller || line_y_start > y_upper);
                
                if (x_overlap && y_overlap) {
                    success = false;
                    break;
                }
            }
            }
            
            if (success) {
                //std::cout<<tiles.at(p.first).first<<" "<<tiles.at(p.first).second<<"\n";
                //std::cout<<tiles.at(p.second).first<<" "<<tiles.at(p.second).second<<"\n";
                //std::cout<<"x bounds: "<<x_smaller<<" "<<x_upper<<"\n";
                //std::cout<<"y bounds: "<<y_smaller<<" "<<y_upper<<"\n";
                biggest_int = area; 
            }
        }
    }
    std::cout<<"biggest area: "<<biggest_int<<"\n";
}