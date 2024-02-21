#include "FileDescriptor.h"

using namespace std;

// Constructor with file name as argument

FileDescriptor::FileDescriptor()
{
    fileName = "";
    line_number = 0;
    char_number = 0;
    buffer = NULL;
}

FileDescriptor::FileDescriptor(char *fileName){
    // Open the file for reading
    fp.open(fileName, ios::in);
    line_number = 1;
    char_number = 0;
    buffer = new char[BUFFER_SIZE];
    // Read the first line from the file into the buffer
    fp.getline(buffer, BUFFER_SIZE);
    // Get the size of the line read

    lineSize = strlen(buffer);
}

string FileDescriptor::GetFileName()
{
    return fileName;
}

bool FileDescriptor::IsOpen()
{
    return fp.is_open();
}

char* FileDescriptor::GetCurrLine()
{
    return buffer;
}


int FileDescriptor::GetLineNum()
{
    return line_number;
}

int FileDescriptor::GetCharNum()
{
    return char_number;
}

void FileDescriptor::Close()
{
  fp.close();
}

// Get the current character from the file

char FileDescriptor::GetChar()
{
    char c = buffer[char_number];

    // If we reached the end of the line, we need to read the next line from the file
    if (lineSize == char_number)
    {
        // If we reached the end of the file, return EOF

        if (isEOF())
            return EOF;
        else
        {
            // Read the next line from the file into the buffer
            fp.getline(buffer, BUFFER_SIZE);

            // Update the line size and reset the character counter
            lineSize =  strlen(buffer);
            char_number = 0;

            // Increase the line number since we are moving to the next line
            line_number++;

            // Return a newline character to indicate the line change
            return '\n';
        }
    }
    char_number++;
    return c;
}

// Report an error with the given message
void FileDescriptor::ReportError(string msg)
{
     cout << msg << " on line: " << line_number << '\n';
     cout << buffer << '\n';

    // Print spaces or tabs until the caret position
    for (int i = 0; i < char_number - 1; i++)
    {
        cout << (buffer[i] == '\t' ? '\t' : ' ');
    }
        cout << "^\n";
}

void FileDescriptor::UngetChar(char c)
{
    char_number--;
}

bool FileDescriptor::isEOF()
{
    return fp.eof();
}


FileDescriptor::~FileDescriptor()
{
    fp.close();
    delete[] buffer;
}