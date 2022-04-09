#include <list>
#include <algorithm>
#include <string>
#include <fstream>

using namespace std;

template <typename T>
T getListItemByIndex(list<T> itemsList, int index){
    typename list<T>::iterator listIterator = itemsList.begin();
    advance(listIterator, index);
    return *listIterator;
}

template <typename T>
bool listContains(list<T> itemList, T item){
    bool found = (find(itemList.begin(), itemList.end(), item) != itemList.end());
    return found;
}
