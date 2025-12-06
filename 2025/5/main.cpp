#include    <iostream>
#include    <fstream>
#include    <string>
#include    <vector>
#include    <list>
#include    <algorithm>

typedef unsigned long long int ull;

void print(std::vector<std::pair<ull, ull>> &v) {
    for (auto p : v)
    {
        std::cout<<p.first<<" - "<<p.second;
        std::cout<<"\n";
    }
    std::cout<<"\n";
}

void print(std::vector<ull> ids) {
    for (auto p : ids)
    {
        std::cout<<p;
        std::cout<<"\n";
    }
    std::cout<<"\n";
}

int main(int argc, char const *argv[])
{
    std::ifstream file("input.txt");
    std::string str;
    std::vector<std::pair<ull, ull>> ranges;
    std::vector<ull> ids;

    bool changed_to_products = false;
    ull total = 0;
    
    // gather data
    while (std::getline(file, str)) {
        // changed to id's
        if (str.empty())
            changed_to_products = true;
        
        if (!changed_to_products) {
            int pos = str.find("-");
            ranges.push_back({stoul(str.substr(0, pos)),  stoul(str.substr(pos +1))});
        } else {
            // ID's
            if (!str.empty())
                ids.push_back(stoul(str));
        }
    }

    // Sort ranges to starting from range start, 
    std::sort(begin(ranges), end(ranges), [](auto p1, auto p2){
        if(p1.first != p2.first) {
            return p1.first < p2.first;
        } else {
            return p1.second < p2.second;
        }});
    
    // remove duplicates
    auto dups = unique(begin(ranges), end(ranges));
	ranges.erase(dups, end(ranges));

    print(ranges);

    ull last_max = 0;
    ull curmax = 0;
    // manipulate ranges
    for (auto &range : ranges) {
        // Compare last ranges max value to current first.
        // if first is smaller or equal to lastmax,
        // update first to lastmax + 1 to prevent overlap.
        //
        if (range.first <= last_max) {
            std::cout<<"range first is overlapped...\n";
            if (range.second > last_max) {
                std::cout<<"Range second is not overlapped, set start to "<<last_max +1<<"\n";
                range.first = last_max + 1;
            // if also second is smaller than lastmax 
            // range is totally overlapped. Set first to lastmax
            // to set range to removed.
            } else {
                range.first = last_max + 1;
                std::cout<<"whole range is overlapped, set first to "<<last_max<<"\n";
            }
        }

        // If first == second, should outcome as +1 if not overlapped.
        // set lastmax to +1 to prevent overlap
        if (range.first == range.second & range.first > last_max){

            last_max = range.first + 2;
        }
        
        curmax = (range.first > range.second) ? range.first : range.second;
        if (curmax > last_max) {
            last_max = curmax;
        }
    }

    //std::cout<<"\n";
    auto last = std::remove_if(begin(ranges), end(ranges), [](auto p){ return p.first > p.second;});
    ranges.erase(last, end(ranges));


    // sum all ranges
    for (auto range : ranges) {
        total = total + range.second  - range.first + 1;
        last_max = range.second;
    }
    
    print(ranges);
    std::cout<<total<<"\n";
}