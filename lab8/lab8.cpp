/*
  Author: Hasan Abdullah
  Course: {135,136}
  Instructor: Gilbert Pajela
  Assignment: Lab 8

  This program inputs a sentence as a string, calls appropriate functions to
process the sentence, and outputs the final string (and number of words in it).
*/

#include <iostream>
#include <string>
#include <cassert>
using namespace std;

const int MAXWORDS = 12;   //maximum number of words in sentence

//Precondition: the words in sentence are delimited by single spaces, and the
//number of words in sentence is 2 - 12; first and last parts aren't space(s)
//and the sentence ends in an end character ('.', '!', or '?'); the words are
//composed of alphanumeric characters only (so no commas, semicolons, etc.)
int splitSent(string sentence, string words[], int maxWords);
//Postcondition: inputs sentence into words[] (each word is an element and last
//word doesn't include its end character); returns number of words in sentence

//Precondition: words[] and numWords both outputs of splitSent and endChar is
//the last character in sentence ('.', '!', or '?')
string convertArray(string words[], int numWords, char endChar);
//Postcondition: words[] converted to a sentence (string), ending in endChar

//Precondition: words[] and numWords both outputs of splitSent
void capitalizeI(string words[], int numWords);
//Postcondition: all elements in words[] which == "i" become "I"

//Precondition: words[] and numWords both outputs of splitSent; 0<=i<=numWords
void removeWord(string words[], int& numWords, int i);
//Postcondition: i'th element in words is removed, and right elements slide in
//(e.g. {1,2,3,4}, i=1 -> {1,3,4}), reducing array size (numWords) by 1

//Precondition: words[] and numWords both outputs of splitSent
void replaceCS(string words[], int& numWords);
//Postcondition: if words[i] + " " + words[i+1] == "computer science" (case-
//sensitive) words[i] becomes "CS" and removeWord is called for words[i+1]

//Precondition: words[] and numWords both outputs of splitSent
void removeDuplicates(string words[], int& numWords);
//Postcondition: if words[i] == words[i+1] (case-sensitive) removeWord is
//called for words[i+1] (assumes user does max. of 2 consecutive duplicates)

int main () {

  cout << "Enter a sentence containing 2 to 12 words. The sentence must end"
       << endl << "in a '.', '!', or '?':" << endl;
  //I assumed the user entered a legal sentence (i.e. pre-cond. of splitSent)
  string sentence;
  getline(cin,sentence);   //gets characters/words AND spaces from input
  //.at function considers 1st char as 0th character, last as .length()-1
  char endChar = sentence.at(sentence.length()-1);   //'.', '!', or '?'
  assert(endChar == '.' || endChar == '!' || endChar == '?');
  string words[MAXWORDS];
  int numWords = splitSent(sentence,words,MAXWORDS);   //# of words in sentence
  assert(numWords >= 2 && numWords <= MAXWORDS);
  //words[MAXWORDS] now contains all words in sentence
  int newNumWords = numWords;   //newNumWords gets changed, numWords remains
  capitalizeI(words,newNumWords); //first, capitalize all "i"
  removeDuplicates(words,newNumWords); //then, remove consecutive duplicates
  replaceCS(words,newNumWords); //then, replace all "computer science" with "CS"
  removeDuplicates(words,newNumWords); //remove any consecutive "CS" duplicates
  //since removeDuplicates called twice, 3 consecutive duplicates fixed too

  cout << "The revised sentence is:" << endl
       << convertArray(words,newNumWords,endChar) << endl
       << "Your original sentence had "<<numWords<<" words, and the revised "
       << "sentence has "<<newNumWords<<" words." << endl;
  /* TESTING (the following is a table of inputs and outputs):
                          string input: num: newNum: string output:
                           Hello world! 2    2       Hello world!
             0 1 2 3 4 5 6 7 8 9 10 11. 12   12      0 1 2 3 4 5 6 7 8 9 10 11.
                               i am me. 3    3       I am me.
              computer science is cool! 4    3       CS is cool!
                   i ate the the pizza. 5    4       I ate the pizza.
             computer computer science. 3    1       CS.
              computer science science? 3    1       CS?
     computer science computer science. 4    1       CS.
     [the next 2 lines are for the same input/output]
         i like like pizza and i i like 12   7       I like pizza and I like CS!
     computer computer science science! */
  return 0;
}

