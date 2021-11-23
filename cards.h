#pragma once
#include <array>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
class Cards {
    std::array<int, 16> m_c;
public:
    int& operator[](size_t t) {
        return m_c[t];
    }
    int operator[](size_t t) const {
        return m_c[t];
    }
    template <template <class T> class Container>
    Cards(const Container<int>& container) {
        std::fill(m_c.begin(), m_c.end(), 0);
        for (const int &card: container) {
            assert(1 <= card && card <= 16);
            m_c[card]++;
        }
    }
    Cards(std::string);
    int count() const;
    std::string to_string() const;
    Cards& operator+=(const Cards& c);
    Cards& operator-=(const Cards& c);
};