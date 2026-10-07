template<class Monoid>
struct lazysegtree{
    private:
        using S = typename Monoid::S;
        using F = typename Monoid::F;

        int N,log;
        S e = Monoid::e();
        F id = Monoid::id();

        int offset;
        vector<S> d;
        vector<F> lz;

        void init(int n){
            N = n;
            assert(N>=0);
            offset = bit_ceil(unsigned(N));
            log = countr_zero(unsigned(offset));
            d.assign(offset*2,e);
            lz.assign(offset,id);
        }
        void build(const vector<S> &v) {
            for(int i=0; i<N; i++) d[i+offset] = v[i];
            for(int k=offset-1; k>0; k--) update(k);
        }

        void update(int k) {
            d[k] = Monoid::op(d[k*2],d[k*2+1]);
        }

        void all_apply(int k, F f){
            d[k] = Monoid::mapping(f, d[k]);
            if(k < offset) lz[k] = Monoid::composition(f,lz[k]);
        }

        void push(int k){
            all_apply(k*2, lz[k]);
            all_apply(k*2+1, lz[k]);
            lz[k] = id;
        }

    public:
        lazysegtree() : lazysegtree(0) {};
        explicit lazysegtree(int n) : lazysegtree(vector<S>(n,Monoid::e())) {}
        explicit lazysegtree(const vector<S> &v) {
            init((int)v.size());
            build(v);
        }

        int size() const{
            return N;
        }
        S operator [] (int p) {return get(p); }

        void set(int p, S x){
            p += offset;
            for(int i=log; i>=1; i--) push(p >> i);
            d[p] = x;
            for(int i=1; i<=log; i++) update(p >> i);
        }

        S get(int p) {
            p += offset;
            for(int i=log; i>=1; i--) push(p>>i);
            return d[p];
        }

        S prod(int l, int r) {
            if(l==r) return e;
            l += offset;
            r += offset;

            for(int i=log; i>=1; i--){
                if((l>>i)<<i != l) push(l >> i);
                if((r>>i)<<i != r) push((r-1) >> i);
            }

            S sml=e,smr=e;
            while(l<r){
                if(l&1) sml = Monoid::op(sml, d[l++]);
                if(r&1) smr = Monoid::op(d[--r], smr);
                l >>= 1;
                r >>= 1;
            }

            return Monoid::op(sml,smr);
        }

        S all_prod() {return d[1]; }

        void apply(int p, F f) {
            p += offset;
            for(int i=log; i>=1; i--) push(p >> i);
            d[p] = Monoid::mapping(f,d[p]);
            for(int i=1; i<=log; i++) update(p >> i);
        }

        void apply(int l, int r, F f) {
            if(l==r) return;
            
            l += offset;
            r += offset;

            for(int i=log; i>=1; i--){
                if((l>>i)<<i != l) push(l >> i);
                if((r>>i)<<i != r) push((r-1) >> i);
            }

            {
                int l2 = l, r2 = r;
                while(l<r){
                    if(l&1) all_apply(l++, f);
                    if(r&1) all_apply(--r, f);
                    l >>= 1;
                    r >>= 1;
                }
                l = l2; r = r2;
            }

            for(int i=1; i<=log; i++) {
                if((l>>i)<<i != l) update(l >> i);
                if((r>>i)<<i != r) update((r-1) >> i);
            }
        }

        template<class G>
        int max_right(int l, G g) {
            assert(0 <= l && l <= N);
            assert(g(e));
            if(l==N) return N;

            l += offset;
            for(int i=log; i>=1; i--) push(l >> i);
            S sm = e;
            do {
                while(~l & 1) l >>= 1;
                if(!g(Monoid::op(sm,d[l]))){
                    while(l<offset){
                        push(l);
                        l <<= 1;
                        if(g(Monoid::op(sm,d[l]))){
                            sm = Monoid::op(sm,d[l]);
                            l++;
                        }
                    }
                    return l - offset;
                }
                sm = Monoid::op(sm,d[l]);
                l++;
            }while((-l & l) != l);

            return N;
        }

        template<class G>
        int min_left(int r, G g) {
            assert(0 <= r && r <= N);
            assert(g(e));
            if(r==0) return 0;

            r += offset;
            for(int i=log; i>=1; i--) push((r-1) >> i);
            S sm = e;
            
            do{
                r--;
                while(r > 1 && r & 1) r >>= 1;
                if(!g(Monoid::op(d[r],sm))){
                    while(r < offset) {
                        push(r);
                        r = r * 2 + 1;
                        if(g(Monoid::op(d[r],sm))){
                            sm = Monoid::op(d[r],sm);
                            r--;
                        }
                    }
                    return r + 1 - offset;
                }
                sm = Monoid::op(d[r],sm);
            }while((-r & r) != r);

            return 0;
        }
};