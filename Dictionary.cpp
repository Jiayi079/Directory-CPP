//
// Created by Eva Gu on 3/3/22.
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <ostream>
#include <algorithm>  

using namespace std;

struct DictionaryData {
    string DicKeyword;
    vector<string> DicSpeech;
    vector<string> DicDef;
};

vector<string> split(string str, char del) {

    // delcare temp string to store the string upto del
    vector<string> splitOut;
    string s = "";

    for (int i = 0; i < (int)str.size(); i++) {
        if (str[i] != del) {
            s += str[i];
        } else {
            splitOut.push_back(s);
            s = "";
        }
    }
	
    return splitOut;
};

string remove(string str, string targetDel){
    string word = "";
	int i = 0;
    for (auto x : str) {
		string s{x};	
        if (s.compare(targetDel) != 0) {
            word = word + s;
        } else {
			return str.substr(i+1);
        }
		i++;
    }
    return word;
}

// string replace(string userInput, string targtDel, string replaceDel) {
// 	int length;
// 	int iterate = 0;
// 	string str = "", let;
// 	length = userInput.length();
// 	length--;
// 	while (iterate <= length) {
// 		let = userInput.substr(iterate, 1);
// 		if (let == targtDel) {
// 			str = str + replaceDel;
// 		}
// 		else {
// 			str = str + let;
// 		}
// 		iterate++;
// 	}
// 	return str;
// };

// int getSize(vector<DictionaryData> vect) {
// 	int = vect.end();
// 	return ;
// }

// Below method is created to convert the given 
// string in upper case in order to make things in same case
string convertToUpperCase(string userInput) {

	for (int i = 0; i <= userInput.size(); i++)
	{
		if (userInput[i] >= 97 && userInput[i] <= 122)
		{
			userInput[i] = userInput[i] - 32;
		}
	}

	return userInput;
};

// Below method is created to trim the space
string trim(const string& userInput)
{
	size_t first = userInput.find_first_not_of(' ');
	if (string::npos == first)
	{
		return userInput;
	}
	size_t last = userInput.find_last_not_of(' ');
	return userInput.substr(first, (last - first + 1));
};

string convertToCamelCase(string inpt_str) {
	if (inpt_str[0] >= 97 && inpt_str[0] <= 122)
	{
		inpt_str[0] = inpt_str[0] - 32;
	}

	return inpt_str;
};



