#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include "helper.cpp"
#include "Vbtree.h"
using namespace std;

unsigned long count_word(string filepath);

int main()
{


    for(int i = 1; i < 11;i++){

        string dataset_path = "../dataset_adjacent/"+ to_string(i*25) ;


        unsigned long N = count_word(dataset_path);

        cout<<"total word is"<<N<<endl;

        const clock_t begin_time = clock();

        //构建一个包含了2个文件的总共有N个关键词的VBtree
        Vbtree vbtree{i*25, N};

        unsigned long before_insert = vbtree.hashtable.bucket_count();

        //开始逐行添加  和fileID对应的keyword，并测试建树时间

        ifstream is{dataset_path};
        string line;
        unsigned int line_number = 0;
        while (getline(is, line))
        {
            string word;
            istringstream il{line};
            // il >> word;
            // cout << "----------------------------------------------------------------\n";
            // cout << "start adding file with ID " << line_number << '\n';
            for (; il >> word;)
            {
                vbtree.insert_keyword(word, line_number);
                // cout << "word [" << word << "] has been added to the vbtree\n";
            }
            cout << "finish adding file with ID " << line_number << '\n';
            cout << "----------------------------------------------------------------\n";
            line_number++;
        }


        const clock_t construction_finish_time = clock();

        float vbtree_construction_time = (float)(construction_finish_time - begin_time) / CLOCKS_PER_SEC;

        cout << "construction time = " << vbtree_construction_time << '\n';


        vector<string> multi_fuzzy1 = {"ezar","numerouus","duratino","explosioms","occuurred","septemnber"};
                                  // { "ear", "numerous","duration", "explosions", "occurred", "september"};

        vector<string> multi_fuzzy2 = {"rsearch","fngerprinting","terminall","grouop","efents"};
                                 //  {"research","fingerprinting","terminal", "group","events"}

        vector<string> multi_fuzzy3 = {"supporfed","divisoins","materiala","physaics"};
                                 // { "supported","divisions","materials","physicas"}

        vector<vector<string>> multi_multi_fuzzy = {multi_fuzzy1, multi_fuzzy2, multi_fuzzy3};

        double total_search_time = 0.0;
        for(int i = 0; i < multi_multi_fuzzy.size(); i++){
            vector<string> multi_trap;
            for(int j = 0;j<multi_multi_fuzzy[i].size();j++)
                multi_trap.push_back(vbtree.first_hash(multi_multi_fuzzy[i][j]));
            const clock_t search_begin_time = clock();
            vbtree.recursive_find_trapdoor_Mul_v2(multi_trap,"");
            const clock_t search_finish_time = clock();
            float keyword_search_time = (float)(search_finish_time - search_begin_time) / CLOCKS_PER_SEC;
            total_search_time+=keyword_search_time;
        }
        string multi_fuzzy_adjacent ="../dataoutcome/multi_adjacent_time.txt";
        ofstream ofs2{multi_fuzzy_adjacent,ios_base::app};
        ofs2 << "fuzzy keyword searching time of "<<i*25<<" is " << total_search_time/3 << " s\n\n";
        
    }
    return 0;
}

unsigned long count_word(string filepath)
{
    ifstream is{filepath};
    string line;
    unsigned long word_count = 0;
    while (getline(is, line))
    {
        string word;
        istringstream il{line};
        // il >> word;
        for (; il >> word;)
            word_count++;
    }
    return word_count;
}