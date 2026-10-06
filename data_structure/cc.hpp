template<class T>
struct Compressor{
    vector<T> xs;
    vector<int> compressed;

    Compressor(const vector<T>&a) : xs(a){
        sort(xs.begin(),xs.end());
        xs.erase(unique(xs.begin(),xs.end()),xs.end());

        compressed.reserve(a.size());
        for(const T&x : a){
            compressed.push_back(
                lower_bound(xs.begin(),xs.end(),x) - xs.begin()
            );
        }
    }

    int index(const T& x) const{
        return lower_bound(xs.begin(),xs.end(),x) - xs.begin();
    }

    const T& value(int i) const{
        return xs[i];
    }

    int size() const{
        return xs.size();
    }
};