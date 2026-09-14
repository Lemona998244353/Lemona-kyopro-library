template<class Monoid> struct segtree {
    using S = typename Monoid::S;
    using Func = function<S(S,S)>;

    int N;
    Func OP=Monoid::op;
    S ID=Monoid::e();

    int offset;
    vector<S> dat;

    segtree() : segtree(0) {}
    segtree(int n) {
        init(n);
    }
    segtree(const vector<S> &v) {
        init((int)v.size());
        build(v);
    }

    void init(int n) {
        N = n;
        offset = 1;
        while(offset < N){
            offset *= 2;
        }
        dat.assign(offset*2,ID);
    }
    void init(const vector<S> &v) {
        init((int)v.size());
        build(v);
    }
    void build(const vector<S> &v) {
        assert(N == (int)v.size());
        for(int i=0; i<N; ++i) dat[i+offset] = v[i];
        for(int k=offset-1; k>0; k--) dat[k] = OP(dat[k*2],dat[k*2+1]);
    }
    int size() const{
        return N;
    }
    S operator [] (int a) const {return dat[a+offset]; }

    void set(int a, const S &v) {
        int k = a+offset;
        dat[k] = v;
        while(k>>=1) dat[k] = OP(dat[k*2],dat[k*2+1]);
    }

    S prod(int a, int b) {
        S vleft = ID, vright = ID;
        for(int left = a+offset, right = b+offset; left<right; left>>=1,right>>=1) {
            if(left & 1) vleft = OP(vleft,dat[left++]);
            if(right & 1) vright = OP(dat[--right],vright);
        }
        return OP(vleft,vright);
    }   
    S all_prod() {return dat[1];}

    int max_right(const function<bool(S)> f, int l=0) {
        if(l==N) return N;
        l += offset;
        S sum = ID;
        do{
            while(l%2==0) l>>=1;
            if(!f(OP(sum,dat[l]))) {
                while(l < offset) {
                    l = l*2;
                    if(f(OP(sum,dat[l]))) {
                        sum = OP(sum,dat[l]);
                        ++l;
                    }
                }
                return l-offset;
            }
            sum = OP(sum,dat[l]);
            ++l;
        } while((l&-l) != l);
        return N;
    }

    int min_left(const function<bool(S)> f, int r=-1) {
        if(r==0) return 0;
        if(r==-1) r=N;
        r += offset;
        S sum = ID;
        do{
            --r;
            while(r>1 && (r%2)) r>>=1;
            if(!f(OP(dat[r],sum))) {
                while(r < offset) {
                    r = r*2+1;
                    if(f(OP(dat[r],sum))) {
                        sum = OP(dat[r],sum);
                        --r;
                    }
                }
                return r+1-offset;
            }
            sum = OP(dat[r],sum);
        } while((r & -r) != r);
        return 0;
    }
};