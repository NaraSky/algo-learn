#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
  public:
    vector<int> twoSum(vector<int> &nums, int target) {
        int n = nums.size();
        // Step 1: 初始化一个索引数组 `ind`，用于存储 `nums`
        // 数组中每个元素的原始索引
        vector<int> ind(n);
        for (int i = 0; i < n; i++) {
            ind[i] = i;
        }

        // Step 2: 对索引数组 `ind` 进行排序，使其按 `nums`
        // 数组中的数值从小到大排列 使用自定义排序函数，这里通过 lambda
        // 表达式指定排序依据
        sort(nums.begin(), nums.end(),
             [&](int i, int j) -> bool { return nums[i] < nums[j]; });

        // Step 3: 使用双指针初始化，分别指向排序后索引数组的最小和最大值
        int p1 = 0, p2 = n - 1;

        // Step 4: 移动双指针，查找满足和为 `target` 的两个数
        // 只要两数之和不等于 target，继续移动指针
        while (nums[p1] + nums[p2] != target) {
            if (nums[p1] + nums[p2] < target) {
                p1++;
            } else {
                p2++;
            }
        }

        // Step 5: 当找到满足条件的两个数时，记录它们的原始索引并返回
        vector<int> ret(2);
        ret[0] = nums[p1];
        ret[1] = nums[p2];

        // 保证返回的索引是从小到大排列
        if (nums[0] > nums[1]) {
            swap(ret[0], ret[1]);
        }
        return ret;
    }
};

int main() {
    Solution solution;
    vector<int> nums = {2, 7, 11, 15};
    int target = 9;

    vector<int> result = solution.twoSum(nums, target);
    cout << "Indices of the numbers that add up to " << target << " are: ";
    cout << result[0] << " and " << result[1] << endl;

    return 0;
}
