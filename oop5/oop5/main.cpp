#include "class5.h"

int main() {
    List<int> list;
    List<std::string> list1;
    list1.push_back("aboba");
    list1.print();
    list1.push_front("bebra");
    list1.print();
    std::cout << "First: " << list1[0] << "\n";
    std::cout << "Size: " << list1.size() << "\n";
    list.push_back(10);
    list.push_back(20);
    list.push_front(5);
    list.print();  

    list.pop_front();
    list.pop_back();
    list.print();  

    list.insert(list.begin(), 7);
    list.print();  

    auto it = list.find(10);
    list.erase(it);
    list.print(); 

    std::cout << "First: " << list[0] << "\n";
    std::cout << "Size: " << list.size() << "\n";

    return 0;
}