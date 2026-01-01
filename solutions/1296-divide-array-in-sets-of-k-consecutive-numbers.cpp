#include <vector>
#include <map>

using namespace std;

class Solution {
public:
    bool isPossibleDivide(vector<int>& nums, int k) {
        // If total elements cannot be divided into groups of k, return false immediately
        if (nums.size() % k != 0) return false;
        
        // Use a map to store frequencies. 
        // std::map keeps keys sorted, which is crucial for the greedy approach.
        map<int, int> counts;
        for (int num : nums) {
            counts[num]++;
        }
        
        // Iterate through the map. Since it's sorted, we always process the smallest available number first.
        for (auto it = counts.begin(); it != counts.end(); ++it) {
            int startNum = it->first;
            int count = it->second;
            
            // If this number has remaining instances, it must be the start of 'count' sequences
            if (count > 0) {
                // Check and decrement the next k-1 numbers
                for (int i = 1; i < k; ++i) {
                    int nextNum = startNum + i;
                    // If next number doesn't have enough instances to pair with startNum, return false
                    if (counts[nextNum] < count) {
                        return false;
                    }
                    counts[nextNum] -= count;
                }
            }
        }
        
        return true;
    }
};
