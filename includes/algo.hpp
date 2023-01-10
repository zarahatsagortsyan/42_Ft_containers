#ifndef ALGO_HPP
#define ALGO_HPP

namespace ft
{
    template<class InputIt1, class InputIt2>
    bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
                                InputIt2 first2, InputIt2 last2)
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
    template<class InputIt1>
    void swap(InputIt1 &ob1, InputIt1 &ob2)
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
    bool equal(InputIt1 first1, InputIt1 last1,InputIt2 first2, BinaryPredicate p)
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
    // bool lexicographical_compare(InputIt1 first1, InputIt1 last1,InputIt2 first2, InputIt2 last2)
    // {
    //     for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2)
    //     {
    //         if (*first1 < *first2)
    //             return true;
    //         if (*first2 < *first1)
    //             return false;
    //     }
    
    //     return (first1 == last1) && (first2 != last2);
    // }

    //second version
    // template<class InputIt1, class InputIt2, class Compare>
    // bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp)
    // {
    //     for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2)
    //     {
    //         if (comp(*first1, *first2))
    //             return true;
    //         if (comp(*first2, *first1))
    //             return false;
    //     }
    
    //     return (first1 == last1) && (first2 != last2);
    // }

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
}



#endif