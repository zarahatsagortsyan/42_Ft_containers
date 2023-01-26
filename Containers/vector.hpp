#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>
#include "../iterators/random_access_iterator.hpp"
#include "../iterators/reverse_iterator.hpp"
#include "../includes/type_traits.hpp"
#include "../includes/algo.hpp"

namespace ft
{
    template <class T, class Alloc = std::allocator<T> >
    class vector
    {    
        public:
            typedef T                                                           value_type;
            typedef Alloc                                                       allocator_type;
            typedef typename allocator_type::reference                          reference;
            typedef typename allocator_type::const_reference                    const_reference;
            typedef typename allocator_type::pointer                            pointer;
            typedef typename allocator_type::const_pointer                      const_pointer;

            typedef typename ft::random_access_iterator<value_type>             iterator;
            typedef typename ft::random_access_iterator<const value_type>       const_iterator;

            typedef typename ft::reverse_iterator<iterator>                     reverse_iterator;
            typedef typename ft::reverse_iterator<const_iterator>               const_reverse_iterator;

            typedef typename ft::iterator_traits<iterator>::difference_type     difference_type;
            typedef size_t                                                      size_type;

        private:
            pointer         _data;
            allocator_type  _alloc;
            size_type       _size;
            size_type       _capacity;

        public:
            explicit vector (const allocator_type& alloc = allocator_type()) : _alloc(alloc), _size(0),_capacity(0)
            {
                _data = _alloc.allocate(_capacity);
            }

            explicit vector (size_type n, const value_type& val = value_type(),
            const allocator_type& alloc = allocator_type()) : _alloc(alloc), _size(n), _capacity(n)
            {
                size_type i;

                _data = _alloc.allocate(_capacity);
                try
                {
                    for(i = 0; i < _size; i++)
                    {
                        _alloc.construct(_alloc.address(_data[i]), val);
                    }
                }
                catch(...)
                {
                    for (size_type j = 0; j < i; j++)
                    {
                        _alloc.destroy(_alloc.address(_data[j]));
                    }
                    _alloc.deallocate(_data, _capacity);
                    throw;
                }
            }

            template <class InputIterator>
            vector (typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last,
            const allocator_type& alloc = allocator_type()) : _alloc(alloc), _size(0),_capacity(0)
            {
                this->assign(first, last);
            }

            virtual ~vector()
		    {
			    for (size_type i = 0; i < _size; ++i) { _alloc.destroy(_alloc.address(_data[i])); }
			    _alloc.deallocate(_data, _capacity);
		    }
        
            vector (const vector& x) : _data(NULL),_alloc(x._alloc), _size(0), _capacity(x._capacity)
            {
               *this = x;
            }
        
