#include <iostream>
#include <functional>
#include <vector>

void function1() {
    std::cout << "Function 1 called" << std::endl;
}

void function2() {
    std::cout << "Function 2 called" << std::endl;
}

void function3() {
    std::cout << "Function 3 called" << std::endl;
}

int main() {
    std::vector<std::function<void()>> functionVector;
    
    functionVector.push_back(function1);
    functionVector.push_back(function2);
    functionVector.push_back(function3);
    
    for (const auto& func : functionVector) {
        func();
    }
    
    return 0;
}
