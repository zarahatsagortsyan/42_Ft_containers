#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

#include <memory>
#include <cstddef>
#include <stdexcept>
#include <string>
#include "../includes/type_traits.hpp"
#include "../includes/algo.hpp"
#include "../iterators/iterator.hpp"
#include "../iterators/normal_iterator.hpp"
#include "../iterators/reverse_iterator.hpp"
#include "../includes/utility.hpp"

namespace ft
{ 
    template<typename T,typename Allocator = std::allocator<T> >
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
            explicit vector (const allocator_type& alloc = allocator_type()): _alloc(alloc), _data(0), _capacity(0), _size(0) { }
            
            explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
            : _alloc(alloc), _data(NULL), _capacity(0), _size(0)
			{
				 _data = _alloc.allocate(n);
            	for(size_type i = -1; i < n; ++i)
               	 	_alloc.construct(_data + i, val);
				// this->_data = _allocate(_check_len(static_cast<size_type>(n), "vector::vector"));
				// this->_capacity = n;
				// fill_construct(n, val);
			}
            
            template <class InputIterator> 
            vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()):
                                             _alloc(alloc), _data(NULL), _capacity(0), _size(0)
			{
				_constructor_dispatch(first, last, typename ft::is_integral<InputIterator>::type());
			}

            vector(const vector &x) : _alloc(x._alloc), _data(NULL), _capacity(0), _size(0)
			{

				(*this) = x;
				//_range_construct(x.begin(), x.end(), std::random_access_iterator_tag());
			}

            //https://gcc.gnu.org/onlinedocs/gcc-4.6.3/libstdc++/api/a01117_source.html line 159
   //         vector	&operator=(const vector &x)
			//{
			//	if (&x != this)
			//	{
			//		const size_type	x_size = x.size();
			//		if (x_size > this->_capacity)
			//		{
			//			pointer	new_data = allocate_and_copy(x_size, x.begin(), x.end());
			//			ft::_destroy(this->_data, this->_data + this->_size, this->_alloc);
			//			_deallocate(this->_data, this->_capacity);
			//			this->_data = new_data;
			//			this->_capacity = x_size;
			//		}
			//		else if (this->_size >= x_size)
			//			ft::_destroy(ft::copy(x.begin(), x.end(), begin()), end(), this->_alloc);
			//		else
			//		{
			//			ft::copy(x._data, x._data + this->_size, this->_data);
			//			ft::_uninitialized_copy_a(x._data + this->_size, x._data + x_size, this->_data + this->_size, this->_alloc);
			//		}
			//		this->_size = x_size;
			//	}
			//	return (*this);
			//}

			vector& operator= (const vector& rhs)
        	{
				if (this == &rhs)
					return *this;
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_data + i);
				this->_size = rhs._size;
				if (_capacity < _size)
				{
					if (_capacity != 0)
						_alloc.deallocate(_data, _capacity);
					_capacity = _size;
					_data = _alloc.allocate(_capacity);
				}
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(_data + i, rhs[i]);
				return (*this);
        	}
			// vector& operator= (const vector& x)
			// {

			// 	std::cout << "asdasd" << std::endl;

			// 	if (this != &x)
			// 	{
			// 		if (_data)
			// 		{
			// 			this->clear();
			// 			_alloc.deallocate(_data, _capacity);
			// 		}
			// 		this->_alloc = x._alloc;
			// 		this->_size = 0;
			// 		this->_capacity = x._capacity;
			// 		_data = _alloc.allocate(_capacity);
			// 		this->assign(x.begin(), x.end());
			// 	}
			// 	return (*this);
			// }

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

            /*void resize (size_type n, value_type val = value_type())
            {
                if (n > this->_size)
					insert(end(), n - this->_size, val);
				else if (n < this->_size)
					erase(end() - (this->_size - n), end());
            }*/

			void resize(size_type n, value_type val = value_type())
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
					_reallocate((_capacity * 2) > n ? _capacity * 2 : n);
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
					catch (...)
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
                return (this->_capacity);
            }

            bool empty() const
            {
                return (!this->_size);
            }

            // void reserve (size_type n)
            // {
            //     if (n > max_size())
			// 		throw std::length_error("vector::reserve");
				
			// 	if (this->_capacity < n)
			// 	{
			// 		pointer	new_data = allocate_and_copy(n, this->_data, this->_data + this->_size);
			// 		ft::_destroy(this->_data, this->_data + this->_size, this->_alloc);
			// 		_deallocate(this->_data, this->_capacity);
			// 		this->_data = new_data;
			// 		this->_capacity = n;
			// 	}
            // }

			void reserve (size_type n)
        	{
				std::cout << "asdasd" << std::endl;
				if (n < _capacity)
					return ;
				pointer arr = _alloc.allocate(n);
				try{
					for (size_type i = 0; i < _size; i++)
						_alloc.construct(arr + i, *(_data + i));
				} catch (std::exception& e){
					size_type i = 0;
					while (arr + i != NULL && i < _size){
						_alloc.destroy(arr + i);
						i++;
					}
					_alloc.deallocate(arr, n);
					throw;
				}
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_data + i);
				if (_capacity)
					_alloc.deallocate(_data, _capacity);
				_capacity = n;
				_data = arr;
        	}
            // void shrink_to_fit();

        //Element access
        public:
            reference operator[] (size_type n)
            {
                return (this->at(n));
            }
            
            const_reference operator[] (size_type n) const
            {
                return (this->at(n));
            }

			reference at(size_type n)
			{
				if (n > _capacity)
					throw std::out_of_range("out of range");
				return (*(_data + n));
				// return(_data[n]);
			}
			const_reference at(size_type n) const
			{
				if (n > _capacity)
					throw std::out_of_range("out of range");
				// return(_data[n]);
				return (*(_data + n));

			}
 			reference front() { return (*_data); }
        	reference back() { return (*(_data + _size - 1)); }
        	const_reference front() const { return (*_data);}
        	const_reference back() const { return (*(_data + _size - 1));}

            // reference front()
            // {
            //     return (this->_data[0]);
            // }

            // const_reference front() const
            // {
            //     return (this->_data[0]);
            // }

            // reference back()
            // {
            //     return (this->_data[this->_size - 1]);
            // }

            // const_reference back() const
            // {
            //     return (this->_data[this->_size - 1]);
            //}
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

     iterator	insert(iterator position, const value_type &val)
			{
				// offset, to return a valid iterator
				const size_type	n = position - begin();
				// building at past-end with enough capacity treated separately
				if (this->_size != this->_capacity and position == end())
					this->_alloc.construct(this->_data + this->_size, val);
				else
				{
					// no reallocation needed, thus 1 element will get displaced past-end
					if (this->_size != this->_capacity)
					{
						// displace last element
						this->_alloc.construct(this->_data + this->_size, *(this->_data + this->_size - 1));
						// in case if an element being inserted is inside the container, after `position`,
						// because the reference will be invalidated after elements are shifted to right
						value_type	val_copy = val;
						// shift elements after position to the right
						ft::copy_backward(position.base(), this->_data + this->_size - 1, this->_data + this->_size);
						// assign to position from copy
						*position = val_copy;
					}
					// reallocation needed
					else
					{
						const size_type	new_capacity = _check_len(1, "vector::insert");
						const size_type	elems_before = position - begin();
						pointer			new_data = _allocate(new_capacity);
						pointer			new_data_end = new_data;
						try
						{
							// elements itself
							this->_alloc.construct(new_data + elems_before, val);
							// so that catch block will destroy only the failed object
							new_data_end = NULL;
							// import everything before position 
							new_data_end = ft::_uninitialized_copy_a(this->_data, position.base(), new_data, this->_alloc);
							new_data_end++;
							// import everything after position 
							new_data_end = ft::_uninitialized_copy_a(position.base(), this->_data + this->_size, new_data_end, this->_alloc);
						}
						catch (...)
						{
							if (!new_data_end)
								this->_alloc.destroy(new_data + elems_before);
							else
								ft::_destroy(new_data, new_data_end, this->_alloc);
							_deallocate(new_data, new_capacity);
							throw ;
						}
						ft::_destroy(this->_data, this->_data + this->_size, this->_alloc);
						_deallocate(this->_data, this->_capacity);
						this->_data = new_data;
						this->_capacity = new_capacity;
					}
				}
				this->_size++;
				return (iterator(this->_data + n));
			}

			void	insert(iterator position, size_type n, const value_type &val)
			{
				fill_insert(position, n, val);
			}

			template <class InputIterator>
			void	insert(iterator position, InputIterator first, InputIterator last)
			{
				// disambiguate between a possible fill call
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

            // iterator erase (iterator first, iterator last)
            // {
            //     if (first != last)
			// 	{
			// 		// if last is the end then no need to shift
			// 		if (last != end())
			// 			ft::copy(last, end(), first);
			// 		// destroying the rest
			// 		ft::_destroy(first.base() + (end() - last), this->_data + this->_size, this->_alloc);
			// 		this->_size -= last - first;
			// 	}
			// 	return (first);
            // }

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

				// pointer	result = _allocate(n);
				pointer	result = _alloc.allocate(n);
				std::cout << "bareeev2" << std::endl;
				try
				{
					ft::_uninitialized_copy_a(first, last, result, this->_alloc);
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
				// std::cout << "bareeev1" << std::endl;

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
				this->_data = _allocate(_check_len(n, "vector::range_construct"));
				this->_capacity = n;
				ft::_uninitialized_copy_a(first, last, this->_data, this->_alloc);
                this->_size = n;
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

			void	fill_insert(iterator position, size_type n, const value_type &val)
			{
				if (!n)
					return ;
				// no reallocation needed, can work with already allocated memory
				if (this->_capacity - this->_size >= n)
				{
					// in case position points to element inside the container
					value_type	val_copy = val;
					const size_type	elems_after = end() - position;
					// if no filled elements will be constructed beyond size
					if (elems_after > n)
					{
						// displace elements from the end of sequence to the right, beyond size, by constructing objects on uninitialized memory
						ft::_uninitialized_copy_a(this->_data + this->_size - n, this->_data + this->_size, this->_data + this->_size, this->_alloc);
						// copying whatever is not displaced into uninitialized memory -- backwards, because it happens to the right
						ft::copy_backward(position.base(), this->_data + this->_size - n, this->_data + this->_size);
						// fill in the gaps
						ft::fill(position.base(), position.base() + n, val_copy);
					}
					// filled elements will be constructed beyond size
					else
					{
						// fill in elements past size
						ft::_uninitialized_fill_n_a(this->_data + this->_size, n - elems_after, val_copy, this->_alloc);
						// move whatever's from position till size past newly constructed filled elements
						ft::_uninitialized_copy_a(position.base(), this->_data + this->_size, this->_data + this->_size + n - elems_after, this->_alloc);
						// now fill in the old range from position till size
						ft::fill(position.base(), this->_data + this->_size, val_copy);
					}
				}
				// allocation is required
				else
				{
					const size_type	new_capacity = _check_len(n, "vector::fill_insert");
					const size_type	elems_before = position - begin();
					pointer			new_data = _allocate(new_capacity);
					pointer			new_data_end = new_data;
					try
					{
						// construct the filled elements in newly allocated memory
						ft::_uninitialized_fill_n_a(new_data + elems_before, n, val, this->_alloc);
						// so that if in next uninitialized_copy_a() an exception is thrown, the section above gets destroyed only
						new_data_end = NULL;
						// copy whatever was before the filled elements to new memory
						new_data_end = ft::_uninitialized_copy_a(this->_data, position.base(), new_data, this->_alloc);
						// so that if in next uninitialized_copy_a() an exception is thrown, elements constructed above don't get missed
						new_data_end += n;
						// copy whatever was after the filled elements to new memory
						new_data_end = ft::_uninitialized_copy_a(position.base(), this->_data + this->_size, new_data_end, this->_alloc);
					}
					catch (...)
					{
						if (!new_data_end)
							ft::_destroy(new_data + elems_before, new_data + elems_before + n, this->_alloc);
						else
							ft::_destroy(new_data, new_data_end, this->_alloc);
						_deallocate(new_data, new_capacity);
						throw ;
					}
					// free old memory
					ft::_destroy(this->_data, this->_data + this->_size, this->_alloc);
					_deallocate(this->_data, this->_capacity);
					// assign new pointers and data
					this->_capacity = new_capacity;
					this->_data = new_data;
				}
				this->_size += n;
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
