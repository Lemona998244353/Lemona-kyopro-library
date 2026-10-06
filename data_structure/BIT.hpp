struct BIT{
    private :
        ll _n;
        vector<ll> a;
        int m;
    public:
        BIT(ll n) : _n(n), a(n+1,0) {
            if(n>0) {
                m=1;
                while(m <= n/2){
                    m *= 2;
                }
            }
        }
        BIT(const vector<ll>& b) : BIT(b.size()) {
            for(ll i=0; i<_n; i++){
                a[i+1] += b[i];
                ll j = (i+1) + ((i+1) & -(i+1));
                if(j<=_n) a[j] += a[i+1];
            }
        }

        void add(ll i, ll x) {
            i++;
            while(i <= _n){
                a[i] += x;
                i += i&-i;
            }
        }

        ll sum(ll r){
            ll res = 0;
            while(r){
                res += a[r];
                r -= (r & -r);
            }
            return res;
        }

        ll sum(ll l, ll r){
            return sum(r)-sum(l);
        }

        // minimum i s.t. sum(i)>=w
        int lower_bound(ll w) {
            int l=0;
            for(int k=m; k; k>>=1) {
                if(l+k <= _n && a[l+k]<w){
                    w -= a[l+k];
                    l += k;
                }
            }
            return l+1;
        }
};