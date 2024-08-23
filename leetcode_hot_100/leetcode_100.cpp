#include <vector>
#include <iostream>
#include <sstream>


using namespace std;

class leetcode {
public:
    vector<int> twoSum(vector<int> nums, int target) {
        int n = nums.size();
        for (int i = 0; i <= n; i++) {
            for (int j = i + 1; i <= n; j++) {
                if (nums[i] + nums[j] == target)
                    return {i, j};
            }
        }
        return {};
    }
};
string a2s(vector<int> arr) {
    ostringstream tmp;
    for (int i: arr)
        tmp << i << " ";
    return tmp.str();
}

int main() {
    vector<int> nums = {1,2,3,4}; int target = 4;
    leetcode l = *new leetcode();
    cout << a2s(l.twoSum(nums, 4));
}