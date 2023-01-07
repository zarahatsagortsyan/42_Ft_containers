#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

# include <memory>
# include <cstddef>
# include <stdexcept>
# include <string>

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
			typedef normal_iterator<pointer, vector>			iterator;
        	typedef ft::normal_iterator<const_pointer, vector>  const_iterator;
			typedef ft::reverse_iterator<const_iterator>	    const_reverse_iterator;
			typedef ft::reverse_iterator<iterator>			    reverse_iterator;
        
        private:
			size_type					_size;
			size_type					_capacity;
			pointer						_array;
			allocator_type				_alloc;

        //constructors and destructors =
        public:
            explicit vector (const allocator_type& alloc = allocator_type()): _alloc(alloc), _data(NULL), _capacity(0), _size(0) { }
            
            explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
            : _alloc(alloc), _data(NULL), _capacity(0), _size(0)
			{
				this->_data = allocate_a(check_length(static_cast<size_type>(n), "vector::vector"));
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

            vector	&operator=(const vector &x)
			{
				if (&x != this)
				{
					const size_type	x_size = x.size();
					// reallocate, not enough memory
					if (x_size > this->_capacity)
					{
						pointer	new_data = allocate_and_copy(x_size, x.begin(), x.end());
						ft::destroy_a(this->_data, this->_data + this->_size, this->_alloc);
						deallocate_a(this->_data, this->_capacity);
						this->_data = new_data;
						this->_capacity = x_size;
					}
					// copy from x to this, and destroy the rest past x's elements
					else if (this->_size >= x_size)
						ft::destroy_a(ft::copy(x.begin(), x.end(), begin()), end(), this->_alloc);
					// memory is enough, assign constructed objects and construct the ones that are beyond size
					else
					{
						ft::copy(x._data, x._data + this->_size, this->_data);
						ft::uninitialized_copy_a(x._data + this->_size, x._data + x_size, this->_data + this->_size, this->_alloc);
					}
					this->_size = x_size;
				}
				return (*this);
			}

            ~vector()
			{
				clear();
				deallocate_a(this->_data, this->_capacity);
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
            const_iterator cbegin() const noexcept;
            const_iterator cend() const noexcept;
            const_reverse_iterator crbegin() const noexcept;
            const_reverse_iterator crend() const noexcept;

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
					// allocate and copy what already was initialized
					pointer		new_data = allocate_and_copy(n, this->_data, this->_data + this->_size);
					// free old data
					ft::destroy_a(this->_data, this->_data + this->_size, this->_alloc);
					deallocate_a(this->_data, this->_capacity);
					this->_data = new_data;
					this->_capacity = n;
				}
            }
            void shrink_to_fit();

        //Element access
        public:
            reference operator[] (size_type n);const_reference operator[] (size_type n) const;
            reference at (size_type n);const_reference at (size_type n) const;
            reference front();const_reference front() const;
            reference back();const_reference back() const;
            value_type* data() noexcept;
            const value_type* data() const noexcept;

        //Modifiers
        public:
            template <class InputIterator>  
            void assign (InputIterator first, InputIterator last);
            void assign (size_type n, const value_type& val);
            void push_back (const value_type& val);
            void pop_back();

            iterator insert (iterator position, const value_type& val);
            void insert (iterator position, size_type n, const value_type& val);
            
            template <class InputIterator>
            void insert (iterator position, InputIterator first, InputIterator last);

            iterator erase (iterator position);iterator erase (iterator first, iterator last);
            void swap (vector& x);

            void clear();

            template <class... Args>iterator emplace (const_iterator position, Args&&... args);
            template <class... Args>  void emplace_back (Args&&... args);

        //Allocator:
        public:
            allocator_type get_allocator() const;

    }

    template <typename T, typename Allocator>
	void	swap(vector<T, Allocator> &lhs, vector<T, Allocator> &rhs);

	template <typename T, typename Allocator>
	bool	operator==(const vector<T, Allocator> &lhs, const vector<T, Allocator> &rhs);

	template <typename T, typename Allocator>
	bool	operator!=(const vector<T, Allocator> &lhs, const vector<T, Allocator> &rhs);

	template <typename T, typename Allocator>
	bool	operator<(const vector<T, Allocator> &lhs, const vector<T, Allocator> &rhs);

	template <typename T, typename Allocator>
	bool	operator<=(const vector<T, Allocator> &lhs, const vector<T, Allocator> &rhs);

	template <typename T, typename Allocator>
	bool	operator>(const vector<T, Allocator> &lhs, const vector<T, Allocator> &rhs);

	template <typename T, typename Allocator>
	bool	operator>=(const vector<T, Allocator> &lhs, const vector<T, Allocator> &rhs);
}

# include "vector_impl.tpp"

#endif
