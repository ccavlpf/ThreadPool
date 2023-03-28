#include <type_traits>

//int add(int a, int b) { return a + b; }
float add(int a, int b) { return 3.14; }

int main() {
  using result_type = std::result_of<decltype((add))(int, int)>::type;
  using result_type1 = std::result_of<decltype(add)&(int, int)>::type;
  using result_type2 = std::result_of<decltype(&add)(int, int)>::type;
  //using result_type = std::result_of<decltype(add &)(int, int)>::type; 错误
  static_assert(std::is_same<result_type, float>::value, "add should return int");
  static_assert(std::is_same<result_type1, float>::value, "add should return int");
  static_assert(std::is_same<result_type2, float>::value, "add should return int");
  return 0;
}
