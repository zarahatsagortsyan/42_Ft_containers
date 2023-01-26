#ifndef RBTREE
#define RBTREE

#include <iostream>
#include <memory>
#include "algo.hpp"
#include "utility.hpp"
#include "node.hpp"
#include "../iterators/map_iterator.hpp"    
#include "../includes/type_traits.hpp"
#include "../iterators/bidirectional_iterator.hpp"
#include "../iterators/reverse_iterator.hpp"

namespace ft
{
    template <                                     
        class T,                                      
        class Compare,
        bool isset,        
        class Alloc = std::allocator<T > >
        class red_black_tree
        {
            public:
                typedef T                                                                                   value_type;
                typedef Compare                                                                             value_compare;
                typedef Alloc                                                                               allocator_type;
                typedef typename ft::Node<value_type>                                                       node;
                typedef typename allocator_type::reference                                                  referenece;
                typedef typename allocator_type::const_reference                                            const_referenece;
                typedef typename allocator_type::pointer                                                    pointer;
                typedef typename allocator_type::const_pointer                                              const_pointer;
                
                typedef typename ft::map_iterator<typename ft::constif<isset, value_type>::type, node>      iterator;
                typedef typename ft::map_iterator<const value_type, node>                                   const_iterator;
                typedef typename ft::reverse_iterator<iterator>                                             reverse_iterator;
                typedef typename ft::reverse_iterator<const_iterator>                                       const_reverse_iterator;
                typedef typename iterator_traits<iterator>::difference_type                                 difference_type;
                typedef size_t                                                                              size_type;
                typedef typename Alloc::template rebind<Node<value_type> >::other                           node_alloc;


                red_black_tree(const value_compare &comp = value_compare(), const allocator_type &alloc = allocator_type()) : _size(0), _compare(comp), _alloc(alloc)
                {
                    _nil = _node_alloc.allocate(1);
                    _nil->left = _nil;
                    _nil->right = _nil;
                    _nil->parent = _nil;
                    _nil->data = _alloc.allocate(1);
                    _nil->color = BLACK;
                    _root = _nil;
                    _begin = _nil;
                }
                red_black_tree(const red_black_tree &x) : _alloc(x._alloc), _compare(x._compare), _begin(_nil), _root(_nil), _nil(x._nil)
                {
                    this->insert(x.begin(), x.end());
                }
                red_black_tree &operator=(const red_black_tree &x)
                {
                    this->clear();
                    _alloc = x._alloc;
                    _compare = x._compare;
                    _begin = _nil;
                    _root = _nil;
                    _nil = x._nil;
                    this->insert(x.begin(), x.end());
                    return (*this);
                }
                ~red_black_tree()
                {
                    this->clear();
                    _alloc.deallocate(_nil->data, 1);
                    _node_alloc.deallocate(_nil, 1);
                }
                iterator begin()
                {
                    return (iterator(_begin, _nil, _root));
                }
                const_iterator begin() const
                {
                    return (const_iterator(_begin, _nil, _root));
                }
                iterator end()
                {
                    return (iterator(_nil, _nil, _root));
                }
                const_iterator end() const
                {
                    return (const_iterator(_nil, _nil, _root));
                }
                reverse_iterator rbegin()
                {
                    return reverse_iterator(this->end());
                }
                const_reverse_iterator rbegin() const
                {
                    return const_reverse_iterator(this->end());
                }
                reverse_iterator rend()
                {
                    return (reverse_iterator(this->begin()));
                }
                const_reverse_iterator rend() const
                {
                    return (const_reverse_iterator(this->begin()));
                }
                bool empty() const
                {
                    return (_size == 0);
                }
                size_type size() const
                {
                    return (_size);
                }
                size_type max_size() const
                {
                    return (_node_alloc.max_size());
                }
                ft::pair<iterator,bool> insert (const value_type& val)
                {
                    node *z = _createnode(val);
                    return (_insert(_root, z));
                }
                iterator insert (iterator position, const value_type& val)
                {
                    (void) position;
                    node *z = _createnode(val);
                    return (_insert(_root, z).first);
                }
                template <class InputIterator>
                void insert (InputIterator first, InputIterator last)
                {
                    while (first != last)
                    {
                        insert(*first);
                        first++;
                    }
                }
                void erase (iterator position)
                {
                    erase(*position);
                }
                node *successor(node *n)
                {
                    node *y;

                    if (n->right != _nil)
                    {
                        return (_min(n->right));
                    }
                    y = n->parent;
                    while (y != _nil && n == y->right)
                    {
                        n = y;
                        y = y->parent;
                    }
                    return (y);
                }
                size_type erase(const value_type& k)
                {
                    node *z = _find(_root, k);
                    if (z != _nil)
                    {
                        if (z == _begin)
                        {
                            _begin = successor(z);
                        }
                        _delete(z);
                        delete_node(z);
                        return (1);
                    }
                    return (0);
                }
                void erase(iterator first, iterator last)
                {
                    iterator tmp;

                    while (first != last)
                    {
                        tmp = first;
                        ++tmp;
                        erase(first);
                        first = tmp;
                    }
                }
                void clear()
                {
                    delete_tree(_root);
                    _root = _nil;
                    _begin = _nil;
                }
                void swap(red_black_tree &other)
                {
                    size_type tmpsize = _size;
                    node* tmpbegin = _begin;
                    node *tmproot = _root;
                    node *tmpnil = _nil;
                    _size =other._size;
                    _root = other._root;
                    _nil = other._nil;
                    _begin = other._begin;
                    other._begin = tmpbegin;
                    other._size = tmpsize;
                    other._root = tmproot;
                    other._nil = tmpnil;
                }
                iterator find (const value_type& k) const
                {
                    node *z = _find(_root, k);
                    if (z == _nil)
                        return (iterator(_nil, _nil, _root));
                    return (iterator(z, _nil, _root));
                }
                size_type count (const value_type& k) const
                {
                    node *z = _find(_root, k);
                    if (z != _nil)
                        return (1);
                    return (0);
                }
                allocator_type get_allocator() const
                {
                    return (_alloc);
                }
                iterator lower_bound (const value_type& k) const
                {
                    node *tmp = _root;
                    node *res = _nil;

                    while (tmp != _nil)
                    {
                        if (_compare(*(tmp->data), k))
                        {
                            tmp = tmp->right;
                        }
                        else
                        {
                            res = tmp;
                            tmp = tmp->left;
                        }
                    }
                    return (iterator(res, _nil, _root));
                }
                iterator upper_bound (const value_type& k) const
                {
                    node *tmp = _root;
                    node *res = _nil;

                    while (tmp != _nil)
                    {
                        if (_compare(*(tmp->data), k))
                        {
                            tmp = tmp->right;
                        }
                        else if (_compare(k, *(tmp->data)))
                        {
                            res = tmp;
                            tmp = tmp->left;
                        }
                        else
                        {
                            tmp = tmp->right;
                        }
                    }
                    return (iterator(res, _nil, _root));
                }
                ft::pair<iterator,iterator> equal_range (const value_type& k) const
                {
                    return (ft::make_pair<iterator, iterator>(this->lower_bound(k), this->upper_bound(k)));
                }
            protected:
                size_type _size;
                value_compare _compare;
                node_alloc _node_alloc;
                allocator_type _alloc;
                node *_root;
                node *_nil;
                node *_begin;

