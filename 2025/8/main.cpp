#include    <iostream>
#include    <fstream>
#include    <string>
#include    <vector>
#include    <array>
#include    <sstream>
#include    <math.h>

typedef std::array<float, 3> point;

void print(std::vector<point> pv) {
    for (auto p : pv) {
    std::cout<<p.at(0)<<" "<<p.at(1)<<" "<<p.at(2)<<"\n";
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


    bool changed_to_products = false;
    int x;
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

    for (int i = 1; i < points.size(); i++)
    {
        std::cout<<distance(points[0], points[i])<<"\n";
    }

    //print(points);

}