class Solution {
    using ll = long long;
    const ll MOD = 1e9 + 7;

    using Mat = vector<vector<ll>>;

    Mat mul(Mat &A, Mat &B) {
        int n = A.size();
        Mat C(n, vector<ll>(n));
        for (int i = 0; i < n; i++)
            for (int k = 0; k < n; k++) if (A[i][k])
                for (int j = 0; j < n; j++)
                    C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
        return C;
    }

    Mat pw(Mat A, long long p) {
        int n = A.size();
        Mat R(n, vector<ll>(n));
        for (int i = 0; i < n; i++) R[i][i] = 1;
        while (p) {
            if (p & 1) R = mul(R, A);
            A = mul(A, A);
            p >>= 1;
        }
        return R;
    }

public:
    int zigZagArrays(long long n, int l, int r) {
        int m = r - l + 1, S = 2 * m;
        if (n == 1) return m;

        vector<ll> v(S);
        for (int i = 0; i < m; i++)
            v[i] = m - 1 - i, v[m + i] = i;

        if (n == 2) {
            ll ans = 0;
            for (ll x : v) ans = (ans + x) % MOD;
            return ans;
        }

        Mat T(S, vector<ll>(S));
        for (int i = 0; i < m; i++) {
            for (int j = i + 1; j < m; j++) T[i][m + j] = 1;
            for (int j = 0; j < i; j++) T[m + i][j] = 1;
        }

        Mat P = pw(T, n - 2);
        ll ans = 0;

        for (int i = 0; i < S; i++) {
            ll cur = 0;
            for (int j = 0; j < S; j++)
                cur = (cur + P[i][j] * v[j]) % MOD;
            ans = (ans + cur) % MOD;
        }
        return ans;
    }
};