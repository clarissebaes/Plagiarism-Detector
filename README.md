# Plagiarism-Detector
A command-line program that performs plagiarism detection using a N-tuple comparison algorithm allowing for synonyms in the text
 
# Command to compile the code.
Compile with: clang++ -std=c++11 detectorMain.cpp detector.cpp -g -o main.exe –Wall
Run with: ./main.exe sysn_file_name file1_name file2_name N-size


# Assumption:
*	Periods, commas etc. are touching 
*	There is a space after each synonym (including the last in each line)
*	Capitalization has no effect
   * “HeLLo”= “hello”
*	Tuple is only considered as matching  if and only if all the words are same (or synonym) in the exact order 
   * "for a run" != "run for a” 
# Approach:
*	I created a Detector class, that stores all the words from each file, the synonyms as well as the map of the tuples from file 2.
*	Handle all the I/O in the main code
*	Outline of Code:
  *	Read-in all the files and store comparing files as vector <string>	
  * Use a map (Map<string, string>) to store the synonyms:
  * First word is a word that can be replaced with a synonym, second is the default word to replace it 
    * Ex.  [“run”, “jog”, “sprint”]    <“run” “run”, >  <“jog” ,“run”> <“sprint”, “run”>
    * Run is replaced by run, jog is replaced by run, sprint is replaced by run;
    * now the synonyms are taken care of
 *	Iterate over both vector < string > and find word in synonyms map ( O-log(n) ) and if found replace with default word
 *	Store the tuple of N-Size of input file 2 in an unordered_map <string, int> where string is the tuple and the int is the frequency
   * Frequency is not utilized in this current code, but it can have future applications
 * Iterate over input file 1 and compare N-sized tuples to map of file 2 tuples
   * If match, count variable is incremented
   * Total number of file 1 tuples is recorded in variable total
 * Output percentage which is calculated by count/total *100
  
# Limitations:
* Sentence restructuring is not accounted for, since order of tuple is important
* Active vs passive sentence structure will not be detected
* There are only a limited number of word delimiters

