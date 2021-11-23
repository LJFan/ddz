#include "oneplay.h"
OnePlay::OnePlay(): type(Empty), length(0), start(0) {}
OnePlay::OnePlay(const Cards &cards): type(None), length(0), start(0) {
    const int count = cards.count();
    if (count == 0) {
        type = Empty;
        return;
    }
    if (count == 2 && cards[14] == 1 && cards[15] == 1) {
        type = WangZha;
        return;
    }
    if (count == 4) {
        int tmp_start = 0;
        for (int i = 1; i <= 15; i++) if (cards[i] == 4) {
            tmp_start = i;
            break;
        }
        if (tmp_start) {
            type = Zhadan;
            length = 1;
            start = tmp_start;
            return;
        }
    }
    if (count == 8) {
        Cards tmp_cards = cards;
        int tmp_start = 0;
        for (int i = 15; i >= 1; i--) {
            int j = (i + 1) % 13 + 1;
            if (tmp_cards[j] >= 4) {
                tmp_start = j;
                tmp_cards[j] -= 4;
                break;
            }
        }
        if (tmp_start) {
            std::vector<int> tmp_appendage;
            for (int i = 15; i >= 1; i--) {
                int j = i > 13 ? i : (i + 1) % 13 + 1;
                if (tmp_cards[j] >= 2) {
                    tmp_appendage.push_back(j);
                    tmp_cards[j] -= 2;
                    i++;
                }
            }
            if (tmp_appendage.size() == 2) {
                type = SiDaiEr2;
                start = tmp_start;
                length = 1;
                appendage.swap(tmp_appendage);
                return;
            }
        }
    }
    if (count == 6) {
        Cards tmp_cards = cards;
        int tmp_start = 0;
        for (int i = 15; i >= 1; i--) {
            int j = (i + 1) % 13 + 1;
            if (tmp_cards[j] >= 4) {
                tmp_start = j;
                tmp_cards[j] -= 4;
                break;
            }
        }
        if (tmp_start) {
            std::vector<int> tmp_appendage;
            for (int i = 15; i >= 1; i--) {
                int j = i > 13 ? i : (i + 1) % 13 + 1;
                if (tmp_cards[j] >= 1) {
                    tmp_appendage.push_back(j);
                    tmp_cards[j] -= 1;
                    i++;
                }
            }
            if (tmp_appendage.size() == 2) {
                type = SiDaiEr1;
                start = tmp_start;
                length = 1;
                appendage.swap(tmp_appendage);
                return;
            }
        }
    }
    if (count % 5 == 0) {
        int tmp_start = 0;
        int tmp_length = 0;
        int length_goal = count / 5;
        Cards tmp_cards = cards;
        for (int i = length_goal == 1 ? 13 : 12; i >= 1; i--) {
            int j = (i + 1) % 13 + 1;
            if (tmp_cards[j] >= 3) {
                if (tmp_start == 0) tmp_start = j;
                tmp_length++;
                if (tmp_length == length_goal) break;
            } else {
                tmp_start = 0;
                tmp_length = 0;
            }
        }
        if (tmp_length == length_goal) {
            for (int i = 0; i < length_goal; i++) {
                int j = (tmp_start - i + 12) % 13 + 1;
                assert(tmp_cards[j] >= 3);
                tmp_cards[j] -= 3;
            }
            std::vector<int> tmp_appendage;
            for (int i = 15; i >= 1; i--) {
                int j = i > 13 ? i : (i + 1) % 13 + 1;
                if (tmp_cards[j] >= 2) {
                    tmp_appendage.push_back(j);
                    tmp_cards[j] -= 2;
                    i++;
                }
            }
            if (tmp_appendage.size() == tmp_length) {
                type = FeiJi2;
                start = tmp_start;
                length = tmp_length;
                appendage.swap(tmp_appendage);
                return;
            }
        }
    }
    if (count % 4 == 0) {
        int tmp_start = 0;
        int tmp_length = 0;
        int length_goal = count / 4;
        Cards tmp_cards = cards;
        for (int i = length_goal == 1 ? 13 : 12; i >= 1; i--) {
            int j = (i + 1) % 13 + 1;
            if (tmp_cards[j] >= 3) {
                if (tmp_start == 0) tmp_start = j;
                tmp_length++;
                if (tmp_length == length_goal) break;
            } else {
                tmp_start = 0;
                tmp_length = 0;
            }
        }
        if (tmp_length == length_goal) {
            for (int i = 0; i < length_goal; i++) {
                int j = (tmp_start - i + 12) % 13 + 1;
                assert(tmp_cards[j] >= 3);
                tmp_cards[j] -= 3;
            }
            std::vector<int> tmp_appendage;
            for (int i = 15; i >= 1; i--) {
                int j = i > 13 ? i : (i + 1) % 13 + 1;
                if (tmp_cards[j] >= 1) {
                    tmp_appendage.push_back(j);
                    tmp_cards[j] -= 1;
                    i++;
                }
            }
            if (tmp_appendage.size() == tmp_length) {
                type = FeiJi1;
                start = tmp_start;
                length = tmp_length;
                appendage.swap(tmp_appendage);
                return;
            }
        }
    }
    if (count % 3 == 0) {
        int tmp_start = 0;
        int tmp_length = 0;
        int length_goal = count / 3;
        Cards tmp_cards = cards;
        for (int i = length_goal == 1 ? 13 : 12; i >= 1; i--) {
            int j = (i + 1) % 13 + 1;
            if (tmp_cards[j] >= 3) {
                if (tmp_start == 0) tmp_start = j;
                tmp_length++;
                if (tmp_length == length_goal) break;
            } else {
                tmp_start = 0;
                tmp_length = 0;
            }
        }
        if (tmp_length == length_goal) {
            type = FeiJi0;
            start = tmp_start;
            length = tmp_length;
            return;
        }
    }
    if (count % 2 == 0) {
        int tmp_start = 0;
        int tmp_length = 0;
        int length_goal = count / 2;
        if (length_goal >= 3 || length_goal == 1) {
            Cards tmp_cards = cards;
            for (int i = length_goal == 1 ? 13 : 12; i >= 1; i--) {
                int j = (i + 1) % 13 + 1;
                if (tmp_cards[j] >= 2) {
                    if (tmp_start == 0) tmp_start = j;
                    tmp_length++;
                    if (tmp_length == length_goal) break;
                } else {
                    tmp_start = 0;
                    tmp_length = 0;
                }
            }
            if (tmp_length == length_goal) {
                type = LianDui;
                start = tmp_start;
                length = tmp_length;
                return;
            }
        }
    }
    if (count % 1 == 0) {
        int tmp_start = 0;
        int tmp_length = 0;
        int length_goal = count / 1;
        if (length_goal >= 5 || length_goal == 1) {
            Cards tmp_cards = cards;
            for (int i = length_goal == 1 ? 15 : 12; i >= 1; i--) {
                int j = i > 13 ? i : (i + 1) % 13 + 1;
                if (tmp_cards[j] >= 1) {
                    if (tmp_start == 0) tmp_start = j;
                    tmp_length++;
                    if (tmp_length == length_goal) break;
                } else {
                    tmp_start = 0;
                    tmp_length = 0;
                }
            }
            if (tmp_length == length_goal) {
                type = Shunzi;
                start = tmp_start;
                length = tmp_length;
                return;
            }
        }
    }
    if (type == None) throw "No Match OnePlay Type";
}