            vector& operator= (const vector& x)
            {
                if (this != &x)
                {
                    if (_data)
                    {
                        this->clear();
                        _alloc.deallocate(_data, _capacity);
                    }
                    this->_alloc = x._alloc;
                    this->_size = 0;
                    this->_capacity = x._capacity;
                    _data = _alloc.allocate(_capacity);
                    this->assign(x.begin(), x.end());
                }
                return (*this);
            }
            // vector& operator= (const vector& rhs)
        	// {
			// 	if (this == &rhs)
			// 		return *this;
			// 	for (size_type i = 0; i < _size; i++)
			// 		_alloc.destroy(_data + i);
			// 	this->_size = rhs._size;
			// 	if (_capacity < _size)
			// 	{
			// 		if (_capacity != 0)
			// 			_alloc.deallocate(_data, _capacity);
			// 		_capacity = _size;
			// 		_data = _alloc.allocate(_capacity);
			// 	}
			// 	for (size_type i = 0; i < _size; i++)
			// 		_alloc.construct(_data + i, rhs[i]);
			// 	return (*this);
        	// }
            iterator begin()
            {
                return (iterator(_data));
            }
            const_iterator begin() const
            {
                return (const_iterator(_data));
            }
            iterator end()
            {
                return(iterator(_data + _size));
            }
            const_iterator end() const
            {
                return (const_iterator(_data + _size));
            }
            reverse_iterator rbegin()
            {
                return (reverse_iterator(_data + _size));
            }
            const_reverse_iterator rbegin() const
            {
                return (const_reverse_iterator(_data + _size));
            }
            reverse_iterator rend()
            {
                return (reverse_iterator(_data));
            }
            const_reverse_iterator rend() const
            {
                return (const_reverse_iterator(_data));
            }
            size_type size() const
            {
                return (_size);
            }
            size_type max_size() const
            {
                return (_alloc.max_size());
            }
            void resize (size_type n, value_type val = value_type())
            {
                size_type i;

                if (n < _size)
                {
                    for (size_type i = n; i < _size; i++)
                    {
                        _alloc.destroy(_alloc.address(_data[i]));
                    }
                    _size = n;
                }
                else if (n > _capacity)
                {
                    reallocate((_capacity * 2) > n ? _capacity * 2 : n);
                }
                if (n > _size)
                {
                    try
                    {
                        for (i = _size; i < n; i++)
                        {
                            _alloc.construct(_alloc.address(_data[i]), val);
                        }
                    }
                    catch(...)
                    {
                        for (size_type j = _size; j < i; j++)
                        {
                            _alloc.destroy(_alloc.address(_data[j]));
                        }
                        _alloc.deallocate(_data, _capacity);
                        throw;

                    }
                    _size = n;
                }
            }
            size_type capacity() const
            {
                return (_capacity);
            }
            bool empty() const
            {
                return (_size==0);
            }
            void reserve(size_type n)
            {
                if ( n > this->max_size())
                    throw std::length_error("greater then max_size");
                if (n > _capacity)
                {
                    reallocate(n);
                }
            }
            // void reserve (size_type n)
        	// {
			// 	if (n < _capacity)
			// 		return ;
			// 	pointer arr = _alloc.allocate(n);
			// 	try{
			// 		for (size_type i = 0; i < _size; i++)
			// 			_alloc.construct(arr + i, *(_data + i));
			// 	} catch (std::exception& e){
			// 		size_type i = 0;
			// 		while (arr + i != NULL && i < _size){
			// 			_alloc.destroy(arr + i);
			// 			i++;
			// 		}
			// 		_alloc.deallocate(arr, n);
			// 		throw;
			// 	}
			// 	for (size_type i = 0; i < _size; i++)
			// 		_alloc.destroy(_data + i);
			// 	if (_capacity)
			// 		_alloc.deallocate(_data, _capacity);
			// 	_capacity = n;
			// 	_data = arr;
        	// }

        public:
            reference operator[] (size_type n)
            {
                return (this->at(n));
            }
            const_reference operator[] (size_type n) const
            {
                return (this->at(n));
            }
            reference at (size_type n)
            {
                if (n >= _size)
                    throw std::out_of_range("out of range");
                return(_data[n]);
            }
            const_reference at(size_type n) const
            {
                if (n >= _size)
                    throw std::out_of_range("out of range");
                return(_data[n]);
            }
            reference front()
            {
                return (this->_data[0]);
            }
            const_reference front() const
            {
                return (this->_data[0]);
            }
            pointer data()
            {
                return (_data);
            }
            const_pointer data() const
            {
                return (_data);
            }
            reference back()
            {
                return (_data[_size - 1]);
            }
            const_reference back() const
            {
                return (_data[_size - 1]);
            }
            template <class InputIterator>
            void assign (typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first,\
            InputIterator last)
            {
                for (size_type i = 0; i < _size; i++)
                {
                   _alloc.destroy(_alloc.address(_data[i]));
                }
               if (std::distance(first, last) > static_cast<difference_type>(_capacity))
                {
                    pointer tmp = _alloc.allocate(std::distance(first, last));
                    if (_capacity != 0)
                        _alloc.deallocate(_data, _capacity);
                    _data = tmp;
                    _capacity = std::distance(first, last);
                }
                size_type i = 0;
                try
                {
                    for (; first != last; first++)
                    {
                        _alloc.construct(_alloc.address(_data[i]), *first);
                        i++;
                    }
                }
                catch(...)
                {
                     for (size_type j = 0; j < i; j++)
                    {
                        _alloc.destroy(_alloc.address(_data[j]));
                    }
                    _alloc.deallocate(_data, _capacity);
                    throw;
                }
                _size = i;
            }
            void assign (size_type n, const value_type& val)
            {
                size_type i;

                for (size_type i = 0; i < _size; i++)
                {
                    _alloc.destroy(_alloc.address(_data[i]));
                }
                if ( n > _capacity)
                {
                     pointer tmp = _alloc.allocate(n);
                    _alloc.deallocate(_data, _capacity);
                    _data = tmp;
                    _capacity = n;
                }
                try
                {
                    for (i = 0; i < n; i++)
                    {
                        _alloc.construct(_alloc.address(_data[i]), val);
                    }
                }
                catch(...)
                {
                    for (size_type j = 0; j < i; j++)
                    {
                        _alloc.destroy(_alloc.address(_data[j]));
                    }
                    _alloc.deallocate(_data, _capacity);
                    throw;
                }
                _size = n;
            }
            void push_back (const value_type& val)
            {
                if (_size + 1 > _capacity)
                    _capacity == 0 ? reallocate(1) : reallocate(_capacity * 2);
                
                try
                {
                    _alloc.construct(_alloc.address(_data[_size++]), val);
                }
                catch(...)
                {
                    _alloc.deallocate(_data, _capacity);
                    throw;
                }
            }
            void pop_back()
            {
                erase(end() - 1);
            }
            iterator insert (iterator position, const value_type& val)
            {
                size_type start = std::distance(this->begin(), position);
                this->insert(position, 1, val);
                return (this->begin() + start);
            }

