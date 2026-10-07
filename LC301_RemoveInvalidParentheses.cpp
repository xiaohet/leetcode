#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

vector<vector<int>> allPos;
vector<int> tempPos = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

void makePos(vector<int>& idxs, vector<int>& eraseIdx, int depth, int lastIdx){
    if(eraseIdx.empty())
        return;
    if(depth < eraseIdx.size()){
        for(int i = lastIdx; i < eraseIdx[depth] + 1; i++){
            tempPos[depth] = idxs[i];
            makePos(idxs, eraseIdx, depth+1, i+1);
        }
    }
    else if(depth == eraseIdx.size()){
        vector<int> resPos(tempPos.begin(), tempPos.begin() + depth);
        allPos.push_back(resPos);
    }
}

string deleteChars(string s, vector<int> pos){
    int n = pos.size();
    sort(pos.begin(), pos.end());
    for(int i = n - 1; i >= 0; i--){
        s.erase(pos[i], 1);
    }
    return s;
}

vector<string> removeInvalidParentheses(string s) {
    vector<string> res;
    int n = s.size();
    int idx = 0;
    // remove all first right brackets
    while(s[idx] != '('){
        idx = s.find_first_of("()");
        if(idx == string::npos)
            return {s};
        else if(s[idx] == ')'){
            s.erase(idx, 1);
        }
    }
    // remove all last left brackets
    idx = n - 1;
    while(s[idx] != ')'){
        idx = s.find_last_of("()");
        if(idx == string::npos)
            return {s};
        else if(s[idx] == '('){
            s.erase(idx, 1);
        }
    }
    // count # of right and left brackets to remove
    idx = 0;
    int count = 0;
    vector<int> leftIdx;
    vector<int> rightIdx;
    vector<int> rightEraseIdx;
    vector<int> leftEraseIdx;
    int maxRight = 0;
    int maxLeft = 0;
    for(int i = 0; i < n; i++){
        if(s[i] == '(')
            count++;
        else if(s[i] == ')'){
            count--;
            rightIdx.push_back(i);
            if(count < 0 && count < -maxRight){
                maxRight = -count;
                rightEraseIdx.push_back(rightIdx.size() - 1);
            }
        }
    }
    count = 0;
    for(int i = n - 1; i >= 0; i--){
        if(s[i] == ')')
            count++;
        else if(s[i] == '('){
            count--;
            leftIdx.push_back(i);
            if(count < 0 && count < -maxLeft){
                maxLeft = -count;
                leftEraseIdx.push_back(leftIdx.size() - 1);
            }
        }
    }
    makePos(leftIdx, leftEraseIdx, 0, 0);
    vector<vector<int>> leftPos = allPos;
    allPos.clear();
    tempPos = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    makePos(rightIdx, rightEraseIdx, 0, 0);
    if(leftPos.empty()){
        if(allPos.empty())
            return {s};
        else{
            for(vector<int> pos : allPos){
                string removed = deleteChars(s, pos);
                if(find(res.begin(), res.end(), removed) == res.end())
                    res.push_back(removed);
            }
        }
    }
    else{
        if(allPos.empty()){
            for(vector<int> pos : leftPos){
                string removed = deleteChars(s, pos);
                if(find(res.begin(), res.end(), removed) == res.end())
                    res.push_back(removed);
            }
        }
        else{
            for(vector<int> pos1 : leftPos){
                for(vector<int> pos2 : allPos){
                    vector<int> thisPos = pos1;
                    thisPos.insert(thisPos.end(), pos2.begin(), pos2.end());
                    string removed = deleteChars(s, thisPos);
                    if(find(res.begin(), res.end(), removed) == res.end())
                        res.push_back(removed);
                }
            }
        }
    }
    return res;
}

int main(){
    string s = "())))m))ab(c(((())";
    vector<string> res = removeInvalidParentheses(s);
    cout << "res: ";
    for(string r : res)
        cout << r << " ";
    cout << endl;
    return 0;
}