/*
 * Name: Mathew Breland 
 * Date Submitted: 2/28/2023
 * Lab Section: 001
 * Assignment Name: Lab 5 - Spell Checker Using a Hash Table
 */

#include "stringset.h"

Stringset::Stringset() : table(4), num_elems(0), size(4) {}

//Used in test cases and testStringset() in main.cpp, do not modify
vector<list<string>> Stringset::getTable() const
{
    return table;
}

//Used in test cases and testStringset() in main.cpp, do not modify
int Stringset::getNumElems() const
{
    return num_elems;
}

//Used in test cases and testStringset() in main.cpp, do not modify
int Stringset::getSize() const
{
    return size;
}

void Stringset::insert(string word)
{
    
    size_t hashCode = std::hash<std::string>{}(word);  // calculating the hash code 

   
    size_t bucketIndex = hashCode % table.size();     // calculating the index   

    if (find(word)) // this runs if the word is already in the set 
    {
        return;
    }

    table[bucketIndex].push_back(word);    // adding the word to the bucket 
    ++num_elems;                            // incrementing the number of elements 

   
    if (num_elems >= size)  // this runs if need to resize the table 
    {
        
        size *= 2;          // doubling the size of the table (don't really know why it is *2, was just told to)

        vector<list<string>> new_table(size);    // creating a new table with the new size

        for (const auto& bucket : table){        // two for loops that rehash all of the previous information into the new table 
        
            for (const auto& elem : bucket){
            
                size_t new_bucketIndex = std::hash<std::string>{}(elem) % new_table.size();

                new_table[new_bucketIndex].push_back(elem);

            }
        }

               table = std::move(new_table);    // replacing the old table with the new table 

    }
}



bool Stringset::find(string word) const
{
    
    size_t hashCode = std::hash<std::string>{}(word);  // calculating the hash code

    size_t bucketIndex = hashCode % table.size();     // calculating the index 

    
    auto it = std::find(table[bucketIndex].begin(), table[bucketIndex].end(), word);  // searching for the word in the bucket via iteration

    
    if (it != table[bucketIndex].end()) {    // if the word is found return true
    
        return true;
    }

    return false;   // if the word isn't found then return false 
}

void Stringset::remove(string word)
{
  
    size_t hashCode = std::hash<std::string>{}(word);  // calculating the hash code

   
    size_t bucketIndex = hashCode % table.size(); // calculating the index 

   
    auto it = std::find(table[bucketIndex].begin(), table[bucketIndex].end(), word);  // searching for the word in the bucket via iteration

   
    if (it != table[bucketIndex].end())    // if statement if the word is found
    {
        table[bucketIndex].erase(it);      // erase it from the bucket 
        --num_elems;                        // decrement the number of elements 
    }
}
