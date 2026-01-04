#include    <iostream>
#include    <fstream>
#include    <string>
#include    <vector>
#include    <sstream>
#include    <regex>
#include    <bitset>
#include    <array>
#include    <algorithm>


std::vector<std::vector<int>> getButtons(const std::string& str) {
    std::vector<std::vector<int>> bits;
    std::regex pattern(R"(\(([0-9,]+)\))");
    std::smatch match;
    
    std::string::const_iterator searchStart(str.cbegin());
    while (std::regex_search(searchStart, str.cend(), match, pattern)) {
        std::string content = match[1].str();
        std::vector<int> buttons;
        
        // Parse comma-separated numbers and set bits
        std::string token;
        std::istringstream iss(content);
        int index = 0;
        while (std::getline(iss, token, ',')) {
            buttons.push_back(stoi(token));
        }
        
        bits.push_back(buttons);
        searchStart = match.suffix().first;
    }
    return bits;
}

std::array<int, 10> getJoltages(const std::string& str) {
    std::regex pattern(R"(\{([0-9,]+)\})");
    std::smatch match;
    std::array<int, 10> arr = {};
    
    if (std::regex_search(str, match, pattern)) {
        std::string content = match[1].str();
        std::string num;
        std::istringstream iss(content);
        int i = 0;
        while (std::getline(iss, num, ',')) {
            arr[i] = stoi(num);
            i++;
        }
    }
    return arr;
}

void print_nums(const std::array<int, 10>& nums, int size) {
    for (int i = 0; i < size; i++) {
        std::cout << nums[i] << ", ";
    }
    std::cout << std::endl;
}

int brute_force(std::array<int, 10> &target_state, std::vector<std::vector<int>> &buttons, const int state_size) {
    int press_count = 0;
    std::sort(begin(buttons), end(buttons), [](auto bs1, auto bs2) {return bs1.size() > bs2.size();});
    // set empty state for start
    std::array<int, 10> init_state = {};

    // press biggest button until some number is at half of solution
    while (true) {
        
        auto button = buttons[0];
        bool stop = false;
        for (int &button_index : button) {
            if (init_state[button_index] >= target_state[button_index] / 2) {
                stop = true;
            }
        }
        if (stop) {
            break;
        }
        for (int &button_index : button) {
            init_state[button_index]++;
        }
        press_count++;
    }
    print_nums(init_state, state_size);
    
    std::vector<std::array<int, 10>> jolt_states;
    jolt_states.push_back(init_state);

    std::vector<std::array<int, 10>> new_states;
    std::array<int, 10> new_state;

    while (true)
    {
        press_count++;
        bool success;
        for (std::array<int, 10> &joltages : jolt_states) {
            // try all button presses, return if it works, else add to new states
            for (std::vector<int> button : buttons) {
            new_state = joltages;
            success = true;
            for (int &button_index : button) {
                new_state[button_index]++;
                if (new_state[button_index] > target_state[button_index]) {
                    success = false;
                }
            }

            // Check if we found the solution by comparing only the used elements
            bool is_solution = true;
            for (int i = 0; i < state_size; i++) {
                if (new_state[i] != target_state[i]) {
                    is_solution = false;
                    break;
                }
            }
            if (is_solution) {
                    //std::cout<<"solved with state: ";
                    //print_nums(new_state, state_size);
                    //std::cout<<"With "<<press_count<<" button presses\n";
                    return press_count;
            }
            if (success) {
                // if vector does not contain new_state, add it
                bool exists = false;
                for (auto state : new_states) {
                    bool states_equal = true;
                    for (int i = 0; i < state_size; i++) {
                        if (state[i] != new_state[i]) {
                            states_equal = false;
                            break;
                        }
                    }
                    if (states_equal) {
                        exists = true;
                        break;
                    }
                }
                if (!exists) {
                    new_states.push_back(new_state);
                }
            }
            }
        }

        // if new_states is empty, no solution found
        if (new_states.size() == 0) {
            std::cout<<"no solution found\n";
            return 0;
        }

        // print number of new states
        std::cout<<"presses "<< press_count <<", new states: " << new_states.size() << "\n";

        // remove duplicates from new_states
        std::sort(new_states.begin(), new_states.end(), [](auto s1, auto s2) {
            for (int i = 0; i < 10; i++) {
                if (s1[i] != s2[i]) {
                    return s1[i] < s2[i];
                }
            }
            return false;
        });
        new_states.erase(std::unique(new_states.begin(), new_states.end(), [state_size](auto s1, auto s2) {
            for (int i = 0; i < state_size; i++) {
                if (s1[i] != s2[i]) {
                    return false;
                }
            }
            return true;
        }), new_states.end());

        jolt_states = new_states;
        new_states.clear();
    }
    return 0;
}

int main(int argc, char const *argv[])
{
    std::ifstream file("input.txt");
    std::string str;
    std::vector<std::string> problems;
    
    while (std::getline(file, str)) {
        problems.push_back(str);
    }

    std::vector<std::pair<std::array<int, 10>, std::vector<std::vector<int>>>> light_diagrams;
    for (auto str : problems) {
        auto joltage_data = getJoltages(str);
        std::vector<std::vector<int>> buttons = getButtons(str);
        light_diagrams.push_back(std::make_pair(joltage_data, buttons));
    }

    int total = 0;
    for (auto ld : light_diagrams) {
        int x = brute_force(ld.first, ld.second, ld.first.size());
        total = total + x;
        std::cout<<"presses " << x <<"\n";
    }

    std::cout<<"total " << total <<"\n";
}