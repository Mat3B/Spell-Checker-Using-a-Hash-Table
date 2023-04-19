/*
 * Name: Mathew Breland
 * Date Submitted: 2/28/2023
 * Lab Section: 001
 * Assignment Name: Lab 5 - Spell Checker Using a Hash Table
 */

#include "stringset.h"
#include <iostream>
#include <fstream>

void testStringset(Stringset& words);
void loadStringset(Stringset& words, string filename);
vector<string> spellcheck(const Stringset& words, string word);

void testStringset(Stringset& words)
{
    string choice;
    string word;
    do
    {
        cout << "I: insert word" << endl;
        cout << "F: find word" << endl;
        cout << "R: remove word" << endl;
        cout << "P: print words in stringset" << endl;
        cout << "Q: quit" << endl;
        cin >> choice;
        switch (choice[0])
        {
        case 'I':
        case 'i':
            cout << "Enter word to insert: ";
            cin >> word;
            words.insert(word);
            break;
        case 'F':
        case 'f':
            cout << "Enter word to find: ";
            cin >> word;
            if (words.find(word))
            {
                cout << word << " in stringset" << endl;
            }
            else
            {
                cout << word << " not in stringset" << endl;
            }
            break;
        case 'R':
        case 'r':
            cout << "Enter word to remove: ";
            cin >> word;
            words.remove(word);
            break;
        case 'P':
        case 'p':
            vector<list<string>> t = words.getTable();
            int numWords = words.getNumElems();
            int tSize = words.getSize();
            for (int i = 0; i < tSize; ++i)
            {
                list<string>::iterator pos;
                for (pos = t[i].begin(); pos != t[i].end(); ++pos)
                {
                    cout << *pos << endl;
                }
            }
            cout << "Words: " << numWords << endl;
        }
    } while (choice[0] != 'Q' && choice[0] != 'q');
}

void loadStringset(Stringset& words, string filename)
{
    
    ifstream input(filename);   // open the input file stream
    std::string currWord;

    
    if (!input) {
        throw runtime_error("Failed to open file: " + filename);    // throwing an exception if the file cant be opened (idk if we have to do this)
    }


    while (getline(input, currWord)) {   // while loop to get each line of the input and insert it   
        words.insert(currWord);
    }

    
    input.close();  // closing the file 
}

vector<string> spellcheck(const Stringset& words, string word)
{
    
    vector<string> wordList;
    string secWord = word; 

    for (size_t i = 0; i < word.length(); i++) {    // for loop that runs untl the length is met 

        for (char j = 'a'; j < 'z' + 1; j++) {      // for loop that runs until every character is passed thorugh 

            secWord.replace(i, 1, 1, j);            // replacing with met parameters

            if (secWord != word && words.find(secWord)) 
                wordList.push_back(secWord);

                secWord = word;                     //reset the word
        }
    }

    return wordList;
}