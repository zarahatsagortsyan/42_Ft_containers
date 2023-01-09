#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

# include <memory>
# include <cstddef>
# include <stdexcept>
# include <string>
#include "iterator.hpp"
#include "normal_iterator.hpp"
#include "reverse_iterator.hpp"

namespace ft
{ 
    template<typename T,typename Allocator = std::allocator<T>>
    class vector
    {
        public:
            typedef T	                value_type;
            typedef Allocator	        allocator_type;
            typedef value_type	        &reference;
            typedef const value_type	&const_reference;
            typedef value_type			*pointer;
            typedef const value_type	*const_pointer;
            typedef ptrdiff_t			difference_type;
            typedef size_t				size_type;

			/* Member types (iterators) */
			typedef ft::normal_iterator<pointer, vector>		iterator;
        	typedef ft::normal_iterator<const_pointer, vector>  const_iterator;
			typedef ft::reverse_iterator<const_iterator>	    const_reverse_iterator;
			typedef ft::reverse_iterator<iterator>			    reverse_iterator;
        
        private:
			size_type					_size;
			size_type					_capacity;
			pointer						_data;
			allocator_type				_alloc;

        //constructors and destructors =
        public:
            explicit vector (const allocator_type& alloc = allocator_type()): _alloc(alloc), _data(NULL), _capacity(0), _size(0) { }
            
            explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
            : _alloc(alloc), _data(NULL), _capacity(0), _size(0)
			{
				this->_data = _allocate(_check_len(static_cast<size_type>(n), "vector::vector"));
				this->_capacity = n;
				fill_construct(n, val);
			}
            
            template <class InputIterator> 
            vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()):
                                             _alloc(alloc), _data(NULL), _capacity(0), _size(0)
			{
				constructor_dispatch(first, last, typename ft::is_integral<InputIterator>::type());
			}

            vector(const vector &x) : _alloc(x._alloc), _data(NULL), _capacity(0), _size(0)
			{
				range_construct(x.begin(), x.end(), std::random_access_iterator_tag());
			}

            //https://gcc.gnu.org/onlinedocs/gcc-4.6.3/libstdc++/api/a01117_source.html line 159
            vector	&operator=(const vector &x)
			{
				if (&x != this)
				{
					const size_type	x_size = x.size();
					if (x_size > this->_capacity)
					{
						pointer	new_data = allocate_and_copy(x_size, x.begin(), x.end());
						ft::_destroy(this->_data, this->_data + this->_size, this->_alloc);
						_deallocate(this->_data, this->_capacity);
						this->_data = new_data;
						this->_capacity = x_size;
					}
					else if (this->_size >= x_size)
						ft::_destroy(ft::copy(x.begin(), x.end(), begin()), end(), this->_alloc);
					else
					{
						ft::copy(x._data, x._data + this->_size, this->_data);
						ft::_uninitialized_copy_a(x._data + this->_size, x._data + x_size, this->_data + this->_size, this->_alloc);
					}
					this->_size = x_size;
				}
				return (*this);
			}

            ~vector()
			{
				clear();
				_deallocate(this->_data, this->_capacity);
			}
        
        //iterators
        public:
            iterator begin()
            {
                return (iterator(this->_data));
            }

            const_iterator begin() const
            {
                return (const_iterator(this->_data));
            }

            iterator end()
            {
                return (iterator(this->_data + this->_size));
            }
            
            const_iterator end() const
            {
                return (const_iterator(this->_data + this->_size));
            }

            reverse_iterator rbegin()
            {
                return (reverse_iterator(end()));
            }

            const_reverse_iterator rbegin() const
            {
                return (const_reverse_iterator(end()));
            }
            
            reverse_iterator rend()
            {
                return (reverse_iterator(begin()));
            }

            const_reverse_iterator rend() const
            {
                return (const_reverse_iterator(begin()));
            }
            // const_iterator cbegin() const noexcept;
            // const_iterator cend() const noexcept;
            // const_reverse_iterator crbegin() const noexcept;
            // const_reverse_iterator crend() const noexcept;

        //Capacity
        public:
            size_type size() const
            {
                return (this->_size);
            }

            size_type max_size() const
            {
                return (this->_alloc.max_size());
            }

            void resize (size_type n, value_type val = value_type())
            {
                f (n > this->_size)
					insert(end(), n - this->_size, val);
				else if (n < this->_size)
					erase(end() - (this->_size - n), end());
            }

            size_type capacity() const
            {
                return (this->_capacity);
            }

            bool empty() const
            {
                return (!this->_size)
            }

            void reserve (size_type n)
            {
                if (n > max_size())
					throw std::length_error("vector::reserve");
				if (this->_capacity < n)
				{
					pointer	new_data = allocate_and_copy(n, this->_data, this->_data + this->_size);
					ft::_destroy(this->_data, this->_data + this->_size, this->_alloc);
					_deallocate(this->_data, this->_capacity);
					this->_data = new_data;
					this->_capacity = n;
				}
            }
            // void shrink_to_fit();