                void delete_tree(node *x)
                {
                    if (x == _nil)
                        return ;
                    if (x->left != _nil)
                        delete_tree(x->left);
                    if (x->right != _nil)
                        delete_tree(x->right);
                    delete_node(x);
                }
                void delete_node(node *x)
                {
                     _alloc.destroy(x->data);
                    _alloc.deallocate(x->data, 1);
                    _node_alloc.destroy(x);
                    _node_alloc.deallocate(x, 1);
                    --_size;
                }

                node *_createnode(const value_type &val)
                {       
                    node *x;
                    
                    x = _node_alloc.allocate(1);
                    x->left = _nil;
                    x->right = _nil;
                    x->parent = _nil;
                    x->data = _alloc.allocate(1);
                    try
                    {
                        _alloc.construct(x->data, val);
                    }
                    catch(...)
                    {
                        _alloc.deallocate(x->data, 1);
                         _node_alloc.deallocate(x, 1);
                    }
                    return (x);
                }   
                node *_min(node *x) const
                {
                    while (x->left != _nil)
                    {
                        x = x->left;
                    }
                    return (x);
                }
                node *_max(node *x) const
                {
                    while (x->right != _nil)
                    {
                        x = x->right;
                    }
                    return (x);
                }
                void left_rotate(node *x)
                {
                    node *y = x->right;
                    x->right = y->left;
                    if (y->left != _nil)
                    {
                        y->left->parent = x;
                    }
                    y->parent = x->parent;
                    if (x->parent == _nil)
                        _root = y;
                    else if (x == x->parent->left)
                    {
                        x->parent->left = y;
                    }
                    else
                    {
                        x->parent->right = y;
                    }
                    y->left = x;
                    x->parent = y;
                }
                void right_rotate(node *x)
                {
                    node *y = x->left;
                    x->left = y->right;
                    if (y->right != _nil)
                    {
                        y->right->parent = x;
                    }
                    y->parent = x->parent;
                    if (x->parent == _nil)
                        _root = y;
                    else if (x == x->parent->right)
                    {
                        x->parent->right = y;
                    }
                    else
                    {
                        x->parent->left = y;
                    }
                    y->right = x;
                    x->parent = y;
                }
                node *_find(node *x, value_type val) const
                {
                    if (x == _nil || ((!_compare(*(x->data), val)) &&\
                    !_compare(val, (*x->data))))
                    {
                        return (x);
                    }
                    if (_compare(val, *(x->data)))
                        return (_find(x->left, val));
                    else
                        return (_find(x->right, val));
                }
                void _insert_fixup(node *z)
                {
                    node *y;

                    while (z->parent->color == RED)
                    {
                       if (z->parent == z->parent->parent->left)
                        {
                            y = z->parent->parent->right;
                            if (y->color == RED)
                            {
                                z->parent->color = BLACK;
                                y->color = BLACK;
                                z->parent->parent->color = RED;
                                z = z->parent->parent;
                            }
                            else
                            {
                                if (z == z->parent->right)
                                {
                                    z = z->parent;
                                left_rotate(z);
                                }
                                z->parent->color = BLACK;
                                z->parent->parent->color = RED;
                                right_rotate(z->parent->parent);
                            }
                        }
                        else
                        {
                            y = z->parent->parent->left;
                            if (y->color == RED)
                            {
                                z->parent->color = BLACK;
                                y->color = BLACK;
                                z->parent->parent->color = RED;
                                z = z->parent->parent;
                            }
                            else
                            {
                                if (z == z->parent->left)
                                {
                                    z = z->parent;
                                    right_rotate(z);
                                }
                                z->parent->color = BLACK;
                                z->parent->parent->color = RED;
                                left_rotate(z->parent->parent);
                            }
                        }
                    }
                    _root->color = BLACK;
                }
                ft::pair<iterator, bool> _insert(node *x, node *z)
                {
                    node *y = _nil;
                    node *found;
                    
                    found = _find(_root, *(z->data));
                    if (found != _nil)
                    {
                        delete_node(z);
                        ++_size;
                        return (ft::make_pair(iterator(found, _nil, _root), false));
                    }
                    while (x != _nil)
                    {
                        y = x;
                        if (_compare(*(z->data), *(x->data)))
                            x = x->left;
                        else
                            x = x->right;
                    }
                    z->parent = y;
                    if (y == _nil)
                    {
                        _root = z;
                    }
                    else if(_compare(*(z->data), *(y->data)))
                        y->left = z;
                    else
                        y->right = z;
                    z->left = _nil;
                    z->right = _nil;
                    z->color = RED;
                    _insert_fixup(z);
                    if (_begin == _nil || _compare(*(z->data), *(_begin->data)))
                        _begin = z;
                    _size++;
                    return ft::make_pair(iterator(z, _nil, _root), true);
                }
                void transplant(node *u, node *v)
                {
                    if (u->parent == _nil)
                        _root = v;
                    else if (u == u->parent->left)
                        u->parent->left = v;
                    else
                        u->parent->right = v;
                    v->parent = u->parent;
                }
                void _delete(node *z)
                {
                    node *y;
                    node *x;
                    int color;

                    y = z;
                    color = y->color;
                    if (z->left == _nil)
                    {
                        x = z->right;
                        transplant(z, x);
                    }
                    else if (z->right == _nil)
                    {
                        x = z->left;
                        transplant(z, x);
                    }
                    else
                    {
                        y = _min(z->right);
                        color = y->color;
                        x = y->right;
                        if (y->parent == z)
                            x->parent = y;
                        else
                        {
                            transplant(y, y->right);
                            y->right = z->right;
                            y->right->parent = y;
                        }
                        transplant(z, y);
                        y->left  = z->left;
                        y->left->parent = y;
                        y->color = z->color;
                    }
                    if (color == BLACK)
                        delete_fixup(x);

                }
                void delete_fixup(node *x)
                {
                    node *w;

                    while (x != _root && x->color == BLACK)
                    {
                        if (x == x->parent->left)
                        {
                            w  = x->parent->right;
                            if (w->color == RED)
                            {
                                w->color = BLACK;
                                x->parent->color = RED;
                                left_rotate(x->parent);
                                w = x->parent->right;
                            }
                            if (w->left->color == BLACK &&\
                                w->right->color == BLACK)
                            {
                                w->color = RED;
                                x = x->parent;
                            }
                            else
                            {
                                if(w->right->color == BLACK)
                                {
                                    w->left->color = BLACK;
                                    w->color = RED;
                                    right_rotate(w);
                                    w = x->parent->right;
                                }
                                w->color = x->parent->color;
                                x->parent->color = BLACK;
                                w->right->color = BLACK;
                                left_rotate(x->parent);
                                x = _root;
                            }
                        }
                        else
                        {
                            w  = x->parent->left;
                            if (w->color == RED)
                            {
                                w->color = BLACK;
                                x->parent->color = RED;
                                right_rotate(x->parent);
                                w = x->parent->left;
                            }
                            if (w->right->color == BLACK &&\
                                w->left->color == BLACK)
                            {
                                w->color = RED;
                                x = x->parent;
                            }
                            else
                            {
                                if(w->left->color == BLACK)
                                {
                                    w->right->color = BLACK;
                                    w->color = RED;
                                    left_rotate(w);
                                    w = x->parent->left;
                                }
                                w->color = x->parent->color;
                                x->parent->color = BLACK;
                                w->left->color = BLACK;
                                right_rotate(x->parent);
                                x = _root; 
                            }
                        }
                    }
                    x->color = BLACK;
                }
        };
}


#endif