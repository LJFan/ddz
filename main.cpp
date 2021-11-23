#include <cstdio>
#include <cstring>
#include <utility>
#include <vector>
#include <unordered_map>
#include "oneplay.h"

Cards read_cards(const char *info) {
    char str[128];
    while (1) {
        printf("%s", info);
        fgets(str, 128, stdin);
        if (*str && str[strlen(str) - 1] == '\n') {
            str[strlen(str) - 1] = '\0';
        }
        try {
            return Cards(str);
        }
        catch (const char *e) {
            printf("Exception: %s\n", e);
        }
    }
}

OnePlay read_onepaly(const char *info, const OnePlay& lastplay, Cards cards) {
    char str[128];
    while (1) {
        printf("%s", info);
        fgets(str, 128, stdin);
        if (*str && str[strlen(str) - 1] == '\n') {
            str[strlen(str) - 1] = '\0';
        }
        try {
            OnePlay oneplay = OnePlay(Cards(str));
            if (!oneplay.follow(lastplay)) {
                printf("The OnePlay does not follow %s\n", lastplay.to_string().c_str());
                continue;
            }
            Cards tmp_cards = cards;
            tmp_cards -= oneplay.to_cards();
            bool flag = 1;
            for (int i = 0; i < 16; i++) {
                if (tmp_cards[i] < 0) flag = 0;
            }
            if (flag) return oneplay;
            else {
                printf("The OnePlay does not in the HandCards\n");
            }
        }
        catch (const char *e) {
            printf("Exception: %s\n", e);
        }
    }
}

static void dfs(int u, Cards &cards, std::vector<OnePlay> &ret) {
    if (u == 0) {
        try {
            OnePlay oneplay(cards);
            ret.push_back(oneplay);
        }
        catch (const char *) {}
        return;
    }
    int cu = cards[u];
    for (int i = 0; i <= cu; i++) {
        cards[u] = i;
        dfs(u - 1, cards, ret);
    }
}

std::vector<OnePlay> get_all_follow(Cards cards, const OnePlay & lastplay) {
    static std::unordered_map<size_t, std::vector<OnePlay>> cache;
    const size_t h = std::hash<std::string>{}(cards.to_string());
    std::vector<OnePlay> t_ret;
    if (cache.count(h)) {
        t_ret = cache[h];
    } else {
        dfs(15, cards, t_ret);
        std::sort(t_ret.begin(), t_ret.end());
        cache[h] = t_ret;
    }
    std::vector<OnePlay> ret;
    for (const OnePlay &oneplay: t_ret) {
        if (oneplay.follow(lastplay)) ret.push_back(oneplay);
    }
    return ret;
}

std::pair<bool, std::vector<OnePlay>> search(Cards your_cards, Cards oppo_cards, const OnePlay& lastplay, int deep = 0) {
    // printf("%*s(your = %s, oppo = %s, last = %s)\n",deep, "", your_cards.to_string().c_str(), oppo_cards.to_string().c_str(), lastplay.to_string().c_str());
    static std::unordered_map<size_t, bool> cache;
    const size_t h = std::hash<std::string>{}(your_cards.to_string() + ";" + oppo_cards.to_string() + ";" + lastplay.to_string());
    if (deep > 0 && cache.count(h)) return {cache[h], {}};
    std::pair<bool, std::vector<OnePlay>> ret = {false, {}};
    if (oppo_cards.count() == 0) {
        cache[h] = false;
        return ret;
    }
    std::vector<OnePlay> follows = get_all_follow(your_cards, lastplay);
    if (deep == 0) {
        printf(">%*s<\n>", follows.size(), "");
        fflush(stdout);
    }
    for (const OnePlay &follow: follows) {
        auto tmp_cards = your_cards;
        try {
            tmp_cards -= follow.to_cards();
        } catch (const char *e) {
            printf("follow.to_string(): %s\n", follow.to_string().c_str());
            printf("Exception: %s\n", e);
        }
        if (!search(oppo_cards, tmp_cards, follow, deep + 1).first) {
            ret.first = true;
            if (deep > 0) break;
            ret.second.push_back(follow);
        }
        if (deep == 0) putchar('-'), fflush(stdout);
    }
    if (deep == 0) puts("<"), fflush(stdout);
    cache[h] = ret.first;
    return ret;
}

int main() {
    Cards your_cards = read_cards("Input Your Cards: ");
    Cards oppo_cards = read_cards("Input Oppo Cards: ");
    puts("");
    OnePlay lastplay;
    while (1) {
        auto ans = search(your_cards, oppo_cards, lastplay);
        printf("[%s]", ans.first ? "Win" : "Lose");
        for (const OnePlay &oneplay: ans.second) {
            printf(" %s ", oneplay.to_string().c_str());
        }
        puts("");
        lastplay = read_onepaly("Your OnePlay: ", lastplay, your_cards);
        your_cards -= lastplay.to_cards();
        if (your_cards.count() == 0) break;
        lastplay = read_onepaly("Oppo OnePlay: ", lastplay, oppo_cards);
        oppo_cards -= lastplay.to_cards();
        if (oppo_cards.count() == 0) break;
        puts("================");
        printf("Your Cards: %s\n", your_cards.to_string().c_str());
        printf("Oppo Cards: %s\n", oppo_cards.to_string().c_str());
    }
}