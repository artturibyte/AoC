#include    <iostream>
#include    <fstream>
#include    <string>
#include    <vector>
#include    <list>
#include    <set>

void print(std::vector<std::set<int>> &v) {
    for (auto set : v)
        {
        for (int i : set) {
            std::cout<<i<<", ";
        }
    std::cout<<"\n";
    }
}

void calc_results(std::vector<unsigned long int> iv){
    unsigned long int tot = 0;
    for (unsigned long int i : iv) {
        tot = tot + i;
    }
    std::cout<<"Total: "<<tot<<"\n";
}

int main(int argc, char const *argv[])
{
    std::ifstream file("input.txt");
    std::string str;

    int pos;
    std::vector<std::set<int>> splitterVec;
    int i = 0;
    while (std::getline(file, str)) {
        pos = 1;
        std::set<int> temp;
        splitterVec.push_back(temp);
        for (char c : str) {
            if (c == 'S' || c == '^') {
                splitterVec[i].insert(pos);
            }
            pos++;
        }
        i++;
    }

    i = 0;
    int length = str.length() + 1;
    std::vector<unsigned long int> results(length, 0);
    for (auto set : splitterVec)
    {
        // first row
        if (i == 0) {
            i++;
            results[*set.begin()]++;
            continue;
        }
        bool splitter_row = i % 2 == 0;
        for (int x : set) {
            if (splitter_row) {
                    results[x - 1] = results[x - 1] + results[x];
                    results[x + 1] = results[x + 1] + results[x];
                    results[x] = 0;
            }
        }
        i++;
    }

    calc_results(results);
    return 0;
}