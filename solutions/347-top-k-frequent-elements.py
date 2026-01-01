from collections import Counter
import heapq

class Solution:
    def topKFrequent(self, nums: list[int], k: int) -> list[int]:
        # 1. Count frequencies: O(N)
        count = Counter(nums)
        
        # 2. Use a heap to find the k most frequent elements: O(N log K)
        # heapq.nlargest maintains a heap of size k
        # It compares elements based on the count (second element of tuple if we passed tuples, 
        # but here we can pass a key)
        return heapq.nlargest(k, count.keys(), key=count.get)
        
        # Alternative one-liner using Counter's built-in method (also O(N log K)):
        # return [item for item, freq in count.most_common(k)]
