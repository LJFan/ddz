#pragma once
#include <cassert>
#include <vector>
#include <string>
#include "cards.h"
class OnePlay {
    enum Type {
        None,
        WangZha,
        Zhadan,
        SiDaiEr2,
        SiDaiEr1,
        FeiJi2,
        FeiJi1,
        FeiJi0,
        LianDui,
        Shunzi,
        Empty,
    };
    Type type;
    int length, start;
    std::vector<int> appendage;
    static int trans(int t);
public:
    OnePlay(const Cards &cards);
    OnePlay();
    Cards to_cards() const;
    std::string to_string() const;
    bool follow(OnePlay lastplay) const;
    bool operator<(const OnePlay &oneplay) const;
};