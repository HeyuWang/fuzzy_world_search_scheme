#include "blake2.h"
#include <unordered_map>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

typedef unsigned int identifier_number;



class Vbtree{
    public:
        // class Hasher;
        // the constructor   m is the number of files,  n is the total keywords in all leaf nodes(n has counted repeated word)
        Vbtree(int m, unsigned long n):L{int(log2(m)) < log2(m)? int(log2(m))+2:int(log2(m) + 1)},N{n}{
            hashtable.reserve(L*N/0.8);
            std::cout<<"this hashtable has successfully reserved "<<L*N << " insert position\n";
            }

        string identifier_to_path(identifier_number fileID);
        identifier_number path_to_identifier(string path);

        string first_hash(string keyword);
        string second_hash(string path,string first_hash_out);
        void insert_keyword(string keyword,identifier_number fileID);

        vector<identifier_number> find_keyword(string keyword);
        vector<identifier_number> find_trapdoor(string trapdoor);//  trapdoor is Fk(w)  pass trapdoor

        bool recursive_find_trapdoor(string trapdoor,string path,vector<identifier_number> v);
        bool recursive_find_trapdoor_v2(string trapdoor,string path,int& count);

        vector<identifier_number> find_trapdoor_mul(vector<string> Trpd_Mul);
        bool recursive_find_trapdoor_Mul(vector<string> Trpd_Mul,string path,vector<identifier_number> v);
        bool recursive_find_trapdoor_Mul_v2(vector<string> Trpd_Mul,string path);

        // void print_trapdoor(string trapdoor){
        //     for (unsigned char s:trapdoor)
        //         cout<<hex<<"0x"<<(short)s<<',';
        //     cout<<'\n';
        // }

    // private:    
        int L;//  m <= 2**(L-1)  
        unsigned long N; //N is the sum of  keywords in all leaf nodes;
        unordered_map<string,int> hashtable;



        unsigned char out[DIGIST_LENGTH];
        char key[1];
        // string datafile;
};

string Vbtree::identifier_to_path(identifier_number x){

    identifier_number temp = pow(2,L-1);
    identifier_number new_n = temp+x;
    string s;
    while(new_n!=1){
        if(new_n%2 == 0){
            s+='0';
            new_n = new_n/2;
        }
        else{
            s+='1';
            new_n = (new_n-1)/2;
        }
    }
    reverse(s.begin(),s.end());
    return s;
}

identifier_number Vbtree::path_to_identifier(string path){
    identifier_number root = 1;
    for(auto& s:path){
        if (s == '0')
            root*=2;
        else
            root = root*2+1;
    }
    return root-pow(2,L-1);
}

// class Vbtree::Hasher{
//     // input is path(v) || F_k(w)
//         size_t operator()(const string& s) const{
//             size_t hashval = hash<string>()(s); 
//             return hashval;
//         }
// };

string Vbtree::first_hash(string keyword){
    return blake2_string(out,DIGIST_LENGTH,keyword,keyword.size(),key,0);
}

string Vbtree::second_hash(string path, string first_hash_out){
    string new_s = path+first_hash_out;
    return blake2_string(out,DIGIST_LENGTH,new_s,new_s.size(),key,0);
}


void Vbtree::insert_keyword(string keyword,identifier_number fileID){
    string path = identifier_to_path(fileID);    // L byte sequence
    string first_hash_out = first_hash(keyword); // 160 bit sequence
    // print_trapdoor(first_hash_out);
    string added_keyword;
    for(int i = 0; i < L;i++){
        added_keyword = second_hash(path,first_hash_out);
        // cout<<"path = "<<path<<" added_keyword is as follows"<<endl;
        
        // print_trapdoor(added_keyword);
        hashtable.insert(make_pair(added_keyword,1));
        path.pop_back();
    }
    // cout<<"keyword :"<<keyword<<" of file "<<fileID<<" has been added to the Vbtree\n";
}


vector<identifier_number> Vbtree::find_keyword(string keyword){
    string trapdoor = first_hash(keyword);
    return find_trapdoor(trapdoor);
}


vector<identifier_number> Vbtree::find_trapdoor(string trapdoor){
    vector<identifier_number> search_result;
    recursive_find_trapdoor(trapdoor,"",search_result);
    return search_result;
}

bool Vbtree::recursive_find_trapdoor(string trapdoor,string path,vector<identifier_number> v){
    try{
    if(path.size() == L-1){
        // cout<<"path = "<<path<<endl;
        string final_verify = second_hash(path,trapdoor);
        // cout<<"final_verify is as follows\n";
        // print_trapdoor(final_verify);
        if(hashtable.at(final_verify) == 1){
            v.push_back(path_to_identifier(path));
            cout<<"trapdoor is found in file "<<path_to_identifier(path)<<endl;
            return true;
        }
        else{
            return false;
        }
    }
    else{
        // cout<<"path = "<<path<<" trapdoor is as follows\n";
        // print_trapdoor(trapdoor);
        string added_keyword = second_hash(path,trapdoor);
        // cout<<"added_keyword is as follows\n";
        // print_trapdoor(added_keyword);

        if(hashtable.at(added_keyword) == 1){
            bool left_search_result = recursive_find_trapdoor(trapdoor,path+'0',v);
            bool right_search_result = recursive_find_trapdoor(trapdoor,path+'1',v);
            return left_search_result || right_search_result;
        }
        else{
            cout<<"search failed\n";
            return false;
        }
    }
    }
    catch(out_of_range){
        // cout<<"nothing is done\n";
    }
}

