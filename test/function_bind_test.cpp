


#include <functional>
#include <iostream>

int myprint(int a)
{
    std::cout << a << std::endl;
    return 0;
}

int myprint3(int a, int b)
{
    std::cout << a << " " << b << std::endl;
    return 0;
}

template <typename T>
int myprint2(T a){
    std::cout << a << std::endl;
    return 0;
}

int main(){
    std::function<int(int)> f = myprint;
    f(3);
    
    std::function<int(int)> flamda = [](int a) -> int {
        std::cout << "lamda" << a << std::endl;
        return 0;
    };

    flamda(4);

    
    std::function<int(float)> f2 = myprint2<float>;
    f2(3.14);

    auto f_bind = std::bind(myprint, std::placeholders::_1);
    f_bind(3);
    auto f_bind2 = std::bind(myprint3, std::placeholders::_1, 34);
    f_bind2(4);

    return 0;
}