        //Element access
        public:
            reference operator[] (size_type n)
            {
                return (this->_data[n]);
            }
            
            const_reference operator[] (size_type n) const
            {
                return (this->_data[n]);
            }

            reference at (size_type n)
            {
                if (n >= this->_size)
					throw std::out_of_range("vector::at: n (which is " + SSTR(n) + ") >= this->size() (which is " + SSTR(this->_size) + ")");
				return (this->_data[n]);
            }

            const_reference at (size_type n) const
            {
                if (n >= this->_size)
					throw std::out_of_range("vector::at: n (which is " + SSTR(n) + ") >= this->size() (which is " + SSTR(this->_size) + ")");
				return (this->_data[n]);
            }

            reference front()
            {
                return (this->_data[0]);
            }

            const_reference front() const
            {
                return (this->_data[0]);
            }

            reference back()
            {
                return (this->_data[this->_size - 1]);
            }

            const_reference back() const
            {
                return (this->_data[this->_size - 1]);
            }
            // value_type* data() noexcept;                                               
            // const value_type* data() const noexcept;

        //Modifiers
        public:
            void	assign(size_type n, const value_type &val)
			{
				_fill_assign(n, val);
			}

			template <class InputIterator>
			void	assign(InputIterator first, InputIterator last)
			{
				_assign_dispatch(first, last, typename ft::is_integral<InputIterator>::type());
			}

