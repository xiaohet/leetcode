#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
    long long sum = 0;
    unordered_map<long long, long long> diffs;
    int n = nums1.size();
    int max = 0;
    
    // get diff map and initial sum
    for(int i = 0; i < n; i++){
        long long diff = (nums1[i] >= nums2[i]) ? (nums1[i] - nums2[i]) : (nums2[i] - nums1[i]);
        if(diff > max)
            max = diff;
        diffs[diff] += 1;
        sum += diff * diff;
    }

    // decrease largest number(s) k1 + k2 times
    long long k = k1 + k2;
    long long curDiff = max;
    if(k == 0)
        return sum;
    while(1){
        if(curDiff == 0)
            return sum;
        if(k <= diffs[curDiff]){
            sum -= k * (curDiff * 2 - 1);
            return sum;
        }
        else{
            sum -= diffs[curDiff] * (curDiff * 2 - 1);
            k -= diffs[curDiff];
            diffs[curDiff-1] += diffs[curDiff];
            curDiff -= 1;
        }
    }

    return sum;
}

int main(){
    vector<int> nums1 = {3, 9, 22};
    vector<int> nums2 = {11, 0, 7};
    int k1 = 6;
    int k2 = 14;
    long long res = minSumSquareDiff(nums1, nums2, k1, k2);
    cout << "res: " << res << endl;
    return 0;
}