bool Vbtree::recursive_find_trapdoor_v2(string trapdoor,string path,int& count){
    try{
    if(path.size() == L-1){
        // cout<<"path = "<<path<<endl;
        string final_verify = second_hash(path,trapdoor);
        // cout<<"final_verify is as follows\n";
        // print_trapdoor(final_verify);
        if(hashtable.at(final_verify) == 1){
            cout<<"trapdoor is found in file "<<path_to_identifier(path)<<endl;
            count+=1;
            return true;
        }
        else{
            return false;
        }
    }
    else{
        // cout<<"path = "<<path<<" trapdoor is as follows\n";
        // print_trapdoor(trapdoor);
        string added_keyword = second_hash(path,trapdoor);
        // cout<<"added_keyword is as follows\n";
        // print_trapdoor(added_keyword);

        if(hashtable.at(added_keyword) == 1){
            bool left_search_result = recursive_find_trapdoor_v2(trapdoor,path+'0',count);
            bool right_search_result = recursive_find_trapdoor_v2(trapdoor,path+'1',count);
            return left_search_result || right_search_result;
        }
        else{
            // cout<<"search failed\n";
            return false;
        }
    }
    }
    catch(out_of_range){
        // cout<<"nothing is done\n";
    }
}

vector<identifier_number> Vbtree::find_trapdoor_mul(vector<string> Trpd_Mul){
    vector<identifier_number> search_result;
    recursive_find_trapdoor_Mul(Trpd_Mul,"",search_result);
    return search_result;
}
bool Vbtree::recursive_find_trapdoor_Mul(vector<string> Trpd_Mul,string path,vector<identifier_number> v){
    try{

        vector<string> final_verify;
        for(int ii=0;ii<Trpd_Mul.size();ii++)
        {
            string trap=Trpd_Mul[ii];
            final_verify.push_back(second_hash(path,trap));
        }
         
        // cout<<"final_verify is as follows\n";
        // print_trapdoor(final_verify);
        int flag=1;
        for(int ii=0;ii<Trpd_Mul.size();ii++)
        {
            string trap_final=final_verify[ii];
            if(hashtable.at(trap_final) != 1)
            {
                flag=0;
                break;
            }

        }
    if(path.size() == L-1){
        // cout<<"path = "<<path<<endl;
     
        if(flag == 1){
            v.push_back(path_to_identifier(path));
            cout<<"multi-trapdoor is found in file "<<path_to_identifier(path)<<endl;
            return true;
        }
        else{
            cout<<"There is no match result"<<endl;
            return false;
        }
    }
    else{
        // cout<<"path = "<<path<<" trapdoor is as follows\n";
        // print_trapdoor(trapdoor);
        // string added_keyword = second_hash(path,Trpd_Mul);
        // cout<<"added_keyword is as follows\n";
        // print_trapdoor(added_keyword);

        if(flag == 1){
            recursive_find_trapdoor_Mul(Trpd_Mul,path+'0',v);
            recursive_find_trapdoor_Mul(Trpd_Mul,path+'1',v);
        }
        else{
            cout<<"search failed\n";
            return false;
        }
    }
    }
    catch(out_of_range){
        // cout<<"nothing is done\n";
    }
}

bool Vbtree::recursive_find_trapdoor_Mul_v2(vector<string> Trpd_Mul,string path){
    try{

        vector<string> final_verify;
        for(int ii=0;ii<Trpd_Mul.size();ii++)
        {
            string trap=Trpd_Mul[ii];
            final_verify.push_back(second_hash(path,trap));
        }
         
        // cout<<"final_verify is as follows\n";
        // print_trapdoor(final_verify);
        int flag=1;
        for(int ii=0;ii<Trpd_Mul.size();ii++)
        {
            string trap_final=final_verify[ii];
            if(hashtable.at(trap_final) != 1)
            {
                flag=0;
                break;
            }

        }
    if(path.size() == L-1){
        // cout<<"path = "<<path<<endl;
     
        if(flag == 1){
            cout<<"multi-trapdoor is found in file "<<path_to_identifier(path)<<endl;
            return true;
        }
        else{
            cout<<"There is no match result"<<endl;
            return false;
        }
    }
    else{
        // cout<<"path = "<<path<<" trapdoor is as follows\n";
        // print_trapdoor(trapdoor);
        // string added_keyword = second_hash(path,Trpd_Mul);
        // cout<<"added_keyword is as follows\n";
        // print_trapdoor(added_keyword);

        if(flag == 1){
            recursive_find_trapdoor_Mul_v2(Trpd_Mul,path+'0');
            recursive_find_trapdoor_Mul_v2(Trpd_Mul,path+'1');
        }
        else{
            cout<<"search failed\n";
            return false;
        }
    }
    }
    catch(out_of_range){
        // cout<<"nothing is done\n";
    }
}


// def find(path,trapdoor):
//     if len(path) == L-1:
//         printf(find in L)
//         return path_to_idetifier(path);
//     else:
//         string cur = second_hash(path,trapdoor)
//         if hashtable.at(cur) != 1:
//             printf("not found")
//         else:
//             find(path+'0',trapdoor)
//             find(path+'1',trapdoor)





