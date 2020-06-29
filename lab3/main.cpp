#include <iostream>
#include "int_list_t.h"

int main() {
    int_list_t l1;
    for (int i = 0; i < 10; ++i) {
        l1.push_back(i);
    }
//  Tests:
    std::cout << l1 << std::endl;
    int_list_t l2 = l1.splice(1, 5);
    std::cout << l2 << std::endl;
    std::cout << l1 << std::endl;
    std::cout << l2.back() << std::endl;
    l2.clear();
    std::cout << l2.empty() << std::endl;
    int_list_t l3(l1), l4(3, 4);
    std::cout << l3 << std::endl;
    std::cout << l3.merge(l4) << std::endl;
    l3.reverse();
    std::cout << l3 << std::endl;
    l3.insert(2, 4);
    std::cout << l3 << std::endl;
    l1.swap(l3);
    std::cout << l1 << std::endl;
    std::cout << l1.size() << std::endl;
    l1.pop_front();
    l1.pop_back();
    std::cout << l1 << std::endl;
    std::cout <<l1[2] << std::endl;
    int_list_t l5 = l1;
    std::cout << l5 << std::endl;

    int_list_t l7;
    std::cout << "Enter valid list with integers: ";
    std::cin >> l7;

    std::cout << l7 << " - int_list_t";

    return 0;
}