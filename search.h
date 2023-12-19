/*------------------------------------------------------------------------
Program 2: Search Query
Course: CS-251, Fall 2023, UIC
System: Visual Studio 2019 on Windows 10
Author: Sean Martil, starter code provided by Professors Koehler, Ordentlich, and Dey
------------------------------------------------------------------------*/

#include <iostream>
#include <string>
#include <set>
#include <map>
#include <algorithm>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

//adds token if not in set tokens
void addToken(set<string>& tokens, string token) {
    if (!tokens.count(token) && token != "") {
        tokens.insert(token);
    }
}

//Returns true if there is atleast 1 alphabetical character in string s, false otherwise
bool checkAlpha(string s) {
    int temp = s.size();
    int alphs = 0;
    for (int i = 0; i < temp; i++) {
        if (isalpha(s[i])) {
            alphs++;
        }
    }
    if (alphs == 0) {
        return false;
    }
    else {
        return true;
    }
}

//Remove all leading and trailing punctuation of string s
//Returns empty string if string s does not contain atleat one letter
string cleanToken(string s) {
    string result;
    int i1 = 0;
    int i2;
    int stringlength;
    if (!checkAlpha(s)){//return empty string if s does not contain atleast one letter
        result = "";
    }
    else {
        while (ispunct(s[i1])) {// updates index i1 to first false ispunct()
            i1++;
        }
        i2 = s.size() - 1;
        while (ispunct(s[i2])) {//updates index i2 to last false ispunct()
            i2--;
        }
        i2++;
        stringlength = i2 - i1;
        result = s.substr(i1, stringlength);
        for (int i = 0; i < stringlength; i++) { //converts to lowercase string
            if (result[i] >= 'A' && result[i] <= 'Z') {
                result[i] = result[i] + 32;
            }
        }
    }
    return result;
}

//Returns string set of unique tokens from string text
set<string> gatherTokens(string text) {
    set<string> tokens;
    
    string currword = "";
    for (auto c : text) {
        if (c == ' ') {
            currword = cleanToken(currword); //cleans token
            addToken(tokens, currword);
            currword = "";
        }
        else {
            currword += c;
        }
    }
    currword = cleanToken(currword);
    addToken(tokens, currword); //add last word
    return tokens;
}

//Helper function for buildIndex
//Adds tokens and urls where needed
//Updates page count and unique word count
void fillIndex(string url, int &count, set<string> tokens, map<string, set<string>>& index) {
    int numwords = 0;
    for (auto token : tokens) {
        if (index.count(token) == 0) {//token is not in index map
            set<string> temp;
            temp.insert(url);
            index.emplace(token, temp); //add token and url to map
            numwords++;
        }
        else{//token IS in index map, add to existing key set
            index.at(token).insert(url);
        }
    }
}

//Read the content from the file and processes it into an inverted text data structure
//Returns the count of web pages that were processed and added to the index
int buildIndex(string filename, map<string, set<string>>& index) {
    string url;
    string bodytext;
    set<string> tokens;
    ifstream inFS;
    int count = 0;

    inFS.open(filename);
    if (inFS.is_open()) {
        while (!inFS.fail()) {
            getline(inFS, url);
            count++;
            getline(inFS, bodytext);
            tokens = gatherTokens(bodytext);
            fillIndex(url, count, tokens, index);
            url = "";
            bodytext = "";
        }
        inFS.close();
        count--;
        return count;
    }
    else {
        return 0;
    }
    
}

//Helper function for findQueryMatches
//Populates result set with the set difference
void setDiff(set<string>& result, map<string, set<string>>& index, string word){
    set<string> diff;
    set_difference(result.begin(), result.end(), index[word].begin(), index[word].end(), inserter(diff, diff.begin()));
    result = diff;
}

//Helper function for findQueryMatches
//Populates result set with the set intersection
void setIntersect(set<string>& result, map<string, set<string>>& index, string word){
    set<string> inter;
    set_intersection(index[word].begin(), index[word].end(), result.begin(), result.end(), inserter(inter, inter.begin()));
    result = inter;
}

//Helper function for findQueryMatches
//Populates result set with the set union
void setUnion(set<string>& result, map<string, set<string>>& index, string word){
    set<string> onion;
    set_union(index[word].begin(), index[word].end(), result.begin(), result.end(), inserter(onion, onion.begin()));
    result = onion;
}

//Parses sentence for search entries
//Returns set containing matches
set<string> findQueryMatches(map<string, set<string>>& index, string sentence) {
    set<string> result;
    stringstream stream;
    string currword;
    stream.str(sentence);//create stringstream to parse sentence by space
    while (stream >> currword) {//breaks sentence by space
        string word = currword.substr(1, currword.size()-1);//word being parsed
        if (currword[0] == '-') {//if first char is '-', set difference
            setDiff(result, index, word);
        }
        else if (currword[0] == '+') {//if first char is '+', set intersection
            setIntersect(result, index, word);
        }
        else {//default set union
            setUnion(result, index, currword);
        }
    }
    return result;
}

//Helper function of searchEngine
//Prints out findQueryMatches's set
void printSet(set<string> results) {
    cout << "Found " << results.size() << " matching pages\n";
    for (auto element : results) {
        cout << element << endl;
    }
}

//Builds index from filename and conducts search query
void searchEngine(string filename) {
    map<string, set<string>> index;
    string command;
    cout << "Stand by while building index...\n";
    cout << "Indexed " << buildIndex(filename, index) << " pages containing " << index.size() << " unique terms\n";
    cout << "\nEnter query sentence (press enter to quit): ";
    getline(cin, command);
    do {
        set<string> result = findQueryMatches(index, command);
        printSet(result);
        cout << "\nEnter query sentence (press enter to quit): ";
        getline(cin, command);
    } while (command.length() != 0);
    cout << "Thank you for searching!\n";
}
