#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
4. 寻找两个正序数组的中位数
给定两个大小为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。

请你找出这两个正序数组的中位数，并且要求算法的时间复杂度为 O(log(m + n))。

你可以假设 nums1 和 nums2 不会同时为空。
*/

class Solution_me {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2)
    {
        //vector<int> nums;
        int temp = 0;
        int idx1 = 0, idx2 = 0, idx_new = 0;
        int len1 = nums1.size(), len2 = nums2.size();
        int len_new = len1 + len2;
        int half_len_new = len_new / 2 + 1;
        int half_values[2] = { 0 };

        while (idx1 < len1 || idx2 < len2)
        {
            temp = 0;
            if ((idx1 < len1) && (idx2 < len2))
            {
                if (nums1[idx1] <= nums2[idx2])
                {
                    //nums.push_back(nums1[idx1]);
                    temp = nums1[idx1];
                    idx1++;
                }
                else
                {
                    //nums.push_back(nums2[idx2]);
                    temp = nums2[idx2];
                    idx2++;
                }
            }
            else if ((idx1 < len1) && (idx2 >= len2))
            {
                //nums.push_back(nums1[idx1]);
                temp = nums1[idx1];
                idx1++;
            }
            else if ((idx1 >= len1) && (idx2 < len2))
            {
                //nums.push_back(nums2[idx2]);
                temp = nums2[idx2];
                idx2++;
            }

            half_values[0] = half_values[1];
            half_values[1] = temp;
            //printf("%d ", temp);

            idx_new++;

            if (idx_new >= half_len_new)
                break;
        }

        return len_new % 2 == 0 ? (half_values[0] + half_values[1]) / 2.0 : half_values[1] * 1.0;
    }
};

class Solution 
{
public:
    double findMedianSortedArrays_single(vector<int>& nums,int len)
    {
        int half = (len + 1) / 2 - 1;
        if (len % 2 == 1)
        {
            return nums[half] * 1.0;
        }
        else
        {
            return (nums[half] + nums[half + 1]) / 2.0;
        }
    }
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2)
    {
        int n = nums1.size();
        int m = nums2.size();

        if (n == 0)
            return findMedianSortedArrays_single(nums2, m);
        else if(m == 0)
            return findMedianSortedArrays_single(nums1, n);
        else if (m < n)
            return findMedianSortedArrays(nums2, nums1);

        int total = n + m; //计算全部长度
        int total_half = (total + 1) / 2;   //合成的新有序串的中位数所在位置，
                                            //因为整数除法向下取整，则[(总数+1)/2]
                                            //兼顾了奇偶个数情况下的中位数

        int left = 0;       // 规定为数组1的游标
        int right = n;

        int i = 0;          //实际访问下标
        int j = 0;
		

        while (left < right)
        {
            //printf("%d %d\t", left, right);
            i = left + (right - left + 1) / 2;      //访问数组1[left,right)的中间位置
            j = total_half - i;                     //访问数组2 对应位置



            //原本需要满足
            //nums1[left_max] <= mums2[right_min] && nums2[left_max] <= mums1[right_min]
            //因为!(nums1[left_max] <= mums2[right_min] && nums2[left_max] <= mums1[right_min]) 等同于 nums1[left_max] > mums2[right_min] || nums2[left_max] > mums1[right_min]
            //如果不满足条件“nums1[left_max] <= mums2[right_min]”既满足“nums1[left_max] > mums2[right_min]”则表示当前访问的数组1的元素偏大，所以下一次检查区域变为[left,当前位置向左移动一个)。
            //反之则确定下一次检查区域为[当前位置,right)
            //直到 检查区域全部检查完成(left >= right)
            //printf("nums1[%d] = %d\tnums2[%d] = %d\n", i - 1, nums1[i - 1], j, nums2[j]);
            if (nums1[i - 1] > nums2[j])                                 
            {
                right = i - 1;
            }
            else
            {
                left = i;
            }
        }

        i = left;
        j = total_half - left;

        int top_left_max =  i == 0 ? INT32_MIN: nums1[i-1];
        int top_right_min = i == n ? INT32_MAX : nums1[i];
        int bottom_left_max = j == 0 ? INT32_MIN : nums2[j-1];
        int bottom_right_min = j == m ? INT32_MAX : nums2[j];


        if (total % 2 == 1)
        {
            return std::max(top_left_max, bottom_left_max) * 1.0;
        }
        else
        {
            return (std::max(top_left_max, bottom_left_max) + std::min(top_right_min, bottom_right_min)) / 2.0;
        }
    }
};

int main()
{
    Solution s;
    vector<int> num1({ 3 });
    vector<int> num2({ -2,-1});
    double x = s.findMedianSortedArrays(num1, num2);
    return 0;
}