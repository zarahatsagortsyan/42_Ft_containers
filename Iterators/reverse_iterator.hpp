#ifndef FT_REVERSE_ITERATOR_HPP
#define FT_REVERSE_ITERATOR_HPP

#include "iterator.hpp"
#include "reverse_iterator.hpp"
#include "../includes/type_traits.hpp"
#include "../includes/memory.hpp"


namespace ft
{
    template<typename Iterator>
    class reverse_iterator
    {
        protected: 
            Iterator _base;
        public:
            typedef Iterator                                                iterator_type;
            typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
            typedef typename iterator_traits<Iterator>::value_type			value_type;
            typedef typename iterator_traits<Iterator>::difference_type		difference_type;
            typedef typename iterator_traits<Iterator>::pointer				pointer;
            typedef typename iterator_traits<Iterator>::reference			reference;
            

            reverse_iterator() : _base() { }
            //Member functions
            // constexpr reverse_iterator() : _base(){}
            explicit reverse_iterator(iterator_type x) : _base(x){}

            //template< class Iterator > 
            reverse_iterator( const reverse_iterator<Iterator>& other ) : _base(other.base()){}
            
            // template< class Iterator > 
            reverse_iterator& operator=( const reverse_iterator<Iterator>& other )
            {
                this->_base = other._base;
                return (*this);
            }
            
            ~reverse_iterator() {}

            iterator_type base() const
            {
                return this->_base;
            }

            reference operator*() const
            {
                return (*(--iterator_type(this->_base)));
            }

            reference operator[]( difference_type n ) const
            {
                return (this->_base[-n - 1]);
            }

            reverse_iterator	operator+(difference_type n) const
            {
                return (reverse_iterator(this->_base - n));
            }
            reverse_iterator	operator-(difference_type n) const
            {
                return (reverse_iterator(this->_base + n));
            }
            reverse_iterator &operator++()
            {
                --this->base;
                return (*this);
            }
            reverse_iterator &operator--()
            {
                ++this->base;
                return (*this);
            }
            reverse_iterator operator++( int )
            {
                reverse_iterator temp(*this);
                ++(*this);
                return (temp);
            }
            reverse_iterator operator--( int )
            {
                reverse_iterator temp(*this);
                --(*this);
                return (temp);
            }

            reverse_iterator& operator+=( difference_type n )
            {
                this->_base -= n;
                return (*this);
            }

            reverse_iterator& operator-=( difference_type n )
            {
                this->_base += n;
                return (*this);
            }

            pointer	operator->() const
            {
                return (ft::_addressof(operator*()));
            }
        };
    }

    //Non-member functions
    template<class Iterator>
    bool operator==( const ft::reverse_iterator<Iterator>& lhs,
                    const ft::reverse_iterator<Iterator>& rhs )
    {
        return (lhs.base() == rhs.base());
    }

    template< class Iterator1, class Iterator2 >
            bool operator==( const ft::reverse_iterator<Iterator1>& lhs,
                             const ft::reverse_iterator<Iterator2>& rhs )
    {
        return (lhs.base() == rhs.base());
    }

    template< class Iterator>
    bool operator!=( const ft::reverse_iterator<Iterator>& lhs,
                    const ft::reverse_iterator<Iterator>& rhs )
    {
        return (lhs.base() != rhs.base());
    }

    template< class Iterator1, class Iterator2 >
    bool operator!=( const ft::reverse_iterator<Iterator1>& lhs,
                    const ft::reverse_iterator<Iterator2>& rhs )
    {
        return (lhs.base() != rhs.base());
    }

    template< class Iterator>
    bool operator<( const ft::reverse_iterator<Iterator>& lhs,
                    const ft::reverse_iterator<Iterator>& rhs )
    {
        return (lhs.base() > rhs.base());
    }

    template< class Iterator1, class Iterator2 >
    bool operator<( const ft::reverse_iterator<Iterator1>& lhs,
                    const ft::reverse_iterator<Iterator2>& rhs )
    {
        return (lhs.base() > rhs.base());
    }

    template< class Iterator>
    bool operator<=(const ft::reverse_iterator<Iterator>& lhs,
                    const ft::reverse_iterator<Iterator>& rhs )
    {
        return (lhs.base() >= rhs.base());
    }

    template< class Iterator1, class Iterator2 >
    bool operator<=(const ft::reverse_iterator<Iterator1>& lhs,
                    const ft::reverse_iterator<Iterator2>& rhs )
    {
        return (lhs.base() >= rhs.base());
    }

    template< class Iterator>
    bool operator>( const ft::reverse_iterator<Iterator>& lhs,
                    const ft::reverse_iterator<Iterator>& rhs )
    {
        return (lhs.base() < rhs.base());
    }
    template< class Iterator1, class Iterator2 >
    bool operator>( const ft::reverse_iterator<Iterator1>& lhs,
                    const ft::reverse_iterator<Iterator2>& rhs )
    {
        return (lhs.base() < rhs.base());
    }

    template< class Iterator >
    bool operator>=(const ft::reverse_iterator<Iterator>& lhs,
                    const ft::reverse_iterator<Iterator>& rhs )
    {
        return (lhs.base() <= rhs.base());
    }

    template< class Iterator1, class Iterator2 >
    bool operator>=(const ft::reverse_iterator<Iterator1>& lhs,
                    const ft::reverse_iterator<Iterator2>& rhs )
    {
        return (lhs.base() <= rhs.base());

    }

    template <class Iterator>
    ft::reverse_iterator<Iterator>
	operator+(typename ft::reverse_iterator<Iterator>::difference_type n,
	          const ft::reverse_iterator<Iterator> &rev_it)
    {
	    return (rev_it + n);
    }

    template< class Iterator1, class Iterator2 >
    typename ft::reverse_iterator<Iterator1>::difference_type 
        operator-( const ft::reverse_iterator<Iterator1>& lhs,
                   const ft::reverse_iterator<Iterator2>& rhs )
    {
        return (rhs.base() - lhs.base());
    }


#endif