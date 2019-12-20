/* ------------------------------------------------
 wlinProg4.cpp

 Program #4: Twisted Hangman
 Program delays choosing which word is chosen,
 making the game as difficult as possible.
 Class: CS 141
 Author: Emily Lin
 Lab: Tues 1pm
 System:  C++ Mac Xcode
 ------------------------------------------------------*/
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <cstring>
using namespace std;

void header();
void openFile(vector<string> &stringWithoutApostrophes);
void throwOutWordsThatIsNotTheRightLength(vector<string> &stringWithoutApostrophes,
                                          int userInputLength);
void letterUsed(vector<char> &charUsed, char userInputLetter);
void throwOutWordsWithLetter(vector<string> &stringWithoutApostrophes, char userInputLetter,
                             vector<char> &letterFound, vector<char> &storeDash);


//Display header
void header()
{
   cout << "Starting with 58528 words.   \n"
         "Author:  Emily, Lin            \n"
         "Class:   CS 141, Spring 2018   \n"
         "Lab:     Tue 1pm               \n"
         "Program: #4, Twisted Hangman   \n"
         "Xcode on a Mac                 \n"
        << endl << endl;

   cout << "Welcome to Hangman.  First you will need to choose which length   \n"
           "word you want.  Then you will have 15 letter guesses to try and   \n"
           "match all the letters in the word.                                \n"
   << endl << endl;

}


//In this function, the file will be opened and throw out any words with apostrophes
void openFile(vector<string> &stringWithoutApostrophes)
{
   ifstream inputFile;
   string stringInFile;

   //Open file with corresponded file
   inputFile.open("dictionary.txt");

   //If there's no file called dictionary.txt, print the statement
   if(!inputFile.is_open())
   {
      cout << "Could not find input file. Exiting..." << endl;
   }
   //If there's file named dictionary.txt, do the following action
   else
   {
      //Read in every words into a string
      while(inputFile >> stringInFile)
      {
         //Loop through the length for a word
         for(int i = 0; i < stringInFile.length(); i++)
         {
            //Make every letter in a word into upper case
            stringInFile.at(i) = toupper(stringInFile[i]);
         }

         //Throw out words with apostrophes
         if(strchr(stringInFile.c_str(),  '\'') == NULL)
         {
            //If the word doesn't contain apostrophes, put the word in a vector
            stringWithoutApostrophes.push_back(stringInFile);
         }
      }

   }
   //Close the file
   inputFile.close();
}


//In this function, the word that is not the same as user input length will be throw out
void throwOutWordsThatIsNotTheRightLength(vector<string> &stringWithoutApostrophes,
                                          int userInputLength)
{
   vector<string> temp;

   //Creat a temporary vector to store orginal vector
   temp = stringWithoutApostrophes;
   //Clear the original vector so that we can put in correct element
   stringWithoutApostrophes.clear();

   //Loope through entire vector
   for(int i = 0; i < temp.size(); i++)
   {
      //Find the length for the word
      size_t wordLength = strlen(temp.at(i).c_str());

      //If the word length is equal to user input length, put into the vector
      if(wordLength == userInputLength)
      {
         //Push word into vector
         stringWithoutApostrophes.push_back(temp.at(i));
      }
   }
   //Clear temporary vector
   temp.clear();

   return;
}


//In this function, the letter that user used will be store into a vector and the letter used
//will be display in alphabet order
void letterUsed(vector<char> &charUsed, char userInputLetter)
{
   char temp;
   //If user input letter, the loop will be executed
   while(userInputLetter != ' ')
   {
      //Put user input letter into the vector
      charUsed.push_back(userInputLetter);

      //In this section of code, will sort the letter into a alphbet order
      for(int pass = 1; pass < charUsed.size(); pass++)
      {
         for(int j = 0; j < charUsed.size() - pass; j++)
         {
            if(charUsed.at(j) > charUsed.at(j + 1))
            {
               temp = charUsed.at(j);
               charUsed.at(j) = charUsed.at(j + 1);
               charUsed.at(j + 1) = temp;
            }
         }
      }
      break;
   }
   return;
}


