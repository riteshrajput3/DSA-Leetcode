from typing import List

class Solution:
    def uniqueXorTriplets(self, nums: List[int]) -> int:
        values = list(set(nums))
        MAXX = 2048

        dp = [False] * MAXX
        dp[0] = True

        for _ in range(3):
            ndp = [False] * MAXX
            for x in range(MAXX):
                if dp[x]:
                    for v in values:
                        ndp[x ^ v] = True
            dp = ndp

        return sum(dp)