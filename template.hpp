#pragma once
#include<bits/stdc++.h>
using namespace std;

#define rep(i,n) for (ll i=0; i<(n); ++i)
#define nall(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define Yes cout << "Yes" << "\n"
#define No cout << "No" << "\n"

template<typename T,typename U>inline bool chmax(T&a,U b){if(a<b){a=b;return 1;}return 0;}
template<typename T,typename U>inline bool chmin(T&a,U b){if(a>b){a=b;return 1;}return 0;}

using ll = long long;
using ull = unsigned long long;
using P = pair<ll,ll>;

const ll inf = (2e9)+2026;
const ll INF = (1e18)+2026;
const ll dx[] = {0,1,0,-1,1,1,-1,-1};
const ll dy[] = {1,0,-1,0,1,-1,1,-1};