#define PROBLEM "https://judge.yosupo.jp/problem/aho_corasick"

#include "../../template.hpp"
#include "../../string/aho_corasick.hpp"

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n; cin >> n;
    aho_corasick ac;
    rep(i,n){
        string s; cin >> s;
        ac.add(s);
    }
    ac.build();
    cout << ac.state_cnt() << endl;
    for(int i=1; i<ac.state_cnt(); i++){
        cout << ac.par(i) << ' ' << ac.link(i) << endl;
    }
    rep(i,n) cout << ac.last(i) << " \n"[i==n-1];
}