#include "iterators/iterator.hpp"
#include "iterators/reverse_iterator.hpp"
#include "iterators/normal_iterator.hpp"
#include "Containers/vector.hpp"
#include <iostream>
#ifdef STDSTL
#define TESTED_NAMESPACE std
#else
#define TESTED_NAMESPACE ft
#endif
int main()
{
    clock_t start;

    start = std::clock();
    std::cout << "**************** vector *****************" << std::endl;
    TESTED_NAMESPACE::vector<int> vec(10, 1);
     TESTED_NAMESPACE::vector<int> v(vec);
    TESTED_NAMESPACE::vector<int> vect;
    for (int i = 0; i < 10; i++)
    {
        vec.push_back(i);
    }
    TESTED_NAMESPACE::vector<int> vv(vect.begin(), vect.end());
    vv.erase(vv.begin(), vv.begin() + 2);
    std::cout << "size: " << vv.size() << std::endl;
    std::cout << "capacity: " << vv.capacity() << std::endl;
    std::cout << vv[0] << std::endl;
    // for (size_t i = 0; i < vv.size(); i++)
    // {
    //     std::cout << "[" << i << "]" << vv[i] << std::endl;
    // }
    // std::cout << "time for vector is: " << std::clock() - start << std::endl;
    return 0;
}

//struct Buffer
//{
//	int idx;
//	char buff[BUFFER_SIZE];
//};
//#define COUNT (MAX_RAM / (int)sizeof(Buffer))
//int main()
//{
//   ft::vector<std::string> vector_str;
//	ft::vector<int> vector_int;
//	ft::vector<Buffer> vector_buffer;
//
//
//	for (int i = 0; i < 5; i++)
//	{
//		vector_str.push_back("rftrt");
//	}
//
//	//for (int i = 0; i < COUNT; i++)
//	//{
//	//	const int idx = rand() % COUNT;
//	//	vector_buffer[idx].idx = 5;
//	//}
//	//ft::vector<Buffer>().swap(vector_buffer);
//
//	//try
//	//{
//	//	for (int i = 0; i < COUNT; i++)
//	//	{
//	//		const int idx = rand() % COUNT;
//	//		vector_buffer.at(idx);
//	//		std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
//	//	}
//	//}
//	//catch(const std::exception& e)
//	//{
//	//	//NORMAL ! :P
//	//}

