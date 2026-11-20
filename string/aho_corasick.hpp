#pragma once
#include "../template.hpp"

template<int sigma = 26, char base = 'a'>
struct aho_corasick{
    aho_corasick() : nodes(1) {}

    vector<int> add(const string& s) {
        vector<int> res;
        int pos = 0;
        nodes[pos].cnt++;
        for(char ch : s){
            int c = ch - base;
            assert(0<=c && c<sigma);
            if(nodes[pos].child[c] == -1){
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

    void build(){
        
    }

    private:
    struct Node{
        array<int,sigma> child;
        int par = -1, cnt = 0;
        vector<int> end;
        Node() {child.fill(-1); }
    };
    vector<Node> nodes;
    vector<int> end_node;
    vector<string> el;
};