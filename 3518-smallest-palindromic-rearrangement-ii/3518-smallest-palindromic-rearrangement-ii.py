from typing import List
from math import gcd

class Solution:
    def smallestPalindrome(self, s: str, k: int) -> str:
        cnt = [0] * 26
        for ch in s:
            cnt[ord(ch) - 97] += 1

        half = [c // 2 for c in cnt]
        mid = ""
        for i in range(26):
            if cnt[i] & 1:
                mid = chr(i + 97)
                break

        CAP = k

        def comb_cap(n: int, r: int, cap: int) -> int:
            r = min(r, n - r)
            res = 1
            for i in range(1, r + 1):
                num = n - r + i
                den = i

                g = gcd(num, den)
                num //= g
                den //= g

                g = gcd(res, den)
                res //= g
                den //= g

                res *= num
                if den != 1:
                    res //= den

                if res >= cap:
                    return cap
            return res

        def ways(counts: List[int]) -> int:
            rem = sum(counts)
            ans = 1
            for c in counts:
                if c:
                    ans *= comb_cap(rem, c, CAP)
                    if ans >= CAP:
                        return CAP
                    rem -= c
            return ans

        if ways(half) < k:
            return ""

        first = []

        for _ in range(sum(half)):
            for i in range(26):
                if half[i] == 0:
                    continue
                half[i] -= 1
                w = ways(half)
                if w >= k:
                    first.append(chr(i + 97))
                    break
                k -= w
                half[i] += 1

        left = "".join(first)
        return left + mid + left[::-1]