//
// Created by Никита on 02.05.2020.
//

#include <vector>
#include <iostream>

int main() {
    auto a = std::vector<int>(2, 0);
    std::cout << a[9999] << "\n";
    a[9999] = 3;
    std::cout << a.at(9999) << "\n" << a.size() << '\n' << a.max_size();


}