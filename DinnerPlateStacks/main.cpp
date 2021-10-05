#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>

#include "DinnerPlates.h"
// https://leetcode.com/problems/dinner-plate-stacks/
int main(int, char**) {
    std::string action;
    std::string skip;
    std::string line;

    std::getline(std::cin, skip, '"');
    std::getline(std::cin, line, ']');
    std::stringstream ss(line);

    std::vector<std::string> actions;
    while(std::getline(ss, action, '"'))
    {
        if(action == ",") continue;
        // std::cout << "action: " << action << '\n';
        actions.emplace_back(move(action));
    }

    std::getline(std::cin, skip, '[');
    std::getline(std::cin, skip, '[');
    std::getline(std::cin, line);
    std::stringstream ss2(line);

    std::vector<int> values;
    while(std::getline(ss2, action, ']'))
    {
        if(action == "]") continue;

        std::stringstream ss3(action);
        int n;
        ss3 >> n;
        values.push_back(n);
        // std::cout << "action: " << n << '\n';
        std::getline(ss2, action, ',');
        std::getline(ss2, action, '[');
    }

    DinnerPlates dinnerPlates(values[0]);
    std::cout << "[";
    for(int i = 1;i < actions.size();i ++){
        if(i > 1){
            std::cout << ",";
        }

        if (actions[i] == "push"){
            dinnerPlates.push(values[i]);
            std::cout << "null";
        }
        else if (actions[i] == "pop"){
            std::cout << dinnerPlates.pop();
        }
        else if (actions[i] == "popAtStack"){
            std::cout << dinnerPlates.popAtStack(values[i]);
        }
    }
    std::cout << "]";
    
    return 0;
}