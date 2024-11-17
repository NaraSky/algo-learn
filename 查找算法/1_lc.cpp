#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
  public:
    vector<int> twoSum(vector<int> &nums, int target) {
        unordered_map<int, int> h; // 哈希表，用于存储元素值和对应的索引
        vector<int> ret(2); // 存储结果的向量，大小为 2，用于返回两个元素的索引

        // 遍历数组中的每个元素
        for (int i = 0; i < nums.size(); i++) {
            // 判断当前元素 nums[i] 对应的目标值 target - nums[i]
            // 是否已经出现在哈希表中
            if (h.find(target - nums[i]) != h.end()) {
                // 如果找到了目标值，返回该值对应的索引和当前元素的索引
                ret[0] = h[target - nums[i]]; // 找到的目标值的索引
                ret[1] = i;                   // 当前元素的索引
                break;                        // 找到答案后立即退出循环
            }
            // 如果没有找到目标值，将当前元素值和索引存入哈希表中
            h[nums[i]] = i;
        }

        // 返回存储结果的向量 ret，包含了两个索引
        return ret;
    }
};

int main() {
    Solution solution;                 // 创建一个 Solution 对象
    vector<int> nums = {2, 7, 11, 15}; // 示例输入数组
    int target = 9;                    // 目标值

    // 调用 twoSum 方法查找符合条件的两个数的索引
    vector<int> result = solution.twoSum(nums, target);

    // 输出结果
    cout << "Output: [" << result[0] << ", " << result[1] << "]" << endl;

    return 0;
}
