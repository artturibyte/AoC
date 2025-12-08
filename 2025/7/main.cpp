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

int main(int argc, char const *argv[])
{
    std::ifstream file("input.txt");
    std::string str;
    std::vector<std::pair<unsigned long long int, unsigned long long int>> ranges;
    std::vector<unsigned long long int> ids;

    bool changed_to_products = false;
    int pos;
    std::vector<std::set<int>> setVec;
    int i = 0;
    while (std::getline(file, str)) {
        pos = 1;
        std::set<int> temp;
        setVec.push_back(temp);
        for (char c : str) {
            if (c == 'S' || c == '^') {
                
                setVec[i].insert(pos);
            }
            pos++;
        }
        i++;
    }

    i = 0;
    int total = 0;
    std::set<int> splitters;
    for (auto set : setVec)
    {
        std::cout<<"step "<<i<<": ";
        if (i == 0) {
            setVec[1].insert(*set.begin());
            std::cout<<"First round. \n";
            i++;
            continue;
        }
        // loop current set and compare to previous
        bool previous_contains;
        bool splitter_row = i % 2 == 0;

        if (!splitter_row) {
            splitters.clear();
        }

        for (int x : set) {
            previous_contains = setVec[i - 1].find(x) != setVec[1- 1].end();
            bool next_is_splitter = splitters.find(x) != splitters.end();

            // splitter row
            if (previous_contains & splitter_row) {
                // add beams to next lane
                if (next_is_splitter){
                    std::cout<<" Spiltter found: "<< x <<".";
                    std::cout<<" adding "<< x - 1 <<" and " << x + 1<<" to next. ";
                    setVec[i + 1].insert(x-1);
                    setVec[i + 1].insert(x+1);
                    setVec[i + 1].erase(x);
                    total++;
                } else {
                    std::cout<<"Continue beam: "<<x<<". ";
                    setVec[i + 1].insert(x);
                }
            }
            
            // only beam row
            if (!splitter_row) {
                bool next_contains = setVec[i + 1].find(x) != setVec[i + 1].end();
                if (next_contains) {
                    // is not splitter but beam continues
                    std::cout<<"added to splitters:";
                    splitters.insert(x);
                }
                
                std::cout<<" Beam "<<x<<" ";
                setVec[i + 1].insert(x);
            }
        }
        std::cout<<"\n";
        i++;
        if (i == setVec.size() - 1) {
            break;
        }
    }
    print(setVec);
    std::cout<<"Total: "<<total<<std::endl;
    return 0;
}