/*------------------------------------------------------------------------
Program 2: Search Query
Course: CS-251, Fall 2023, UIC
System: Visual Studio 2019 on Windows 10
Author: Sean Martil, starter code provided by Professors Koehler, Ordentlich, and Dey
------------------------------------------------------------------------*/

#include "search.h"
using namespace std;

int main() {
    /*---------------------------------
    * Test cases:
    * searchEngine("tiny.txt");
    * searchEngine("cplusplus.txt");
    * searchEngine("uiccs-news.txt");
    ---------------------------------*/

    string filename;
    cout << "Welcome to the Search Engine Query!\n";
    cout << "------------------------------------------------------------------\n";
    cout << "   -Add '+' to the begining of a search token (ie. tasty +healthy)\n";
    cout << "    to search for pages that contain both 'tasty' and 'healthy'\n";
    cout << "   -Add '-' to the begining of a search token (ie. tasty -mushrooms)\n";
    cout << "    to search for pages that contain 'tasty' without 'mushrooms'\n";
    cout << "------------------------------------------------------------------\n";
    cout << "Enter a textfile in the directory to search through: ";
    getline(cin, filename);
    searchEngine(filename);
    return 0;
}