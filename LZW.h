#pragma once
#include <iostream>
#include <utility>
#include <vector>
#include <ostream>
#include <istream>
#include <limits>
#include <map>
using namespace std;

using Code = uint16_t;


//int BruteSearch(vector<string> list, string find);

void ResetEncodeDictionary(map<pair<Code, char>, Code> &dictionary);
void ResetDecodeDictionary(vector<pair<Code, char>>& dictionary);
vector<char> RebuildString(vector<pair<Code, char>>& dictionary, Code k);

void LZWEncoder(istream &input, ostream &output);
void LZWDecoder(istream& input, ostream& output);
