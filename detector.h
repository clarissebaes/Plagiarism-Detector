#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <cassert>
#include <tuple>
#include <functional>
#include <algorithm>


using namespace std;

class Detector{
private:
//----------PRIVATE VARIABLES---------//
	int total;
	int count;
	float percentage;
	unordered_map<string,string> synonyms_map;
	vector<string> file1_words;
    vector<string> file2_words;
    unordered_map<string,int> tuple_map;



//----------PRIVATE FUNCTIONS---------//
	string fixWordz(string word);//removes ['.', ',']
	void readFile();
	void makeSynonymMap();
	void changeSynonyms();
	void make_map_tuple();
	void checkDuplicates();

	
public:
//----------PUBLIC VARIABLES---------//
	string file1_name;
	string file2_name;
	string file_syn_name;
	int N; //N is the tuple size, if none is inputed default is N = 3


//----------PUBLIC FUCNTIONS---------//	
	Detector(string file_syn_name_,string file1_name_, string file2_name); //2 constructor
	Detector(string file_syn_name_,string file1_name_, string file2_name, int N);
	int get_file_2_size();
	int run_plagarism_check();




};

