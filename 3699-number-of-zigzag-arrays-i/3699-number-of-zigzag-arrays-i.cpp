class Solution {
public:
    static constexpr long long MOD = 1000000007LL;

    int zigZagArrays(int n, int l, int r) {
        int m = r - l + 1;

        vector<long long> up(m + 1), down(m + 1);

        // Length = 2
        for (int v = 1; v <= m; v++) {
            up[v] = v - 1;
            down[v] = m - v;
        }

        for (int len = 3; len <= n; len++) {
            vector<long long> newUp(m + 1), newDown(m + 1);

            // prefix sums of down
            long long pref = 0;
            for (int v = 1; v <= m; v++) {
                newUp[v] = pref;
                pref = (pref + down[v]) % MOD;
            }

            // suffix sums of up
            long long suff = 0;
            for (int v = m; v >= 1; v--) {
                newDown[v] = suff;
                suff = (suff + up[v]) % MOD;
            }

            up.swap(newUp);
            down.swap(newDown);
        }

        long long ans = 0;

        if (n == 2) {
            for (int v = 1; v <= m; v++) {
                ans = (ans + up[v] + down[v]) % MOD;
            }
            return (int)ans;
        }

        for (int v = 1; v <= m; v++) {
            ans = (ans + up[v] + down[v]) % MOD;
        }

        return (int)ans;
    }
};