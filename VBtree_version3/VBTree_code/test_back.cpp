#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include "Vbtree.h"
using namespace std;

unsigned long count_word(string filepath);

int main()
{




        string dataset_path = "../dataset_wildcard/"+ string("fuzzy_set_of_hello_and_world") ;


        unsigned long N = count_word(dataset_path);

        const clock_t begin_time = clock();

        //构建一个包含了2个文件的总共有N个关键词的VBtree
        Vbtree vbtree{2, N};

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
                cout << "word [" << word << "] has been added to the vbtree\n";
            }
            cout << "finish adding file with ID " << line_number << '\n';
            cout << "----------------------------------------------------------------\n";
            line_number++;
        }


        const clock_t construction_finish_time = clock();

        float vbtree_construction_time = (float)(construction_finish_time - begin_time) / CLOCKS_PER_SEC;

        cout << "construction time = " << vbtree_construction_time << '\n';


        //测试传trapdoor的搜索时间

        const clock_t search_begin_time = clock();

        string keyword = "helloi";

        string trapdoor = vbtree.first_hash(keyword);


        vbtree.find_trapdoor(trapdoor);

        const clock_t search_finish_time = clock();

        float keyword_search_time = (float)(search_finish_time - search_begin_time) / CLOCKS_PER_SEC;
        cout << "searching time for "<<keyword<<" is " << keyword_search_time * pow(10, 6) << "us\n";
    

        // string single_keyword_searching_time = "../experiment_results/searching_time.txt";
        // ofstream ofs2{single_keyword_searching_time,ios_base::app};
        // ofs2 << "single keyword searching time of "<<keyword<<" is " << keyword_search_time * pow(10, 6) << " us\n\n";




        // const clock_t search_begin_time = clock();
        // string multi_keyword[2] = {"heello","helllo"};
        // vector<string> multi_trapdoor = {vbtree.first_hash(multi_keyword[0]),vbtree.first_hash(multi_keyword[1])};
        // vbtree.find_trapdoor_mul(multi_trapdoor);
        // const clock_t search_finish_time = clock();

        // float keyword_search_time = (float)(search_finish_time - search_begin_time) / CLOCKS_PER_SEC;

        // cout << "searching time for "<<multi_keyword[0]<<" and "<<multi_keyword[1]<<" is " << keyword_search_time * pow(10, 6) << "us\n";
        // memory usage estimation

        // size_t memory_usage = vbtree.hashtable.size()*(20+4)+vbtree.hashtable.bucket_count()*8;

        // size_t count = 0;
        // cout << "reserved: " << vbtree.L * N << endl;
        // cout << "before insert bucket_count: " << before_insert << endl;
        // ;
        // cout << "bucket_count: " << vbtree.hashtable.bucket_count() << endl;
        // cout << "total number of elements = " << vbtree.hashtable.size() << endl;
        // cout << "total number of keywords = " << N << endl;
        // for (unsigned i = 0; i < vbtree.hashtable.bucket_count(); ++i)
        // {
        //     size_t bucket_size = vbtree.hashtable.bucket_size(i);
        //     if (bucket_size == 0)
        //     {
        //         count++;
        //     }
        //     else
        //     {
        //         count += bucket_size;
        //     }
        // }

        // cout<<"count of each bucket == "<<count<<endl;

        // cout<<"index size is almost "<<memory_usage<<" bytes, which is "<<memory_usage/pow(2,10)<<" KB, which is "<<memory_usage/pow(2,20)<<" MB, which is "<<memory_usage/pow(2,30)<<" GB\n";

        // string index_construction_time = "../experiment_results/construction_time.txt";
        // string single_keyword_searching_time = "../experiment_results/single_keyword_searching_time.txt";
        // string index_size = "../experiment_results/index_size.txt";

        // ofstream ofs1{index_construction_time,ios_base::app};
        // ofs1 << "construction time of "<<m<<"files and "<<N<<"total words is " << vbtree_construction_time << " s\n\n";
        
        // ofstream ofs2{single_keyword_searching_time,ios_base::app};
        // ofs2 << "single keyword searching time of "<<m<<"files is " << keyword_search_time * pow(10, 6) << " us\n\n";

        // ofstream ofs3{index_size,ios_base::app};
        // ofs3<<"index size of " <<m<<" files is almost "<<memory_usage<<" bytes, which is "<<memory_usage/pow(2,10)<<" KB, which is "<<memory_usage/pow(2,20)<<" MB, which is "<<memory_usage/pow(2,30)<<" GB\n\n";

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