//
// Copyright (c) 2013-2016 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BEAST_HTTP_DETAIL_RFC7230_HPP
#define BEAST_HTTP_DETAIL_RFC7230_HPP

#include <boost/utility/string_ref.hpp>
#include <array>
#include <iterator>
#include <utility>

namespace beast {
namespace http {
namespace detail {

inline
bool
is_digit(char c)
{
    return c >= '0' && c <= '9';
}

inline
bool
is_alpha(char c)
{
    static std::array<char, 256> constexpr tab = {{
        0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0, // 0
        0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0, // 16
        0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0, // 32
        0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0, // 48
        0, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1, // 64
        1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 0,  0, 0, 0, 0, // 80
        0, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1, // 96
        1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 0,  0, 0, 0, 0, // 112
    }};
    return tab[static_cast<std::uint8_t>(c)] != 0;
}

inline
bool
is_text(char c)
{
    // TEXT = <any OCTET except CTLs, but including LWS>
    static std::array<char, 256> constexpr tab = {{
        0, 0, 0, 0,  0, 0, 0, 0,  0, 1, 0, 0,  0, 0, 0, 0, // 0
        0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0, // 16
        1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1, // 32
        1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1, // 48
        1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1, // 64
        1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1, // 80
        1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1, // 96
        1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 0, // 112
        1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1, // 128
        1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1, // 144
        1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1, // 160
        1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1, // 176
        1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1, // 192
        1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1, // 208
        1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1, // 224
        1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1  // 240
    }};
    return tab[static_cast<std::uint8_t>(c)] != 0;
}

inline
bool
is_tchar(char c)
{
    /*
        tchar = "!" | "#" | "$" | "%" | "&" |
                "'" | "*" | "+" | "-" | "." |
                "^" | "_" | "`" | "|" | "~" |
                DIGIT | ALPHA
    */
    static std::array<char, 256> constexpr tab = {{
        0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0, // 0
        0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0, // 16
        0, 1, 0, 1,  1, 1, 1, 1,  0, 0, 1, 1,  0, 1, 1, 0, // 32
        1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 0, 0,  0, 0, 0, 0, // 48
        0, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1, // 64
        1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 0,  0, 0, 1, 1, // 80
        1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1, // 96
        1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 0,  1, 0, 1, 0, // 112
    }};
    return tab[static_cast<std::uint8_t>(c)] != 0;
}

inline
bool
is_qdchar(char c)
{
    /*
        qdtext = HTAB / SP / "!" / %x23-5B ; '#'-'[' / %x5D-7E ; ']'-'~' / obs-text
    */
    static std::array<bool, 256> constexpr tab = {{
        0, 0, 0, 0,  0, 0, 0, 0,  0, 1, 0, 0,  0, 0, 0, 0, // 0
        0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0, // 16
        1, 1, 0, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1, // 32
        1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1, // 48
        1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1, // 64
        1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  0, 1, 1, 1, // 80
        1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1, // 96
        1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 0, // 112
        1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1, // 128
        1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1, // 144
        1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1, // 160
        1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1, // 176
        1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1, // 192
        1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1, // 208
        1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1, // 224
        1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1  // 240
    }};
    return tab[static_cast<std::uint8_t>(c)];
}

inline
bool
is_qpchar(char c)
{
    /*
        quoted-pair = "\" ( HTAB / SP / VCHAR / obs-text )
        obs-text = %x80-FF
    */
    static std::array<bool, 256> constexpr tab = {{
        0, 0, 0, 0,  0, 0, 0, 0,  0, 1, 0, 0,  0, 0, 0, 0, // 0
        0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0, // 16
        1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1, // 32
        1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1, // 48
        1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1, // 64
        1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1, // 80
        1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1, // 96
        1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 0, // 112
        1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1, // 128
        1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1, // 144
        1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1, // 160
        1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1, // 176
        1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1, // 192
        1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1, // 208
        1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1, // 224
        1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1  // 240
    }};
    return tab[static_cast<std::uint8_t>(c)];
}

// converts to lower case,
// returns 0 if not a valid token char
//
inline
char
to_field_char(char c)
{
    /*  token = 1*<any CHAR except CTLs or separators>
        CHAR  = <any US-ASCII character (octets 0 - 127)>
        sep   = "(" | ")" | "<" | ">" | "@"
              | "," | ";" | ":" | "\" | <">
              | "/" | "[" | "]" | "?" | "="
              | "{" | "}" | SP | HT
    */
    static std::array<char, 256> constexpr tab = {{
        0,   0,   0,   0,   0,   0,   0,    0,   0,   0,   0,   0,   0,   0,   0,    0,
        0,   0,   0,   0,   0,   0,   0,    0,   0,   0,   0,   0,   0,   0,   0,    0,
        0,  '!',  0,  '#', '$', '%', '&', '\'',  0,   0,  '*', '+',  0,  '-', '.',   0,
       '0', '1', '2', '3', '4', '5', '6',  '7', '8', '9',  0,   0,   0,   0,   0,    0,
        0,  'a', 'b', 'c', 'd', 'e', 'f',  'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',  'o',
       'p', 'q', 'r', 's', 't', 'u', 'v',  'w', 'x', 'y', 'z',  0,   0,   0,  '^',  '_',
       '`', 'a', 'b', 'c', 'd', 'e', 'f',  'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',  'o',
       'p', 'q', 'r', 's', 't', 'u', 'v',  'w', 'x', 'y', 'z',  0,  '|',  0,  '~',   0
    }};
    return tab[static_cast<std::uint8_t>(c)];
}

// converts to lower case,
// returns 0 if not a valid text char
//
inline
char
to_value_char(char c)
{
    // TEXT = <any OCTET except CTLs, but including LWS>
    static std::array<std::uint8_t, 256> constexpr tab = {{
          0,   0,   0,   0,   0,   0,   0,   0,   0,   9,   0,   0,   0,   0,   0,   0, // 0
          0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 16
         32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47, // 32
         48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,  63, // 48
         64,  97,  98,  99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, // 64
        112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122,  91,  92,  93,  94,  95, // 80
         96,  97,  98,  99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, // 96
        112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126,   0, // 112
        128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, // 128
        144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, // 144
        160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, // 160
        176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, // 176
        192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, // 192
        208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, // 208
        224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, // 224
        240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255  // 240
    }};
    return static_cast<char>(tab[static_cast<std::uint8_t>(c)]);
}

inline
std::int8_t
unhex(char c)
{
    static std::array<std::int8_t, 256> constexpr tab = {{
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 0
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 16
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 32
         0,  1,  2,  3,  4,  5,  6,  7,  8,  9, -1, -1, -1, -1, -1, -1, // 48
        -1, 10, 11, 12, 13, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 64
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 80
        -1, 10, 11, 12, 13, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 96
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1  // 112
    }};
    return tab[static_cast<std::uint8_t>(c)];
}

template<class FwdIt>
void
skip_ows(FwdIt& it, FwdIt const& end)
{
    while(it != end)
    {
        auto const c = *it;
        if(c != ' ' && c != '\t')
            break;
        ++it;
    }
}

inline
boost::string_ref
trim(boost::string_ref const& s)
{
    auto first = s.begin();
    auto last = s.end();
    skip_ows(first, last);
    while(first != last)
    {
        auto const c = *std::prev(last);
        if(c != ' ' && c != '\t')
            break;
        --last;
    }
    if(first == last)
        return {};
    return {&*first,
        static_cast<std::size_t>(last - first)};
}

struct param_iter
{
    using iter_type = boost::string_ref::const_iterator;

