auto z_algorithm(const string& s){
    ll n = s.size();
    vector<ll> z(n);
    ll c = 0;
    for(ll i=1; i<n; i++){
        if(i+z[i-c] < c+z[c]){
            z[i] = z[i-c];
        }
        else{
            ll k = max(0LL, c+z[c] - i);
            while(i+k<n && s[k]==s[i+k]) k++;
            z[i] = k;
            c = i;
        }
    }
    if(n==0) return z;
    z[0] = n;
    return z;
}