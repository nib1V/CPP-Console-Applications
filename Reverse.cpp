//This program is used to revese the order of words in a file from last to first not the characters themselves
//A test input is given in the repository under the name "Rinput.txt" feel free to try it out

#include "Library.h"

//Giving my file name a to constant in order to clean up the code

const string rfile = "Rinput.txt";

int main()
{
    try
    {
        vector<string>buffer;                               //Creating a vector that will serve as a buffer
        ifstream ist(rfile);                                //Opening the file for input
        if (!ist) error("Couldn't Open File for Input!");   //Handling error with the file
        while(!ist.eof())                                   //For every single entry in the file
        {
            string tempword;                //Creating a dummy variable that will be used as input to the buffer
            ist >> tempword;
            buffer.push_back(tempword);     //Reading the entry of the input file and pushing it into the buffer
            if(!ist.eof())                  //If the file hasn't reached the end then input a "space" into the buffer
            {
                buffer.push_back(" ");
            }
        }
        ist.close();                                        //Closing the file to prevent any potential overflow
        ofstream ost(rfile);                                //Opening the same file but now as output    
        if (!ost) error("Couldn't Open File for Output!");  //Handling errors
        for(int i = buffer.size() - 1; i >= 0; i--)         //For every single item in the buffer starting from the last
        {
            ost << buffer[i];                               //Give that item to the output file
        }
    }
    catch(exception&e)
    {
        cerr << e.what() << endl;
    }
    catch(...)
    {
        cerr << "Unexpected Error" << endl;
    }
}