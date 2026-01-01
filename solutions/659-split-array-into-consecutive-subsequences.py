from collections import Counter, defaultdict

class Solution:
    def isPossible(self, nums: list[int]) -> bool:
        # Frequency map to count occurrences of each number
        freq = Counter(nums)
        
        # Need map to store the "demand" for the next number in a sequence
        # need[x] means there is a sequence ending at x-1 that needs x to continue
        need = defaultdict(int)
        
        for num in nums:
            if freq[num] == 0:
                continue
            
            # Case 1: If this number can extend an existing sequence
            if need[num] > 0:
                need[num] -= 1
                need[num + 1] += 1
                freq[num] -= 1
            
            # Case 2: If we can start a new sequence of length at least 3 (num, num+1, num+2)
            elif freq[num + 1] > 0 and freq[num + 2] > 0:
                freq[num] -= 1
                freq[num + 1] -= 1
                freq[num + 2] -= 1
                need[num + 3] += 1
            
            # Case 3: Cannot extend or start a new sequence
            else:
                return False
                
        return True
