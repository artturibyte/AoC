#include    <iostream>
#include    <fstream>
#include    <string>
#include    <vector>
#include    <sstream>
#include    <regex>
#include    <bitset>

const int BIT_LENGTH = 6;

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

std::vector<int> getJoltages(const std::string& str) {
    std::regex pattern(R"(\{([0-9,]+)\})");
    std::smatch match;
    std::vector<int> vec;
    
    if (std::regex_search(str, match, pattern)) {
        std::string content = match[1].str();
        std::string num;
        std::istringstream iss(content);
        while (std::getline(iss, num, ',')) {
            vec.push_back(stoi(num));
        }
    }
    return vec;
}

void print_nums(const std::vector<int>& nums) {
    for (auto n : nums) {
        std::cout << n << ", ";
    }
    std::cout << std::endl;
}

bool big_vec_small_numbers(std::vector<int> &v1, std::vector<int> &v2) {
    if (v1.size() != v2.size()) {
        return v1.size() > v2.size();
    }
    else {
        // return true if v1 has smaller numbers than v2
        int sum1 = 0;
        int sum2 = 0;
        for (auto n : v1) {
            sum1 += n;
        }
        for (auto n : v2) {
            sum2 += n;
        }
        return sum1 < sum2;
    }
}

int solve_voltage_presses(std::pair<std::vector<int>, std::vector<std::vector<int>>> &setup) {
    // sort buttons to biggest amount of joltage changes first
    auto buttons = setup.second;
    std::sort(begin(buttons), end(buttons), [](auto bs1, auto bs2) {return big_vec_small_numbers(bs1,  bs2);});

    int presses = 0;
    std::vector<int> outcome(setup.first.size(), 0);
    std::vector<int> lastround;

    // for (auto bs : buttons) {
    //     print_nums(bs);
    // }
    //std::cout << std::endl;
    bool success;
    while (true)
    {
        presses++;
        
        // check every button, from most sificant to least,
        // if button can be pressed, press and continue to next round.
        lastround = outcome;
        int remove_index = 99;
        int i = 0;
        for (auto button : buttons) {
            success = true;
            // joltage is at limit and button cannot be pressed
            for (int button_index : button) {
                if (outcome.at(button_index) == setup.first.at(button_index)) {
                    success = false;
                    remove_index = i;
                }
            }

            // update numbers
            if (success) {
                //std::cout << " button ";
                //print_nums(button);
                //std::cout <<" pressed\n";
                for (int button_index : button) {
                    outcome.at(button_index) = outcome.at(button_index) + 1;
                }
                break;
            } else {
                //std::cout<<"Tried: ";
                //print_nums(button);
            }
            i++;
        }
        if (remove_index != 99) {
            //std::cout<< "removed " << remove_index<< "\n";
            buttons.erase(buttons.begin());
        }

        print_nums(outcome);
        if (outcome == lastround) {
                std::cout << " loop got stuck...\n";
                return 0;
            }
        
        if (outcome == setup.first) {
            return presses;
        }
    }
    //print_nums(outcome);
    //std::cout << std::endl;
    return 0;
}

int brute_force(std::pair<std::vector<int>, std::vector<std::vector<int>>> &setup) {
    int press_count = 0;
    auto buttons = setup.second;
    std::sort(begin(buttons), end(buttons), [](auto bs1, auto bs2) {return big_vec_small_numbers(bs1,  bs2);});
    // set empty state for start
    std::vector<int> init_state(setup.first.size(), 0);

    // press biggest button until some number is at half of solution
    while (true) {
        
        auto button = buttons[0];
        bool stop = false;
        for (int &button_index : button) {
            if (init_state.at(button_index) >= setup.first.at(button_index) / 2) {
                stop = true;
            }
        }
        if (stop) {
            break;
        }
        for (int &button_index : button) {
            init_state.at(button_index)++;
        }
        press_count++;
    }
    print_nums(init_state);
    
    std::vector<std::vector<int>> jolt_states;
    jolt_states.push_back(init_state);

    std::vector<std::vector<int>> new_states;
    std::vector<int> new_state;

    while (true)
    {
        press_count++;
        bool success;
        for (std::vector<int> &joltages : jolt_states) {
            // try all button presses, return if it works, else add to new states
            for (std::vector<int> button : buttons) {
            new_state = joltages;
            success = true;
            for (int &button_index : button) {
                new_state.at(button_index)++;
                if (new_state.at(button_index) > setup.first.at(button_index)) {
                    success = false;
                }
            }

            if (new_state == setup.first) {
                    //std::cout<<"solved with state: ";
                    //print_bits(new_state);
                    //std::cout<<"With "<<press_count<<" button presses\n";
                    return press_count;
            }
            if (success) {
                // if vector does not contain new_state, add it
                bool exists = false;
                for (auto state : new_states) {
                    if (state == new_state) {
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
        //std::cout<<"loop\n";

        // if new_states is empty, no solution found
        if (new_states.size() == 0) {
            std::cout<<"no solution found\n";
            return 0;
        }

        std::cout<<"new states count: " << new_states.size() <<"\n";

        // remove duplicates from new_states with algorith library
        std::sort(new_states.begin(), new_states.end());
        new_states.erase(std::unique(new_states.begin(), new_states.end()), new_states.end());
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

    std::vector<std::pair<std::vector<int>, std::vector<std::vector<int>>>> light_diagrams;
    for (auto str : problems) {
        std::vector<int> lights = getJoltages(str);
        std::vector<std::vector<int>> buttons = getButtons(str);
        light_diagrams.push_back(make_pair(lights, buttons));
    }

    int total = 0;
    for (auto ld : light_diagrams) {
        int x = brute_force(ld);
        total = total + x;
        std::cout<<"presses " << x <<"\n";
    }

    std::cout<<"total " << total <<"\n";



}
