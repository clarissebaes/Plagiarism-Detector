#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <cassert>
#include <functional>
#include <algorithm>
#include <math.h>
#include <unordered_map>
#include "detector.h"


using namespace std;

int main(int argc, char* argv[]){
//handles if user inputs wrong amount of files in command line
	if (argc < 4 || argc>5){
    	cerr << "Error: Invalid number of parameters! Please enter:"<<endl;
    	cerr <<"\t1. File name for a list of synonyms"<<endl;
    	cerr <<"\t2. Input File 1"<<endl;
    	cerr <<"\t3. Input File 2"<<endl;
    	cerr <<"\t4. (optional) Number N, the tuple size "<<endl;
		return 1;
    }
//if no tupple size is specified
    if(argc == 4){
    	Detector the_Detector(argv[1], argv[2], argv[3]);
    	float percent = the_Detector.run_plagarism_check();
    	cout<<"Percentage plagiarized: "<<percent<<"%"<<endl;

    }
    else{
    	int N_ = atoi(argv[4]);
    	Detector the_Detector(argv[1], argv[2], argv[3], N_);
    	if(N_> the_Detector.get_file_2_size()||N_<1){//if tuple size is too big or small
    		cerr << "Error: Invalid Tuple Size! Please enter a valid n"<<endl;
    		return 1;
    	}
    	float percent = the_Detector.run_plagarism_check();
    	cout<<"Percentage plagiarized: "<<percent<<"%"<<endl;

    }




}