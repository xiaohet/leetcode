#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> lefts;
vector<string> str;

void generator(int n, int depth){
    if(depth < n - 1){
        for(int i = lefts[depth] + 1; i < depth * 2 + 3; i++){
            lefts[depth+1] = i;
            generator(n, depth+1);
        }
    }
    else if(depth == n - 1){
        string s(n*2, ')');
        for(int i = 0; i < n; i++){
            s[lefts[i]] = '(';
        }
        str.push_back(s);
    }
}
vector<string> generateParenthesis(int n) {
    lefts.resize(n);
    lefts[0] = 0;
    generator(n, 0);
    return str;
}

int main(){
    int n = 5;
    vector<string> res = generateParenthesis(n);
    cout << "res: ";
    for(string s : res){
        cout << "\"" << s << "\" ";
    }
    cout << endl;
}