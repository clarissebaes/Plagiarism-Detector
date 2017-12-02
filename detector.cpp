#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <cassert>
#include <tuple>
#include <functional>
#include <algorithm>
#include <unordered_map>
#include "detector.h"

using namespace std;

//----------Constructor with default input N-size---------//
Detector::Detector(string file_syn_name_,string file1_name_, string file2_name_){ //2 constructor
	N = 3;
	file_syn_name = file_syn_name_;
	file1_name = file1_name_;
	file2_name = file2_name_;
	total = 0;
	count = 0;

}
//----------Constructor with input N-size---------//
Detector::Detector(string file_syn_name_,string file1_name_, string file2_name_, int N_){
	N = N_;
	file_syn_name = file_syn_name_;
	file1_name = file1_name_;
	file2_name = file2_name_;	
	total = 0;
	count = 0;

}
//----------fuction that removes ['.', ','] from words---------//
string Detector::fixWordz(string word){
	transform(word.begin(), word.end(), word.begin(), ::tolower);
	word.erase(remove(word.begin(), word.end(), '.'), word.end());
	word.erase(remove(word.begin(), word.end(), ','), word.end());
	word.erase(remove(word.begin(), word.end(), '!'), word.end());
	word.erase(remove(word.begin(), word.end(), '?'), word.end());
	return word;
}
//----------fuction that gets a vector of all the words from both input files---------//
void Detector::readFile(){
	//creates vector of words from file 1
	ifstream openFile1;
	openFile1.open(this->file1_name);
	string tempWord;
	openFile1 >> tempWord;//reads in word by word
    while(openFile1){//while there are still words in the file
    	tempWord = fixWordz(tempWord);
    	file1_words.push_back(tempWord);
    	openFile1 >> tempWord;
    }

	//creates vector of words from file 2 similare to loop above
   	ifstream openFile2;
	openFile2.open(this->file2_name);
	tempWord = "";//clears tempword
	openFile2 >> tempWord;
    while(openFile2){
    	tempWord = fixWordz(tempWord);
    	file2_words.push_back(tempWord);
    	openFile2 >> tempWord;
    }

}
//----------fuction that makes a map of all sysnonms and set default sysnonm---------//
void Detector::makeSynonymMap(){
	ifstream synFile;
	synFile.open(file_syn_name);
	string tempSentence;//temp sentence is each line of synonyms
	while(getline(synFile,tempSentence)){//gets file line by line
		string temp_word = "";
		bool first = true;//to determine if first word in line-> first word is the default word
		string default_word = "";
		for(int i = 0; i<tempSentence.size(); i++){
			if((tempSentence[i] == ' ' || i == (tempSentence.size()-1) )&& !first){//finished with other words
				if(tempSentence[i] != ' ' ){
					temp_word+=tempSentence[i];
				}
				synonyms_map.insert(pair<string, string>(temp_word,default_word));
				temp_word = "";	
			}
			else if(tempSentence[i] == ' ' && first){//finished with gathering first word
				synonyms_map.insert(pair<string, string>(temp_word,temp_word));
				default_word = temp_word;//sets default word
				first = false;
				temp_word = "";//clears temp word	
			}
			else{//gets letter for individual word
				temp_word+=tempSentence[i];
			}

		}//end of for loop

	}//end of while loop

}
//----------fuction that replaces sysnonmy with default synonym---------//
void Detector::changeSynonyms(){
	unordered_map<string,string>::iterator it; //iteratr for map
	string current_word;
	for(int i = 0; i<file1_words.size();i++){
		current_word = file1_words[i];//compares current word to map
		it = synonyms_map.find(current_word);
		if(it == synonyms_map.end() ){
			continue;//if not found nothing happens
		}
		else{
			string new_word = it->second;//if found then replace with default word
			file1_words[i] = new_word;
		}
	}
	//same logic as above but for file 2
	for(int i = 0; i<file2_words.size();i++){
		current_word = file2_words[i];
		it = synonyms_map.find(current_word);
		if(it == synonyms_map.end() ){
			continue;
		}
		else{
			string new_word = it->second;
			file2_words[i] = new_word;
		}
	}

}
//----------fuction that map of tuple for file 2---------//
void Detector::make_map_tuple(){
	string temp_tuple;
	for(int i = 0; i<file2_words.size()-N+1;i++){
		temp_tuple ="";
		for(int j = 0; j<N; j++){//iterates for N amount of words
			temp_tuple+= file2_words[i+j];//adds it to tupple
		}
		tuple_map[temp_tuple]++;//adds tupple according to frequeny
	}
}
//----------fuction that mchecks for duplicates---------//
void Detector::checkDuplicates(){
	unordered_map<string,int>::const_iterator it;
	for(int i = 0; i<file1_words.size()-N+1;i++){//iterates through words in file 1
		string temp_tuple ="";
		for(int j = 0; j<N; j++){
			temp_tuple+= file1_words[i+j];//makes n-size tupple of words
		}
		total+=1;
		it= tuple_map.find(temp_tuple);//attempts to find in tuple map
		if(it != tuple_map.end() ){
			count+= 1;//if found count is incramented by 1
		} 


	}

}
//----------fuction returns size of file 2 word vector aka number of words in file 2---------//
int Detector::get_file_2_size(){
	return file2_words.size();
}

//----------fuction that puts the whole sha-bang together---------//
int Detector::run_plagarism_check(){
	this->readFile();//reads filles
	this->makeSynonymMap();//makes Synonym map
	this->changeSynonyms();//replaces synonym
	this->make_map_tuple();//makes tuple map of 2
	this->checkDuplicates();//compares file 1 tuples to file 2 tuples
	percentage = (count*100)/total;//gets percentage
	return percentage;//returns to user

}