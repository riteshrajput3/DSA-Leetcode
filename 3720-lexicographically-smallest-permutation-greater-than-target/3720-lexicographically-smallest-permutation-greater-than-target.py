class Solution:
    def lexGreaterPermutation(self, s: str, target: str) -> str:
        n = len(s)

        freq = [0] * 26
        for ch in s:
            freq[ord(ch) - ord('a')] += 1

        # Match target from left to right
        matched = 0

        while matched < n:
            x = ord(target[matched]) - ord('a')

            if freq[x] == 0:
                break

            freq[x] -= 1
            matched += 1

        # Case 1:
        # We could not match target[matched].
        # Try making this position bigger.
        if matched < n:
            x = ord(target[matched]) - ord('a')

            for c in range(x + 1, 26):
                if freq[c] > 0:
                    freq[c] -= 1

                    ans = target[:matched] + chr(c + ord('a'))

                    for j in range(26):
                        ans += chr(j + ord('a')) * freq[j]

                    return ans

        # Case 2:
        # Backtrack through the matched prefix.
        for i in range(matched - 1, -1, -1):
            x = ord(target[i]) - ord('a')

            # Restore target[i]
            freq[x] += 1

            # Find the smallest character greater than target[i]
            for c in range(x + 1, 26):
                if freq[c] > 0:
                    freq[c] -= 1

                    ans = target[:i] + chr(c + ord('a'))

                    # Remaining characters in sorted order
                    for j in range(26):
                        ans += chr(j + ord('a')) * freq[j]

                    return ans

        return ""