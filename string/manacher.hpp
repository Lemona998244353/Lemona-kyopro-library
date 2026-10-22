auto manacher(const string& s){
    ll n = s.size();
    ll c=0,r=0;
    vector<ll> d(n);
    rep(i,n){
        ll l = c - (i-c); // |l-c| = |i-c|
        if(i<c+d[c] && i+d[l] < c+d[c]){ //すでに探索した右端を越えるか
            d[i] = d[l]; //越えないならおわり
        }
        else{ //越えるなら右端をさらに探索。
            ll k = c+d[c] - i;
            while(i-k>=0 && i+k<n && s[i-k] == s[i+k]) k++;
            d[i] = k;
            c = i;
        }
    }
    return d;
}