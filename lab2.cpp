/*Name: Wanposop Surayut******************* Student ID:168000180*/
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

template <typename aTypeSort>
void sortArray(aTypeSort* arr, int size, char order = 'a') {
    if (order == 'd') {
        for (int a = 0; a < size - 1; a++) {
            for (int j = 0; j < size - a - 1; j++) {
                if (arr[j] < arr[j + 1]) {
                    aTypeSort temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    } else {
        for (int a = 0; a < size - 1; a++) {
            for (int j = 0; j < size - a - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    aTypeSort temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    }
}

template <typename bTypeDis>
void displayArray(bTypeDis* arr, int size) {
    for (int a = 0; a < size; a++) {
        std::cout << arr[a] << " ";
    }
    std::cout << std::endl;
}

int main() {
    int size;
    std::cout << "Enter the size of the integer array: ";
    std::cin >> size;

    if (size <= 0) {
        std::cout << "Invalid array size. Exiting program." << std::endl;
        return 0;
    }

    int* intArray = new int[size];

    srand(static_cast<unsigned>(time(0)));
    for (int a = 0; a < size; a++) {
        intArray[a] = rand() % 100 + 1;
    }

    char order;
    std::cout << "Enter the order of sorting for the integer array ('a' for ascending and 'd' for descending): ";
    std::cin >> order;

    if (order != 'a' && order != 'd') {
        std::cout << "Invalid sorting order. Exiting program." << std::endl;
        delete[] intArray;
        return 0;
    }

    std::cout << "Integer array before sorting: ";
    displayArray(intArray, size);

    sortArray(intArray, size, order);

    std::cout << "Integer array after sorting: ";
    displayArray(intArray, size);

    delete[] intArray;


    std::cout << "Enter the size of the character array: ";
    std::cin >> size;

    if (size <= 0) {
        std::cout << "Invalid array size. Exiting program." << std::endl;
        return 0;
    }

    char* charArray = new char[size];

    for (int a = 0; a < size; a++) {
        charArray[a] = rand() % 26 + 65;
    }

    std::cout << "Enter the order of sorting for the character array ('a' for ascending and 'd' for descending): ";
    std::cin >> order;

    if (order != 'a' && order != 'd') {
        std::cout << "Invalid sorting order. Exiting program." << std::endl;
        delete[] charArray;
        return 0;
    }

    std::cout << "Character array before sorting: ";
    displayArray(charArray, size);

    sortArray(charArray, size, order);

    std::cout << "Character array after sorting: ";
    displayArray(charArray, size);

    delete[] charArray;

    return 0;
}
