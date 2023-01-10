#include "iterators/iterator.hpp"
#include "iterators/reverse_iterator.hpp"
#include "iterators/normal_iterator.hpp"
#include "Containers/vector.hpp"
#include <iostream>
#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};
#define COUNT (MAX_RAM / (int)sizeof(Buffer))
int main()
{
   ft::vector<std::string> vector_str;
	ft::vector<int> vector_int;
	ft::vector<Buffer> vector_buffer;


	for (int i = 0; i < COUNT; i++)
	{
		vector_buffer.push_back(Buffer());
	}

	for (int i = 0; i < COUNT; i++)
	{
		const int idx = rand() % COUNT;
		vector_buffer[idx].idx = 5;
	}
	ft::vector<Buffer>().swap(vector_buffer);

	try
	{
		for (int i = 0; i < COUNT; i++)
		{
			const int idx = rand() % COUNT;
			vector_buffer.at(idx);
			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
		}
	}
	catch(const std::exception& e)
	{
		//NORMAL ! :P
	}
    return (0);
}