int splitSent(string sentence, string words[], int maxWords) {
  //precondition guarantees sentence starts with a word
  int numWords = 1, pos = 0, startWord = 0, endWord = 0;
  //string function .at(i) works when i is 0 - sentence.length()-1 (inclusive)
  while (numWords <= maxWords && pos < sentence.length()-1) {
    //if next position is part of the word (and not end of sentence)
    if (sentence.at(pos+1) != ' ' && sentence.at(pos+1) != '.' &&
	sentence.at(pos+1) != '!' && sentence.at(pos+1) != '?') {
      endWord++; pos++;   //increase positions for next iteration
    }
    //if current pos is end of a word or right before end of sentence
    else if (sentence.at(pos+1) == ' ' || sentence.at(pos+1) == '.' ||
	     sentence.at(pos+1) == '!' || sentence.at(pos+1) == '?') {
      string temp = "";   //will become the current word in the sentence
      if (sentence.at(pos+1) == ' ') {   //there are more word(s) in sentence
	for (int i = startWord; i <= endWord; i++) {
          temp += sentence.at(i);   //temp records the current word
        }
        words[numWords-1] = temp;   //since numWords was initialized to 1
        numWords++;   //a space after a word guarantees another word (precond.)
	pos += 2; startWord = pos; //pos+1 is ' ', so next word starts at pos+2
        endWord = startWord;   //endWord increases with respect to startWord
      }
      else {   //i.e. next pos is end of sentence
	for (int j = startWord; j <= endWord; j++) {
          temp += sentence.at(j);
        }   //assert: numWords == total # of words in sentence
        words[numWords-1] = temp;   //last word in array is numWords-1
	pos++;   //assert: pos == sentence.length()-1, which stops while loop
      }
    }   //end of else if
  }   //end of while loop
  return numWords;
  /* TESTING (the following is a table of inputs and outputs):
                string input:   numWords:
                 Hello world!   2
            My name is Hasan.   4
     a b c d e f g h i j k l.   12
  -words[0] to words[numWords-1] output the correct strings for each. */
}

string convertArray(string words[], int numWords, char endChar) {
  string sentence = "";   //will become the sentence contained in words[]
  for (int i = 0; i < numWords; i++) {   //go through entire array
    sentence += words[i];   //add the word to sentence
    if (i < numWords-1) {   //add a space if not last word
      sentence += " ";
    }
    else if (i == numWords-1) {   //add the end character if last word
      sentence += endChar;
    }
  }
  return sentence;
  /* TESTING: inputs = "Hello world!" and "0 1 2 3 4 5 6 7 8 9 10 11."
     outputs = "Hello world!" and "0 1 2 3 4 5 6 7 8 9 10 11." */
}

void capitalizeI(string words[], int numWords) {
  for (int i = 0; i < numWords; i++) {   //search through all words in array
    if (words[i] == "i") {
      words[i] = "I";
    }
  }
  return;
  /* TESTING (the following is a table of inputs and outputs):
                  string input:   string output:
                           i i.   I I.
       i i i i i i i i i i i i.   I I I I I I I I I I I I.
     i like typing i but not I.   I like typing I but not I. */
}

void removeWord(string words[], int& numWords, int i) {
  assert(i >= 0);
  assert(i <= numWords);
  if (i < numWords-1) {   //i'th element is not the last element in words[]
    for (int j = i; j < numWords-1; j++) { //from i'th word to 2nd-to-last word
      words[j] = words[j+1];   //the current word = the next word
    }   //assert: 2nd-to-last element == last element
    numWords--;   //numWords is pass-by-reference
  }
  else if (i == numWords-1) {
  //if i'th element is the last word, reducing numWords by 1 "removes" it
    numWords--;
  }
  return;
  /* TESTING (the following is a table of inputs and outputs):
                  string input:  i:  numWords:  string output:
                   Hello world!   0  1          world!
     0 1 2 3 4 5 6 7 8 9 10 11.   0  11         1 2 3 4 5 6 7 8 9 10 11.
              My name is Hasan.   3  3          My name is.
                    My name is.   3  3          My name is.
       a b c d e f g h i j k l.  11  11         a b c d e f g h i j k. */
}

void replaceCS(string words[], int& numWords) {
  for (int i = 0; i < numWords-1; i++) { //limit: compare 2nd-to-last and last
    if (words[i] == "computer" && words[i+1] == "science") {
      words[i] = "CS";
      removeWord(words,numWords,i+1);   //side effect: numWords--
    }
  }
  return;
  /* TESTING (the following is a table of inputs and outputs):
                          string input:  numWords:  string output:
                      computer science.  1          CS.
     computer science computer science.  2          CS CS.
     [the next 3 lines are for the same input/output]
        computer science is awesome and  9          CS is awesome and CS is
           computer science is equal to             equal to CS!
                      computer science! */
}

void removeDuplicates(string words[], int& numWords) {
  //assumes user does maximum of 2 consecutive duplicates
  for (int i = 0; i < numWords-1; i++) { //limit: compare 2nd-to-last and last
    if (words[i] == words[i+1]) {
      removeWord(words,numWords,i+1);   //side effect: numWords--
    }
  }
  return;
  /* TESTING (the following is a table of inputs and outputs):
                              string input:  numWords:  string output:
                               hello hello.  1          hello.
     hi hi i i am am ok ok and and you are?  7          hi i am ok and you are?
                   0 0 1 1 2 2 3 3 4 4 5 5.  6          0 1 2 3 4 5. */
}
