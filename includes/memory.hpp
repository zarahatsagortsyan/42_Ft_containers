#ifndef MEMORY_HPP
#define MEMORY_HPP

#include "../iterators/iterator.hpp"
#include <memory>

namespace ft
{
    //_addressof
    template <typename T>
	T	*_addressof(T &ref)
	{
		return (reinterpret_cast<T*>(&const_cast<char&>(reinterpret_cast<const volatile char&>(ref))));
	}

    // _Destroy
    //https://gcc.gnu.org/onlinedocs/gcc-4.6.3/libstdc++/api/a01048_source.html line 139
    
    template<typename _ForwardIterator, typename _Allocator>
    void _destroy(_ForwardIterator __first, _ForwardIterator __last,
         _Allocator& __alloc)
    {
        for (; __first != __last; ++__first)
            __alloc.destroy(ft::_addressof(*__first));
    }

    //https://gcc.gnu.org/onlinedocs/libstdc++/libstdc++-html-USERS-4.3/a02038.html line 241

    template<typename _InputIterator, typename _ForwardIterator, typename _Allocator>
    _ForwardIterator _uninitialized_copy_a(_InputIterator __first, _InputIterator __last,
                                            _ForwardIterator __result, _Allocator& __alloc)
    {
        _ForwardIterator __cur = __result;
        try
        {
            for (; __first != __last; ++__first, ++__cur)
                __alloc.construct(ft::_addressof(*__cur), *__first);
            return __cur;
        }
        catch(...)
        {
            ft::_destroy(__result, __cur, __alloc);
            throw;
        }
    }

    //https://gcc.gnu.org/onlinedocs/libstdc++/libstdc++-html-USERS-4.3/a02038.html line 277
    // constructs objects of the given full range with the given alloc
    template<typename _ForwardIterator, typename _Tp, typename _Allocator>
    void _uninitialized_fill_a(_ForwardIterator __first, _ForwardIterator __last,
                               const _Tp& __x, _Allocator& __alloc)
    {
        _ForwardIterator __cur = __first;
        try
        {
            for (; __cur != __last; ++__cur)
            __alloc.construct(ft::_addressof(*__cur), __x);
        }
        catch(...)
        {
            ft::_destroy(__first, __cur, __alloc);
            throw;
        }
    }

    //_uninitialized_fill_n_a
    //https://gcc.gnu.org/onlinedocs/libstdc++/libstdc++-html-USERS-4.3/a02038.html line 321    
    // constructs objects of the given n range with the given alloc
    template<typename _ForwardIterator, typename _Size, typename _Tp, typename _Allocator>
    void _uninitialized_fill_n_a(_ForwardIterator __first, _Size __n, 
                  const _Tp& __x, _Allocator& __alloc)
    {
        _ForwardIterator __cur = __first;
        try
        {
            for (; __n > 0; --__n, ++__cur)
                __alloc.construct(ft::_addressof(*__cur), __x);
        }
        catch(...)
        {
            ft::_destroy(__first, __cur, __alloc);
            throw;
        }
    }
}


#endif