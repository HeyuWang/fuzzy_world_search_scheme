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


    for(int i = 1; i < 2;i++){

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



        vector<string> multi_fuzzy = {"numeroys","duratioh","duratfion","xseptember","at"};

        vector<string> multi_trap;

        for(int i = 0;i<multi_fuzzy.size();i++)
            multi_trap.push_back(vbtree.first_hash(multi_fuzzy[i]));
        
        vbtree.recursive_find_trapdoor_Mul_v2(multi_trap,"");

        // string keyword_3[5] = {"ans","thd","ain","oir","foe"};// 分别是 are the aim our for的误输入形式
        // double total_search_time = 0.0;
        // int count = 0;
        // for(int i = 0; i < 5;i++){
        //     string trapdoor = vbtree.first_hash(keyword_3[i]);
        //     const clock_t search_begin_time = clock();
        //     bool searchresult = vbtree.recursive_find_trapdoor_v2(trapdoor,"",count);
        //     const clock_t search_finish_time = clock();
        //     float keyword_search_time = (float)(search_finish_time - search_begin_time) / CLOCKS_PER_SEC;
        //     total_search_time+=keyword_search_time;
        // }

        // string fuzzy_adjacent ="../dataoutcome/adjacent_time.txt";
        // ofstream ofs2{fuzzy_adjacent,ios_base::app};
        // ofs2 << "fuzzy keyword searching time of "<<i*25<<" files with length "<< keyword_3[0].size()<<" is " << total_search_time/5 << " s\n";
        // ofs2 << "average time of target hit is "<< count/5 << " times \n\n";

        

        // string keyword_4[5] = {"manu","willl","fro","helo","vrry"};//分别是 many, will, from, help, very的误输入形式
        // total_search_time = 0.0;
        // count = 0;
        // for(int i = 0; i < 5;i++){
        //     string trapdoor = vbtree.first_hash(keyword_4[i]);
        //     const clock_t search_begin_time = clock();
        //     bool searchresult = vbtree.recursive_find_trapdoor_v2(trapdoor,"",count);
        //     const clock_t search_finish_time = clock();
        //     float keyword_search_time = (float)(search_finish_time - search_begin_time) / CLOCKS_PER_SEC;
        //     total_search_time+=keyword_search_time;
        // }


        // ofs2 << "fuzzy keyword searching time of "<<i*25<<" files with length "<< keyword_4[0].size()<<" is " << total_search_time/5 << " s\n";
        // ofs2 << "average time of target hit is "<< count/5 << " times \n\n";


        // string keyword_5[5] = {"theee","partd","otherr","ofen","rotue"};//分别是 thest, parts ,other, often, route的误输入形式
        // total_search_time = 0.0;
        // count = 0;
        // for(int i = 0; i < 5;i++){
        //     string trapdoor = vbtree.first_hash(keyword_5[i]);
        //     const clock_t search_begin_time = clock();
        //     bool searchresult = vbtree.recursive_find_trapdoor_v2(trapdoor,"",count);
        //     const clock_t search_finish_time = clock();
        //     float keyword_search_time = (float)(search_finish_time - search_begin_time) / CLOCKS_PER_SEC;
        //     total_search_time+=keyword_search_time;
        // }

        // ofs2 << "fuzzy keyword searching time of "<<i*25<<" files with length "<< keyword_5[0].size()<<" is " << total_search_time/5 << " s\n";
        // ofs2 << "average time of target hit is "<< count/5 << " times \n\n";

        // string keyword_6[5] = {"befroe","cloudsd","numbe","comon","familu"};//分别是 clouds, before, number, common,family的误输入形式
        // total_search_time = 0.0;
        // count = 0;
        // for(int i = 0; i < 5;i++){
        //     string trapdoor = vbtree.first_hash(keyword_6[i]);
        //     const clock_t search_begin_time = clock();
        //     bool searchresult = vbtree.recursive_find_trapdoor_v2(trapdoor,"",count);
        //     const clock_t search_finish_time = clock();
        //     float keyword_search_time = (float)(search_finish_time - search_begin_time) / CLOCKS_PER_SEC;
        //     total_search_time+=keyword_search_time;
        // }

        // ofs2 << "fuzzy keyword searching time of "<<i*25<<" files with length "<< keyword_6[0].size()<<" is " << total_search_time/5 << " s\n";
        // ofs2 << "average time of target hit is "<< count/5 << " times \n\n";

        // string keyword_7[5] = {"projecr", "releasee", "contrlo", "scoence", "systms"};//分别是 project, release, control, science, systems的误输入形式
        // total_search_time = 0.0;
        // count = 0;
        // for(int i = 0; i < 5;i++){
        //     string trapdoor = vbtree.first_hash(keyword_7[i]);
        //     const clock_t search_begin_time = clock();
        //     bool searchresult = vbtree.recursive_find_trapdoor_v2(trapdoor,"",count);
        //     const clock_t search_finish_time = clock();
        //     float keyword_search_time = (float)(search_finish_time - search_begin_time) / CLOCKS_PER_SEC;
        //     total_search_time+=keyword_search_time;
        // }

        // ofs2 << "fuzzy keyword searching time of "<<i*25<<" files with length "<< keyword_7[0].size()<<" is " << total_search_time/5 << " s\n";
        // ofs2 << "average time of target hit is "<< count/5 << " times \n\n";

        // string keyword_8[5] = {"adjacwnt", "collapsse", "pressurr", "parcticel", "improveds"};//分别是 adjacent, collapse, pressure, parcticle, improved的误输入形式
        // total_search_time = 0.0;
        // count = 0;
        // for(int i = 0; i < 5;i++){
        //     string trapdoor = vbtree.first_hash(keyword_8[i]);
        //     const clock_t search_begin_time = clock();
        //     bool searchresult = vbtree.recursive_find_trapdoor_v2(trapdoor,"",count);
        //     const clock_t search_finish_time = clock();
        //     float keyword_search_time = (float)(search_finish_time - search_begin_time) / CLOCKS_PER_SEC;
        //     total_search_time+=keyword_search_time;
        // }

        // ofs2 << "fuzzy keyword searching time of "<<i*25<<" files with length "<< keyword_8[0].size()<<" is " << total_search_time/5 << " s\n";
        // ofs2 << "average time of target hit is "<< count/5 << " times \n\n";
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