

#ifndef COMPLIER_FILEDESCRIPTOR_H
#define COMPLIER_FILEDESCRIPTOR_H

#include<iostream>
#include<cstring>
#include<fstream>

using namespace std;

#define BUFFER_SIZE 256
#define SET 1
#define UNSET 0

class FileDescriptor
{

private:
    ifstream fp;
    int lineSize;
    char *buffer;
    int line_number; /* line number in the file */
    int char_number; /* character number in the line */
    string fileName; /* file name, allocate memory for this */

public:
    FileDescriptor();
    FileDescriptor(char *fileName);
    string GetFileName();
    bool IsOpen() ; // returns true if a file is open without errors, otherwise returns false
    char *GetCurrLine(); // returns a pointer to buffer, null if EOF
    int GetLineNum();
    int GetCharNum();
    void Close (); // closes the file descriptor
    char GetChar (); // Gets the current character in the file
    void ReportError (string msg); // reports the error specifying the current line and character
    void UngetChar (char c); // puts back the current character, modifies char number
    bool isEOF();
    ~FileDescriptor();
};

#endif //COMPLIER_FILEDESCRIPTOR_H
