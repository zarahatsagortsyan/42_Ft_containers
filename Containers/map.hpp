#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include "../includes/algo.hpp"
#include "../includes/type_traits.hpp"
#include "../includes/utility.hpp"
#include "../includes/rbtree.hpp"
#include "../iterators/map_iterator.hpp"

namespace ft
{
    template <class Key,
              class T,
              class Compare = ft::less<Key>,
              class Alloc = std::allocator<ft::pair<const Key, T> > >
    class map
    {
    public:
        typedef Key key_type;
        typedef T mapped_type;
        typedef typename ft::pair<const key_type, mapped_type> value_type;
        typedef Compare key_compare;
        typedef Alloc allocator_type;
        typedef typename ft::Node<value_type> node;
        class value_compare : std::binary_function<value_type, value_type, bool>
        {
            friend class map;

        protected:
            Compare comp;

        public:
            typedef bool result_type;
            typedef value_type first_argument_type;
            typedef value_type second_argument_type;
            bool operator()(const value_type &x, const value_type &y) const
            {
                return comp(x.first, y.first);
            }
        };
        typedef typename allocator_type::reference referenece;
        typedef typename allocator_type::const_reference const_referenece;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef typename ft::map_iterator<value_type, node> iterator;
        typedef typename ft::map_iterator<const value_type, node> const_iterator;
        typedef typename ft::reverse_iterator<iterator> reverse_iterator;
        typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;
        typedef typename iterator_traits<iterator>::difference_type difference_type;
        typedef size_t size_type;
        typedef typename allocator_type::template rebind<node>::other node_alloc_type;

        explicit map(const key_compare &comp = key_compare(),
                     const allocator_type &alloc = allocator_type()) : _compare(comp), _compval(value_compare()), _alloc(alloc)
        {
        }
        template <class InputIterator>
        map(InputIterator first, InputIterator last,
            const key_compare &comp = key_compare(),
            const allocator_type &alloc = allocator_type()) : _compare(comp), _compval(value_compare()), _alloc(alloc)
        {
            this->insert(first, last);
        }
        map(const map &x) : _compare(x._compare), _compval(x._compval), _alloc(x._alloc)
        {
            this->insert(x.begin(), x.end());
        }
        map &operator=(const map &x)
        {
            _compare = x._compare;
            _alloc = x._alloc;
            _compval = x._compval;
            this->clear();
            this->insert(x.begin(), x.end());
            return (*this);
        }

