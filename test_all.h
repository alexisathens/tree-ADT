//
//  main.cpp
//  Project2
//
//  Created by Alexis Athens on 12/1/17.
//  Copyright © 2017 Alexis Athens. All rights reserved.
//

#include <iostream>
#include "bstleaf.h"
#include "bstroot.h"
#include "bstrand.h"
#include "avl.h"

using namespace std;
using namespace cop3530;

bool compare(int item1, int item2)
{
    return item1 < item2;
}

bool equals(int item1, int item2)
{
    return item1 == item2;
}

int main()
{
    Leaf<int, int, compare, equals> test1;
    
    test1.insert(6, 10);
    test1.insert(2, 5);
    test1.insert(1, 2);
    test1.insert(12, 8);
    test1.insert(3, 7);
    test1.insert(3, 10);
    test1.insert(15, 9);
    test1.print();
    
    int temp1 = test1.lookup(3);
    cout << temp1 << endl;
    
    //test1.remove(40);
    
    test1.remove(3);
    test1.print();
    
    
    cout << "========== Test 2 ============ " << endl;
    
    Root<int, int, compare, equals> test2;
    
    test2.insert(6, 10);
    test2.print();
    test2.insert(2, 5);
    test2.print();
    test2.insert(12, 8);
    test2.print();
    test2.insert(3, 7);
    test2.print();
    test2.insert(3, 10);
    test2.print();
    test2.insert(15, 9);
    test2.print();
    
    int temp2 = test2.lookup(3);
    cout << temp2 << endl;
    
    //test2.remove(40);
    
    test2.remove(3);
    test2.print();
    
    
    cout << "========== Test 3 ============ " << endl;
    
    Rand<int, int, compare, equals> test3;
    
    test3.insert(6, 10);
    test3.print();
    test3.insert(2, 5);
    test3.print();
    test3.insert(12, 8);
    test3.print();
    test3.insert(3, 7);
    test3.print();
    test3.insert(3, 10);
    test3.print();
    test3.insert(15, 9);
    test3.print();
    
    int temp3 = test3.lookup(3);
    cout << temp3 << endl;
    
    //test3.remove(40);
    
    test3.remove(3);
    test3.print();
    
    
    
    cout << "========== Test 4 ============ " << endl;
    
    AVL<int, int, compare, equals> test4;
    
    test4.insert(6, 10);
    test4.print();
    test4.insert(2, 5);
    test4.print();
    test4.insert(12, 8);
    test4.print();
    test4.insert(3, 7);
    test4.print();
    test4.insert(3, 10);
    test4.print();
    test4.insert(15, 9);
    test4.print();
    
    int temp4 = test4.lookup(3);
    cout << temp4 << endl;
    
    //test4.remove(40);
    
    test4.remove(3);
    test4.print();
    
    
    cout << "========== Test 5 ============ " << endl;
    
    AVL<int, int, compare, equals> test5;
    
    test5.insert(9, 10);
    test5.insert(5, 5);
    test5.insert(10, 8);
    test5.insert(0, 7);
    test5.insert(6, 10);
    test5.insert(11, 16);
    test5.insert(-2, 53);
    test5.insert(1, 93);
    test5.insert(2, 78);
    test5.print();
    
    int temp5 = test5.lookup(10);
    cout << temp5 << endl;
    
    //test5.remove(40);
    
    test5.remove(10);
    test5.print();
    
    
    
    
    
    return 0;
}
