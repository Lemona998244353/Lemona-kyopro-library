struct BIT{
    ll _n;
    vector<ll> a;
    BIT(ll n) : _n(n), a(n+1,0) {}
    BIT(const vector<ll>& b) : _n(b.size()), a(n+1,0) {
        for(ll i=0; i<_n; i++){
            a[i+1] += b[i];
            ll j = (i+1) + (i+1) & -(i+1);
            if(j<=_n) a[j] += b[i+1];
        }
    }

    ll sum(ll r){
        ll res = 0;
        while(r){
            res += a[r];
            r -= r & -r;
        }
        return res;
    }

    ll sum(ll l, ll r){
        return sum(r)-sum(l);
    }

    // sum(i)>=wとなるような最小のi
    int lower_bound(ll w) {
        int l=0, r=_n-1;
        int m=1;
        while(m < _n/2){
            m *= 2;
        }
        for(int k=m; k; k>>=1) {
            if(l+k <= r && a[l+k]<w){
                w -= a[l+k];
                l += k;
            }
        }
        return l+1;
    }
};