#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <regex>
#include <array>
#include <algorithm>
#include <unordered_set>
#include <functional>

// Custom hash function for array<int, 10>
struct ArrayHash {
    std::size_t operator()(const std::array<int, 10>& arr) const {
        std::size_t seed = 0;
        for (int i = 0; i < 10; ++i) {
            seed ^= std::hash<int>{}(arr[i]) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};

// Custom equality function for array<int, 10> considering only first state_size elements
struct ArrayEqual {
    int state_size;
    ArrayEqual(int size) : state_size(size) {}
    
    bool operator()(const std::array<int, 10>& lhs, const std::array<int, 10>& rhs) const {
        return std::equal(lhs.begin(), lhs.begin() + state_size, rhs.begin());
    }
};

std::vector<std::vector<int>> getButtons(const std::string& str) {
    std::vector<std::vector<int>> bits;
    std::regex pattern(R"(\(([0-9,]+)\))");
    std::smatch match;
    
    std::string::const_iterator searchStart(str.cbegin());
    while (std::regex_search(searchStart, str.cend(), match, pattern)) {
        std::string content = match[1].str();
        std::vector<int> buttons;
        
        // Parse comma-separated numbers
        std::string token;
        std::istringstream iss(content);
        while (std::getline(iss, token, ',')) {
            buttons.push_back(std::stoi(token));
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
        while (std::getline(iss, num, ',') && i < 10) {
            arr[i] = std::stoi(num);
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

int brute_force_optimized(std::array<int, 10> &target_state, std::vector<std::vector<int>> &buttons, const int state_size) {
    int press_count = 0;
    std::sort(buttons.begin(), buttons.end(), [](const auto& bs1, const auto& bs2) {
        return bs1.size() > bs2.size();
    });
    
    // Set empty state for start
    std::array<int, 10> init_state = {};

    // Press biggest button until some number is at half of solution
    if (!buttons.empty()) {
        auto& button = buttons[0];
        while (true) {
            bool stop = false;
            for (int button_index : button) {
                if (init_state[button_index] >= target_state[button_index] / 2) {
                    stop = true;
                    break;
                }
            }
            if (stop) break;
            
            for (int button_index : button) {
                init_state[button_index]++;
            }
            press_count++;
        }
    }
    
    print_nums(init_state, state_size);
    
    // Use unordered_set for O(1) duplicate detection
    std::unordered_set<std::array<int, 10>, ArrayHash> current_states;
    std::unordered_set<std::array<int, 10>, ArrayHash> next_states;
    current_states.insert(init_state);
    
    while (!current_states.empty()) {
        press_count++;
        next_states.clear();
        
        for (const auto& joltages : current_states) {
            for (const auto& button : buttons) {
                std::array<int, 10> new_state = joltages;
                bool valid = true;
                
                // Apply button press and check validity
                for (int button_index : button) {
                    new_state[button_index]++;
                    if (new_state[button_index] > target_state[button_index]) {
                        valid = false;
                        break;
                    }
                }
                
                if (!valid) continue;
                
                // Check if we found the solution
                if (std::equal(new_state.begin(), new_state.begin() + state_size, target_state.begin())) {
                    return press_count;
                }
                
                // Add to next states if not duplicate
                next_states.insert(new_state);
            }
        }
        
        if (next_states.empty()) {
            std::cout << "no solution found\n";
            return 0;
        }
        
        std::cout << "presses " << press_count << ", new states: " << next_states.size() << "\n";
        std::swap(current_states, next_states);
    }
    
    return 0;
}

int main(int argc, char const *argv[]) {
    std::ifstream file("input.txt");
    std::string str;
    std::vector<std::string> problems;
    
    while (std::getline(file, str)) {
        problems.push_back(str);
    }

    std::vector<std::pair<std::array<int, 10>, std::vector<std::vector<int>>>> light_diagrams;
    
    for (const auto& str : problems) {
        auto joltage_data = getJoltages(str);
        std::vector<std::vector<int>> buttons = getButtons(str);
        light_diagrams.emplace_back(joltage_data, std::move(buttons));
    }

    int total = 0;
    for (auto& ld : light_diagrams) {
        int x = brute_force_optimized(ld.first, ld.second, ld.first.size());
        total += x;
        std::cout << "presses " << x << "\n";
    }

    std::cout << "total " << total << "\n";
    return 0;
}