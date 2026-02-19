#include <iostream>
#include <map>

using namespace std;

long long sx, sy, ex, ey;
long long type_cnt[6];
map<pair<long long, long long>, bool> chk_mp;

bool get_type(long long x, long long y) {
    return ((x - 1) / 5) % 2 == ((y - 1) / 5) % 2;
}

void get_side_type(long long& x, long long& y) {
    while (true) {
        if (chk_mp.find(make_pair(x, y)) != chk_mp.end())  break;
        chk_mp[make_pair(x, y)] = true;

        long long fex = min((x / 5 + 1) * 5, ex);
        long long fey = min((y / 5 + 1) * 5, ey);
        if (get_type(fex, fey)) {
            type_cnt[fex - x] += fey - y;
        } else {
            type_cnt[fey - y] += fex - x;
        }
        
        if (x == sx && fey != ey) {
            y = fey;
            continue;
        }

        if (fey == ey && fex != ex) {
            x = fex;
            continue;
        }

        if (fex == ex && y != sy) {
            y = max(y - 5, sy);
            continue;
        }

        if (y == sy && x != sx) {
            x = max(x - 5, sx);
            continue;
        }
    }
}

long long get_ans() {
    long long ans = 0;

    sx = min((sx / 5 + 1) * 5, ex);
    sy = min((sy / 5 + 1) * 5, ey);
    ex = max(((ex - 1) / 5) * 5, sx);
    ey = max(((ey - 1) / 5) * 5, sy);

    ans += ((ex - sx) * (ey - sy)) / 5;

    ans += type_cnt[5];

    ans += type_cnt[4];
    type_cnt[1] -= type_cnt[4];

    ans += type_cnt[3];
    type_cnt[2] -= type_cnt[3];

    if(type_cnt[2] > 0) {
        while(type_cnt[2] > 0) {
            ans++;
            type_cnt[2] -= 2;
            type_cnt[1] -= 1;
        }
    }
    type_cnt[1] += type_cnt[2] * 2;

    if (type_cnt[1] > 0) {
        while(type_cnt[1] > 0) {
            ans++;
            type_cnt[1] -= 5;
        }
    }
    return ans;
}

int main() {
    cin >> sx >> sy >> ex >> ey;

    long long x = sx, y = sy;
    get_side_type(x, y);
    cout << get_ans() << '\n';
    return 0;
}