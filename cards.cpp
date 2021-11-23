#include "cards.h"
#include <unordered_map>
Cards::Cards(const std::string str) {
    static const std::unordered_map<char, int> text2card = {
        {'Y', 15}, {'y', 15},
        {'X', 14}, {'x', 14},
        {'K', 13}, {'k', 13},
        {'Q', 12}, {'q', 12},
        {'J', 11}, {'j', 11},
        {'0', 10},
        {'9', 9},
        {'8', 8},
        {'7', 7},
        {'6', 6},
        {'5', 5},
        {'4', 4},
        {'3', 3},
        {'2', 2},
        {'A', 1}, {'a', 1},
    };
    std::fill(m_c.begin(), m_c.end(), 0);
    for (const char &c: str) {
        auto p = text2card.find(c);
        if (p == text2card.end()) throw "Unrecognized Char";
        m_c[p->second]++;
    }
}
int Cards::count() const {
    int ret = 0;
    for (const int &sub_count: m_c) ret += sub_count;
    return ret;
}
std::string Cards::to_string() const {
    static const char text[] = "?A234567890JQKXY";
    std::string ret;
    for (int i = 15; i > 0; i--) {
        int k = i > 13 ? i : (i + 1) % 13 + 1;
        for (int j = 0; j < m_c[k]; j++) {
            ret += text[k];
        }
    }
    return ret;
}
Cards& Cards::operator+=(const Cards& c) {
    for (int i = 0; i < 16; i++) m_c[i] += c[i];
    return *this;
}
Cards& Cards::operator-=(const Cards& c) {
    for (int i = 0; i < 16; i++) m_c[i] -= c[i];
    return *this;
}