#include <future>

template <class T, class U>
auto add(T a, U b) -> decltype( a + b ){
    return a + b;
}

int add1(int a, int b){
    return a + b;
}

int main(){
    std::result_of<decltype((add<int, int>))(int, int)>::type a = add<int, int>(1,2);
    std::result_of<decltype((add1))(int, int)>::type b = add1(1,2);
    return 0;
}