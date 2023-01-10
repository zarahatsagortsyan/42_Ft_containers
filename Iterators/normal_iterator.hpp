#ifndef FT_NORMAL_ITERATOR_HPP
#define FT_NORMAL_ITERATOR_HPP

#include "iterator.hpp"
#include "../includes/type_traits.hpp"
#include <iterator>

namespace ft
{
    template<typename Iterator, typename Container>
    class normal_iterator
    {
        protected: 
            Iterator _base;
            typedef ft::iterator_traits<Iterator>   traits_type;
        public:
            typedef Iterator    iterator_type;
            typedef typename traits_type::iterator_category	iterator_category;
            typedef typename traits_type::value_type			value_type;
            typedef typename traits_type::difference_type		difference_type;
            typedef typename traits_type::pointer				pointer;
            typedef typename traits_type::reference			reference;
            
            //Member functions
            normal_iterator() : _base(){}

            template<typename Iter>
			normal_iterator(const normal_iterator<Iter,
			typename ft::enable_if<(ft::is_same<Iter, typename Container::pointer>::value), Container>::type> &copy) : _base(copy.base()) { }            
            explicit normal_iterator(const Iterator &_base) : _base(_base) { }
            
            normal_iterator& operator=( const normal_iterator& other )
            {
                this->_base = other._base;
                return (*this);
            }
            ~normal_iterator();

            iterator_type base() const
            {
                return this->_base;
            }

            reference operator*() const
            {
                return (*this->_base);
            }

            normal_iterator	operator+(difference_type n) const
            {
                return (normal_iterator(this->_base + n));
            }

            normal_iterator	operator-(difference_type n) const
            {
                return (normal_iterator(this->_base - n));
            }

            normal_iterator &operator++()
            {
                ++this->_base;
                return (*this);
            }

            normal_iterator &operator--()
            {
                --this->base;
                return (*this);
            }

            normal_iterator operator++( int )
            {
                normal_iterator temp(*this);
                operator++();
                return (temp);
            }

            normal_iterator operator--( int )
            {
                normal_iterator temp(*this);
                operator--();
                return (temp);
            }

            normal_iterator& operator+=( difference_type n )
            {
                this->_base += n;
                return (*this);
            }

            normal_iterator& operator-=( difference_type n )
            {
                this->_base -= n;
                return (*this);
            }

            pointer	operator->() const
            {
                return (ft::_addressof(operator*()));
            }

            reference	operator[](difference_type n) const
            {
                return (this->_base[n]);
            }
    };

    //Non-member functions
    template<class Iterator, class Container>
    bool operator==( const ft::normal_iterator<Iterator, Container>& lhs, 
                     const ft::normal_iterator<Iterator, Container>& rhs )
    {
        return (lhs.base() == rhs.base());
    }

    template< class Iterator1, class Iterator2, class Container >
    bool operator==( const ft::normal_iterator<Iterator1, Container>& lhs,
                     const ft::normal_iterator<Iterator2, Container>& rhs )
    {
        return (lhs.base() == rhs.base());
    }

    template <class Iterator, class Container>
    bool operator!=( const ft::normal_iterator<Iterator, Container>& lhs,
                     const ft::normal_iterator<Iterator, Container>& rhs )
    {
        return (lhs.base() != rhs.base());
    }

    template< class Iterator1, class Iterator2, class Container >
    bool operator!=( const ft::normal_iterator<Iterator1, Container>& lhs,
                     const ft::normal_iterator<Iterator2, Container>& rhs )
    {
        return (lhs.base() != rhs.base());
    }

    template<class Iterator, class Container>
    bool operator<( const ft::normal_iterator<Iterator, Container>& lhs,
                    const ft::normal_iterator<Iterator, Container>& rhs )
    {
        return (lhs.base() < rhs.base());
    }

    template< class Iterator1, class Iterator2, class Container >
    bool operator<( const ft::normal_iterator<Iterator1, Container>& lhs,
                    const ft::normal_iterator<Iterator2, Container>& rhs )
    {
        return (lhs.base() < rhs.base());
    }

    template<class Iterator, class Container>
    bool operator<=(const ft::normal_iterator<Iterator, Container>& lhs,
                    const ft::normal_iterator<Iterator, Container>& rhs )
    {
        return (lhs.base() <= rhs.base());
    }

    template< class Iterator1, class Iterator2, class Container >
    bool operator<=(const ft::normal_iterator<Iterator1, Container>& lhs,
                    const ft::normal_iterator<Iterator2, Container>& rhs )
    {
        return (lhs.base() <= rhs.base());
    }

    template<class Iterator, class Container>
    bool operator>( const ft::normal_iterator<Iterator, Container>& lhs,
                    const ft::normal_iterator<Iterator, Container>& rhs )
    {
        return (lhs.base() > rhs.base());
    }

    template< class Iterator1, class Iterator2, class Container >
    bool operator>( const ft::normal_iterator<Iterator1, Container>& lhs,
                    const ft::normal_iterator<Iterator2, Container>& rhs )
    {
        return (lhs.base() > rhs.base());
    }

    template<class Iterator, class Container>
    bool operator>=(const ft::normal_iterator<Iterator, Container>& lhs,
                    const ft::normal_iterator<Iterator, Container>& rhs )
    {
        return (lhs.base() >= rhs.base());
    }

    template< class Iterator1, class Iterator2, class Container >
    bool operator>=(const ft::normal_iterator<Iterator1, Container>& lhs,
                    const ft::normal_iterator<Iterator2, Container>& rhs )
    {
        return (lhs.base() >= rhs.base());
    }

    template< class Iterator, class Container > 
    normal_iterator<Iterator, Container> 
    operator+(typename ft::normal_iterator<Iterator, Container>::difference_type n,
            const ft::normal_iterator<Iterator, Container>& it )
    {
        return (it + n);
    }

    template< class Iterator1, class Iterator2, class Container >
    typename normal_iterator<Iterator1, Iterator2>::difference_type 
    operator-( const normal_iterator<Iterator1, Container>& lhs,
               const normal_iterator<Iterator2, Container>& rhs )
    {
        return (rhs.base() - lhs.base());
    }
}


#endif