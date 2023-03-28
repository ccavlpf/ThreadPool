#include <type_traits>

//int add(int a, int b) { return a + b; }
float add(int a, int b) { return 3.14; }


// 在这个例子中，decltype((add)) 是获取一个表达式的类型，这个表达式是用来调用函数add的。
//这个表达式的类型就是float(int, int)，它是一个函数指针类型。所以在这个例子中，result_of
// 是用来获取一个函数类型的返回值类型，而不是获取一个函数对象的返回值类型。

// template<typename Fn>
// multimap<typename result_of<Fn(Person)>::type, Person> GroupBy(const vector<Person>& vt,const Fn& keySelect)
// {
// 	typedef typename result_of<Fn(Person)>::type key_type;
// 	multimap<key_type,Person> map;
//         for_each(vt.begin(),vt.end(),
//                     [&](const Person& p){
//                     map.insert(make_pair(keySelect(p),p));
//                     });
//     return map;
// }

// 而在你提供的代码中（），Fn 是作为GroupBy函数的一个模板参数，它是一个函数对象类型，
// 而不是一个函数指针类型。因此，我们可以在使用result_of的时候直接使用Fn，而不需要使用decltype。

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
