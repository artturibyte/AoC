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


typedef unsigned long long int ull;
typedef std::pair<long long int, long long int> tile;
typedef std::pair<tile, tile> tile_pair;

ull area_between(tile p1, tile p2) {
    return (abs(p2.first - p1.first) + 1) * (abs(p2.second - p1.second) + 1); 
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

    std::vector<tile_pair> combinations;
    for (int i = 0; i < tiles.size() ; i++)
    {
        for (int j = i; j < tiles.size() ; j++)
        {
            if (i != j) {
                combinations.push_back({std::make_pair(tiles.at(i), tiles.at(j))});
            }
        }
    }

    ull biggest_int = 0 ;
    ull area;
    for (auto pair : combinations) {
        //std::cout<<pair.first.first<<" "<<pair.first.second<<"\n";
        //std::cout<<pair.second.first<<" "<<pair.second.second<<"\n";
        area = area_between(pair.first, pair.second);
        if (area > biggest_int) {
            //std::cout<<pair.first.first<<" "<<pair.first.second<<"\n";
            //std::cout<<pair.second.first<<" "<<pair.second.second<<"\n";
            biggest_int = area;
            std::cout<<area<<"\n";
        }
    }

    std::cout<<"biggest area: "<<biggest_int<<"\n";
}