void throwOutWordsWithLetter(vector<string> &stringWithoutApostrophes, char userInputLetter,
                             vector<char> &letterFound, vector<char> &storeDash)
{
   vector<string> temp;  //Creat a temporary vector to store the origial vector
   string firstWordOnTheList;  //Creat a string to store first string find on the list

   int letterCount = 0;  //Count how target letter there are in a string

   string tempString = " ";  //Creat a temporary to store a string so that I can check how
                             //many target letter are there in a string

   //finalWord = " ";

   temp = stringWithoutApostrophes;  //First, make a copy vector into temp vector
   stringWithoutApostrophes.clear();  //Clear the original vector so that we can store
                                      //new element into vector

   //Throw out all the words that contain the usr input letter
   for(int i = 0; i < temp.size(); i++)
   {
      if(strchr(temp.at(i).c_str(), userInputLetter) == NULL)
      {
         stringWithoutApostrophes.push_back(temp.at(i));
      }
   }

   //In this point, if we continue throw out words then there will be no word left, so we
   //have to put back the words that contain the letter into original vector
   if(stringWithoutApostrophes.size() == 0)
   {
      //Creat a loop that will go through entire vector and find the words that contain
      //the letter user enter
      for(int i = 0; i < temp.size(); i++)
      {
         //If we find the words, put it back into the original vector
         if(strchr(temp.at(i).c_str(), userInputLetter) != NULL)
         {
            stringWithoutApostrophes.push_back(temp.at(i));
         }
      }

      //Find the first word in the vector
      firstWordOnTheList = stringWithoutApostrophes.front();

      //Find the index of the letter
      size_t indexForFirstLetter = firstWordOnTheList.find(userInputLetter);

      //Put the correct letter into the storeDash vector so that we will show the index of
      //the correct letter
      for(int i = 0; i < firstWordOnTheList.length(); i++)
      {
         size_t indexForTargetLetter = firstWordOnTheList.find(userInputLetter);

         storeDash.at(indexForTargetLetter) = userInputLetter;
      }


      //Clear the original vector so that we can put in the new element we want
      stringWithoutApostrophes.clear();

      //Creat a loop that will go through entire vector
      for(int i = 0; i < temp.size(); i++)
      {
         //Find the index for the letter we want in the word that is in the vector
         size_t indexForTargetLetter = (temp.at(i)).find(userInputLetter);

         //Creat a condition to check whether two words have the same index of the letter
         if(indexForFirstLetter == indexForTargetLetter)
         {
            //Store the word into temperaory string
            tempString = temp.at(i);
            //Creat a loop that will go through entire string
            for(int j = 0; j < tempString.length(); j++)
            {
               //Creat a condition to check whether how many time does the letter
               //appear in the word
               if(tempString.at(j) == userInputLetter)
               {
                  //If we find the letter in the one word, we increase the count
                  letterCount++;
               }
            }

            //Creat a condition to check whether the word have only one letter in it
            if(letterCount == 1)
            {
               //If the word have only one letter in it, we put it into the original vector
               stringWithoutApostrophes.push_back(temp.at(i));
            }

            //Make count back to 0 so that we can continue to have a new process again
            letterCount = 0;
         }
      }

      //Display to user that they found the letter
      cout << "You found letter " << userInputLetter << endl;

      //Put letter found into the vector
      letterFound.push_back(userInputLetter);
   }
   temp.clear();
   return;
}


int main()
{
   char userInputLetter = ' ';
   char userCheat = '~';
   string finalWord;

   int playCount = 15;
   int charUsedCount = 0;
   int userInputLength;

   vector<string> stringWithoutApostrophes;
   vector<char> charUsed;
   vector<char> letterFound;
   vector<char> storeDash;

   header();

   //Open file and throw out words that is not fit with description
   openFile(stringWithoutApostrophes);

   //Display how many words are there for user to guess
   cout << "Starting with " << stringWithoutApostrophes.size() << " words" << endl;

   //Ask user what length of word they want
   cout << "What length word do you want? ";
   cin >> userInputLength; //Store user input into userInputLength


   //Resize storeDash vector into user input length
   storeDash.resize(userInputLetter);

   //Print out dash correspond to user input length
   for(int i = 0; i < userInputLength; i++)
   {
      storeDash.at(i) = '_';
   }

   //Executed throw out words function
   throwOutWordsThatIsNotTheRightLength(stringWithoutApostrophes, userInputLength);

   //Display what length of word we are playing
   cout << "Now we have " << stringWithoutApostrophes.size() << " words of length "
        << userInputLength << endl;


   //Loop will be run 15 times
   while(playCount !=0)
   {
      letterUsed(charUsed, userInputLetter);

      //Print out letter that user used
      cout << endl << playCount << ". Letters used so far: ";

      charUsedCount++;

      //If the charUsed vector size is not equal to 1, run the loop
      while(charUsed.size() != 0)
      {
         //Go through entire charUsed vector
         for(int i = 0; i < charUsed.size(); i++)
         {
            //If user input ~, don't put into vector
            if(charUsed.at(i) != '~')
            {
               //Print letter
               cout << charUsed.at(i) << " ";
            }
         }
         break;
      }
      cout << endl;

      cout << "Letters found: ";

      //Print out letter that user found and print out to right position
      for(int i = 0; i < storeDash.size(); i++)
      {
         cout << storeDash.at(i) << " ";
      }

      cout << endl;

      //Ask user to guess a letter
      cout << "Guess a letter: ";
      cin >> userInputLetter;

      //Convert user input into upper case
      userInputLetter = toupper(userInputLetter);


      //Executed throw out words function
      throwOutWordsWithLetter(stringWithoutApostrophes, userInputLetter, letterFound, storeDash);


      //If user enter ~, we print what word left in the vector
      if(userInputLetter == userCheat)
      {
         //Go through entire vector
         for(int i = 0; i < stringWithoutApostrophes.size(); i++)
         {
            //Print out the word
            cout << stringWithoutApostrophes.at(i) << " ";
         }
         cout << endl;
         continue;
      }

      //Print out how many word left to guess
      cout << "Now we have " << stringWithoutApostrophes.size() << " words. " << endl;

      //Play count - 1
      playCount--;

      if(stringWithoutApostrophes.size() == 1)
      {
         finalWord = stringWithoutApostrophes.front();
      }

      //If user guess every letter in the word, print out congratulation information
      if(storeDash.at((userInputLength - 1)) != '_')
      {
         //Display again letter that user found
         for(int i = 0; i < finalWord.length(); i++)
         {
            cout << finalWord.at(i) << " ";
         }
         cout << endl;
         cout << "*** Congratulations, you did it! ***" << endl;
         break;
      }
   }
   return 0;
}