std::string OnePlay:: to_string() const {
    static const char text[] = "?A234567890JQKXY";
    std::string ret = "(";
    switch (type) {
        case None:
            ret += "None";
            break;
        case Empty:
            ret += "Empty";
            break;
        case WangZha:
            ret += "WangZha, YX";
            break;
        case Zhadan:
            ret += "Zhadan, ";
            for (int i = 0; i < 4; i++) {
                ret += text[start];
            }
            break;
        case SiDaiEr2:
            ret += "SiDaiEr2, ";
            for (int i = 0; i < 4; i++) {
                ret += text[start];
            }
            for (const auto &card: appendage) {
                for (int i = 0 ; i < 2; i++) {
                    ret += text[card];
                }
            }
            break;
        case SiDaiEr1:
            ret += "SiDaiEr1, ";
            for (int i = 0; i < 4; i++) {
                ret += text[start];
            }
            for (const auto &card: appendage) {
                for (int i = 0 ; i < 1; i++) {
                    ret += text[card];
                }
            }
            break;
        case FeiJi2:
            ret += "FeiJi2, ";
            for (int k = 0; k < length; k++){
                for (int i = 0; i < 3; i++) {
                    ret += text[(start - k + 12) % 13 + 1];
                }
            }
            for (const auto &card: appendage) {
                for (int i = 0 ; i < 2; i++) {
                    ret += text[card];
                }
            }
            break;
        case FeiJi1:
            ret += "FeiJi1, ";
            for (int k = 0; k < length; k++){
                for (int i = 0; i < 3; i++) {
                    ret += text[(start - k + 12) % 13 + 1];
                }
            }
            for (const auto &card: appendage) {
                for (int i = 0 ; i < 1; i++) {
                    ret += text[card];
                }
            }
            break;
        case FeiJi0:
            ret += "FeiJi0, ";
            for (int k = 0; k < length; k++){
                for (int i = 0; i < 3; i++) {
                    ret += text[(start - k + 12) % 13 + 1];
                }
            }
            break;
        case LianDui:
            ret += "LianDui, ";
            for (int k = 0; k < length; k++){
                for (int i = 0; i < 2; i++) {
                    ret += text[(start - k + 12) % 13 + 1];
                }
            }
            break;
        case Shunzi:
            ret += "Shunzi, ";
            if (length == 1) {
                ret += text[start];
            } else {
                for (int k = 0; k < length; k++){
                    for (int i = 0; i < 1; i++) {
                        ret += text[(start - k + 12) % 13 + 1];
                    }
                }
            }
            break;
        default:
            ret += "Error";
            break;
    }
    return ret + ")";
}

