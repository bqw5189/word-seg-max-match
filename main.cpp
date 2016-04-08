#include"CreatDic.h"
#include<time.h>
#include<string>
#include<cstring>

#define MaxWordLength 10*3


using namespace std;

string Segment(string s1);           // 正向分割函数
string SegmentSentence(string s1);
int lastLength(string s1);

int main() {
//    string s = "（";
//    cout << s << "length: " << s.length() << " code : " << ((int)(unsigned char)s[0]) << "max code:" << ((int)(unsigned char)s[1]) <<endl;
////
    CreatDic();
//    string line  = SegmentSentence("注1：（");
//    cout << lastLength("注1：1") << endl;
//    cout << line << endl;

//    cout << SegmentSentence("注1：（田弘茂等著，国防外交白皮书，台北：业强出版社，1992年3月，页192）") << endl;
    string tmp;
    string line;
    string output;
    output = "/Users/baiqunwei/ClionProjects/word-seg-max-match/source/SegmentOutput.txt";
    ifstream testfile("/Users/baiqunwei/ClionProjects/word-seg-max-match/source/sentence.txt");
    ofstream outfile1(output);
    while (getline(testfile, tmp)) {
        line = tmp;
        line = SegmentSentence(line);
        outfile1 << line << endl;
    }

    return 0;
}

string Segment(string s1) {
    string s2 = "";
    while (!s1.empty()) {
        int len = (int) s1.length();
        if (len > MaxWordLength) {
            len = MaxWordLength;
        }
        string w = s1.substr(0, len);

//        cout << s1 << " substr : " << w << " len: " << len << endl;

        bool flag = Find(w);

        while (len > 3 && flag == false) // 如果不是词
        {
            len -= lastLength(w);

//            cout << "s1:" << s1 << " -> w : " << w << " len: " << len << endl;

            w = w.substr(0, len);
            flag = Find(w);
        }
        s2 += w + '/'; //将匹配得到的词连同词界标记加到输出串末尾
        s1 = s1.substr(w.length(), s1.length()); //从s1-w处开始
    }
    return s2;
}

const unsigned char kFirstBitMask = 128; // 1000000
const unsigned char kSecondBitMask = 64; // 0100000
const unsigned char kThirdBitMask = 32; // 0010000
const unsigned char kFourthBitMask = 16; // 0001000
const unsigned char kFifthBitMask = 8; // 0000100

int utf8_char_len(char firstByte)
{
    std::string::difference_type offset = 1;

    if(firstByte & kFirstBitMask) // This means the first byte has a value greater than 127, and so is beyond the ASCII range.
    {
        if(firstByte & kThirdBitMask) // This means that the first byte has a value greater than 224, and so it must be at least a three-octet code point.
        {
            if(firstByte & kFourthBitMask) // This means that the first byte has a value greater than 240, and so it must be a four-octet code point.
                offset = 4;
            else
                offset = 3;
        }
        else
        {
            offset = 2;
        }
    }
    return offset;
}

int lastLength(string str)
{
    string s1 = str;
    int i = 0;
    int dd = 0;
    int lastLeng = 1;

    i = utf8_char_len(s1[i]);

    dd = (int) s1.length();

    while (i < dd) {
        lastLeng = utf8_char_len(s1[i]);
        i += utf8_char_len(s1[i]);
    }

    return lastLeng;
}

string SegmentSentence(string s1) {
    string s2 = ""; //用s2存放分词结果
    int i=0;
    int dd;
    while (!s1.empty()) {
        i= utf8_char_len(s1[i]);
        dd = (int) s1.length();
        cout << s1 << " length " << dd << endl;
        while (i < dd) {
            i += utf8_char_len(s1[i]);
        }
//        cout << s1 << " : i = "<< i << "->" << s1.substr(0, i) << endl;
        s2 += Segment(s1.substr(0, i));
        s1 = s1.substr(i, dd);
    }

    return s2;
}

string prf(string segment, string answer){
    vector<string> segmentWord;
    vector<string> answerWord;
    split(segment,segmentWord, " ");
    split(answer,answerWord, " ");

    int segmentWordCount = segmentWord.size();
    int segmentWordSearchCount = count(segmentWord);
    float precision = segmentWordSearchCount*1.0/segmentWordSearchCount * 100;

    int answerWordCount = answerWord.size();
    int answerWordSearchCount = count(answerWord);
    int recall = answerWordSearchCount*1.0/answerWordCount * 100;

    float f = (segmentWordSearchCount*1.0/segmentWordSearchCount) * (answerWordSearchCount*1.0/answerWordCount)*2/(segmentWordSearchCount*1.0/segmentWordSearchCount+answerWordSearchCount*1.0/answerWordCount) * 100;

    cout << "识别出的个体总数:" << segmentWordCount << " 正确识别的个体总数:" << segmentWordSearchCount << " 正确率(Precision): " << precision << "%" << endl;
    cout << "测试集中存在的个体总数:" << answerWordCount << " 正确识别的个体总数:" << answerWordSearchCount << " 召回率(Recall) : " << recall << "%" << endl;
    cout << "F值:" << f << "%" << endl;

    return "";
}

int count(vector<string>& source){
    int count = 0;

    for(vector<string>::iterator it  = source.begin(); it != source.end(); ++it )
    {
        if (Find(*(it))){
            count++;
        }
    }

    return count;
}

//注意：当字符串为空时，也会返回一个空字符串
int split(const string& str, vector<string>& ret_, string sep)
{
    if (str.empty())
    {
        return 0;
    }

    string tmp;
    string::size_type pos_begin = str.find_first_not_of(sep);
    string::size_type comma_pos = 0;

    while (pos_begin != string::npos)
    {
        comma_pos = str.find(sep, pos_begin);
        if (comma_pos != string::npos)
        {
            tmp = str.substr(pos_begin, comma_pos - pos_begin);
            pos_begin = comma_pos + sep.length();
        }
        else
        {
            tmp = str.substr(pos_begin);
            pos_begin = comma_pos;
        }

        if (!tmp.empty())
        {
            ret_.push_back(tmp);
            tmp.clear();
        }
    }
    return 0;
}
