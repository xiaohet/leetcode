#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

    int maxPalindromes(string s, int k) {
        int n = s.size();
        vector<vector<int>> pstrings;
        if(k <= 1)
            return n;
        for(int i = 0; i < n - 1; i++){
            if(s[i] == s[i+1]){
                if(k <= 2)
                    pstrings.push_back({i, i+1});
                int count = 1;
                while(i-count >= 0 && i + 1 + count < n){
                    if(s[i-count] == s[i+1+count]){
                        if(k <= 2 + 2 * count) 
                            pstrings.push_back({i-count, i+1+count});
                        count++;
                    }
                    else
                        break;
                }
            }
            if(i < n - 2){
                if(s[i] == s[i+2]){
                    if(k <= 3)
                        pstrings.push_back({i, i+2});
                    int count = 1;
                    while(i-count >= 0 && i + 1 + count < n){
                        if(s[i-count] == s[i+2+count]){
                            if(k <= 3 + 2 * count) 
                                pstrings.push_back({i-count, i+2+count});
                            count++;
                        }
                        else
                            break;
                    }
                }
            }
        }
        
        int np = pstrings.size();
        if(np == 0 || np == 1)
            return np;

        sort(pstrings.begin(), pstrings.end());
        cout << "pstrings: ";
        for(vector<int> p : pstrings){
            cout << p[0] << " " << p[1] << ", ";
        }
        cout << endl;

        int count = 0;
        int prev_start = pstrings[np-1][0];

        for(int i = np - 2; i >= 0; i--){
            if(pstrings[i][1] >= prev_start)
                count++;
            else
                prev_start = pstrings[i][0];
        }
        return np - count;
    }

int main(){
    string s = "fttfjofpnpfydwdwdnns";
    int k = 2;
    int res = maxPalindromes(s, k);
    cout << "res: " << res << endl;
    return 0;
}