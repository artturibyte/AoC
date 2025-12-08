#include    <iostream>
#include    <fstream>
#include    <string>
#include    <vector>
#include    <algorithm>
#include <sstream>

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
    std::vector<std::string> vec;
    std::vector<std::string> problems;
    std::vector<std::vector<int>> numvec;
    bool firstloop = true;
    std::string lastline;

    while (std::getline(file, str)) {
        std::reverse(begin(str), end(str));
        vec.push_back(str);
        
        lastline = str;
    }
    // remove last line
    vec.pop_back();

    std::istringstream is2{lastline};
    std::string temps;
    while (is2 >> temps) {
        problems.push_back(temps);
    }

    int len = vec.back().length();
    bool vector_updated = false;
    int vec_i = 0;
    for (size_t i = 0; i < len; i++)
    { 
        if (!vector_updated){
            // add new vector
            std::vector<int> temp_vec;
            numvec.push_back(temp_vec);
            vector_updated = true;
        }

        std::string temp_int = "";
        for (auto s : vec) {
            if ( isdigit(s.at(i)) ){
                temp_int.append(s.substr(i, 1));
            }
        }
        temp_int.erase(remove_if(temp_int.begin(), temp_int.end(), isspace), temp_int.end());
        
        if (!temp_int.empty()) {
            //std::cout<<temp_int<<"\n";
            numvec[vec_i].push_back(stoi(temp_int));
        } else {
            vector_updated = false;
            vec_i++;
            
        }
    }
    print(numvec);
    

    int ii = 0;
    unsigned long long int start = 0;
    unsigned long long int total = 0;
   
    for (auto v : numvec) {
        bool first_round = true;
        for (auto x : v) {
            std::cout<<x<<problems[ii]<<start<<"\n";
            if (problems[ii] == "*") {
                if (first_round) {start = 1;}
                start = x*start;
            } else if (problems[ii] == "+") {
                start = start + x;
            } else {
                std::cout<<"error!!\n";
            }
            first_round = false;
        }
        std::cout<<"start"<<start<<"\n";
        
        total = total + start;
        start = 0;
        ii++;
    }
    std::cout<<total<<"\n";
}