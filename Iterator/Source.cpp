#include "List.h"
#include <iostream>
#include <time.h>
#include <windows.h>

using namespace std;

unsigned counting(ListIterator* li) {
    unsigned cnt = 0;
    if (li->operator()())
        do {
            cnt++;
            cerr << li->operator*() << " ";
        } while (li->operator++());
        cerr << endl;
        return cnt;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand((unsigned)time(0));
    unsigned capacity, count;
    cout << "Введите объём стека: ";
    cin >> capacity;
    List list(capacity);
    cout << "Введите количество элементов для заполнения стека: ";
    cin >> count;
    for (auto i = 0; i < count; i++) {
        int x = rand() % 5;
        if (list.append(x))
            cout << x << " ";
    }
    cout << endl;

    try 
    {
        ListIterator* litS3 = list.createIterator(Iterators::STEP, 3);
        cout << counting((ListIteratorStep*)litS3) << endl;
        
    }
    catch (exception e) 
    {
        cout << e.what() << endl;
    }

    try
    {
        ListIterator* litV4 = list.createIterator(Iterators::VALUE, 4);
        cout << counting((ListIteratorValue*)litV4) << endl;
    }
    catch (exception e)
    {
        cout << e.what() << endl;
    }

    return 0;
}

