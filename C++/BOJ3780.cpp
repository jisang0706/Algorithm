#include <iostream>
#include <algorithm>

#define MX 200001

using namespace std;

int t, n;
char s;
int par[MX];
int dist[MX];

void faster() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

int compress_union(int i) {
    if (par[i] == i)    return i;
    int center = compress_union(par[i]);
    dist[i] += dist[par[i]];
    par[i] = center;
    return par[i];
}

void join_union(int i, int j) {
    dist[i] = abs(i - j) % 1000;
    par[i] = j;
}

int main() {
    
    faster();

    cin >> t;
    while(t-- > 0) {
        cin >> n;
        for(int i = 0; i <= n; i++) {
            par[i] = i;
            dist[i] = 0;
        }

        do {
            cin >> s;

            if (s == 'E') {
                int i;
                cin >> i;
                compress_union(i);
                cout << dist[i] << '\n';
            } else if (s == 'I') {
                int i, j;
                cin >> i >> j;
                join_union(i, j);
            }
        } while (s != 'O');
    }
    return 0;
}