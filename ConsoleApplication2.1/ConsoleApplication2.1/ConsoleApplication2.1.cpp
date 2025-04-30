#include "Array.h"

int main()
{
    // Тестирование конструкторов
    std::cout << "=== Testing constructors ===" << std::endl;
    Array<int> arr1;  // Default constructor
    std::cout << "arr1 (default): " << arr1 << std::endl;

    Array<int> arr2(5);  // Constructor with size
    std::cout << "arr2 (size 5): " << arr2 << std::endl;

    int TempArr3[] = { 1, 2, 3, 4, 5 };
    Array<int> arr3(TempArr3, 5);  // Constructor from array
    std::cout << "arr3 (from array): " << arr3 << std::endl;

    Array<int> arr4(arr3);  // Copy constructor
    std::cout << "arr4 (copy of arr3): " << arr4 << std::endl;

    int TempArr5[] = { 3, 1, 4, 2, 5 };  // Создаем массив вручную
    Array<int> arr5(TempArr5, 5);
    std::cout << "arr5 (with size): " << arr5 << std::endl;


    // Тестирование добавления элементов
    std::cout << "\n=== Testing push operations ===" << std::endl;
    arr1.push_back(10);
    arr1.push_front(5);
    std::cout << "arr1 after pushes: " << arr1 << std::endl;

    // Тестирование вставки
    std::cout << "\n=== Testing insert operations ===" << std::endl;
    arr1.insert(1, 15);
    std::cout << "arr1 after insert at 1: " << arr1 << std::endl;

    arr1.insert_after(15, 17);
    std::cout << "arr1 after insert after 15: " << arr1 << std::endl;

    // Тестирование удаления
    std::cout << "\n=== Testing remove operations ===" << std::endl;
    arr1.pop_back();
    arr1.pop_front();
    std::cout << "arr1 after pops: " << arr1 << std::endl;

    arr1.remove(15);
    std::cout << "arr1 after remove 15: " << arr1 << std::endl;

    // Тестирование поиска
    std::cout << "\n=== Testing find operations(find 3) ===" << std::endl;
    auto it = arr3.find(3);
    if (it != arr3.end()) {
        std::cout << "Found 3 in arr3 at position " << (it - arr3.begin()) << std::endl;
    }

    // Тестирование сортировки
    std::cout << "\n=== Testing sort ===" << std::endl;
    std::cout << "Before sort: " << arr5 << std::endl;
    arr5.sort();
    std::cout << "After sort: " << arr5 << std::endl;

    // Тестирование min/max
    std::cout << "\n=== Testing min/max ===" << std::endl;
    std::cout << "Min of arr5: " << arr5.min() << ", Max of arr5: " << arr5.max() << std::endl;

    // Тестирование операторов
    std::cout << "\n=== Testing operators ===" << std::endl;
    Array<int> arr6 = arr3 + arr5;
    std::cout << "arr6 (arr3 + arr5): " << arr6 << std::endl;

    arr3 += arr5;
    std::cout << "arr3 after += arr5: " << arr3 << std::endl;

    std::cout << "arr3 == arr4? " << std::endl;
    std::cout << "===Answer=== " << std::endl;
    if (arr3 == arr4)
    {
        std::cout << "arr3 == arr4" << std::endl;
    }
    else
    {
        std::cout << "arr3 != arr4" << std::endl;
    }
    // Тестирование перемещающих операций
    std::cout << "\n=== Testing move operations ===" << std::endl;
    Array<int> arr7 = std::move(arr6);
    std::cout << "arr7 (moved from arr6): " << arr7 << std::endl;
    std::cout << "arr6 after move: " << arr6 << std::endl;

    // Тестирование очистки
    std::cout << "\n=== Testing clear ===" << std::endl;
    arr7.clear();
    std::cout << "arr7 after clear: " << arr7 << std::endl;

    // Тестирование доступа по индексу
    std::cout << "\n=== Testing index access ===" << std::endl;
    std::cout << "arr5[2]: " << arr5[2] << std::endl;
    arr5[2] = 10;
    std::cout << "After arr5[2] = 10: " << arr5 << std::endl;

    // Тестирование итераторов
    std::cout << "\n=== Testing iterators ===" << std::endl;
    std::cout << "arr5 elements: ";
    for (auto& item : arr5) {
        std::cout << item << " ";
    }
    std::cout << std::endl;

    return 0;
}