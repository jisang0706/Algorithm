#include <iostream>
#include <vector>

using namespace std;

long long gcd(long long a, long long b){
    while(b){
        long long t = a % b;
        a = b;
        b = t;
    }
    return a;
}

long long lcm(long long a, long long b){
    return a / gcd(a,b) * b;
}

struct Edge{
    int to;
    long long p, q;
};

int n;
vector<vector<Edge>> g;
vector<long long> num, den;
vector<int> visited;

void dfs(int cur){
    visited[cur] = 1;

    for(auto &e : g[cur]){
        int nxt = e.to;
        if(visited[nxt]) continue;

        num[nxt] = num[cur] * e.q;
        den[nxt] = den[cur] * e.p;

        long long d = gcd(num[nxt], den[nxt]);
        num[nxt] /= d;
        den[nxt] /= d;

        dfs(nxt);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    g.resize(n);
    num.resize(n);
    den.resize(n);
    visited.assign(n, 0);

    for(int i=0;i<n-1;i++){
        int a,b;
        long long p,q;
        cin >> a >> b >> p >> q;

        long long d = gcd(p,q);
        p/=d; q/=d;

        g[a].push_back({b,p,q});
        g[b].push_back({a,q,p});
    }

    num[0] = 1;
    den[0] = 1;

    dfs(0);

    long long L = 1;
    for(int i=0;i<n;i++){
        L = lcm(L, den[i]);
    }

    vector<long long> val(n);
    for(int i=0;i<n;i++){
        val[i] = num[i] * (L / den[i]);
    }

    long long G = val[0];
    for(int i=1;i<n;i++){
        G = gcd(G, val[i]);
    }

    for(int i=0;i<n;i++){
        cout << val[i] / G << (i+1==n?'\n':' ');
    }

    return 0;
}