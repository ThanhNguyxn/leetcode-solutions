class Solution:
    def maxScoreIndices(self, nums: list[int]) -> list[int]:
        # Initial score at index 0: 0 zeros on left + all ones on right
        current_score = sum(nums)
        max_score = current_score
        res = [0]
        
        # Iterate through the array to calculate score at each division point
        # If nums[i] == 0: left_zeros increases -> score increases by 1
        # If nums[i] == 1: right_ones decreases -> score decreases by 1
        for i, num in enumerate(nums):
            if num == 0:
                current_score += 1
            else:
                current_score -= 1
            
            if current_score > max_score:
                max_score = current_score
                res = [i + 1]
            elif current_score == max_score:
                res.append(i + 1)
                
        return res
