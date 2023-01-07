#ifndef FT_RANDOM_ACCESS_ITERATOR_HPP
#define FT_RANDOM_ACCESS_ITERATOR_HPP

namespace ft
{
    template<typename Iterator, typename Container>
    class normal_iterator
    {
        protected: 
            Iterator _base;
            typedef iterator_traits<Iterator>   traits_type;
        public:
            typedef Iterator    iterator_type;
            typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
            typedef typename iterator_traits<Iterator>::value_type			value_type;
            typedef typename iterator_traits<Iterator>::difference_type		difference_type;
            typedef typename iterator_traits<Iterator>::pointer				pointer;
            typedef typename iterator_traits<Iterator>::reference			reference;
            
            //Member functions
            normal_iterator() : _base(){}

            template<typename Iter>
			normal_iterator(const normal_iterator<Iter,
			typename ft::enable_if<(ft::is_same<Iter, typename Container::pointer>::value), Container>::type> &copy) : _base(copy.base()) { }
            
            explicit normal_iterator(const Iterator &_base) : _base(_base) { }

            template< class Iterator > 
            normal_iterator( const normal_iterator<Iterator>& other ) : _base(other.base()){}
            
            template< class Iterator > 
            normal_iterator& operator=( const normal_iterator& other )
            {
                this->_base = rhs._base;
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
                ++this->base;
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
                return (ft::addressof(operator*()));
            }

            reference	operator[](difference_type n) const
            {
                return (this->_base[n]);
            }
    };
}

//Non-member functions
template<class Iterator>
bool operator==( const std::normal_iterator<Iterator>& lhs,
                const std::normal_iterator<Iterator>& rhs )
{
    return (lhs.base() == rhs.base());
}

template< class Iterator1, class Iterator2 >
        bool operator==( const std::normal_iterator<Iterator1>& lhs,
        const std::normal_iterator<Iterator2>& rhs )
{
    return (lhs.base() == rhs.base());
}

template< class Iterator>
bool operator!=( const std::normal_iterator<Iterator>& lhs,
                const std::normal_iterator<Iterator>& rhs )
{
    return (lhs.base() != rhs.base());
}

template< class Iterator1, class Iterator2 >
bool operator!=( const std::normal_iterator<Iterator1>& lhs,
                const std::normal_iterator<Iterator2>& rhs )
{
    return (lhs.base() != rhs.base());
}

template< class Iterator>
bool operator<( const std::normal_iterator<Iterator>& lhs,
                const std::normal_iterator<Iterator>& rhs )
{
    return (lhs.base() < rhs.base());
}

template< class Iterator1, class Iterator2 >
bool operator<( const std::normal_iterator<Iterator1>& lhs,
                const std::normal_iterator<Iterator2>& rhs )
{
    return (lhs.base() < rhs.base());
}

template< class Iterator>
bool operator<=(const std::normal_iterator<Iterator>& lhs,
                const std::normal_iterator<Iterator>& rhs )
{
    return (lhs.base() <= rhs.base());
}

template< class Iterator1, class Iterator2 >
bool operator<=(const std::normal_iterator<Iterator1>& lhs,
                const std::normal_iterator<Iterator2>& rhs )
{
    return (lhs.base() <= rhs.base());
}

template< class Iterator>
bool operator>( const std::normal_iterator<Iterator>& lhs,
                const std::normal_iterator<Iterator>& rhs )
{
    return (lhs.base() > rhs.base());
}
template< class Iterator1, class Iterator2 >
bool operator>( const std::normal_iterator<Iterator1>& lhs,
                const std::normal_iterator<Iterator2>& rhs );
{
    return (lhs.base() > rhs.base());
}

template< class Iterator >
bool operator>=(const std::normal_iterator<Iterator>& lhs,
                const std::normal_iterator<Iterator>& rhs )
{
    return (lhs.base() >= rhs.base());
}

template< class Iterator1, class Iterator2 >
bool operator>=(const std::normal_iterator<Iterator1>& lhs,
                const std::normal_iterator<Iterator2>& rhs )
{
    return (lhs.base() >= rhs.base());
}
template< class Iterator > 
ft::normal_iterator<Iterator> 
operator+(typename normal_iterator<Iter>::difference_type n,
          const normal_iterator<Iter>& it )
{
    return (it + n);
}

template< class Iterator1, class Iterator2 >
typename normal_iterator<Iterator1>::difference_type 
    operator-( const normal_iterator<Iterator1>& lhs,
               const normal_iterator<Iterator2>& rhs )
{
    return (rhs.base() - lhs.base());
}