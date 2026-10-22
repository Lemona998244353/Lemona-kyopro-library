auto KMP(const string& s){
    ll n = s.size();
    vector<ll> r(n+1);
    r[0] = -1;
    ll j = -1;
    rep(i,n){
        while(j>=0 && s[i]!=s[j]) j=r[j];
        r[i+1] = ++j;
    }
    return r;
}