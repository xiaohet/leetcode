#include <iostream>
#include <vector>
using namespace std;


double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    if(nums1.size() < nums2.size())
        nums1.swap(nums2);
    int n1 = nums1.size();
    int n2 = nums2.size();
    bool oddFlag = ((n1 + n2) % 2 == 1) ? true : false;
    int idx11 = 0;
    int idx12 = n1;
    int idx21 = 0;
    int idx22 = n2;
    if(n2 == 0){
        int idx1 = (idx11 + idx12) / 2;
        if(oddFlag)
            return (double)(nums1[idx1]);
        else
            return (double)((nums1[idx1-1] + nums1[idx1]) / 2.0);
    }
    while(1){
        int idx1 = (idx11 + idx12) / 2;
        int idx2 = (idx21 + idx22) / 2;
        if(idx22 - idx21 == 1){
            if(idx12 - idx11 == 1)
                return (double)((nums2[idx2] + nums1[idx1]) / 2.0);
            if(oddFlag){
                if(nums2[idx2] >= nums1[idx1-1] && nums2[idx2] <= nums1[idx1])
                    return (double)(nums2[idx2]);
                else if(nums2[idx2] > nums1[idx1])
                    return (double)(nums1[idx1]);
                else
                    return (double)(nums1[idx1-1]);
            }
            else{
                if(nums2[idx2] == nums1[idx1])
                    return (double)(nums2[idx2]);
                else if(nums2[idx2] >= nums1[idx1]){
                    if(nums2[idx2] <= nums1[idx1+1])
                        return (double)((nums2[idx2] + nums1[idx1]) / 2.0);
                    else
                        return (double)((nums1[idx1] + nums1[idx1+1]) / 2.0);
                }
                else{
                    if(nums2[idx2] >= nums1[idx1-1])
                        return (double)((nums2[idx2] + nums1[idx1]) / 2.0);
                    else
                        return (double)((nums1[idx1] + nums1[idx1-1]) / 2.0);
                }
            }
        }
        else if(oddFlag){
            if((idx22 - idx21) % 2 == 1){
                if(nums2[idx2] > nums1[idx1]){
                    int newIdx22 = idx2 + 1;
                    idx11 += idx22 - newIdx22;
                    idx22 = newIdx22;
                }
                else if(nums2[idx2] < nums1[idx1-1]){
                    int newIdx21 = idx2;
                    idx12 -= newIdx21 - idx21;
                    idx21 = newIdx21;
                }
                else{ // nums2[idx2] between nums1[idx1-1] and [idx1]
                    return (double)(nums2[idx2]);
                }
            }
            else{
                if(nums2[idx2] < nums1[idx1]){
                    int newIdx21 = idx2;
                    idx12 -= newIdx21 - idx21;
                    idx21 = newIdx21;
                }
                else if(nums2[idx2-1] > nums1[idx1]){
                    int newIdx22 = idx2;
                    idx11 += idx22 - newIdx22;
                    idx22 = newIdx22;
                }
                else{
                    return (double)(nums1[idx1]);
                }
            }
        }
        else{
            if((idx22 - idx21) % 2 == 1){
                if(nums2[idx2] > nums1[idx1]){
                    int newIdx22 = idx2 + 1;
                    idx11 += idx22 - newIdx22;
                    idx22 = newIdx22;
                }
                else if(nums2[idx2] < nums1[idx1]){
                    int newIdx21 = idx2;
                    idx12 -= newIdx21 - idx21;
                    idx21 = newIdx21;
                }
                else{
                    return (double)((nums2[idx2] + nums1[idx1]) / 2.0);
                }
            }
            else{
                if(nums2[idx2-1] > nums1[idx1]){
                    int newIdx22 = idx2;
                    idx11 += idx22 - newIdx22;
                    idx22 = newIdx22;
                }
                else if(nums2[idx2] < nums1[idx1-1]){
                    int newIdx21 = idx2;
                    idx12 -= newIdx21 - idx21;
                    idx21 = newIdx21;
                }
                else{
                    int lower = max(nums2[idx2-1], nums1[idx1-1]);
                    int upper = min(nums2[idx2], nums1[idx1]);
                    return (double)((lower + upper) / 2.0);
                }
            }
        }
    }
}

int main(){
    vector<int> v1 = {1, 2, 6, 7};
    vector<int> v2 = {3, 4, 6, 12};
    double res = findMedianSortedArrays(v1, v2);
    cout << "res: " << res << endl;
    return 0;
}