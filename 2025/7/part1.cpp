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
    int total = 0;
    std::set<int> splitters;
    int length = str.length() + 1;
    std::string dots;
    for (auto set : splitterVec)
    {
        //std::cout<<"step "<<i<<": ";
        dots = std::string(length, '.');
        if (i == 0) {
            splitterVec[1].insert(*set.begin());
            //std::cout<<"First round. \n";
            i++;
            continue;
        }
        // loop current set and compare to previous
        bool previous_contains;
        bool splitter_row = i % 2 == 0;

        if (!splitter_row) {
            splitters = splitterVec[i + 1];
        }

        for (int x : set) {
            previous_contains = splitterVec[i - 1].find(x) != splitterVec[i- 1].end();
            bool is_splitter = splitters.find(x) != splitters.end();

            if (is_splitter) {
                dots[x - 1] = '^';
            }
            // splitter row
            if (previous_contains & splitter_row) {
                // add beams to next lane
                if (is_splitter){
                    //std::cout<<" Splitter found: "<< x <<".";
                    //std::cout<<" adding "<< x - 1 <<" and " << x + 1<<" to next. ";
                    splitterVec[i].insert(x-1);
                    splitterVec[i].insert(x+1);
                    splitterVec[i + 1].insert(x-1);
                    splitterVec[i + 1].insert(x+1);
                    dots[x-2] = '|';
                    dots[x] = '|';
                    total++;
                } else {
                    // not splitter, add straight to next
                    //std::cout<<"Continue beam: "<<x<<". ";
                    
                    splitterVec[i + 1].insert(x);
                    dots[x-1] = '|';
                    
                }
            }
            
            // only beam row
            if (!splitter_row) {
                dots[x-1] = '|';
                
                //std::cout<<" Beam "<<x<<" ";
                splitterVec[i + 1].insert(x);
            }
        }
        std::cout<<dots<<"\n";
        if (i == splitterVec.size() - 2) {
            break;
        }
        i++;
    }
    dots = std::string(length, '.');
    for (int x : splitterVec[i+1]) {
        dots[x-1] = '|';
    }
    std::cout<<dots<<"\n";
    //print(splitterVec);
    std::cout<<"Total: "<<total<<std::endl;
    return 0;
}