            void push_back (const value_type& val)
            {
                insert(end(), val);
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
                    {
                        _alloc.construct(_alloc.address(tmp[i]), _data[i]);
                    }
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
            void insert (iterator position, InputIterator first, InputIterator last)
            {
                insert_dispatch(position, first, last, typename ft::is_integral<InputIterator>::type());
            }

            iterator erase (iterator position)
            {
                // if it's not the last element, then do shifting to left
				if (position + 1 != end())
					ft::copy(position + 1, end(), position);
				this->_size--;
				// destroying the extra element at the end
				this->_alloc.destroy(this->_data + this->_size);
				return (position);
            }

            iterator erase (iterator first, iterator last)
            {
                if (first != last)
				{
					// if last is the end then no need to shift
					if (last != end())
						ft::copy(last, end(), first);
					// destroying the rest
					ft::_destroy(first.base() + (end() - last), this->_data + this->_size, this->_alloc);
					this->_size -= last - first;
				}
				return (first);
            }

            void swap (vector& x)
            {
                ft::swap(this->_data, x._data);
				ft::swap(this->_capacity, x._capacity);
				ft::swap(this->_size, x._size);
            }

            void clear()
            {
                erase(begin(), end());
            }

            // template <class... Args>iterator emplace (const_iterator position, Args&&... args);
            // template <class... Args>  void emplace_back (Args&&... args);

        //Allocator:
        public:
            allocator_type get_allocator() const
            {
                return (this->_alloc);
            }

        private:
            void	_deallocate(pointer p, size_type n)
			{
				if (p)
					this->_alloc.deallocate(p, n);
			}

            //https://gcc.gnu.org/onlinedocs/gcc-4.6.3/libstdc++/api/a01069_source.html#l01049 line 1049
            template <typename ForwardIterator>
			pointer	allocate_and_copy(size_type n, ForwardIterator first, ForwardIterator last)
			{
				pointer	result = _allocate(n);
				try
				{
					ft::__uninitialized_copy_a(first, last, result, this->_alloc);
					return (result);
				}
				catch (...)
				{
					_deallocate(result, n);
					throw ;
				}
			}

            //https://gcc.gnu.org/onlinedocs/gcc-4.6.3/libstdc++/api/a01069_source.html#l01049 line 149
            pointer	_allocate(size_type n)
			{
				return (n ? this->_alloc.allocate(n) : pointer());
			}

            //https://gcc.gnu.org/onlinedocs/gcc-4.6.3/libstdc++/api/a01069_source.html#l01049 line 1238
            size_type	_check_len(size_type n, const char *s)
			{
                //to avoid out of memory expand it twice or fit
				if (max_size() - this->_size < n)
					throw std::length_error(s);
				const size_type	new_size = this->_size + ft::max(this->_size, n);
				return ((new_size < this->_size || new_size > max_size()) ? max_size() : new_size);
			}

            private:
			template <typename InputIterator>
			void	_assign_dispatch(InputIterator first, InputIterator last, false_type)
			{
				// template argument was an iterator, proceed
				_range_assign(first, last, typename iterator_traits<InputIterator>::iterator_category());
			}

			template <typename Integral>
			void	_assign_dispatch(Integral n, Integral val, true_type)
			{
				// template argument was an integer, do fill_assign() instead
				_fill_assign(n, val);
			}

            //https://gcc.gnu.org/onlinedocs/gcc-4.6.3/libstdc++/api/a01117_source.html#l00109 line 201
			void	_fill_assign(size_type n, const value_type &val)
			{
				// reallocation required
				if (n > this->_capacity)
				{
					vector	temp(n, val, this->_alloc);
					temp.swap(*this);
				}
				else if (n > this->_size)
				{
					ft::fill(begin(), end(), val);
					ft::_uninitialized_fill_n_a(this->_data + this->_size, n - this->_size, val, this->_alloc);
				}
				else
					ft::_destroy(ft::fill_n(this->_data, n, val), this->_data + this->_size, this->_alloc);
				this->_size = n;
			}

            //_M_assign_aux
            //https://gcc.gnu.org/onlinedocs/gcc-4.6.3/libstdc++/api/a01117_source.html#l00109 line 220
			template <typename InputIterator>
			void	_range_assign(InputIterator first, InputIterator last, std::input_iterator_tag)
			{
				pointer		curr = this->_data;
				// copy starting from the beginning
				for (; first != last and curr != this->_data + this->_size; ++curr, ++first)
					*curr = *first;
				// if range is shorter than the vector
				if (first == last)
				{
					// destroy the end
					ft::_destroy(curr, this->_data + this->_size);
					// update the size
					this->_size = curr - this->_data;
				}
				else
					insert(end(), first, last);
			}

            // _M_assign_aux(_ForwardIterator __first, _ForwardIterator __last, std::forward_iterator_tag)
            //https://gcc.gnu.org/onlinedocs/gcc-4.6.3/libstdc++/api/a01117_source.html#l00109 line 237
			template <typename ForwardIterator>
			void	_range_assign(ForwardIterator first, ForwardIterator last, std::forward_iterator_tag)
			{
				const size_type	len = ft::distance(first, last);
				if (len > this->_capacity)
				{
					pointer	temp = allocate_and_copy(len, first, last);
					ft::_destroy(this->_data, this->_data + this->_size, this->_alloc);
					_deallocate(this->_data, this->_capacity);
					this->_data = temp;
					this->_capacity = len;
				}
				else if (this->_size >= len)
					ft::_destroy(ft::copy(first, last, this->_data), this->_data + this->_size, this->_alloc);
				else
				{
					ForwardIterator	mid = first;
					ft::advance(mid, this->_size);
					ft::copy(first, mid, this->_data);												// copy upper part
					ft::_uninitialized_copy_a(mid, last, this->_data + this->_size, this->_alloc);	// construct lower part
				}
				this->_size = len;
			}

            template <class InputIterator>
			void	_constructor_dispatch(InputIterator first, InputIterator last, ft::false_type)
			{
				_range_construct(first, last, typename ft::iterator_traits<InputIterator>::iterator_category());
			}

			template <typename Integral>
			void	_constructor_dispatch(Integral n, Integral val, ft::true_type)
			{
				this->_data = _allocate(_check_len(static_cast<size_type>(n), "vector::constructor_dispatch"));
				this->_capacity = n;
				_fill_construct(static_cast<size_type>(n), val);
			}

			void	_fill_construct(size_type n, const value_type &val)
			{
				ft::_uninitialized_fill_n_a(this->_data, n, val, this->_alloc);
				this->_size = n;
			}

			template <typename InputIterator>
			void	_range_construct(InputIterator first, InputIterator last, std::input_iterator_tag)
			{
				try
				{
					for (; first != last; ++first)
						push_back(*first);
				}
				catch (...)
				{
					clear();
					throw ;
				}
			}

			template <typename ForwardIterator>
			void	_range_construct(ForwardIterator first, ForwardIterator last, std::forward_iterator_tag)
			{
				const size_type	n = ft::distance(first, last);
				this->_data = _allocate(check_length(n, "vector::range_construct"));
				this->_capacity = n;
				ft::_uninitialized_copy_a(first, last, this->_data, this->_alloc);
                s->_size = n;
			}

            void _reallocate(size_type new_capacity)
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
                this->_capacity = new_capacity;
                this->_data = tmp;
            }

    };

    template <typename T, typename Allocator>
	void	swap(vector<T, Allocator> &lhs, vector<T, Allocator> &rhs)
    {
        lhs.swap(rhs);
    }

	template <typename T, typename Allocator>
	bool	operator==(const vector<T, Allocator> &lhs, const vector<T, Allocator> &rhs)
    {
        return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
    }

	template <typename T, typename Allocator>
	bool	operator!=(const vector<T, Allocator> &lhs, const vector<T, Allocator> &rhs)
    {
        return !(lhs == rhs); 
    }

	template <typename T, typename Allocator>
	bool	operator<(const vector<T, Allocator> &lhs, const vector<T, Allocator> &rhs)
    {
        return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }

	template <typename T, typename Allocator>
	bool	operator<=(const vector<T, Allocator> &lhs, const vector<T, Allocator> &rhs)
    {
        return !(lhs < rhs); 
    }

	template <typename T, typename Allocator>
	bool	operator>(const vector<T, Allocator> &lhs, const vector<T, Allocator> &rhs)
    {
        return lhs < rhs;
    }

	template <typename T, typename Allocator>
	bool	operator>=(const vector<T, Allocator> &lhs, const vector<T, Allocator> &rhs)
    {
        return !(lhs < rhs); 
    }
}

#endif
