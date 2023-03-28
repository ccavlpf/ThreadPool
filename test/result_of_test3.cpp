#include <string>
#include <iostream>
#include <vector>
#include <type_traits>
#include <map>
#include<algorithm>
using namespace std;

struct Person{
    string name;
    int age;
};

vector<Person> vecPerson = {
    {"zhang", 30},
    {"wang", 20},
    {"li", 20},
    {"zhao", 30}
};

template <typename Fn>
multimap<typename result_of<Fn(const Person & p)>::type, Person> GroupBy(vector<Person> vecPesron, const Fn& keySelect){//typename

    using keyType = typename result_of<Fn(const Person & p)>::type;
    multimap<keyType, Person> map;
    for_each(vecPerson.begin(), vecPerson.end(), [&](const Person & p){
        keyType key = keySelect(p);
        map.insert(make_pair(key, p));
    });


    // for (const auto & iter : vecPerson)
    // {
    //     keyType key = keySelect(iter);
    //     map.insert(make_pair(key, iter));
    // } 
    return map;

}

int main(){
    auto res = GroupBy(vecPerson, [](const Person & p){return p.age;});
    // for (const auto & iter:res)
    // {
    //     cout << iter.second.age << " " << iter.second.name << endl;
    // }
    
    //可以decltype(res)代替multimap<int, Person>

    for_each(res.begin(),res.end(),[](decltype(res)::value_type & p){
         cout << p.second.age << " " << p.second.name << endl;        
    });

    // for_each(res.begin(),res.end(),[](multimap<int, Person>::value_type & p){
    //      cout << p.second.age << " " << p.second.name << endl;        
    // });

    return 0;
}