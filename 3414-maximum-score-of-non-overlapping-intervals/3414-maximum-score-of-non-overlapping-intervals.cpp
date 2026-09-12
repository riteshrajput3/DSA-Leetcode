class Solution {
public:
    struct State {
        long long score;
        vector<int> ids;
    };

    // Return true if a is lexicographically smaller than b
    bool smaller(const vector<int>& a, const vector<int>& b) {
        return a < b;
    }

    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();

        // Store: {left, right, weight, original_index}
        vector<array<long long, 4>> a;

        for (int i = 0; i < n; i++) {
            a.push_back({
                intervals[i][0],
                intervals[i][1],
                intervals[i][2],
                i
            });
        }

        // Sort by left endpoint
        sort(a.begin(), a.end(), [](const auto& x, const auto& y) {
            if (x[0] != y[0])
                return x[0] < y[0];

            if (x[1] != y[1])
                return x[1] < y[1];

            return x[3] < y[3];
        });

        // next[i] = first interval whose left > a[i].right
        vector<int> next(n);

        vector<long long> starts(n);
        for (int i = 0; i < n; i++)
            starts[i] = a[i][0];

        for (int i = 0; i < n; i++) {
            next[i] = upper_bound(
                starts.begin(),
                starts.end(),
                a[i][1]
            ) - starts.begin();
        }

        /*
            dp[i][k]:
            Best result using intervals [i ... n-1],
            with at most k intervals.
        */
        vector<vector<State>> dp(
            n + 1,
            vector<State>(5, {0, {}})
        );

        for (int i = n - 1; i >= 0; i--) {

            for (int k = 1; k <= 4; k++) {

                // Option 1: skip current interval
                State skip = dp[i + 1][k];

                // Option 2: take current interval
                State take;
                take.score = a[i][2] + dp[next[i]][k - 1].score;

                take.ids.push_back((int)a[i][3]);

                for (int id : dp[next[i]][k - 1].ids)
                    take.ids.push_back(id);

                // Lexicographical comparison must use sorted indices
                sort(take.ids.begin(), take.ids.end());

                // Select better option
                if (take.score > skip.score) {
                    dp[i][k] = take;
                }
                else if (take.score < skip.score) {
                    dp[i][k] = skip;
                }
                else {
                    // Same score -> lexicographically smallest
                    if (take.ids < skip.ids)
                        dp[i][k] = take;
                    else
                        dp[i][k] = skip;
                }
            }
        }

        return dp[0][4].ids;
    }
};