    iter_type it;
    iter_type begin;
    iter_type end;
    std::pair<boost::string_ref, boost::string_ref> v;

    bool
    empty() const
    {
        return begin == it;
    }

    template<class = void>
    void
    increment();
};

template<class>
void
param_iter::
increment()
{
/*
    ext-list    = *( "," OWS ) ext *( OWS "," [ OWS ext ] )
    ext         = token param-list
    param-list  = *( OWS ";" OWS param )
    param       = token OWS "=" OWS ( token / quoted-string )
            
    quoted-string = DQUOTE *( qdtext / quoted-pair ) DQUOTE
    qdtext = HTAB / SP / "!" / %x23-5B ; '#'-'[' / %x5D-7E ; ']'-'~' / obs-text
    quoted-pair = "\" ( HTAB / SP / VCHAR / obs-text )
    obs-text = %x80-FF

    Example:
        chunked;a=b;i=j,gzip;windowBits=12
        x,y
*/
    auto const err =
        [&]
        {
            it = begin;
        };
    v.first.clear();
    v.second.clear();
    detail::skip_ows(it, end);
    begin = it;
    if(it == end)
        return err();
    if(*it != ';')
        return err();
    ++it;
    detail::skip_ows(it, end);
    if(it == end)
        return err();
    // param
    if(! detail::is_tchar(*it))
        return err();
    auto const p0 = it;
    for(;;)
    {
        ++it;
        if(it == end)
            return err();
        if(! detail::is_tchar(*it))
            break;
    }
    auto const p1 = it;
    detail::skip_ows(it, end);
    if(it == end)
        return err();
    if(*it != '=')
        return err();
    ++it;
    detail::skip_ows(it, end);
    if(it == end)
        return err();
    if(*it == '"')
    {
        // quoted-string
        auto const p2 = it;
        ++it;
        for(;;)
        {
            if(it == end)
                return err();
            auto c = *it++;
            if(c == '"')
                break;
            if(detail::is_qdchar(c))
                continue;
            if(c != '\\')
                return err();
            if(it == end)
                return err();
            c = *it++;
            if(! detail::is_qpchar(c))
                return err();
        }
        v.first = { &*p0, static_cast<std::size_t>(p1 - p0) };
        v.second = { &*p2, static_cast<std::size_t>(it - p2) };
    }
    else
    {
        // token
        if(! detail::is_tchar(*it))
            return err();
        auto const p2 = it;
        for(;;)
        {
            it++;
            if(it == end)
                break;
            if(! detail::is_tchar(*it))
                break;
        }
        v.first = { &*p0, static_cast<std::size_t>(p1 - p0) };
        v.second = { &*p2, static_cast<std::size_t>(it - p2) };
    }
}

} // detail
} // http
} // beast

#endif

