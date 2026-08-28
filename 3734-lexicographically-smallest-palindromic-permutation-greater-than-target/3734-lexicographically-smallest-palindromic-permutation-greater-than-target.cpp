class Solution {
public:
    string lexPalindromicPermutation(string s, string target) {
        int n = s.size();
        int m = n / 2;

        // Count characters in s
        vector<int> freq(26, 0);
        for (char c : s) {
            freq[c - 'a']++;
        }

        // Check whether palindrome is possible
        int odd = 0;
        int mid = -1;

        for (int i = 0; i < 26; i++) {
            if (freq[i] % 2) {
                odd++;
                mid = i;
            }
        }

        if (odd > 1) {
            return "";
        }

        // Characters available in the left half
        vector<int> half(26, 0);
        for (int i = 0; i < 26; i++) {
            half[i] = freq[i] / 2;
        }

        // Build palindrome from left half
        auto build = [&](const string& left) {
            string ans = left;

            if (n % 2) {
                ans += char('a' + mid);
            }

            for (int i = m - 1; i >= 0; i--) {
                ans += left[i];
            }

            return ans;
        };

        string t = target.substr(0, m);

        /*
         * ---------------------------------------------------------
         * STEP 1:
         * Check whether t itself can be the left half.
         * ---------------------------------------------------------
         */

        vector<int> cnt = half;
        bool canEqual = true;

        for (char c : t) {
            if (cnt[c - 'a'] == 0) {
                canEqual = false;
                break;
            }

            cnt[c - 'a']--;
        }

        if (canEqual) {
            string candidate = build(t);

            if (candidate > target) {
                return candidate;
            }
        }

        /*
         * ---------------------------------------------------------
         * STEP 2:
         * Find the smallest permutation of half that is
         * lexicographically GREATER than t.
         *
         * This is basically "next permutation", but with
         * duplicate characters.
         * ---------------------------------------------------------
         */

        /*
         * We try the rightmost possible position as the point
         * where we make the string larger.
         */
        for (int pos = m - 1; pos >= 0; pos--) {

            // Characters required for t[0 ... pos-1]
            vector<int> remaining = half;
            bool possible = true;

            for (int i = 0; i < pos; i++) {
                int c = t[i] - 'a';

                if (remaining[c] == 0) {
                    possible = false;
                    break;
                }

                remaining[c]--;
            }

            if (!possible) {
                continue;
            }

            /*
             * At pos, choose the smallest character strictly
             * greater than t[pos].
             */
            int tc = t[pos] - 'a';

            for (int c = tc + 1; c < 26; c++) {

                if (remaining[c] == 0) {
                    continue;
                }

                string left;

                // Prefix equal to target
                for (int i = 0; i < pos; i++) {
                    left += t[i];
                }

                // Make this position larger
                left += char('a' + c);
                remaining[c]--;

                // Fill remaining positions as small as possible
                for (int x = 0; x < 26; x++) {
                    while (remaining[x] > 0) {
                        left += char('a' + x);
                        remaining[x]--;
                    }
                }

                return build(left);
            }
        }

        return "";
    }
};