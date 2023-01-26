#include "iterators/iterator.hpp"
#include "iterators/reverse_iterator.hpp"
#include "iterators/random_access_iterator.hpp"
#include "containers/vector.hpp"
#include "containers/stack.hpp"
#include "containers/map.hpp"
#include <iostream>
#ifdef STDSTL
#define TESTED_NAMESPACE std
#else
#define TESTED_NAMESPACE ft
#endif
int main()
{
    ft::vector<int> g1;
 
    std::cout << "-------------------vector---------------------" << std::endl;
    for (int i = 1; i <= 5; i++)
        g1.push_back(i);
 
    std::cout << "Size : " << g1.size();
    std::cout << "\nCapacity : " << g1.capacity();
    std::cout << "\nMax_Size : " << g1.max_size();
 
    // resizes the vector size to 4
    g1.resize(4);
 
    // prints the vector size after resize()
    std::cout << "\nSize : " << g1.size();
 
    // checks if the vector is empty or not
    if (g1.empty() == false)
        std::cout << "\nempty(): Vector is not empty";
    else
        std::cout << "\nempty(): Vector is empty";
 
    // Shrinks the vector

    std::cout << "\nVector elements are: ";
    for (ft::random_access_iterator<int> it = g1.begin(); it != g1.end(); it++)
        std::cout << *it << " ";

    for (int i = 1; i <= 10; i++)
        g1.push_back(i * 10);
 
    std::cout << "\nReference operator [g] : g1[2] = " << g1[2];
 
    std::cout << "\nat : g1.at(4) = " << g1.at(4);
 
    std::cout << "\nfront() : g1.front() = " << g1.front();
 
    std::cout << "\nback() : g1.back() = " << g1.back();
 
    // pointer to the first element
    int* pos = g1.data();
 
    std::cout << "\nThe first element is " << *pos;
 
    // Assign vector
    ft::vector<int> v;
 
    // fill the vector with 10 five times
    v.assign(5, 10);
 
    std::cout << "The vector elements are: ";
    for (size_t i = 0; i < v.size(); i++)
        std::cout << v[i] << " ";
 
    // inserts 15 to the last position
    v.push_back(15);
    int n = v.size();
    std::cout << "\nThe last element is: " << v[n - 1];
 
    // removes last element
    v.pop_back();
 
    // prints the vector
    std::cout << "\nThe vector elements are: ";
    for (size_t i = 0; i < v.size(); i++)
        std::cout << v[i] << " ";
 
    // inserts 5 at the beginning
    v.insert(v.begin(), 5);
 
    std::cout << "\nThe first element is: " << v[0];
 
    // removes the first element
    v.erase(v.begin());
 
    std::cout << "\nThe first element is: " << v[0];
 
    // erases the vector
    v.clear();
    std::cout << "\nVector size after erase(): " << v.size();
 
    // two vector to perform swap
    ft::vector<int> v1, v2;
    v1.push_back(1);
    v1.push_back(2);
    v2.push_back(3);
    v2.push_back(4);
 
    std::cout << "\n\nVector 1: ";
    for (size_t i = 0; i < v1.size(); i++)
        std::cout << v1[i] << " ";
 
    std::cout << "\nVector 2: ";
    for (size_t i = 0; i < v2.size(); i++)
        std::cout << v2[i] << " ";
 
    // Swaps v1 and v2
    v1.swap(v2);
 
    std::cout << "\nAfter Swap \nVector 1: ";
    for (size_t i = 0; i < v1.size(); i++)
        std::cout << v1[i] << " ";
 
    std::cout << "\nVector 2: ";
    for (size_t i = 0; i < v2.size(); i++)
        std::cout << v2[i] << " ";



    std::cout << "\n------------------------------stack-------------------------------" << std::endl;
    ft::stack<int> stack;
    stack.push(21);// The values pushed in the stack should be of the same data which is written during declaration of stack
    stack.push(22);
    stack.push(24);
    stack.push(25);

    while (!stack.empty()) {
        std::cout << ' ' << stack.top();
        // pop() function to remove the top element from the stack
        stack.pop();
    }


    std::cout << "\n----------------------------map----------------------------------" << std::endl;
     // Create a map of strings to integers
    ft::map<std::string, int> map;
    
    // Insert some values into the map
    map["one"] = 1;
    map["two"] = 2;
    map["three"] = 3;
    
    // Get an iterator pointing to the first element in the map
    ft::map<std::string, int>::iterator it = map.begin();
    
    // Iterate through the map and print the elements
    while (it != map.end())
    {
        std::cout << "Key: " << it->first << ", Value: " << it->second << std::endl;
        ++it;
    }
    std::cout << "Size of map: " << map.size() << std::endl;


     // empty map container
    ft::map<int, int> gquiz1;
  
    // insert elements in random order
    gquiz1.insert(ft::pair<int, int>(1, 40));
    gquiz1.insert(ft::pair<int, int>(2, 30));
    gquiz1.insert(ft::pair<int, int>(3, 60));
    gquiz1.insert(ft::pair<int, int>(4, 20));
    gquiz1.insert(ft::pair<int, int>(5, 50));
    gquiz1.insert(ft::pair<int, int>(6, 50));
      
      gquiz1[7]=10;     // another way of inserting a value in a map
     
  
    // printing map gquiz1
    ft::map<int, int>::iterator itr;
    std::cout << "\nThe map gquiz1 is : \n";
    std::cout << "\tKEY\tELEMENT\n";
    for (itr = gquiz1.begin(); itr != gquiz1.end(); ++itr) {
        std::cout << '\t' << itr->first << '\t' << itr->second
             << '\n';
    }
    std::cout << std::endl;
  
    // assigning the elements from gquiz1 to gquiz2
    ft::map<int, int> gquiz2(gquiz1.begin(), gquiz1.end());
  
    // print all elements of the map gquiz2
    std::cout << "\nThe map gquiz2 after"
         << " assign from gquiz1 is : \n";
    std::cout << "\tKEY\tELEMENT\n";
    for (itr = gquiz2.begin(); itr != gquiz2.end(); ++itr) {
        std::cout << '\t' << itr->first << '\t' << itr->second
             << '\n';
    }
    std::cout << std::endl;
  
    // remove all elements up to
    // element with key=3 in gquiz2
    std::cout << "\ngquiz2 after removal of"
            " elements less than key=3 : \n";
    std::cout << "\tKEY\tELEMENT\n";
    gquiz2.erase(gquiz2.begin(), gquiz2.find(3));
    for (itr = gquiz2.begin(); itr != gquiz2.end(); ++itr) {
        std::cout << '\t' << itr->first << '\t' << itr->second
             << '\n';
    }
  
    // remove all elements with key = 4
    int num;
    num = gquiz2.erase(4);
    std::cout << "\ngquiz2.erase(4) : ";
    std::cout << num << " removed \n";
    std::cout << "\tKEY\tELEMENT\n";
    for (itr = gquiz2.begin(); itr != gquiz2.end(); ++itr) {
        std::cout << '\t' << itr->first << '\t' << itr->second
             << '\n';
    }
  
    std::cout << std::endl;
  
    // lower bound and upper bound for map gquiz1 key = 5
    std::cout << "gquiz1.lower_bound(5) : "
         << "\tKEY = ";
    std::cout << gquiz1.lower_bound(5)->first << '\t';
    std::cout << "\tELEMENT = " << gquiz1.lower_bound(5)->second
         << std::endl;
    std::cout << "gquiz1.upper_bound(5) : "
         << "\tKEY = ";
    std::cout << gquiz1.upper_bound(5)->first << '\t';
    std::cout << "\tELEMENT = " << gquiz1.upper_bound(5)->second
         << std::endl;
}



