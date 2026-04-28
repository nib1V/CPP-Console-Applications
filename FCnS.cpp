//FCnS stands for File Connect and Sort
//Two test inputs are given in the repository under the names "input1.txt" and "input2.txt" feel free to try them out

#include "Library.h"

//Giving my files' names to constants in order to clean up the code

const string in1 = "input1.txt";
const string in2 = "input2.txt";
const string nin = "newfile.txt";

int main()
{
    try
    {
        vector<string>nfile;    //Creating a vector that will store all of the text contained in the .txt files
        ifstream ist1(in1);     //Opening the files as input to the program
        ifstream ist2(in2);
        if(!ist1 || !ist2) error("Couldn't open one or more files!");   //Handling error if file couldn't open
        while (!ist1.eof())     //While the file still has something in it read from it
        {
            string temp;            //Then create a dummy string variable that will temporarly hold the data
            ist1 >> temp;           //From the input file
            nfile.push_back(temp);  //Give the vector said value from the file
        }
        while (!ist2.eof())         //Do the same but now for the second file
        {
            string temp;
            ist2 >> temp;
            nfile.push_back(temp);
        }
        sort(nfile.begin(), nfile.end());   //Using the sort algorithm in order to sort alphabetically the given words
        ist1.close();                       //Closing the files in order to prevent any potential overflow
        ist2.close();
        ofstream ost(nin);                          //Creating a new file that will serve as the output of the program
        if(!ost) error("Couldn't open new file!");  //Handling errors
        for(int i = 0; i < nfile.size(); i++)       //For every item in the vector
        {   
            ost << nfile[i];                        //Give the output file an entry
            if (!((i + 1) == nfile.size()))         //If the next item isn't the last then print a "space"
            {
                ost << " ";
            }
        }
        ost.close();                //Closing the file to prevent any potential overflow
    }
    catch(exception& e)
    {
        cerr << e.what() << endl;
    }
    catch(...)
    {
        cerr << "Unexpected Error Occured!" << endl;
    }
}