#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

#include "../../data_structure/BIT.hpp"

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n,q; cin >> n >> q;
    vector<ll> a(n);
    for(int i=0; i<n; i++) cin >> a[i];
    BIT fw(a);
    while(q--){
        int t; cin >> t;
        if(t==0){
            int p,x; cin >> p >> x;
            fw.add(p,x);
        }
        else{
            int l,r; cin >> l >> r;
            cout << fw.sum(l,r) << endl;
        }
    }
    return 0;
}