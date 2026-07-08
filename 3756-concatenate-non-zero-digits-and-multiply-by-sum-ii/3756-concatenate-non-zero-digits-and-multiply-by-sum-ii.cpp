class Solution {
public:
    static const int MOD = 1e9 + 7;

    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        vector<int> pos, d;

        for (int i = 0; i < s.size(); i++) {
            if (s[i] != '0') {
                pos.push_back(i);
                d.push_back(s[i] - '0');
            }
        }

        int n = d.size();

        vector<long long> pow10(n + 1, 1), prefVal(n + 1, 0), prefSum(n + 1, 0);

        for (int i = 1; i <= n; i++)
            pow10[i] = pow10[i - 1] * 10 % MOD;

        for (int i = 0; i < n; i++) {
            prefVal[i + 1] = (prefVal[i] * 10 + d[i]) % MOD;
            prefSum[i + 1] = prefSum[i] + d[i];
        }

        vector<int> ans;

        for (auto &q : queries) {
            int l = q[0], r = q[1];

            int L = lower_bound(pos.begin(), pos.end(), l) - pos.begin();
            int R = upper_bound(pos.begin(), pos.end(), r) - pos.begin() - 1;

            if (L > R) {
                ans.push_back(0);
                continue;
            }

            int k = R - L + 1;

            long long x = (prefVal[R + 1] - prefVal[L] * pow10[k]) % MOD;
            x = (x % MOD + MOD) % MOD;

            long long sum = prefSum[R + 1] - prefSum[L];

            ans.push_back((x * sum) % MOD);
        }

        return ans;
    }
};