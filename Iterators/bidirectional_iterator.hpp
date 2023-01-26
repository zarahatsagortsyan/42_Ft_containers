#ifndef BIDIRECTIONAL_ITERATOR_HPP
#define BIDIRECTIONAL_ITERATOR_HPP

#include "iterator.hpp"

namespace ft
{
	template <
		typename T,
		typename pair_type>
	class bidirectional_iterator : public ft::iterator<ft::bidirectional_iterator_tag, T>
	{
	public:
		typedef ft::iterator<ft::bidirectional_iterator_tag, T> iterator_type;
		typedef ft::iterator<ft::bidirectional_iterator_tag, pair_type> iterator_pair_type;

		typedef typename iterator_type::iterator_category iterator_category;
		typedef typename iterator_type::pointer node_pointer;
		typedef typename iterator_type::reference node_reference;
		typedef typename iterator_type::value_type value_type;
		typedef typename iterator_type::difference_type difference_type;

		typedef typename iterator_pair_type::pointer pointer;
		typedef typename iterator_pair_type::reference reference;

	public:
		bidirectional_iterator() : _null_node(), _elem() {}
		bidirectional_iterator(node_pointer null_node, node_pointer ptr) : _null_node(null_node), _elem(ptr) {}
		bidirectional_iterator(const bidirectional_iterator &other)
		{
			this->_null_node = other._null_node;
			this->_elem = other._elem;
		}
		bidirectional_iterator &operator=(const bidirectional_iterator &other)
		{
			if (this != &other)
			{
				_null_node = other._null_node;
				_elem = other._elem;
			}
			return (*this);
		}
		operator bidirectional_iterator<const T, const pair_type>() const
		{
			return (bidirectional_iterator<const T, const pair_type>(this->_null_node, this->_elem));
		}
		virtual ~bidirectional_iterator() {}

	public:
		bidirectional_iterator<T, pair_type> &operator++()
		{
			if (_elem->right != _null_node)
			{
				_elem = _elem->right;
				while (_elem->left != _null_node)
					_elem = _elem->left;
			}
			else
			{
				if (_elem == _elem->p->left)
					_elem = _elem->p;
				else
				{
					while (_elem == _elem->p->right)
						_elem = _elem->p;
					_elem = _elem->p;
				}
			}
			return (*this);
		}

		bidirectional_iterator<T, pair_type> operator++(int)
		{
			bidirectional_iterator<T, pair_type> tmp = *this;

			operator++();
			return (tmp);
		}

		bidirectional_iterator<T, pair_type> &operator--()
		{
			if (_elem == _null_node)
			{
				_elem = _null_node->p;
				while (_elem->right != _null_node)
					_elem = _elem->right;
			}
			else if (_elem->left != _null_node)
			{
				_elem = _elem->left;
				while (_elem->right != _null_node)
					_elem = _elem->right;
			}
			else
			{
				if (_elem == _elem->p->right)
					_elem = _elem->p;
				else
				{
					while (_elem == _elem->p->left)
						_elem = _elem->p;
					_elem = _elem->p;
				}
			}
			return (*this);
		}
		bidirectional_iterator<T, pair_type> operator--(int)
		{
			bidirectional_iterator<T, pair_type> tmp = *this;

			operator--();
			return (tmp);
		}
		pair_type &operator*() const
		{
			return (_elem->data);
		}
		pair_type *operator->() const
		{
			return (&(_elem->data));
		}
		node_pointer get_node() const
		{
			return (_elem);
		}

		bool operator==(const bidirectional_iterator &other) const
		{
			return (_elem == other._elem);
		}
		bool operator!=(const bidirectional_iterator &other) const
		{
			return (this->_elem != other._elem);
		}

	private:
		node_pointer _null_node;
		node_pointer _elem;
	};
}

#endif