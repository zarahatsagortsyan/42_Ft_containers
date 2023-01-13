#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP
#include "iterator.hpp"
#include <iostream>

namespace ft
{
    template <class T>
    class random_access_iterator : public ft::iterator<ft::random_access_iterator_tag, T>
    {
        public:
            typedef typename ft::iterator<std::random_access_iterator_tag, T>::iterator_category 	iterator_category;
            typedef typename ft::iterator<std::random_access_iterator_tag, T>::value_type 			value_type;
            typedef typename ft::iterator<std::random_access_iterator_tag, T>::difference_type 		difference_type;
            typedef typename ft::iterator<std::random_access_iterator_tag, T>::pointer 				pointer;
            typedef typename ft::iterator<std::random_access_iterator_tag, T>::reference 			reference;
            typedef pointer 																		iterator_type;

        protected:
            pointer p;

		public:
            random_access_iterator(pointer p = NULL)
            {
                this->p = p;
            }

            random_access_iterator(const random_access_iterator &other)
            {
                this->p = other.p;
            }

            operator random_access_iterator<const T> () const
            {
                return (random_access_iterator<const T>(this->p));
            }

            random_access_iterator &operator=(const random_access_iterator &other)
            {
                this->p = other.p;
                return (*this);
            }

            reference operator*(){return (*p);}
            pointer operator->(){return (p);}
            random_access_iterator &operator++()
            {
                this->p++;
                return (*this);
            }

            pointer const base() const
            {
                return (this->p);
            }

            random_access_iterator operator++(int t)
            {
                (void) t;
                random_access_iterator tmp = *this;
                this->p++;
                return (tmp);
            }

            random_access_iterator &operator--()
            {
                this->p--;
                return (*this);
            }

            random_access_iterator operator--(int t)
            {
                (void) t;
                random_access_iterator tmp = *this;
                this->p--;
                return (tmp);
            }

            random_access_iterator operator+(difference_type n) const
            {
                return random_access_iterator(this->p + n);
            }

            random_access_iterator operator-(difference_type n) const
            {
                return random_access_iterator(this->p - n);
            }
			
            reference operator[](size_t n) const{return (this->p[n]);}
            random_access_iterator &operator+=(difference_type n){this->p += n; return (*this);}
            random_access_iterator &operator-=(difference_type n){this->p -= n; return (*this);}
            friend random_access_iterator operator+(difference_type n, random_access_iterator &rhs)
            {
                return (random_access_iterator(rhs.p + n));
            }

    };
    template<class T1, class T2>
    bool operator<(const random_access_iterator<T1> lhs, const random_access_iterator<T2> rhs)
    {
        return (lhs.base() < rhs.base());
    }

    template<class T1, class T2>
    bool operator>(random_access_iterator<T1> lhs, random_access_iterator<T2> rhs)
    {
        return (lhs.base() > rhs.base());
    }

    template<class T1, class T2>
    bool operator<=(random_access_iterator<T1> lhs, random_access_iterator<T2> rhs)
    {
        return (lhs.base() <= rhs.base());
    }

    template<class T1, class T2>
    bool operator>=(random_access_iterator<T1> lhs, random_access_iterator<T2> rhs)
    {
        return (lhs.base() >= rhs.base());
    }

    template<class T1, class T2>
    bool operator==(const random_access_iterator<T1> lhs, const random_access_iterator<T2> rhs)
    {
        return (lhs.base() == rhs.base());
    }

    template<class T1, class T2>
    bool operator!=(random_access_iterator<T1> lhs, random_access_iterator<T2> rhs)
    {
        return (lhs.base() != rhs.base());
    }

    template<class T1, class T2>
    typename random_access_iterator<T1>::difference_type operator-(random_access_iterator<T1> lhs, \
    random_access_iterator<T2> rhs)
    {
        return (lhs.base() - rhs.base());
    }
}

#endif