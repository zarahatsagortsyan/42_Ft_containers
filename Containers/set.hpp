#ifndef SET_HPP
#define SET_HPP

#include <memory>
#include "../includes/algo.hpp"
#include "../includes/type_traits.hpp"
#include "../includes/utility.hpp"
#include "../includes/rbtree.hpp"
#include "../iterators/reverse_iterator.hpp"
#include "../iterators/map_iterator.hpp"
#include "../iterators/iterator.hpp"
#include "../includes/node.hpp"

namespace ft
{
    template <class T, class Compare = ft::less<T>, class Alloc = std::allocator<T> >
    class set
    {
        public:
            typedef T key_type;
            typedef T value_type;
            typedef Compare key_compare;
            typedef Compare value_compare;
            typedef Alloc allocator_type;
            typedef typename ft::Node<value_type> node;
            typedef typename allocator_type::reference reference;
            typedef typename allocator_type::const_reference const_reference;
            typedef typename allocator_type::pointer pointer;
            typedef typename allocator_type::const_pointer const_pointer;
            typedef typename ft::map_iterator<const value_type, node> iterator;
            typedef typename ft::map_iterator<const value_type, node> const_iterator;
            typedef typename ft::reverse_iterator<iterator> reverse_iterator;
            typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;
            typedef typename ft::iterator_traits<iterator>::difference_type difference_type;
            typedef size_t size_type;

            explicit set(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
            {
                this->_alloc = alloc;
                this->_comp = comp;
            }
            template <class InputIterator>
            set(InputIterator first, InputIterator last, const key_compare &comp = key_compare(),
                const allocator_type &alloc = allocator_type()): _comp(comp), _alloc(alloc)
            {
                this->insert(first, last);
            }
            set(const set &x) : _comp(x._comp), _alloc(x._alloc)
            {
                this->insert(x.begin(), x.end());
            }
            ~set()
            {
            }
            set &operator=(const set &x)
            {
                if (this != &x)
                {
                    _comp = x._comp;
                    _alloc = x._alloc;
                    this->clear();
                    this->insert(x.begin(), x.end());
                }
                return (*this);
            }
            iterator begin()
            {
                return (tree.begin());
            }
            const_iterator begin() const
            {
                return (const_iterator(tree.begin()));
            }
            iterator end()
            {
                return (tree.end());
            }
            const_iterator end() const
            {
                return const_iterator(tree.end());
            }
            reverse_iterator rbegin()
            {
                return (tree.rbegin());
            }
            const_reverse_iterator rbegin() const
            {
                return (const_reverse_iterator(tree.rbegin()));
            }
            reverse_iterator rend()
            {
                return (tree.rend());
            }
            const_reverse_iterator rend() const
            {
                return const_reverse_iterator(tree.rend());
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
            pair<iterator, bool> insert(const value_type &val)
            {
                return (tree.insert(val));
            }
            iterator insert(iterator position, const value_type &val)
            {
                return (tree.insert(position, val));
            }
            template <class InputIterator>
            void insert (InputIterator first, InputIterator last)
            {
                tree.insert(first, last);
            }
            void erase (iterator position)
            {
                tree.erase(position);
            }
            size_type erase (const value_type& val)
            {
                return (tree.erase(val));
            }
            void erase (iterator first, iterator last)
            {
                tree.erase(first, last);
            }
            void swap (set& x)
            {
                tree.swap(x.tree);
            }
            void clear()
            {
                tree.clear();
            }
            key_compare key_comp() const
            {
                return (_comp);
            }
            value_compare value_comp() const
            {
                return (_comp);
            }
            iterator find (const value_type& val) const
            {
                return (tree.find(val));
            }
            size_type count (const value_type& val) const
            {
                return (tree.count(val));
            }
            iterator lower_bound (const value_type& val) const
            {
                return (tree.lower_bound(val));
            }
            iterator upper_bound (const value_type& val) const
            {
                return (tree.upper_bound(val));
            }
            pair<iterator,iterator> equal_range (const value_type& val) const
            {
                return (tree.equal_range(val));
            }
            allocator_type get_allocator() const
            {
                return (_alloc);
            }
    protected:
        key_compare _comp;
        allocator_type _alloc;
        ft::red_black_tree<value_type,
        key_compare, true, allocator_type>   tree;
    };
     template< class Key, class Compare, class Alloc >
        bool operator==( const ft::set<Key,Compare,Alloc>& lhs,
        const ft::set<Key,Compare,Alloc>& rhs )
        {
            if (lhs.size() != rhs.size())
                return (false);
            return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
        }
        template< class Key, class Compare, class Alloc >

        bool operator!=( const ft::set<Key,Compare,Alloc>& lhs,
        const ft::set<Key,Compare,Alloc>& rhs )
        {
            return (!(lhs == rhs));
        }
        template< class Key, class Compare, class Alloc >
        bool operator<( const ft::set<Key,Compare,Alloc>& lhs,
        const ft::set<Key,Compare,Alloc>& rhs )
        {
            return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
        }
        template< class Key, class Compare, class Alloc >
        bool operator<=( const ft::set<Key,Compare,Alloc>& lhs,
        const ft::set<Key,Compare,Alloc>& rhs )
        {
            return (!(rhs < lhs));
        }        
        template< class Key, class Compare, class Alloc >
        bool operator>( const ft::set<Key,Compare,Alloc>& lhs,
        const ft::set<Key,Compare,Alloc>& rhs )
        {
            return (rhs < lhs);
        }
        template< class Key, class Compare, class Alloc >
        bool operator>=( const ft::set<Key,Compare,Alloc>& lhs,
        const ft::set<Key,Compare,Alloc>& rhs )
        {
            return (!(lhs < rhs));
        }
        template< class Key, class Compare, class Alloc >
        void swap( const ft::set<Key,Compare,Alloc>& lhs,
        const ft::set<Key,Compare,Alloc>& rhs)
        {
            lhs.swap(rhs);
        }
}

#endif