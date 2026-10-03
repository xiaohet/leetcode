#include <iostream>
#include <string>
using namespace std;
 
int longestValidParentheses(string s) {
    int n = s.size();
    int max = 0;
    int count = 0;
    int cur = 0;
    int curStart = n;
    int lastZero = -1;
    for(int i = 0; i < n; i++){
        if(s[i] == '('){
            if(count == 0 && curStart == n)
                curStart = i;
            count++;
        }
        else if(s[i] == ')'){
            if(count > 0){
                count--;
                if(count == 0){
                    lastZero = i;
                }
            }
            else{
                if(lastZero - curStart + 1 > max)
                    max = lastZero - curStart + 1;
                curStart = n;
                lastZero = -1;
            }
        }
    }
    if(lastZero - curStart + 1 > max){
        max = lastZero - curStart + 1;
    }
    if(curStart < n && count > 0){
        count = 0;
        int curEnd = curStart - 1;
        int firstZero = n;
        for(int i = n-1; i >= curStart; i--){
            if(s[i] == '('){
                if(count > 0){
                    count--;
                    if(count == 0){
                        firstZero = i;
                    }
                }
                else{
                    if(curEnd - firstZero + 1 > max)
                        max = curEnd - firstZero + 1;
                    curEnd = curStart - 1;
                    firstZero = n;
                }
            }
            else if(s[i] == ')'){
                if(count == 0 && curEnd == curStart - 1)
                    curEnd = i;
                count++;
            }
        }
    }
    return max;
}

int main(){
    string s = "))((((()(";
    int res = longestValidParentheses(s);
    cout << "res: " << res << endl;
    return 0;
}