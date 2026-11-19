#pragma once
#include "../template.hpp"

template<int sigma=26, char base='a'>
struct trie{
    trie() : node(1,init()), cnt(1,0), end(1) {}
    
    vector<int> add(const string& s){
        vector<int> res;
        int pos = 0;
        res.emplace_back(pos);
        cnt[pos]++;
        for(char ch : s){
            int c = ch-base;
            assert(0<=c && c<sigma);
            if(node[pos][c]==-1){
                node[pos][c] = node.size();
                node.emplace_back(init());
                cnt.emplace_back(0);
                end.emplace_back();
            }
            pos = node[pos][c];
            cnt[pos]++;
            res.emplace_back(pos);
        }
        end[pos].emplace_back(end_node.size());
        end_node.emplace_back(pos);
        el.emplace_back(s);
        return res;
    }

    vector<int> track(const string& s) const {
        vector<int> res(s.size(),-1);
        int pos = 0;
        for(int i=0; i<s.size(); i++){
            int c = s[i]-base;
            assert(0<=c && c<sigma);
            if(node[pos][c]==-1) break;
            pos = node[pos][c];
            res[i] = pos;
        }
        return res;
    }

    int sub_cnt(int v) const {
        return cnt[v];
    }

    int next(int v, char ch) const {
        assert(0<=v && v<node.size());
        int c = ch - base;
        assert(0<=c && c<sigma);
        return node[v][c];
    }

    string kth_element(int k) const {
        assert(0<=k && k<cnt[0]);
        string res;
        int pos = 0;
        while(true){
            if(k < end[pos].size()) return res;
            k -= end[pos].size();

            for(int i=0; i<sigma; i++){
                int to = node[pos][i];
                if(to==-1) continue;
                if(k < cnt[to]){
                    res.push_back((char)(base+i));
                    pos = to;
                    break;
                }
                k -= cnt[to];
            }
        }
    }

    string operator [](int k) const {
        assert(0<=k && k<end_node.size());
        return el[k];
    }

    int count_less(const string& s) const {
        return count_bound(s,false);
    }

    int count_lesseq(const string& s) const {
        return count_bound(s,true);
    }

    //preをprefixに持つ文字列の数
    int count_prefix(const string& pre) const {
        int pos = 0;
        for(char ch : pre){
            int c = ch - base;
            if(c<0 || c>=sigma) return 0;
            pos = node[pos][c];
            if(pos == -1) return 0;
        }
        return cnt[pos];
    }

    //この文字列のprefixであるような文字列の数
    int prefix_count(const string& s) const{
        int pos = 0, res = 0;
        res += end[pos].size();
        for(char ch : s){
            int c = ch - base;
            if(c<0 || c>=sigma) return res;
            pos = node[pos][c];
            if(pos == -1) return res;
            res += end[pos].size();
        }
        return res;
    }

    //キーsの内最後のものを消去する
    bool erase(const string& s){
        auto path = track(s);
        int v = path.empty() ? 0 : path.back();
        if(v == -1 || end[v].empty()) return false;

        int id = end[v].back();
        end[v].pop_back();
        end_node[id] = -1;

        cnt[0]--;
        for(int u : path) cnt[u]--;
        return true;
    }

    private:
    vector<array<int,sigma>> node;
    vector<int> cnt,end_node;
    vector<vector<int>> end;
    vector<string> el;
    constexpr array<int,sigma> init(){
        array<int,sigma> x;
        x.fill(-1);
        return x;
    }

    int count_bound(const string& s, bool in) const {
        int pos = 0, res = 0;
        for(char ch : s){
            res += end[pos].size();
            int c = ch - base;
            if(c<0) return res;
            for(int j=0; j<c && j<sigma; j++){
                int to = node[pos][j];
                if(to != -1) res += cnt[to];
            }
            if(c>=sigma) return res;
            pos = node[pos][c];
            if(pos == -1) return res;
        }
        if(in) res += end[pos].size();
        return res;
    }
};

template<int depth>
struct binary_trie{
    vector<int> add(const string& s) {
        return tr.add(to_fixed_bits(s));
    }

    vector<int> add(const ull& x) {
        return tr.add(to_fixed_bits(x));
    }

    bool erase(const string& s){
        return tr.erase(to_fixed_bits(s));
    }

    bool erase(const ull& x){
        return tr.erase(to_fixed_bits(x));
    }

    int sub_cnt(int v) const {
        return tr.sub_cnt(v);
    }

    int next(int v, char ch) const {
        return tr.next(v,ch);
    }

    string operator [] (int k) const {
        return tr[k];
    }

    int count_prefix(const string& pre) const {
        return tr.count_prefix(pre);
    }

    int count_less(const string& s){
        return tr.count_less(to_fixed_bits(s));
    }

    int count_less(const ull& x){
        return tr.count_less(to_fixed_bits(x));
    }

    int count_lesseq(const string& s){
        return tr.count_lesseq(to_fixed_bits(s));
    }

    int count_lesseq(const ull& x){
        return tr.count_lesseq(to_fixed_bits(x));
    }

    string kth_element(int k) const {
        return tr.kth_element(k);
    }


    private:
    trie<2,'0'> tr;

    static string to_fixed_bits(const string& s){
        assert(s.size() <= depth);
        return string(depth - s.size(), '0') + s;
    }
    static string to_fixed_bits(const ull& x){
        assert((x >> (depth-1)) <= 1);
        string res;
        for(int i=depth-1; i>=0; i--){
            res += ((x>>i)&1) ? '1' : '0';
        }
        return res;
    }
};

using binary_trieint = binary_trie<30>;
using binary_triell = binary_trie<60>;