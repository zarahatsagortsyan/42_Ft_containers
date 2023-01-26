#ifndef TYPE_TRAITS
#define TYPE_TRAITS

namespace ft
{
    //https://gcc.gnu.org/onlinedocs/gcc-4.6.3/libstdc++/api/a01090_source.html
    
    template <typename T, T v>
	struct	integral_const
	{
		typedef T						value_type;
		typedef integral_const<T, v>	type;
		static const T					value = v;
		operator T() {return v;}
	};

	typedef ft::integral_const<bool, true>	true_type;
	typedef ft::integral_const<bool, false>	false_type;

    template <typename T> struct	is_integral : ft::integral_const<bool, false> {};

	template <> struct	is_integral<bool> : ft::integral_const<bool, true> {};
	template <> struct	is_integral<char> : ft::integral_const<char, true> {};
	template <> struct	is_integral<signed char> : ft::integral_const<signed char, true> {};
	template <> struct	is_integral<unsigned char> : ft::integral_const<unsigned char, true> {};
	template <> struct	is_integral<short> : ft::integral_const<short, true> {};
	template <> struct	is_integral<unsigned short> : ft::integral_const<unsigned short, true> {};
	template <> struct	is_integral<int> : ft::integral_const<int, true> {};
	template <> struct	is_integral<unsigned int> : ft::integral_const<unsigned int, true> {};
	template <> struct	is_integral<long> : ft::integral_const<long, true> {};
	template <> struct	is_integral<unsigned long> : ft::integral_const<unsigned long, true> {};
	template <> struct	is_integral<long long> : ft::integral_const<long long, true> {};
	template <> struct	is_integral<unsigned long long> : ft::integral_const<unsigned long long, true> {};
	template <> struct	is_integral<wchar_t> : ft::integral_const<wchar_t, true> {};
	template <> struct	is_integral<char16_t> : ft::integral_const<char16_t, true> {};

    //enable_if
    template<bool, typename _Tp = void>
    struct enable_if
    { };

     // Partial specialization for true.
    template<typename _Tp>
    struct enable_if<true, _Tp>
    { typedef _Tp type; };

    /// is_same
    template<typename, typename>
    struct is_same : public false_type { };
    
    template<typename _Tp>
    struct is_same<_Tp, _Tp> : public true_type { };

	template<bool cond, class T>
    struct constif
    {
        typedef T type;
    };

    template <class T>
    struct constif<true, T>
    {
        typedef const T type;
    };
};

#endif