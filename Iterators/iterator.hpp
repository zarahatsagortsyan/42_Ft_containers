#ifndef FT_ITERATOR_HPP
#define FT_ITERATOR_HPP

# include <cstddef>
# include <iterator>
# include "iterator.hpp"

namespace ft
{
    //Category tags
    struct input_iterator_tag { };
    struct output_iterator_tag { };
    struct forward_iterator_tag : public ft::input_iterator_tag { };
    struct bidirectional_iterator_tag : public ft::forward_iterator_tag { };
    struct random_access_iterator_tag : public ft::bidirectional_iterator_tag { };

    //Iterator
    template<class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
    struct Iterator
    {
        typedef Category    iterator_category;
        typedef T           value_type;
        typedef Distance    difference_type;
        typedef Pointer     pointer;
        typedef Reference   reference;
    };

    //iterator_traits
    template<class Iterator>
    struct iterator_traits
    {
        typedef typename Iterator::difference_type          difference_type;
        typedef typename Iterator::value_type               value_type;
        typedef typename Iterator::pointer                  pointer;
        typedef typename Iterator::reference                reference;
        typedef typename Iterator::iterator_category        iterator_category;
    };

    template< class T >
    struct iterator_traits<T*>
    {
        typedef ft::random_access_iterator_tag  iterator_category;
        typedef T                               value_type;
        typedef std::ptrdiff_t                  difference_type;
        typedef T*                              pointer;
        typedef T&                              reference;
    };

    template< class T >
    struct iterator_traits<const T*>
    {
        typedef ft::random_access_iterator_tag  iterator_category;
        typedef T                               value_type;
        typedef std::ptrdiff_t                  difference_type;
        typedef T*                              pointer;
        typedef T&                              reference;
    };

    // distance difference_type
    template<class InputIterator>
    typename ft::iterator_traits<InputIterator>::difference_type 
    do_distance(InputIterator first, InputIterator last, ft::input_iterator_tag)
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
    do_distance(_RandomAccessIterator first, _RandomAccessIterator last, ft::random_access_iterator_tag)
    {
        return (last - first);
    }
    
    template<class InputIterator>
    typename ft::iterator_traits<InputIterator>::difference_type
    distance(InputIterator first, InputIterator last)
    {
        return detail::do_distance(first, last,
                                typename std::iterator_traits<InputIterator>::iterator_category());
    }

    //advance
    template<typename InputIterator, typename Distance>
    void do_advance(InputIterator& it, Distance n,
                    ft::input_iterator_tag)
    {
        while (n > 0)
        {
            --n;
            ++it;
        }
    }
 
    template<typename InputIterator, typename Distance>
    void do_advance(InputIterator& it, Distance n,
                    ft::bidirectional_iterator_tag)
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
 
    template<typename It, typename Distance>
    void do_advance(It& it, Distance n,
                    ft::random_access_iterator_tag)
    {
        it += n;
    }

    template<typename InputIterator, typename Distance>
    void advance(InputIterator& it, Distance n)
    {
        ft::advance(it, ft::iterator_traits<InputIterator>::difference_type(n),
                       typename std::iterator_traits<IInputIteratort>::iterator_category());
    }       

}
#endif