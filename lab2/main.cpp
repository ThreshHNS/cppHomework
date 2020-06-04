#include "safe_c_array.tpp"

int main() {
    safe_c_array<int> custom_array(20);
    custom_array[11] = 11;
    std::cout << custom_array[11];
    return 0;
}