#ifndef FT_NORMAL_ITERATOR_HPP
#define FT_NORMAL_ITERATOR_HPP

#include "iterator.hpp"
#include "../includes/type_traits.hpp"
#include "../includes/memory.hpp"
#include "../includes/utility.hpp"
#include "../includes/algo.hpp"

namespace ft
{
    template <class Iterator, class Container>
	class	normal_iterator
	{
		protected:
			Iterator										_base;
			typedef iterator_traits<Iterator>				traits_type;
		public:
			// member types
			typedef Iterator								iterator_type;
			typedef typename traits_type::iterator_category	iterator_category;
			typedef typename traits_type::value_type		value_type;
			typedef typename traits_type::difference_type	difference_type;
			typedef typename traits_type::reference			reference;
			typedef typename traits_type::pointer			pointer;

			normal_iterator() : _base() { }

			// copy ctor allowing conversion to const_iterator
			template<typename Iter>
			normal_iterator(const normal_iterator<Iter,
			typename ft::enable_if<(ft::is_same<Iter, typename Container::pointer>::value), Container>::type> &copy) : _base(copy.base()) { }

			explicit normal_iterator(const Iterator &_base) : _base(_base) { }
			~normal_iterator() { }

			const iterator_type	&base() const 
			{
				return (this->_base);
			}

			normal_iterator	&operator=(const normal_iterator &rhs)
			{
				this->_base = rhs._base;
				return (*this);
			}

			reference	operator*() const
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

			normal_iterator	&operator++()
			{
				this->_base++;
				return (*this);
			}

			normal_iterator	&operator--()
			{
				this->_base--;
				return (*this);
			}

			normal_iterator	operator++(int)
			{
				normal_iterator temp = *this;
				operator++();
				return (temp);
			}

			normal_iterator	operator--(int)
			{
				normal_iterator temp = *this;
				operator--();
				return (temp);
			}

			normal_iterator	&operator+=(difference_type n)
			{
				this->_base += n;
				return (*this);
			}

			normal_iterator	&operator-=(difference_type n)
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

	template <class Iterator, class Container>
	bool	operator==(const normal_iterator<Iterator, Container> &lhs,
					const normal_iterator<Iterator, Container> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <class IteratorL, class IteratorR, class Container>
	bool	operator==(const normal_iterator<IteratorL, Container> &lhs,
					const normal_iterator<IteratorR, Container> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <class Iterator, class Container>
	bool	operator!=(const normal_iterator<Iterator, Container> &lhs,
						const normal_iterator<Iterator, Container> &rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <class IteratorL, class IteratorR, class Container>
	bool	operator!=(const normal_iterator<IteratorL, Container> &lhs,
						const normal_iterator<IteratorR, Container> &rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <class Iterator, class Container>
	bool	operator<(const normal_iterator<Iterator, Container> &lhs,
						const normal_iterator<Iterator, Container> &rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <class IteratorL, class IteratorR, class Container>
	bool	operator<(const normal_iterator<IteratorL, Container> &lhs,
						const normal_iterator<IteratorR, Container> &rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <class Iterator, class Container>
	bool	operator<=(const normal_iterator<Iterator, Container> &lhs,
						const normal_iterator<Iterator, Container> &rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <class IteratorL, class IteratorR, class Container>
	bool	operator<=(const normal_iterator<IteratorL, Container> &lhs,
						const normal_iterator<IteratorR, Container> &rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <class Iterator, class Container>
	bool	operator>(const normal_iterator<Iterator, Container> &lhs,
						const normal_iterator<Iterator, Container> &rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <class IteratorL, class IteratorR, class Container>
	bool	operator>(const normal_iterator<IteratorL, Container> &lhs,
						const normal_iterator<IteratorR, Container> &rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <class Iterator, class Container>
	bool	operator>=(const normal_iterator<Iterator, Container> &lhs,
						const normal_iterator<Iterator, Container> &rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <class IteratorL, class IteratorR, class Container>
	bool	operator>=(const normal_iterator<IteratorL, Container> &lhs,
						const normal_iterator<IteratorR, Container> &rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <class Iterator, class Container>
	normal_iterator<Iterator, Container>
	operator+(typename normal_iterator<Iterator, Container>::difference_type n,
				const normal_iterator<Iterator, Container> &it)
	{
		return (it + n);
	}

	template <class IteratorL, class IteratorR, class Container>
	typename normal_iterator<IteratorL, Container>::difference_type operator-(
		const normal_iterator<IteratorL, Container> &lhs,
		const normal_iterator<IteratorR, Container> &rhs)
	{
		return (lhs.base() - rhs.base());
	}
    

}
#endif