struct DiGraph{
    int n;
    vector<vector<int>> g, gt;
    DiGraph() {}
    DiGraph(int n) : n(n), g(n), gt(n) {}
    void add_edge(int u,int v){
        g[u].push_back(v);
        gt[v].push_back(u);
    }
private:
    vector<int> _ts;
    vector<uint8_t> _ts_vis;
    void _ts_dfs(int u){
        _ts_vis[u] = 1;
        for(auto &v : g[u]){
            if(_ts_vis[v]) continue;
            _ts_dfs(v);
        }
        _ts.push_back(u);
    }
public:
    vector<int> topological_sort(){
        _ts_vis.assign(n, 0);
        _ts.assign(0, 0);
        _ts.reserve(n);
        for(int i=0;i<n;i++) if(!_ts_vis[i]) _ts_dfs(i);
        reverse(_ts.begin(), _ts.end());
        return std::move(_ts);
    }
private:
    vector<int> _scc_label;
    int scc_count = 0;
    void _scc_dfs(int u){
        _scc_label[u] = scc_count;
        for(auto &v : gt[u]){
            if(_scc_label[v] != -1) continue;
            _scc_dfs(v);
        }
    }
public:
    pair<DiGraph, vector<int>> decompose_scc(){
        _scc_label.assign(n, -1);
        vector<int> ord = topological_sort();
        for(auto &v : ord) if(_scc_label[v] == -1){
                _scc_dfs(v);
                ++scc_count;
            }
        DiGraph scc_graph(scc_count);
        for(int i=0;i<n;i++){
            for(auto &v : g[i]) if(_scc_label[i] != _scc_label[v])
                    scc_graph.add_edge(_scc_label[i], _scc_label[v]);
        }
        return pair(std::move(scc_graph), std::move(_scc_label));
    }
    vector<int>& operator[](int u){
        return g[u];
    }
    vector<int>& operator()(int u){
        return gt[u];
    }
    int size(){
        return n;
    }