            void insert (iterator position, size_type n, const value_type& val)
            {
                pointer tmp;
                size_type i;
                size_type tmpcapacity;

                if (position < this->begin() || position > this->end())
                    throw std::out_of_range("out of range");
                difference_type range = n;
                if (range + this->size() > this->max_size())
                    throw std::out_of_range("out of range");
                tmpcapacity = _capacity;
                if (_size + range > _capacity)
                    tmpcapacity = (_capacity * 2) > _size + range ?_capacity * 2 : _size + range;
                tmp = _alloc.allocate(tmpcapacity);
                try
                {
                    for (i = 0; i < static_cast<size_type>(std::distance(this->begin(), position)); i++)
                        _alloc.construct(_alloc.address(tmp[i]), _data[i]);
                    
                    while (n--)
                    {
                        _alloc.construct(_alloc.address(tmp[i]), val);
                        i++;
                    }
                    for (size_type j = std::distance(this->begin(), position); j < _size; j++)
                    {
                        _alloc.construct(_alloc.address(tmp[i]), _data[j]);
                        i++;
                    }
                }
                catch(...)
                {
                    for (size_type j = 0; j < i; j++)
                    {
                        _alloc.destroy(_alloc.address(tmp[j]));
                    }
                    _alloc.deallocate(tmp, tmpcapacity);
                    if (!this->empty())
                        this->~vector();
                    throw;
                }
                this->~vector();
                _data = tmp;
                _capacity = tmpcapacity;
                _size = i;
            }
            template <class InputIterator>
            void insert (iterator position, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first,\
            InputIterator last)
            {
                pointer tmp;
                size_type i;
                size_type tmpcapacity;

                if (position < this->begin() || position > this->end())
                    throw std::out_of_range("out of range");
                difference_type range = std::distance(first, last);
                if (range + this->size() > this->max_size())
                    throw std::out_of_range("out of range");
                tmpcapacity = _capacity;
                if (_size + range > _capacity)
                    tmpcapacity = (_capacity * 2) > _size + range ?_capacity * 2 : _size + range;
                tmp = _alloc.allocate(tmpcapacity);
                try
                {
                    for (i = 0; i < static_cast<size_type>(std::distance(this->begin(), position)); i++)
                        _alloc.construct(_alloc.address(tmp[i]), _data[i]);
                    
                    for (; first != last; first++)
                    {
                        _alloc.construct(_alloc.address(tmp[i]), *first);
                        i++;
                    }
                    for (size_type j = std::distance(this->begin(), position); j < _size; j++)
                    {
                        _alloc.construct(_alloc.address(tmp[i]), _data[j]);
                        i++;
                    }
                }
                catch(...)
                {
                    for (size_type j = 0; j < i; j++)
                    {
                        _alloc.destroy(_alloc.address(tmp[j]));
                    }
                    _alloc.deallocate(tmp, tmpcapacity);
                    if (!this->empty())
                        this->~vector();
                    throw;
                }
                this->~vector();
                _data = tmp;
                _capacity = tmpcapacity;
                _size = i;
            }
            iterator erase (iterator position)
            {
                size_type i;

                iterator temp(position);
                size_type index = std::distance(this->begin(), position);
                _alloc.destroy(&(*position));
                try
                {
                    for (i = index; i < _size - 1; i++)
                        _alloc.construct(_alloc.address(_data[i]), _data[i + 1]);
                }
                catch(...)
                {
                    for (size_type j = index; j < i; j++)
                        _alloc.destroy(_alloc.address(_data[i]));
                    _alloc.deallocate(_data, _capacity);

                    throw;
                }
                _size--;
                return (temp);
            }

