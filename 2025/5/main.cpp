#include    <iostream>
#include    <fstream>
#include    <string>
#include    <vector>
#include    <list>

void print(std::vector<std::pair<unsigned long long int, unsigned long long int>> &v) {
    for (auto p : v)
        {

            std::cout<<p.first<<" - "<<p.second;

        std::cout<<"\n";
    }
}

void print(std::vector<unsigned long long int> ids) {
    for (auto p : ids)
        {
            std::cout<<p;

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
    int total = 0;
    
    while (std::getline(file, str)) {
        
        if (str.empty())
            changed_to_products = true;
        
        if (!changed_to_products) {
            int pos = str.find("-");
            ranges.push_back({stoul(str.substr(0, pos)),  stoul(str.substr(pos +1))});
            //std::cout<<str<<"\n";
        } else {
            //std::cout<<str<<"\n";
            if (!str.empty())
                ids.push_back(stoul(str));
        }
    }

    //print(ranges);
    //print(ids);

        for (auto range : ranges) {
            total = total + range.second - range.first;
            std::cout<<range.second - range.first << "\n";
            
        }
    

    std::cout<<total<<"\n";

}