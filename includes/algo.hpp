#ifndef ALGO_HPP
#define ALGO_HPP

#include <iostream>
namespace ft
{

	template<class InputIt1>
	void swap(InputIt1& ob1, InputIt1& ob2)
	{
		InputIt1 tmp = ob1;
		ob1 = ob2;
		ob2 = ob1;
	}

	//https://en.cppreference.com/w/cpp/algorithm/equal
	//First version
	template<class InputIt1, class InputIt2>
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
	{
		for (; first1 != last1; ++first1, ++first2) {
			if (!(*first1 == *first2)) {
				return false;
			}
		}
		return true;
	}

	//Second version
	template<class InputIt1, class InputIt2, class BinaryPredicate>
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p)
	{
		for (; first1 != last1; ++first1, ++first2) {
			if (!p(*first1, *first2)) {
				return false;
			}
		}
		return true;
	}

	//lexicographical_compare
	//first version
	//Checks if the first range [first1, last1) is lexicographically less than the second range [first2, last2).
	// template<class InputIt1, class InputIt2>
	template<class InputIt1, class InputIt2>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
	{
		for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2)
		{
			if (*first1 < *first2)
				return true;
			if (*first2 < *first1)
				return false;
		}

		return (first1 == last1) && (first2 != last2);
	}

	//second version
	template<class InputIt1, class InputIt2, class Compare>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp)
	{
		for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2)
		{
			if (comp(*first1, *first2))
				return true;
			if (comp(*first2, *first1))
				return false;
		}

		return (first1 == last1) && (first2 != last2);
	}

	template<class InputIt, class OutputIt>
	OutputIt copy(InputIt first, InputIt last,
		OutputIt d_first)
	{
		for (; first != last; (void)++first, (void)++d_first) {
			*d_first = *first;
		}
		return d_first;
	}

	template<class ForwardIt, class T>
	void fill(ForwardIt first, ForwardIt last, const T& value)
	{
		for (; first != last; ++first)
			*first = value;
	}

	template<class OutputIt, class Size, class T>
	OutputIt fill_n(OutputIt first, Size count, const T& value)
	{
		for (Size i = 0; i < count; i++)
			*first++ = value;
		return first;
	}

	//max_element 1
	template<class ForwardIt>
	ForwardIt max_element(ForwardIt first, ForwardIt last)
	{
		if (first == last)
			return last;

		ForwardIt largest = first;
		++first;

		for (; first != last; ++first)
			if (*largest < *first)
				largest = first;

		return largest;
	}

	//max_element 2
	template<class ForwardIt, class Compare>
	ForwardIt max_element(ForwardIt first, ForwardIt last, Compare comp)
	{
		if (first == last)
			return last;

		ForwardIt largest = first;
		++first;

		for (; first != last; ++first)
			if (comp(*largest, *first))
				largest = first;

		return largest;
	}


	// First version 
	template<class T>
	const T& max(const T& a, const T& b)
	{
		return (a < b) ? b : a;
	}

	// Second version 
	template<class T, class Compare>
	const T& max(const T& a, const T& b, Compare comp)
	{
		return (comp(a, b)) ? b : a;
	}

	// Third version 
	// template<class T>
	// T max(std::initializer_list<T> ilist)
	// {
	// 	return *ft::max_element(ilist.begin(), ilist.end());
	// }

	// // Fourth version 
	// template<class T, class Compare>
	// T max(std::initializer_list<T> ilist, Compare comp)
	// {
	// 	return *ft::max_element(ilist.begin(), ilist.end(), comp);
	// }

	template< class BidirIt1, class BidirIt2 >
	BidirIt2 copy_backward(BidirIt1 first, BidirIt1 last, BidirIt2 d_last)
	{
		while (first != last) {
			*(--d_last) = *(--last);
		}
		return d_last;
	}
}



#endif