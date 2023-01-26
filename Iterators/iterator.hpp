#ifndef FT_ITERATOR_HPP
#define FT_ITERATOR_HPP

# include <cstddef>
# include <iterator>
# include "../includes/memory.hpp"

namespace ft
{
    //Category tags
    struct input_iterator_tag { };
    struct output_iterator_tag { };
    struct forward_iterator_tag : public ft::input_iterator_tag { };
    struct bidirectional_iterator_tag : public ft::forward_iterator_tag { };
    struct random_access_iterator_tag : public ft::bidirectional_iterator_tag { };

    template <class Category, class T, class Distance = ptrdiff_t,
            class Pointer = T*, class Reference = T&>
    struct iterator {
        typedef T         value_type;
        typedef Distance  difference_type;
        typedef Pointer   pointer;
        typedef Reference reference;
        typedef Category  iterator_category;
    };
template <class Iterator>
	struct iterator_traits
	{
		typedef Iterator iterator_type;
		typedef typename Iterator::iterator_category	iterator_category;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
	};
	template <class T>
	struct iterator_traits<T*>
	{
		typedef ptrdiff_t						difference_type;
		typedef T								value_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef std::random_access_iterator_tag		iterator_category;
	};

	template <class T>
	struct iterator_traits<const T*>
	{
		typedef ptrdiff_t						difference_type;
		typedef T								value_type;
		typedef const T*						pointer;
		typedef const T&						reference;
		typedef std::random_access_iterator_tag		iterator_category;
	};

    // distance difference_type
    template<class InputIterator>
    typename ft::iterator_traits<InputIterator>::difference_type 
    distance(InputIterator first, InputIterator last, std::input_iterator_tag)
    {
        typename std::iterator_traits<InputIterator>::difference_type result = 0;
        while (first != last) {
            ++first;
            ++result;
        }
        return result;
    }

    template<class _RandomAccessIterator>
    typename ft::iterator_traits<_RandomAccessIterator>::difference_type 
    distance(_RandomAccessIterator first, _RandomAccessIterator last, std::random_access_iterator_tag)
    {
        return (last - first);
    }
    
    template<class InputIterator>
    typename ft::iterator_traits<InputIterator>::difference_type
    distance(InputIterator first, InputIterator last)
    {
        return ft::distance(first, last,
                                typename std::iterator_traits<InputIterator>::iterator_category());
    }

    //advance
  template<class It>
    void advance(It& it, typename std::iterator_traits<It>::difference_type n,
                    std::input_iterator_tag)
    {
        while (n > 0)
        {
            --n;
            ++it;
        }
    }
 
    template<class It>
    void advance(It& it, typename std::iterator_traits<It>::difference_type n,
                    std::bidirectional_iterator_tag)
    {
        while (n > 0)
        {
            --n;
            ++it;
        }
        while (n < 0)
        {
            ++n;
            --it;
        }
    }
 
    template<class It>
    void advance(It& it, typename std::iterator_traits<It>::difference_type n,
                    std::random_access_iterator_tag)
    {
        it += n;
    }
    
    template<class It, class Distance>
    void advance(It& it, Distance n)
    {
        ft::advance(it, typename std::iterator_traits<It>::difference_type(n),
                        typename std::iterator_traits<It>::iterator_category());
    } 
} 

 
#endif