int main() {
    
    struct DictionaryData dic;
    vector<DictionaryData> vec;
    std::string eachLine;

    // read the text file

    fstream dataFile;

    cout << "! Opening data file... ";

    while (!dataFile.is_open()) {
        string path;
        cin >> path;


        dataFile.open(path,ios::in);
        if (dataFile.is_open()) {
            cout << "! Loading data..." << endl;



		    while (getline(dataFile, eachLine)) {
			    dic.DicKeyword = split(eachLine, '|')[0]; // get all keyword from each line
				eachLine = remove(eachLine, dic.DicKeyword);

				// eachLine = remove(remove(eachLine, dic.DicKeyword), "|");
				// cout << eachLine << endl;

				while (eachLine.find("|") != string::npos) {
					eachLine = remove(eachLine, "|");
					dic.DicSpeech.push_back(eachLine.substr(0, eachLine.find(" ")));
					dic.DicDef.push_back(eachLine.substr(eachLine.find(">>")+3, eachLine.find(".")-9));
					// eachLine = split(eachLine, '|')[1];
				}
				vec.push_back(dic);
			    dic = {}; 
            }
            cout << "! Loading completed..." << endl;
            cout << "! Closing data file..." << path << endl;
	        cout << "----- DICTIONARY 340 C++ -----" << endl;
        } else {
            cout << "<!>ERROR<!> ===> File could not be opened." << endl;
            cout << "<!>ERROR<!> ===> Provided file path: " << path << endl;
            cout << "<!>Enter the CORRECT data file path: ";
        }
    }
    
    int value;
	int check;
	int ValidationCheck, counter;
	string DicKeyword;

	string val_distinct[15];
	string val_distinct_temp[15];

	vector<DictionaryData>::iterator distinct_vp;

	string search, word_key, distinct, DicSpeech;


	int dicDefSize = 0;

	for (int i = 0; i < vec.size(); i++) {
		for (int j = 0; j < vec.at(i).DicDef.size(); j++) {
			dicDefSize++;
		}
	}

	cout << "------ Keywords: " << vec.size() << "\n------ Definitions: " << dicDefSize << endl;
	
	int times = 1;

	//loop starts here
	while (search != "!Q" || search != "!q") {

		cout << "Search [" << times << "]: " << endl;
		cin >> search;

	
		getline(cin, search);
		value = 0;

		if (search == "!Q")
		{
			cout << "\n-----THANK YOU-----\n ";
			exit(0);
		}



		for (int i = 0; i < vec.size(); i++)
		{
			if (split(search, ' ').size() == 1) {

				check = 0;
				if (convertToUpperCase(vec[i].DicKeyword) == convertToUpperCase(search)) {
					// cout<<"        |\n\n";
					for (int j = 0; j < vec[i].DicSpeech.size(); j++) {
						// cout<<"         ";
						if (convertToUpperCase(search) == "ARROW") {

							val_distinct[check] = trim(vec[i].DicSpeech[j]) + "] : " + vec[i].DicDef[j] + "  -=>>.";
							DicKeyword = convertToCamelCase(vec[i].DicKeyword);
							check++;
						}
						else {
							val_distinct[check] = trim(vec[i].DicSpeech[j]) + "] : " + vec[i].DicDef[j];
							DicKeyword = convertToCamelCase(vec[i].DicKeyword);
							check++;
						}
                        value = 1;
					}

				}
			}
			if (split(search, ' ').size() == 2 && ((convertToUpperCase(split(search, ' ')[1])).compare("DISTINCT")) == 0) {

				word_key = split(search, ' ')[0];


				if (convertToUpperCase(vec[i].DicKeyword) == convertToUpperCase(word_key)) {

					check = 0;
					for (int j = 0; j < vec[i].DicSpeech.size(); j++)
					{
						ValidationCheck = 0;

						for (int k = 0; k < sizeof(val_distinct) / sizeof(val_distinct[0]); k++)
						{
							if (val_distinct[k] == trim(vec[i].DicSpeech[j]) + "] : " + vec[i].DicDef[j])
							{
								ValidationCheck = 1;
							}

						}

						if (ValidationCheck == 0) {
							val_distinct[check] = trim(vec[i].DicSpeech[j]) + "] : " + vec[i].DicDef[j];
							DicKeyword = convertToCamelCase(vec[i].DicKeyword);
							check++;
							value = 1;
						}


					}
				}

			}

			if (split(search, ' ').size() == 2 && ((convertToUpperCase(split(search, ' ')[1])).compare("DISTINCT")) != 0) {

				word_key = split(search, ' ')[0];
				DicSpeech = split(search, ' ')[1];
				check = 0;
				if (convertToUpperCase(vec[i].DicKeyword) == convertToUpperCase(word_key)) {
					for (int j = 0; j < vec[i].DicSpeech.size(); j++) {

						if (convertToUpperCase(trim(vec[i].DicSpeech[j])) == convertToUpperCase(DicSpeech)) {
							val_distinct[check] = trim(vec[i].DicSpeech[j]) + "] : " + vec[i].DicDef[j];
							DicKeyword = convertToCamelCase(vec[i].DicKeyword);
							value = 1;
							check++;
							
						}

					}
				}


			}

			if (split(search, ' ').size() == 3) {

				word_key = split(search, ' ')[0];
				DicSpeech = split(search, ' ')[1];

				if (convertToUpperCase(vec[i].DicKeyword) == convertToUpperCase(word_key)) {
					check = 0;
					for (int j = 0; j < vec[i].DicSpeech.size(); j++)
					{
						ValidationCheck = 0;

						for (int k = 0; k < sizeof(val_distinct_temp) / sizeof(val_distinct_temp[0]); k++)
						{
							if (val_distinct_temp[k] == trim(vec[i].DicSpeech[j]) + "] : " + trim(vec[i].DicDef[j]))
							{
								ValidationCheck = 1;
							}

						}

						if (value == 0) {
							val_distinct_temp[check] = trim(vec[i].DicSpeech[j]) + "] : " + trim(vec[i].DicDef[j]);
							check++;
							// value=1;
							DicKeyword = convertToCamelCase(vec[i].DicKeyword);
						}


					}

					for (int j = 0; j < check; j++) {

						counter = 0;
						if (convertToUpperCase(trim(split(val_distinct_temp[j], ']')[0])) == convertToUpperCase(DicSpeech)) {
							
							val_distinct[counter] = val_distinct_temp[j];


							value = 1;
							counter++;
						}

					}


				}


			}


		}

		DicSpeech = convertToUpperCase(DicSpeech);
		if (value == 0 && DicSpeech != "ADJECTIVE" && DicSpeech != "VERB" && DicSpeech != "ADVERB" && DicSpeech != "NOUN" && split(search, ' ').size() == 3) {
			cout << "        |\n";
			cout << "         ";
			cout << "<2nd argument must be a part of DicSpeech or \"distinct\">";
			cout << "\n        |\n\n";

		}
		if (value == 0 && (DicSpeech == "ADJECTIVE" || DicSpeech == "VERB" || DicSpeech == "ADVERB" || DicSpeech == "NOUN" || split(search, ' ').size() < 3)) {
			cout << "        |\n";
			cout << "         ";
			cout << "<Not found>";
			cout << "\n        |\n\n";

		}
		if (value == 1)
		{
			cout << "        |\n\n";

			sort(begin(val_distinct), end(val_distinct));
			for (int k = 0; k < 15; k++) {
				if (val_distinct[k] != "")
				{
					cout << "         ";
					cout << DicKeyword << " [" << val_distinct[k] << " " << endl;

				}
			}
			cout << "\n        |\n\n";
		}

		for (int k = 0; k < 15; k++) {
			val_distinct[k] = "";
		}
	}

	return 0;
};



#include "Dictionary.h"
