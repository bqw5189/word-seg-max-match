#ifndef CreatDic_H_INCLUDED
#define CreatDic_H_INCLUDED

#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <map>
using namespace std;

string wordfile = "/Users/baiqunwei/ClionProjects/word-seg-max-match/source/dict.txt";
string strtmp;
string word ;
map<string, int> wordhash; // 用于读取词典后的哈希
map<string, int >::iterator worditer; //
typedef pair<string, int> sipair;

void CreatDic(void)
{
	ifstream dic(wordfile);
	 if (!dic.is_open()) // 打开词典失败则退出程序
     {
      cerr << "Unable to open input file: " << "wordlexicon"<< " -- bailing out!" << endl;
	  exit(-1);
     }
	while (getline(dic, strtmp)) // 读入词典的每一行并将其添加入哈希中
    {
     istringstream istr(strtmp);
     istr >> word;
     wordhash.insert(sipair(word, 1)); 
    }
}

bool Find(string s)
{
//    cout << s << " find : " << (wordhash.find(s)!=wordhash.end()) << endl;
	if(wordhash.find(s)!=wordhash.end())
		return true ;
	else 
		return false;
}

#endif // CraetDic_H_INCLUDED