            iterator erase (iterator first, iterator last)
        	{
				difference_type left = std::distance(begin(), first);
				difference_type right = std::distance(last, end());
				bool is_last = (last == end());
				for (; first != last; first++)
					_alloc.destroy(&(*first));
				size_type i = left;
				while (last < end())
				{
					if (this->_data + left)
						_alloc.destroy(_data + i);
					_alloc.construct(_data + i, *last);
					i++;
					last++;
				}
				for ( size_type i = left + right; i < _size; i++)
					_alloc.destroy(_data + i);
				_size = left + right;
				return is_last ? end() : iterator(_data + left);          
       		}
            // iterator erase(iterator first, iterator last)
            // {
            //     size_type j;
            //     size_type dist;

            //     j = 0;
            //     dist = std::distance(this->begin(), first);
            //     difference_type diff = std::distance(this->begin(), last);
            //     difference_type d = std::distance(first, last);
            //     iterator temp(first);
            //     while (first != last)
            //     {
            //         _alloc.destroy(_alloc.address((*first)));
            //         first++;
            //     }
            //     try
            //     {
            //         for (size_type i = 0; i < _size; i++)
            //         {
            //             if (i < dist || i >= static_cast<size_type>(diff))
            //                 _data[j++] = _data[i];
            //         }
            //     }
            //     catch(...)
            //     {
            //         for (size_type i = 0; i < j; i++)
            //         {
            //             _alloc.destroy(_alloc.address(_data[i]));
            //         }
            //         _alloc.deallocate(_data, _capacity);
            //         throw;
            //     }
            //     _size -= d;
            //     return (temp);
            // }
            void clear()
            {
                for (size_type i = 0; i < this->size(); i++)
                {
                    _alloc.destroy(_alloc.address(_data[i]));
                }
                _size = 0;
            }
            void swap (vector& x)
            {
                std::swap(_data, x._data);
                std::swap(_size, x._size);
                std::swap(_capacity, x._capacity);
                std::swap(_alloc, x._alloc);
            }

            // void    swap (vector& x)
            // {
            //     pointer         tmp_data;
            //     size_type       tmp_size;
            //     allocator_type  tmp_alloc;

            //     tmp_data = _data;
            //     _data = x._data;
            //     x._data = tmp_data;

            //     tmp_size = _size;
            //     _size = x._size;
            //     x._size = tmp_size;

            //     tmp_size = _capacity;
            //     _capacity = x._capacity;
            //     x._capacity = tmp_size;

            //     tmp_alloc = _alloc;
            //     _alloc = x._alloc;
            //     x._alloc = tmp_alloc;
            // }
            allocator_type get_allocator() const
            {
                return (_alloc);
            }

            
            void reallocate(size_type new_capacity)
            {
                size_type i;

                pointer tmp = _alloc.allocate(new_capacity);
                try
                {
                    for (i = 0; i < _size; i++)
                    {
                        _alloc.construct(_alloc.address(tmp[i]), _data[i]);
                    }
                }
                catch(...)
                {
                    for (size_type j = 0; j < i; j++)
                    {
                        _alloc.destroy(_alloc.address(tmp[j]));
                    }
                    _alloc.deallocate(tmp, new_capacity);
                    throw;
                }
                this->~vector();
                _capacity = new_capacity;
                _data = tmp;
            }

    };
    template <class T, class Alloc>
    bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        if (lhs.size() != rhs.size())
            return (false);
        return (ft::equal(lhs.begin(), lhs.end(),rhs.begin()));
    }
    template <class T, class Alloc>
    bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return (!(lhs == rhs));
    }
    template <class T, class Alloc>
    bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }
    template <class T, class Alloc>
    bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return (!(rhs < lhs));
    }
    template <class T, class Alloc>
    bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return (rhs < lhs);
    }	
    template <class T, class Alloc>
    bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return (!(lhs < rhs));
    }
    template <class T, class Alloc>
        void swap (vector<T,Alloc>& lhs, vector<T,Alloc>& rhs)
    {
        ft::vector<T, Alloc> tmp;
        tmp.swap(lhs);
        lhs.swap(rhs);
        rhs.swap(tmp);
    }
};
    namespace std{
        template< class T, class Alloc >
        void swap(ft::vector<T,Alloc>& lhs, ft::vector<T,Alloc>& rhs ) {
            lhs.swap(rhs);
        }
    }

#endif