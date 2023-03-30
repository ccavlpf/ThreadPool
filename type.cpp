#include <iostream>
#include <type_traits>

template <typename T, typename U>
auto add(T t, U u) -> decltype(t + u) {
    return t + u;
}

int main() {
    int a = 1, b = 2;
    std::result_of<decltype(&add<int, double>)(int, double)>::type c = add(a, b);
   // std::result_of<decltype(add<int, double>)&(int, double)>::type c = add(a, b);
    std::cout << c << std::endl;
    return 0;
}