int OnePlay::trans(int t) {
    if (t > 13) return t;
    return (t + 10) % 13 + 1;
}

Cards OnePlay::to_cards() const {
    static const char text[] = "?A234567890JQKXY";
    Cards ret("");
    switch (type) {
        case None:
            throw "None to Cards";
        case Empty:
            break;
        case WangZha:
            ret[14] = ret[15] = 1;
            break;
        case Zhadan:
            ret[start] = 4;
            break;
        case SiDaiEr2:
            ret[start] = 4;
            for (const auto &card: appendage) {
                ret[card] += 2;
            }
            break;
        case SiDaiEr1:
            ret[start] = 4;
            for (const auto &card: appendage) {
                ret[card] += 1;
            }
            break;
        case FeiJi2:
            for (int k = 0; k < length; k++){
                ret[(start - k + 12) % 13 + 1] = 3;
            }
            for (const auto &card: appendage) {
                ret[card] += 2;
            }
            break;
        case FeiJi1:
            for (int k = 0; k < length; k++){
                ret[(start - k + 12) % 13 + 1] = 3;
            }
            for (const auto &card: appendage) {
                ret[card] += 1;
            };
            break;
        case FeiJi0:
            for (int k = 0; k < length; k++){
                ret[(start - k + 12) % 13 + 1] = 3;
            }
            break;
        case LianDui:
            for (int k = 0; k < length; k++){
                ret[(start - k + 12) % 13 + 1] = 2;
            }
            break;
        case Shunzi:
            if (length == 1) {
                ret[start] = 1;
            } else {
                for (int k = 0; k < length; k++){
                    ret[(start - k + 12) % 13 + 1] = 1;
                }
            }
            break;
    }
    return ret;
}

bool OnePlay::follow(OnePlay lastplay) const {
    if (lastplay.type == Empty) return type != Empty;
    if (lastplay.type != Empty && type == Empty) return true;
    if (lastplay.type == WangZha) return false;
    if (type == WangZha) return true;
    if (lastplay.type == Zhadan && type == WangZha) return true;
    if (lastplay.type == Zhadan && type == Zhadan) return trans(start) > trans(lastplay.start);
    if (type == Zhadan) return true;
    if (lastplay.type == type) return length == lastplay.length && trans(start) > trans(lastplay.start);
    return false;
}

bool OnePlay::operator<(const OnePlay &oneplay) const {
    if (type != oneplay.type) return type < oneplay.type;
    if (length != oneplay.length) return length > oneplay.length;
    if (start != oneplay.start) return trans(start) < trans(oneplay.start);
    return appendage < oneplay.appendage;
}