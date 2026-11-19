#pragma once
#include "../template.hpp"

template<int sigma=26, char base='a'>
struct trie{
    trie() : cnt(1,0), node(1,init()){};
    
    vector<int> add(string& s){
        vector<int> res;
        int pos = 0;
        res.emplace_back(pos);
        for(char c : s){
            int i = c-base;
            if(node[pos][i]==-1){
                node[pos][i] = node.size();
                node.emplace_back(init());
                cnt.emplace_back(0);
            }
            pos = node[pos][i];
            cnt[pos]++;
            res.emplace_back(pos);
        }
        return res;
    }

    vector<int> track(string& s){
        vector<int> res(s.size(),-1);
        int pos = 0;
        for(int j=0; j<s.size(); j++){
            int i = s[j]-base;
            if(node[pos][i]==-1) break;
            pos = node[pos][i];
            res[j] = pos;
        }
        return res;
    }

    string lower_bound(int k){

    }

    string operator [](int k){

    }

    int lower_element(string& s){

    }

    private:
    vector<array<int,sigma>> node;
    vector<int> cnt;
    constexpr array<int,sigma> init(){
        array<int,sigma> x;
        x.fill(-1);
        return x;
    }
};

template<int depth>
struct binary_trie{
    binary_trie(){};

    int add(string& s){

    }
    int add(ll& x){
        
    }

    private:

};

using binary_trieint = binary_trie<30>;
using binary_triell = binary_trie<60>;