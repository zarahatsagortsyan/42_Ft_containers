#ifndef TYPE_TRAITS
#define TYPE_TRAITS

namespace ft
{
    //https://gcc.gnu.org/onlinedocs/gcc-4.6.3/libstdc++/api/a01090_source.html
    
    template<typename Tp, Tp v>
    struct integral_constant
    {
        typedef Tp value_type;
		static const value_type value = v;
		typedef integral_constant<Tp, v> type;
		operator value_type() const throw() { return value; }
    };

    //true_type, false_type
    typedef integral_constant<bool, true> true_type;
    typedef integral_constant<bool, false> false_type;

    template < class T>
    struct is_integral : public false_type{};

    template <> struct is_integral<bool> : public true_type{};
    template <> struct is_integral<char> : public true_type{};
    template <> struct is_integral<int> : public true_type{};
    template <> struct is_integral< wchar_t> : public true_type{};
    template <> struct is_integral< signed char> : public true_type{};
    template <> struct is_integral< long int> : public true_type{};
    template <> struct is_integral< short int> : public true_type{};
    template <> struct is_integral< long long int> : public true_type{};
    template <> struct is_integral< unsigned char> : public true_type{};
    template <> struct is_integral< unsigned short int> : public true_type{};
    template <> struct is_integral< unsigned int> : public true_type{};
    template <> struct is_integral< unsigned long int> : public true_type{};
    template <> struct is_integral< unsigned long long int> : public true_type{};

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

};

#endif