        pair<iterator, bool> insert(const value_type &val)
        {
            return (tree.insert(val));
        }
        iterator insert(iterator position, const value_type &val)
        {
            return (tree.insert(position, val));
        }
        template <class InputIterator>
        void insert(InputIterator first, InputIterator last)
        {
            return (tree.insert(first, last));
        }
        iterator begin()
        {
            return (tree.begin());
        }
        const_iterator begin() const
        {
            return (tree.begin());
        }
        iterator end()
        {
            return (tree.end());
        }
        const_iterator end() const
        {
            return (tree.end());
        }
        reverse_iterator rbegin()
        {
            return (tree.rbegin());
        }
        const_reverse_iterator rbegin() const
        {
            return (tree.rbegin());
        }
        reverse_iterator rend()
        {
            return (tree.rend());
        }
        const_reverse_iterator rend() const
        {
            return (tree.rend());
        }
        bool empty() const
        {
            return (tree.size() == 0);
        }
        size_type size() const
        {
            return (tree.size());
        }
        size_type max_size() const
        {
            return (tree.max_size());
        }
        mapped_type &operator[](const key_type &k)
        {
            this->insert(ft::pair<const key_type, mapped_type>(k, mapped_type()));
            return (this->find(k)->second);
        }
        mapped_type &at(const key_type &k)
        {
            iterator z = this->find(k);
            if (z == tree.end())
            {
                throw std::out_of_range("out of range");
            }
            else
            {
                return ((*z).second);
            }
        }
        const mapped_type &at(const key_type &k) const
        {
            const_iterator z = this->find(k);
            if (z == tree.end())
            {
                throw std::out_of_range("out of range");
            }
            else
            {
                return ((*z).second);
            }
        }
        void erase(iterator position)
        {
            tree.erase(position);
        }
        size_type erase(const key_type &k)
        {
            return (tree.erase(ft::make_pair(k, mapped_type())));
        }
        void erase(iterator first, iterator last)
        {
            tree.erase(first, last);
        }
        void swap(map &x)
        {
            tree.swap(x.tree);
        }
        void clear()
        {
            tree.clear();
        }
        key_compare key_comp() const
        {
            return (_compare);
        }
        value_compare value_comp() const
        {
            return (_compval);
        }
        allocator_type get_allocator() const
        {
            return (_alloc);
        }
        iterator find(const key_type &k)
        {
            return (tree.find(ft::make_pair(k, mapped_type())));
        }
        const_iterator find(const key_type &k) const
        {
            return (tree.find(ft::make_pair(k, mapped_type())));
        }
        size_type count(const key_type &k) const
        {
            return (tree.count(ft::make_pair(k, mapped_type())));
        }
        iterator lower_bound(const key_type &k)
        {
            return (tree.lower_bound(ft::make_pair(k, mapped_type())));
        }
        const_iterator lower_bound(const key_type &k) const
        {
            return (const_iterator(tree.lower_bound(ft::make_pair(k, mapped_type()))));
        }
        iterator upper_bound(const key_type &k)
        {
            return (tree.upper_bound(ft::make_pair(k, mapped_type())));
        }
        const_iterator upper_bound(const key_type &k) const
        {
            return (const_iterator(tree.upper_bound(ft::make_pair(k, mapped_type()))));
        }
        pair<const_iterator, const_iterator> equal_range(const key_type &k) const
        {
            return (tree.equal_range(ft::make_pair(k, mapped_type())));
        }
        pair<iterator, iterator> equal_range(const key_type &k)
        {
            return (tree.equal_range(ft::make_pair(k, mapped_type())));
        }

    protected:
        key_compare _compare;
        value_compare _compval;
        allocator_type _alloc;
        ft::red_black_tree<value_type,
                           value_compare, false, allocator_type>
            tree;
    };
    template <class Key, class T, class Compare, class Alloc>
    bool operator==(const ft::map<Key, T, Compare, Alloc> &lhs,
                    const ft::map<Key, T, Compare, Alloc> &rhs)
    {
        if (lhs.size() != rhs.size())
            return (false);
        return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
    }
    template <class Key, class T, class Compare, class Alloc>

    bool operator!=(const ft::map<Key, T, Compare, Alloc> &lhs,
                    const ft::map<Key, T, Compare, Alloc> &rhs)
    {
        return (!(lhs == rhs));
    }
    template <class Key, class T, class Compare, class Alloc>
    bool operator<(const ft::map<Key, T, Compare, Alloc> &lhs,
                   const ft::map<Key, T, Compare, Alloc> &rhs)
    {
        return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }
    template <class Key, class T, class Compare, class Alloc>
    bool operator<=(const ft::map<Key, T, Compare, Alloc> &lhs,
                    const ft::map<Key, T, Compare, Alloc> &rhs)
    {
        return (!(rhs < lhs));
    }
    template <class Key, class T, class Compare, class Alloc>
    bool operator>(const ft::map<Key, T, Compare, Alloc> &lhs,
                   const ft::map<Key, T, Compare, Alloc> &rhs)
    {
        return (rhs < lhs);
    }
    template <class Key, class T, class Compare, class Alloc>
    bool operator>=(const ft::map<Key, T, Compare, Alloc> &lhs,
                    const ft::map<Key, T, Compare, Alloc> &rhs)
    {
        return (!(lhs < rhs));
    }
    template <class Key, class T, class Compare, class Alloc>
    void swap(const ft::map<Key, T, Compare, Alloc> &lhs,
              const ft::map<Key, T, Compare, Alloc> &rhs)
    {
        lhs.swap(rhs);
    }
}

#endif