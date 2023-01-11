#ifndef UTILITY_HPP
#define UTILITY_HPP

# include <sstream>
# include <exception>
# include <cstddef>
# include <climits>


#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

namespace ft
{
// is a class template that provides a way to store
//two heterogeneous objects as a single unit. A pair 
//is a specific case of a std::tuple with two elements. 
    template<class T1,class T2>
    struct pair
    {
    
		typedef T1 first_type;
		typedef T2 second_type;
		first_type	first;
		second_type	second;

		//Member functions
		pair(){}
		
		template<class U, class V>
		pair(const pair<U, V>& pr) : first(pr.first), second(pr.second) {}

		pair(const first_type& a, const second_type& b) : first(a), second(b) {}

		pair& operator=(const pair& pr)
		{
			this->first = pr.first;
			this->second = pr.second;
			return (*this);
		}
		
    
    };

	//Non-member functions
	template< class T1, class T2 >
	pair<T1, T2> make_pair(T1 t, T2 u)
	{
		return (pair<T1, T2>(t, u));
	}

	template< class T1, class T2 >
	bool operator==(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
	{
		return (lhs.first == rhs.first and lhs.second == rhs.second);
	}

	template< class T1, class T2 >
	bool operator!=(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
	{
		return (!(lhs == rhs));
	}

	template< class T1, class T2 >
	bool operator<(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
	{
		return (lhs.first < rhs.first or (!(rhs.first < lhs.first) and lhs.second < rhs.second));
	}

	template< class T1, class T2 >
	bool operator<=(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
	{
		return (!(lhs > rhs));
	}

	template< class T1, class T2 >
	bool operator>(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
	{
		return (lhs > rhs);
	}

	template< class T1, class T2 >
	bool operator>=(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
	{
		return (!(lhs < rhs));
	}


}
#endif