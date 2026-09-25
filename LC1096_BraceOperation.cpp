#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;


    vector<string> multiplyStrings(vector<string> str1, vector<string> str2){
        vector<string> res;
        
        auto it = find(str1.begin(), str1.end(), "");
        while(it != str1.end()){
            str1.erase(it);
            it = find(it, str1.end(), "");
        }
            
        it = find(str2.begin(), str2.end(), "");
        while(it != str2.end()){
            str2.erase(it);
            it = find(it, str2.end(), "");
        }

        for(string s1 : str1){
            for(string s2 : str2){
                string s = s1 + s2;
                if(find(res.begin(), res.end(), s) == res.end()){
                    res.push_back(s);
                }
            }
        }
        return res;
    }

    vector<string> resolveStrings(vector<string> str1, vector<string> str2){
        vector<string> res = str1;
        for(string s2 : str2){
            if(find(res.begin(), res.end(), s2) == res.end())
                res.push_back(s2);
        }
        auto it = find(res.begin(), res.end(), "");
        if(it != res.end())
            res.erase(it);
        return res;
    }

    bool isLetter(char ch){
        if(ch >= 'a' && ch <= 'z')
            return true;
        return false;
    }

    vector<string> braceExpansionII(string expression) {
        int n = expression.size();
        vector<vector<string>> words = {{""}};
        vector<vector<string>> multiWords = {{""}};
        int braceLevel = 0;
        vector<int> braceIdx(32, 0);
        char lastCh = 0;
        int bsFlag = 0; // for the case {} multiplies one string

        for(int i = 0; i < n; i++){
            char ch = expression[i];
            if(ch == '{'){
                if(i == 0){
                    braceLevel += 1;
                    if(words.size() <= braceLevel)
                        words.push_back({""});
                    else
                        words[braceLevel] = {""};
                    if(multiWords.size() <= braceLevel)
                        multiWords.push_back({""});
                    else
                        multiWords[braceLevel] = {""};
                }
                else if(lastCh == '{'){
                    braceLevel += 1;
                    if(words.size() <= braceLevel)
                        words.push_back({""});
                    else
                        words[braceLevel] = {""};
                    if(multiWords.size() <= braceLevel)
                        multiWords.push_back({""});
                    else
                        multiWords[braceLevel] = {""};
                }
                else if(lastCh == '}'){
                    if(words[braceLevel][0] != "")
                        multiWords[braceLevel] = words[braceLevel];
                    words[braceLevel] = {""};
                    braceIdx[braceLevel] = 0;
                }
                else if(lastCh == ','){
                    braceLevel += 1;
                    if(words.size() <= braceLevel)
                        words.push_back({""});
                    else
                        words[braceLevel] = {""};
                    if(multiWords.size() <= braceLevel)
                        multiWords.push_back({""});
                    else
                        multiWords[braceLevel] = {""};
                }
                else if(isLetter(lastCh)){
                    if(bsFlag){
                        multiWords[braceLevel] = multiplyStrings(multiWords[braceLevel], words[braceLevel]);
                        words[braceLevel] = {""};
                        braceIdx[braceLevel] = 0;
                        bsFlag = 0;
                    }
                    else{
                        braceLevel += 1;
                        if(words.size() <= braceLevel)
                            words.push_back({""});
                        else
                            words[braceLevel] = {""};
                        if(multiWords.size() <= braceLevel)
                            multiWords.push_back({""});
                        else
                            multiWords[braceLevel] = {""};
                        if(multiWords.size() <= braceLevel)
                            multiWords.push_back({words[braceLevel-1][braceIdx[braceLevel-1]]});
                        else
                            multiWords[braceLevel] = {words[braceLevel-1][braceIdx[braceLevel-1]]};
                        words[braceLevel-1][braceIdx[braceLevel-1]] = "";
                    }
                }
            }
            else if(ch == '}'){
                if(lastCh == '}'){
                    words[braceLevel-1] = resolveStrings(words[braceLevel-1], multiWords[braceLevel]);
                    multiWords[braceLevel] = {""};
                    if(multiWords[braceLevel-1][0] != ""){
                        multiWords[braceLevel-1] = multiplyStrings(multiWords[braceLevel-1], words[braceLevel-1]);
                        words[braceLevel-1] = {""};
                        braceIdx[braceLevel-1] = 0;
                    }
                    else{
                        multiWords[braceLevel-1] = words[braceLevel-1];
                        words[braceLevel-1] = {""};
                        braceIdx[braceLevel-1] = 0;

                    }
                    braceLevel -= 1;
                    
                }
                else if(isLetter(lastCh)){
                    if(bsFlag){
                        multiWords[braceLevel] = multiplyStrings(multiWords[braceLevel], words[braceLevel]);
                        words[braceLevel] = {""};
                        braceIdx[braceLevel] = 0;
                        
                        words[braceLevel-1] = resolveStrings(words[braceLevel-1], multiWords[braceLevel]);
                        multiWords[braceLevel] = {""};
                        if(multiWords[braceLevel-1][0] != ""){
                            multiWords[braceLevel-1] = multiplyStrings(multiWords[braceLevel-1], words[braceLevel-1]);
                            words[braceLevel-1] = {""};
                            braceIdx[braceLevel-1] = 0;
                        }
                        else{
                            multiWords[braceLevel-1] = words[braceLevel-1];
                            words[braceLevel-1] = {""};
                            braceIdx[braceLevel-1] = 0;

                        }
                        braceLevel -= 1;
                        bsFlag = 0;
                    }
                    else{
                        if(words[braceLevel][0] != "" && multiWords[braceLevel][0] == ""){
                            multiWords[braceLevel] = words[braceLevel];
                            words[braceLevel] = {""};
                            braceIdx[braceLevel] = 0;
                        }
                        else if(words[braceLevel][0] != "" && multiWords[braceLevel][0] != ""){
                            multiWords[braceLevel] = multiplyStrings(multiWords[braceLevel], words[braceLevel]);
                            words[braceLevel] = {""};
                            braceIdx[braceLevel] = 0;
                        }
                    }
                }
            }
            else if(ch == ','){
                if(lastCh == '}'){
                    words[braceLevel-1] = resolveStrings(words[braceLevel-1], multiWords[braceLevel]);
                    multiWords[braceLevel] = {""};
                    braceIdx[braceLevel] = 0;
                    words[braceLevel] = {""};
                    braceIdx[braceLevel-1] = words[braceLevel-1].size();
                    words[braceLevel-1].push_back("");
                    braceLevel -= 1;
                }
                else if(isLetter(lastCh)){
                    if(bsFlag){
                        multiWords[braceLevel] = multiplyStrings(multiWords[braceLevel], words[braceLevel]);
                        words[braceLevel] = {""};
                        braceIdx[braceLevel] = 0;
                        bsFlag = 0;

                        words[braceLevel-1] = resolveStrings(words[braceLevel-1], multiWords[braceLevel]);
                        multiWords[braceLevel] = {""};
                        braceIdx[braceLevel] = 0;
                        words[braceLevel] = {""};
                        braceIdx[braceLevel-1] = words[braceLevel-1].size();
                        words[braceLevel-1].push_back("");
                        braceLevel -= 1;
                    }
                    else{
                        braceIdx[braceLevel] += 1;
                        words[braceLevel].push_back("");
                    }
                }
            }
            else if(isLetter(ch)){
                if(i == 0){
                    words[braceLevel][braceIdx[braceLevel]] += ch;
                }
                if(lastCh == '{'){
                    words[braceLevel][braceIdx[braceLevel]] += ch;
                }
                else if(lastCh == '}'){
                    if(words[braceLevel][0] != ""){
                       multiWords[braceLevel] = words[braceLevel];
                    }
                    string s(1, ch);
                    words[braceLevel] = {s};
                    braceIdx[braceLevel] = 0;
                    bsFlag = 1;
                }
                else if(lastCh == ','){
                    words[braceLevel][braceIdx[braceLevel]] += ch;
                }
                else if(isLetter(lastCh)){
                    words[braceLevel][braceIdx[braceLevel]] += ch;
                }
            }
            lastCh = ch;
            cout << "idx: " << i << " words: ";
            for(vector<string> w1 : words){
                for(string w2 : w1){
                    cout << w2 << ", ";
                }
                cout << "; ";
            }
            cout << endl;
            cout << "idx: " << i << " multiWords: ";
            for(vector<string> w1 : multiWords){
                for(string w2 : w1){
                    cout << w2 << ", ";
                }
                cout << "; ";
            }
            cout << endl;
        }
        for(int i = words.size() - 1; i >= 1; i--){
            cout << "i: " << i << endl;
            if(words[i][0] != "" && multiWords[i][0] != ""){
                multiWords[i] = multiplyStrings(multiWords[i], words[i]);
                words[i-1] = resolveStrings(words[i-1], multiWords[i]);
                multiWords[i] = {""};
            }
            else if(words[i][0] == "" && multiWords[i][0] != ""){
                words[i-1] = resolveStrings(words[i-1], multiWords[i]);
                multiWords[i] = {""};
            }
            else if(words[i][0] != "" && multiWords[i][0] == ""){
                words[i-1] = resolveStrings(words[i-1], words[i]);
                words[i] = {""};
            }
                
            
            cout << "idx: " << i << " words: ";
            for(vector<string> w1 : words){
                for(string w2 : w1){
                    cout << w2 << ", ";
                }
                cout << "; ";
            }
            cout << endl;
            cout << "idx: " << i << " multiWords: ";
            for(vector<string> w1 : multiWords){
                for(string w2 : w1){
                    cout << w2 << ", ";
                }
                cout << "; ";
            }
            cout << endl;
        }
        
        auto it = find(words[0].begin(), words[0].end(), "");
        if(it != words[0].end())
            words[0].erase(it);
        sort(words[0].begin(), words[0].end());
        return words[0];
    }

int main(){
    string s = "n{{c,g},{h,j},l}a{{a,{x,ia,o},w},er,a{x,ia,o}w}n";
    // expected: ["ncaaiawn","ncaan","ncaaown","ncaaxwn","ncaern","ncaian","ncaon","ncawn",
    // "ncaxn","ngaaiawn","ngaan","ngaaown","ngaaxwn","ngaern","ngaian","ngaon","ngawn","ngaxn",
    // "nhaaiawn","nhaan","nhaaown","nhaaxwn","nhaern","nhaian","nhaon","nhawn","nhaxn",
    // "njaaiawn","njaan","njaaown","njaaxwn","njaern","njaian","njaon","njawn","njaxn",
    // "nlaaiawn","nlaan","nlaaown","nlaaxwn","nlaern","nlaian","nlaon","nlawn","nlaxn"]
    vector<string> res = braceExpansionII(s);
    cout << "res: ";
    for(string r : res)
        cout << r << ", ";
    cout << endl;
}