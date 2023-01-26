#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft
{
    template <class T, class Container = ft::vector<T> >
    class stack
    {
        public:
            typedef T value_type;
            typedef Container container_type;
            typedef size_t size_type;

            explicit stack (const container_type& ctnr = container_type())
            {
                this->c = ctnr;
            }

			stack &operator=(const stack &other)
            {
                if (this != &other)
                    this->c = other.c;
                return (*this);
            }

            virtual ~stack(){}

            bool empty() const
            {
                return (c.empty());
            }
            size_type size() const
            {
                return (c.size());
            }
            value_type& top()
            {
                return (c.back());
            }
            const value_type& top() const
            {
                return (c.back());
            }
            void push (const value_type& val)
            {
                c.push_back(val);
            }
            void pop()
            {
                c.pop_back();
            }
            template <class _T, class _Container>
            friend bool operator== (const stack<_T, _Container>& lhs, const stack<_T, _Container>& rhs)
            {
                return (lhs.c == rhs.c);
            }
            template <class _T, class _Container>
            friend bool operator!= (const stack<_T, _Container>& lhs, const stack<_T, _Container>& rhs)
            {
                return(lhs.c != rhs.c);
            }
            template <class _T, class _Container>
            friend bool operator<  (const stack<_T, _Container>& lhs, const stack<_T, _Container>& rhs)
            {
                return (lhs.c < rhs.c);
            }
            template <class _T, class _Container>
            friend bool operator<= (const stack<_T, _Container>& lhs, const stack<_T, _Container>& rhs)
            {
                return (lhs.c <= rhs.c);
            }
            template <class _T, class _Container>
            friend bool operator>  (const stack<_T, _Container>& lhs, const stack<_T, _Container>& rhs)
            {
                return (lhs.c > rhs.c);
            }
            template <class _T, class _Container>
            friend bool operator>= (const stack<_T, _Container>& lhs, const stack<_T, _Container>& rhs)
            {
                return (lhs.c >= rhs.c);
            }
        protected:
            container_type c;
    };
}

#endif