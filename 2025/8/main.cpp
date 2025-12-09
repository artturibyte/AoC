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

typedef std::array<float, 3> point;
typedef std::pair<int,int> intpair;

void print(std::vector<point> pv) {
    for (auto p : pv) {
    std::cout<<p.at(0)<<" "<<p.at(1)<<" "<<p.at(2)<<"\n";
    }
}

void print(std::vector<std::set<int>> v) {
    int i = 0;
    for (auto s : v) {
        std::cout<<i +1<<" network size: "<<s.size();
        
        for (auto i : s) {
           //std::cout<<i<<" "; 
        }
        i++;
    std::cout<<"\n";
    }
}

float distance(point p1, point p2) {
    return sqrt( pow(p2.at(0) - p1.at(0),  2)   +  pow(p2.at(1) - p1.at(1), 2)  +  pow(p2.at(2) - p1.at(2), 2)) ;
}

int main(int argc, char const *argv[])
{
    std::ifstream file("input.txt");
    std::string str;
    std::vector<point> points;
    std::string str2;

    while (std::getline(file, str)) {
        point p;
        std::istringstream iss(str);
        int index = 0;
        while (std::getline(iss, str2, ',')) {
            p[index] = stoul(str2);
            index++;
        }
        points.push_back(p);
    }

    std::vector<intpair> combinations;
    for (int i = 0; i < points.size() ; i++)
    {
        for (int j = i; j < points.size() ; j++)
        {
            if (i != j) {
                int id = 10 * i + j;
                combinations.push_back({std::make_pair(i, j)});
            }
        }
    }

    std::vector<std::pair<intpair, float>> distances;
    for (auto const &comb : combinations)
    {
        //std::cout << first<<second << " : "   << std::endl;
        distances.push_back(std::make_pair(comb, distance(points[comb.first], points[comb.second])));
    }

    std::sort(begin(distances), end(distances), [](auto d1, auto d2){return d1.second < d2.second;});
    for (auto const& [key, val] : distances)
    {
        //std::cout << key.first<<", "<<key.second << " : "  << val << std::endl;
    }

    // get i shortest combinations and add to circuit
    // part1 : i < 1000
    std::vector<std::set<int>> circuits{};
    for (size_t i = 0; i < combinations.size(); i++)
    {
        //std::cout<<i<<"\n";
        // first circuit need to be created manually
        if(i == 0) {
            std::set<int> circuit;
            circuit.insert(distances[i].first.first);
            circuit.insert(distances[i].first.second);
            circuits.push_back(circuit);
            continue;
        }

        bool contains_first = false;
        bool contains_second = false;
        int index = 0;
        int cirpos = 0;
        int cirpos2 = 0;
        bool index_lock = false;
        bool found2 = false;

        for (auto s : circuits) {
            //check if circuit is already part of some circuit
            contains_first = s.find(distances[i].first.first) != s.end();
            contains_second = s.find(distances[i].first.second) != s.end();

            // if other index is part of some circuit, check if 
            // other is part of some other circuit. if yes, combine them after.
            if (index_lock & (contains_first | contains_second)) {
                cirpos2 = index;
                found2 = true;
                break;
            }
            if (contains_first | contains_second) {
                if (!index_lock) {cirpos = index;}
                index_lock = true;
            }
            index++;
        }
        
        if (index_lock) {
            //std::cout<<"insert "<<distances[i].first.first<<" " <<distances[i].first.second<<"\n";;
            circuits[cirpos].insert(distances[i].first.first);
            circuits[cirpos].insert(distances[i].first.second);
        } else {
            std::set<int> circuit;
            //std::cout<<"create: "<<distances[i].first.first<<" " <<distances[i].first.second<<"\n";
            circuit.insert(distances[i].first.first);
            circuit.insert(distances[i].first.second);
            circuits.push_back(circuit);
        }

        if (found2) {
            circuits[cirpos].insert(begin(circuits[cirpos2]), end(circuits[cirpos2]));
            circuits.erase(circuits.begin() + cirpos2);
        }

        bool is_tuhat = false;
        for (auto c : circuits) {
            if (c.size() == 1000) 
                is_tuhat = true;
        }

        if (is_tuhat) {
            
            std::cout<<"last index: "<<i<<" from : "<<combinations.size()<<"\n";
            std::cout<<points[distances[i].first.first][0]<<"\n";
            std::cout<<points[distances[i].first.second][0]<<"\n";
            std::cout.setf(std::ios::fixed, std::ios::floatfield );
            std::cout.setf(std::ios::showpoint);  
            std::cout<<"Combine: " << points[distances[i].first.first][0] * points[distances[i].first.second][0]<<"\n";
            break;
        }
    }

    // part1:
    std::sort(begin(circuits), end(circuits), [](auto d1, auto d2){return d1.size() > d2.size();});
    int total = circuits[0].size() * circuits[1].size() * circuits[2].size();
    std::cout<<"part 1: Total: "<<total;
    
    //print(points);

}
