#include    <iostream>
#include    <fstream>
#include    <string>
#include    <vector>
#include    <list>

int max_neighbours = 3;

int is_paper(const char &c) {
    if (c=='@' || c=='x') { // paper or removable paper
        return 1;
    } else {
        return 0;
    } 
}

bool is_access(const std::vector<std::string> &cells, int row, int col) {
    if (cells[row][col]=='.') {
        std::cout<<".";
        return false; // not paper
    }

    int papers = is_paper(cells[row - 1][col - 1]) +
    is_paper(cells[row - 1][col]) +
    is_paper(cells[row + 1][col]) +
    is_paper(cells[row][col + 1]) +
    is_paper(cells[row][col - 1]) +
    is_paper(cells[row + 1][col + 1]) +
    is_paper(cells[row + 1][col - 1]) +
    is_paper(cells[row - 1][col + 1]);

    if (papers > max_neighbours) {
        std::cout<<papers;
        return false;
    } else { 
        std::cout<<"x";
        return true;
    }
}

int iter_list(std::vector<std::string> &v, int l) {
    int max = 0;

        for (size_t i = 1; i < l + 1; i++)
        {
            for (size_t j = 1; j < v[i].length() - 1; j++)
            {
                //std::cout<<v[i][j];
                if (is_access(v, i, j) ) {
                    v[i][j] = '.';
                    max++; // accessible paper found
                }  
            }
            std::cout<<"\n";
        }
        return max;
}

void print(std::vector<std::string> v) {
    for (auto l : v)
        {
        for (auto str : l)
        {
            std::cout<<str;
        }
        std::cout<<"\n";
    }
}


int main(int argc, char const *argv[])
{
    std::ifstream file("input.txt");
    std::string str;
    std::vector<std::string> vec;
        
    int i = 0;
    int width = 100;
    
    // create vec. add "." around the set.
    while (std::getline(file, str)) {
        if (i == 0) {
            width = str.length() + 1;
           std::string s(width, '.');
           vec.push_back(s);
        }
        str.append(".");
        str.insert(0, ".");
        vec.push_back(str);
        i++;
    }
    std::string s(width, '.');
    vec.push_back(s);


    int max = 0;
    int res;
    while (true) {
        std::cout << "\x1b[2J"; // clear screen for visu
        res = iter_list(vec, i);
        if (res == 0)
            break;

        max = max + res;
        std::cin.get();  // wait input for visu
    }
    //print(vec);
    std::cout<<max<<"\n";

}