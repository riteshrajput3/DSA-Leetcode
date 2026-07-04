class Solution {
public:
    int findMaxPathScore(vector<vector<int>>& edges, vector<bool>& online, long long k) {
        int n = online.size();

        vector<vector<pair<int,int>>> g(n);
        vector<int> indeg(n);
        int hi = 0;

        for (auto &e : edges) {
            g[e[0]].push_back({e[1], e[2]});
            indeg[e[1]]++;
            hi = max(hi, e[2]);
        }

        // Topological order
        vector<int> topo;
        queue<int> q;
        for (int i = 0; i < n; i++)
            if (indeg[i] == 0) q.push(i);

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            topo.push_back(u);
            for (auto &[v, w] : g[u])
                if (--indeg[v] == 0)
                    q.push(v);
        }

        auto check = [&](int x) {
            const long long INF = 4e18;
            vector<long long> dp(n, INF);
            dp[0] = 0;

            for (int u : topo) {
                if (dp[u] == INF) continue;
                if (u != 0 && u != n - 1 && !online[u]) continue;

                for (auto &[v, w] : g[u]) {
                    if (w < x) continue;
                    if (v != n - 1 && !online[v]) continue;
                    dp[v] = min(dp[v], dp[u] + w);
                }
            }
            return dp[n - 1] <= k;
        };

        if (!check(0)) return -1;

        int lo = 0;
        while (lo < hi) {
            int mid = (lo + hi + 1) / 2;
            if (check(mid))
                lo = mid;
            else
                hi = mid - 1;
        }

        return lo;
    }
};