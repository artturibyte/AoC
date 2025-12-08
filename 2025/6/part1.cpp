#include    <iostream>
#include    <fstream>
#include    <string>
#include    <vector>
#include    <list>
#include    <algorithm>
#include <sstream>

#include    <iterator>

void print(std::vector<std::string> &s) {
    for (auto p : s)
    {
        std::cout<<p;
        std::cout<<"\n";
    }
    std::cout<<"\n";
}
void print(std::vector<std::vector<int>> &s) {
    for (auto p : s)
    {   
        for ( auto i : p) {
            std::cout<<i<<" ";
        }
        std::cout<<"\n";
    }
    std::cout<<"\n";
}
int main(int argc, char const *argv[])
{
    std::ifstream file("input.txt");
    std::string str;
    std::vector<std::vector<int>> vec;
    std::vector<std::string> problem;
    bool firstloop = true;
    std::string lastline;

    while (std::getline(file, str)) {
        std::istringstream is{str};
        int word;
        std::string s;
        lastline = str;

        int vecn = 0;
        while (is >> word) {
            if ( firstloop) {
                std::vector<int> vi;
                vec.push_back(vi);
            }
            vec[vecn].push_back(word);
            vecn++;
        }
        firstloop = false;
    }
    std::istringstream is2{lastline};
    std::string tempw;
    while (is2 >> tempw) {
            problem.push_back(tempw);
    }
    
    int ii = 0;
    unsigned long long int start = 0;
    unsigned long long int total = 0;
   
    for (auto v : vec) {
        bool first_round = true;
        for (auto x : v) {
            if (problem[ii] == "*") {
                if (first_round) {start = 1;}
                start = x*start;
            } else if (problem[ii] == "+") {
                start = start + x;
            } else {
                std::cout<<"error!!\n";
            }
            first_round = false;
        }
        std::cout<<start<<"\n";
        
        total = total + start;
        start = 0;
        ii++;
    }
    std::cout<<total<<"\n";
}