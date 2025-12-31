#include    <iostream>
#include    <fstream>
#include    <string>
#include    <vector>
#include    <sstream>
#include    <regex>
#include    <bitset>

const int BIT_LENGTH = 16;
typedef std::bitset<BIT_LENGTH> light_conf, light_state;
typedef std::vector<light_conf> button_vec;

button_vec getButtons(const std::string& str) {
    std::vector<std::bitset<BIT_LENGTH>> bits;
    std::regex pattern(R"(\(([0-9,]+)\))");
    std::smatch match;
    
    std::string::const_iterator searchStart(str.cbegin());
    while (std::regex_search(searchStart, str.cend(), match, pattern)) {
        std::string content = match[1].str();
        light_conf bitPattern = 0;
        
        // Parse comma-separated numbers and set bits
        std::string token;
        std::istringstream iss(content);
        int index = 0;
        while (std::getline(iss, token, ',')) {
            bitPattern[BIT_LENGTH - 1 - stoi(token)] = 1;
        }
        
        bits.push_back(bitPattern);
        searchStart = match.suffix().first;
    }
    
    return bits;
}

light_conf getLights(const std::string& str) {
    std::regex pattern(R"(\[([.#]+)\])");
    std::smatch match;
    light_conf bitPattern;
    
    if (std::regex_search(str, match, pattern)) {
        std::string content = match[1].str();
        
        // Convert # to 1 and . to 0
        int i = 0;
        for (char c : content) {
            if (c == '#') {
                bitPattern[BIT_LENGTH -1 - i] = 1;
            }
            i++;
        }
    }
    return bitPattern;
}

void print_bits(light_conf bs) {
    std::cout << bs.to_string() << " ";
}

int solve_smallest_button_press_count(std::pair<light_conf, button_vec> ld) {
    int press_count = 0;
    // set empty state for start
    light_conf lc;
    std::vector<light_conf> light_states {lc};
    while (true)
    {
        std::vector<light_conf> new_states;
        press_count++;
        for (auto state : light_states) {
            for (auto button : ld.second) {
                light_state new_state = state ^ button;

                if (new_state == ld.first) {
                    //std::cout<<"solved with state: ";
                    //print_bits(new_state);
                    std::cout<<"With "<<press_count<<" button presses\n";
                    return press_count;
                }
                new_states.push_back(new_state);
            }
        }
        light_states = new_states;
    }
    return press_count;
}

int main(int argc, char const *argv[])
{
    std::ifstream file("input.txt");
    std::string str;
    std::vector<std::string> problems;

    while (std::getline(file, str)) {
        problems.push_back(str);
    }

    std::vector<std::pair<light_conf, button_vec>> light_diagrams;
    for (auto str : problems) {
        auto lights = getLights(str);
        button_vec buttons = getButtons(str);
        light_diagrams.push_back({lights, buttons});
    }

    int total = 0;
    for (auto ld : light_diagrams){
        total = total + solve_smallest_button_press_count(ld);
    }
    std::cout<<"total = "<<total<<"\n";

    //for (auto ld : light_diagrams) {
        //print_bits(ld.first);
        //std::cout << " | ";
        //for (std::bitset<16> bs : ld.second) {
        //    print_bits(bs);
        //}
        //std::cout << std::endl;
    //}

}
