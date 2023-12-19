# SearchEngine

SearchEngine is a Project made for CS-251 at the Univeristy of Illinois Chicago developed to challenge and help develop a better
understanding of using map and set abstractions to build a document search engine that can find matching pages for a user's search
query with lightning-fast response time. It is a simplified version of the code that Google, Bing, Yahoo, and every other modern
search engine utilizes today.

## Description

An in-depth paragraph about your project and overview of use.
This implementation of a search engine utilizes maps and sets to build a document search engine that can find matching pages for
a user's query. Similar to Google's very own search engine, users can include, exclude, search set differences, unions, and intersections
for a more refined search to find a query. 

## Getting Started

### Dependencies

* Windows 10/11
* Any IDE utilizing C++17 or newer
* Recommend using VSCode or similar
* WSL
* C/C++ Themes

### Installing

* Extract to IDE of choice, ensure all files are exported

### Executing program

* Before running, ensure to compile the program with the included makefile, executing
```
    make build
```
* To run the SearchEngine program
```
    make run
```
* The user will be instructed to enter the name of a textfile in the current directory
ie 'tiny.txt', 'uiccs-news.txt', 'stackoverflow.txt', etc

* ---------------------ENSURE SEARCH QUERIES ARE IN LOWERCASE---------------------

* The query allows search modifiers to refine a search to include and exclude search queries
* pointer
    matches all pages containing the term 'pointer' within the textfile
* simple cheap
    matches all pages containing either 'simple' OR 'cheap', or both
* tasty +healthy
    means 'tasty' AND 'healthy'
    matches all pages contain both 'tasty' and 'healthy'
* tasty -mushrooms
    means 'tasty' WITHOUT 'mushrooms'
    matches all pages containing 'tasty' but do not contain 'mushrooms'
* tasty -mushrooms simple +cheap
    means 'tasty' WITHOUT 'mushrooms' OR 'simple' AND 'cheap'
    matches pages that match ((('tasty' without 'mushrooms') OR 'simple') AND 'cheap')

## Authors

Sean Martil email@ smart71@uic.edu

## Acknowledgments

Citations & Resources
Julie Zelenski - Stanford University
Joe Hummel, PhD - Northwestern University
Shannon Reckinger, PhD - University of Illinois Chicago
Copyright 2023 Adam T Koehler, PhD - University of Illinois Chicago