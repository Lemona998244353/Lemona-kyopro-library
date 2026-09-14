struct dsu{
  private:
    int _n;
    vector<int> p_or_s;

    int _leader(int x){
      if(p_or_s[x]<0) return x;
      else{
        return p_or_s[x]=_leader(p_or_s[x]);
      }
    }

  public:
    dsu() : _n(0){};
    explicit dsu(int n) : _n(n), p_or_s(n,-1){};

    int leader(int x){
      assert(0<=x&&x<_n);
      return _leader(x);
    }

    int size(int x){
      assert(0<=x&&x<_n);
      return -p_or_s[_leader(x)];
    }

    int merge(int x, int y){
      assert(0<=x&&x<_n);
      assert(0<=y&&y<_n);
      ll lx=_leader(x), ly=_leader(y);
      if(lx==ly) return lx;
      if(-p_or_s[lx]<-p_or_s[ly]) {
        p_or_s[ly]+=p_or_s[lx];
        p_or_s[lx] = ly;
        return ly;
      }
      else{
        p_or_s[lx]+=p_or_s[ly];
        p_or_s[ly]=lx;
        return lx;
      }
    }

    bool same(int x, int y){
      assert(0<=x&&x<_n);
      assert(0<=y&&y<_n);
      return _leader(x)==_leader(y);
    }
};
