#pragma once
#include "../template.hpp"

template<int sigma = 26, char base = 'a'>
struct aho_corasick{
    aho_corasick() : built(false), nodes(1) {}

    vector<int> add(const string& s) {
        assert(!built);
        vector<int> res;
        int pos = 0;
        for(char ch : s){
            int c = ch - base;
            assert(0<=c && c<sigma);
            if(nodes[pos].child[c] == -1){
                nodes[pos].child[c] = nodes.size();
                nodes.emplace_back();
                nodes[nodes[pos].child[c]].par = pos;
            }
            pos = nodes[pos].child[c];
            res.emplace_back(pos);
        }
        nodes[pos].cnt++;
        nodes[pos].end.emplace_back(end_node.size());
        end_node.emplace_back(pos);
        el.emplace_back(s);
        return res;
    }

    void build(){
        if(built) return;

        queue<int> q;
        nodes[0].link = -1;

        for(int c=0; c<sigma; c++){
            int to = nodes[0].child[c];
            if(to == -1){
                nodes[0].accept[c] = 0;
            }
            else{
                nodes[0].accept[c] = to;
                nodes[to].link = 0;
                q.emplace(to);
            }
        }

        while(!q.empty()){
            int v = q.front();
            q.pop();

            int link = nodes[v].link;
            nodes[v].cnt += nodes[link].cnt;
            for(int c=0; c<sigma; c++){
                int to = nodes[v].child[c];
                if(to == -1){
                    nodes[v].accept[c] = nodes[link].accept[c];
                }
                else{
                    nodes[v].accept[c] = to;
                    nodes[to].link = nodes[link].accept[c];
                    q.emplace(to);
                }
            }
        }

        built = true;
    }

    ll count(const string& s) const {
        assert(built);
        int pos = 0;
        ll res = nodes[0].cnt;
        for(auto ch : s){
            int c = ch - base;
            assert(0<=c && c<sigma);
            pos = nodes[pos].accept[c];
            res += nodes[pos].cnt;
        }
        return res;
    }

    int state_cnt() const {
        return nodes.size();
    }

    int par(int v) const {
        assert(0<=v && v<state_cnt());
        return nodes[v].par;
    }

    int next(int v, char ch) const {
        assert(built);
        assert(0<=v && v<state_cnt());
        int c = ch - base;
        assert(0<=c && c<sigma);
        return nodes[v].accept[c];
    }

    int link(int v) const {
        assert(built);
        assert(0<=v && v<state_cnt());
        return nodes[v].link;
    }

    int match_cnt(int v) const {
        assert(built);
        assert(0<=v && v<state_cnt());
        return nodes[v].cnt;
    }

    string operator [](int k) const {
        assert(0<=k && k<end_node.size());
        return el[k];
    }

    int last(int k) const {
        assert(0<=k && k<end_node.size());
        return end_node[k];
    }

    vector<int> ends(int v) const {
        assert(0<=v && v<state_cnt());
        return nodes[v].end;
    }

    private:
    struct Node{
        array<int,sigma> child,accept;
        int par = -1, cnt = 0, link = -1;
        vector<int> end;
        Node() {child.fill(-1); }
    };
    bool built;
    vector<Node> nodes;
    vector<int> end_node;
    vector<string> el;
};