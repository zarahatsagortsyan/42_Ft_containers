#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

# include <memory>
# include <cstddef>
# include <stdexcept>
# include <string>

namespace ft
{
    class vector
    {
        template<
            typename T,
            typename Allocator = std::allocator<T>
        >

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
			typedef ft::random_access_iterator<T>			iterator;
        	typedef ft::random_access_iterator<const T>		const_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
        
        //constructors and destructors =
        public:
            explicit vector (const allocator_type& alloc = allocator_type());
            explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
            template <class InputIterator> vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
            vector (const vector& x);
            vector	&operator=(const vector &other);
            ~vector();
        
        //iterators
        public:
            iterator begin();
            const_iterator begin() const;
            iterator end();
            const_iterator end() const;
            reverse_iterator rbegin();
            const_reverse_iterator rbegin() const;
            reverse_iterator rend();
            const_reverse_iterator rend() const;
            const_iterator cbegin() const noexcept;
            const_iterator cend() const noexcept;
            const_reverse_iterator crbegin() const noexcept;
            const_reverse_iterator crend() const noexcept;

        //Capacity
        public:
            size_type size() const;
            size_type max_size() const;
            void resize (size_type n, value_type val = value_type());
            size_type capacity() const;
            bool empty() const;
            void reserve (size_type n);
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
        private:
			size_type					_size;
			size_type					_capacity;
			pointer						_array;
			allocator_type				_alloc;

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
