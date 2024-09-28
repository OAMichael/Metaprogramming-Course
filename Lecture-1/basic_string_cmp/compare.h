#ifndef COMPARE_H
#define COMPARE_H

#include <string>

// Make operator== for std::basic_string free function to be able to compare:
// - std::basic_string and std::basic_string
// - std::basic_string and null-terminated array of CharT
// - null-terminated array of CharT and std::basic_string
namespace MyCompare {

template <class CharT, class Traits, class Alloc>
bool operator==(const std::basic_string<CharT, Traits, Alloc> &lhs,
                const std::basic_string<CharT, Traits, Alloc> &rhs)
{
    return !lhs.compare(rhs);
}

template <class CharT, class Traits, class Alloc>
bool operator==(const std::basic_string<CharT, Traits, Alloc> &lhs, const char *rhs) {
    return !lhs.compare(rhs);
}

template <class CharT, class Traits, class Alloc>
bool operator==(const char *lhs, const std::basic_string<CharT, Traits, Alloc> &rhs) {
    return !rhs.compare(lhs);
}

}   // namespace MyCompare

#endif  // COMPARE_H
