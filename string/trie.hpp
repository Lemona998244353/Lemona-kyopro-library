#pragma once
#include "../template.hpp"

template<int sigma=26, char base='a'>
struct trie{
    trie() : nodes(1) {}
    
    vector<int> add(const string& s){
        vector<int> res;
        int pos = 0;
        res.emplace_back(pos);
        nodes[pos].cnt++;
        for(char ch : s){
            int c = ch-base;
            assert(0<=c && c<sigma);
            if(nodes[pos].child[c]==-1){
                nodes[pos].child[c] = nodes.size();
                nodes.emplace_back();
                nodes[nodes[pos].child[c]].par = pos;
            }
            pos = nodes[pos].child[c];
            nodes[pos].cnt++;
            res.emplace_back(pos);
        }
        nodes[pos].end.emplace_back(end_node.size());
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
            if(nodes[pos].child[c]==-1) break;
            pos = nodes[pos].child[c];
            res[i] = pos;
        }
        return res;
    }

    int sub_cnt(int v) const {
        return nodes[v].cnt;
    }

    int next(int v, char ch) const {
        assert(0<=v && v<nodes.size());
        int c = ch - base;
        assert(0<=c && c<sigma);
        return nodes[v].child[c];
    }

    int parent(int v) const {
        asser(0<=v && v<nodes.size());
        return nodes[v].par;
    }

    string kth_element(int k) const {
        assert(0<=k && k<nodes[0].cnt);
        string res;
        int pos = 0;
        while(true){
            if(k < nodes[pos].end.size()) return res;
            k -= nodes[pos].end.size();

            for(int i=0; i<sigma; i++){
                int to = nodes[pos].child[i];
                if(to==-1) continue;
                if(k < nodes[to].cnt){
                    res.push_back((char)(base+i));
                    pos = to;
                    break;
                }
                k -= nodes[to].cnt;
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
            pos = nodes[pos].child[c];
            if(pos == -1) return 0;
        }
        return nodes[pos].cnt;
    }

    //この文字列のprefixであるような文字列の数
    int prefix_count(const string& s) const{
        int pos = 0, res = 0;
        res += nodes[pos].end.size();
        for(char ch : s){
            int c = ch - base;
            if(c<0 || c>=sigma) return res;
            pos = nodes[pos].child[c];
            if(pos == -1) return res;
            res += nodes[pos].end.size();
        }
        return res;
    }

    //キーsの内最後のものを消去する
    bool erase(const string& s){
        auto path = track(s);
        int v = path.empty() ? 0 : path.back();
        if(v == -1 || nodes[v].end.empty()) return false;

        int id = nodes[v].end.back();
        nodes[v].end.pop_back();
        end_node[id] = -1;

        nodes[0].cnt--;
        for(int u : path) nodes[u].cnt--;
        return true;
    }

    private:
    struct Node {
        array<int, sigma> child;
        int par = -1;
        int cnt = 0;
        vector<int> end;
        Node() { child.fill(-1); }
    };
    vector<Node> nodes;
    vector<int> end_node;
    vector<string> el;    

    int count_bound(const string& s, bool in) const {
        int pos = 0, res = 0;
        for(char ch : s){
            res += nodes[pos].end.size();
            int c = ch - base;
            if(c<0) return res;
            for(int j=0; j<c && j<sigma; j++){
                int to = nodes[pos].child[j];
                if(to != -1) res += nodes[to].cnt;
            }
            if(c>=sigma) return res;
            pos = nodes[pos].child[c];
            if(pos == -1) return res;
        }
        if(in) res += nodes[pos].end.size();
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