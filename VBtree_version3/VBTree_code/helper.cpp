#include <string>
#include <vector>
#include <iostream>
using namespace std;

vector<string> generate_wildcard(string s){
    vector<string> ret;

    ret.push_back(s);

    string inserted = "*";

    for(int i = 0; i < s.size();i++){
        char temp = s[i];
        s[i] = '*';
        string s1 = s;
        ret.push_back(s1);
        s[i] = temp;
    }

    for(int i = 0; i <= s.size();i++){
        string temp = s.insert(i,inserted);
        ret.push_back(temp);
        s.erase(i,1);
    }

    return ret;
}



// int main(){
//     string s = "castle";
//     vector<string> v = generate_wildcard(s);
//     for(auto t : v)
//         cout<<t<<"\t";
// }