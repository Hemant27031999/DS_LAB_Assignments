
/**
 * @file prims.cpp
 * @author Hemant 
 * @brief 
 * @date 2019-09-23
 * 
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream> 
#include <map>
#include <algorithm>
#include <list>
#include <time.h>
#include <bits/stdc++.h> 
#include <string>
using namespace std;


/*
 * @brief function to split a string against a delimiter provided
 * @param string to be devided
 * @param delimeter against which the string will be divided
 * @return vector containing the divided string
*/
vector<string> split(string str, char delimiter) {
  vector<string> internal;
  stringstream ss(str);
  string tok;
  while(getline(ss, tok, delimiter)) {
    internal.push_back(tok);
  }
  return internal;
}


/*
 * the main driving program
*/
int main()
{
	clock_t start, end;
	double cpu_time_used;
	start = clock();

	ifstream fin; 
	fin.open("2019_CSN_261_L5_P2.csv"); 
	string line,s;
	vector<string> words;
	map<string, int> store; 
	getline(fin, line);
	string max="";

	cout<<"Input is : "<<endl;
	while (fin) { 
  		words = split(line, ',');
  		s = words[0]+words[1];
  		max = (max>s)?max:(words[0]>words[1]?words[0]:words[1]);
  		
  		store[s] = stoi(words[2]);
  		cout<<"{"<<s<<", "<<store[s]<<"}"<<endl;
		getline(fin, line);
    } 

    vector<pair<string,int>> vec;
    vector<pair<string,int>> MSP;

    copy(store.begin(), store.end(), back_inserter<vector<pair<string,int>>>(vec));

    sort(vec.begin(), vec.end(), [](const pair<string,int>& l, const pair<string,int>& r) {
			if (l.second != r.second)
				return l.second < r.second;

			return l.first < r.first;
		});

    map<char, char> final;
    int c = (int) max.at(0);
    char temp, copy;
    bool b;

    for(int i=65; i<=c; i++){
    	temp = (char) i;
    	final[temp] = temp;
    }

    char c1, c2;
    for (auto const &pair: vec) {

    	c1 = pair.first.at(0);
    	c2 = pair.first.at(1);
    	if(final[c1] != final[c2]){
    		b = (final[c1] < final[c2])?true:false;

    		if(b){
    		copy = final[c2];
    		final[c2] = final[c1];
    		for(int i=65; i<=c; i++){
		    	temp = (char) i;
		    	if(final[temp] == copy)
		    		final[temp] = final[c1];
			    }
	    	}
	    	else{
	    		copy = final[c1];
	    		final[c1] = final[c2];
	    		for(int i=65; i<=c; i++){
			    	temp = (char) i;
			    	if(final[temp] == copy)
			    		final[temp] = final[c2];
			    }
	    	}

	    	MSP.insert(MSP.end(), pair);
    	}

		
	}

	cout<<endl;

	bool decision = true;

	for(int i=65; i<=c && decision; i++){
	    	temp = (char) i;
	    	if(final['A'] != final[temp]) decision = false;
	    }

	if(decision){
	cout<<"The final MSP is : "<<endl;
	int sum = 0;
	for (auto const &pair: MSP) {
		sum += pair.second;
		cout << '{' << pair.first << ", " << pair.second << '}' << '\n';
		}

	cout<<"The total weight of MSP is : "<<sum<<endl;
	}
	else
		cout<<"No MSP is possible."<<endl;

	string out;
	out = "graph output {\n";

	for (auto const &pair: MSP) {
		out += pair.first.at(0) + string(" -- ") + pair.first.at(1) + string("[label=\"") + to_string(pair.second) + string("\"];\n");
		}

	out += "}";

	int n = out.length();
	char char_array_out[n + 1];
	strcpy(char_array_out, out.c_str()); 

	FILE *fptr;
    fptr = fopen("firstgraph.dot","w");

    if(fptr == NULL)
    {
      printf("Error!");   
      exit(1);             
    }

    fprintf(fptr,"%s",char_array_out);
    fclose(fptr);

    end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	cout<<"Time Taken : "<<cpu_time_used<<endl;
	
	return 0;
}

