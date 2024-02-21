
#include "Scanner.h"

Scanner::Scanner(char *NameOfFile)
{
    FileDescriptor *Fd = new FileDescriptor(NameOfFile);
    fd = Fd;
}

int keys = 30; /* number of keywords */
string keyword[] ={
        "and", "begin", "boolean", "by", "constant",
        "do", "else", "end", "false", "fi", "float", "for", "from",
        "function", "if", "integer", "not", "od", "or", "procedure",
        "program", "read", "return", "string", "then", "to", "true",
        "var", "while", "write"
};

// Definition of TOKEN
TOKEN *Scanner::Scan() {
    TOKEN *myToken;
    char get_char = fd->GetChar();

    // Check if the current character is the start of an identifier.
    if (isStartID(get_char))
    {
        myToken = get_id(get_char);
        return myToken;
    }

    // Check if the current character is the start of an integer literal.
    else if (isdigit(get_char) != 0)
    {
        myToken = new TOKEN();
        myToken = get_int(get_char, ' ');
        return myToken;
    }

    // Check if the current character is a minus sign, which could be part of an integer literal or an operator.
    else if (get_char == '-')
    {
        char digit = fd->GetChar();
        if (isdigit(digit) != 0)
        {
            myToken = get_int(digit, '-');
            return myToken;
        }
        else
        {
            // If it's not part of an integer literal, it is an operator (minus sign).
            if (!isSpace(digit) && (digit != EOF))
                fd->UngetChar(digit);
            myToken = new TOKEN();
            myToken->type = lx_minus;
            return myToken;
        }
    }
    // Check if the current character is a double quote, indicating the start of a string literal.
    else if (get_char == '\"')
    {
        char aChar = fd->GetChar();
        myToken = get_string(aChar);
        if (myToken->str_ptr.compare("error") == 0)
        {
            fd->ReportError("Expected End Of Quotation");
            // Skip to the next line.
            while (aChar != '\n' && aChar != EOF)
                aChar = fd->GetChar();
            return Scan();
        }
        return myToken;
    }

    // Check if the current character is the start of a comment (##).
    else if (get_char == '#')
    {
        if (fd->GetChar() == '#')
        {
            // Skip the comments enclosed by double # (# #).
            skipComments();
        }
        else
        {
            fd->ReportError("Comments are indicated by double # (# #), so We Expected another # one, the error ");
            // Skip to the next line.
            char aChar = fd->GetChar();
            while (aChar != '\n' && aChar != EOF)
                aChar = fd->GetChar();
            return Scan();
        }
        return Scan();
    }
    // Handle individual operators and symbols.
    else if (get_char == ')')
    {
        myToken = new TOKEN();
        myToken->type = lx_rparen;
        return myToken;
    }
    else if (get_char == '(')
    {
        myToken = new TOKEN();
        myToken->type = lx_lparen;
        return myToken;
    }
    else if (get_char == '=')
    {
        myToken = new TOKEN();
        myToken->type = lx_eq;
        return myToken;
    }
    else if (get_char == '/')
    {
        myToken = new TOKEN();
        myToken->type = lx_slash;
        return myToken;
    }
    else if (get_char == '!')
    {
        myToken = new TOKEN();
        get_char = fd->GetChar();
        if (get_char == '=')
        {
            myToken->type = lx_neq;
            return myToken;
        }
        else
        {
            fd->ReportError("Expected Equal = ");
            // Skip to the next line.
            char aChar = fd->GetChar();
            while (aChar != '\n' && aChar != EOF)
                aChar = fd->GetChar();
            return Scan();
        }
    }
    else if (get_char == '*')
    {
        myToken = new TOKEN();
        myToken->type = lx_star;
        return myToken;
    }
    else if (get_char == ':')
    {
        myToken = new TOKEN();
        get_char = fd->GetChar();
        if (get_char == '=')
        {
            myToken->type = Ix_colon_eq;
            return myToken;
        }
        else
        {
            myToken->type = Ix_colon;
            fd->UngetChar(get_char);
            return myToken;
        }
    }
    else if (get_char == '+')
    {
        myToken = new TOKEN();
        myToken->type = lx_plus;
        return myToken;
    }
    else if (get_char == '<')
    {
        myToken = new TOKEN();
        get_char = fd->GetChar();
        if (get_char == '=')
        {
            myToken->type = lx_le;
            return myToken;
        }
        else
        {
            myToken->type = lx_lt;
            fd->UngetChar(get_char);
            return myToken;
        }
    }
    else if (get_char == '>')
    {
        myToken = new TOKEN();
        get_char = fd->GetChar();
        if (get_char == '=')
        {
            myToken->type = lx_ge;
            return myToken;
        }
        else
        {
            myToken->type = lx_gt;
            fd->UngetChar(get_char);
            return myToken;
        }
    }
    else if (get_char == '.')
    {
        myToken = new TOKEN();
        myToken->type = lx_dot;
        return myToken;
    }
    else if (get_char == ';')
    {
        myToken = new TOKEN();
        myToken->type = lx_semicolon;
        return myToken;
    }
    else if (get_char == '[')
    {
        myToken = new TOKEN();
        myToken->type = lx_lsbracket;
        return myToken;
    }
    else if (get_char == ']')
    {
        myToken = new TOKEN();
        myToken->type = lx_rsbracket;
        return myToken;
    }
    else if (get_char == ',')
    {
        myToken = new TOKEN();
        myToken->type = lx_comma;
        return myToken;
    }
    else if (get_char == '{')
    {
        myToken = new TOKEN();
        myToken->type = lx_lbracket;
        return myToken;
    }
    else if (get_char == '}')
    {
        myToken = new TOKEN();
        myToken->type = lx_rbracket;
        return myToken;
    }

    // Check if the current character is a space, and skip any consecutive spaces.
    else if (isSpace(get_char))
    {
        skipSpaces(get_char);
        fd->UngetChar(get_char);
        return Scan();
    }

    // Check if we reached the end of the file.
    else if (get_char == EOF)
    {
        myToken = new TOKEN();
        myToken->type = lx_eof;
        return myToken;
    }

    // Check if illegal_token
    myToken = new TOKEN();
    myToken->type = illegal_token;
    myToken->str_ptr = get_char;
    return myToken;
}


TOKEN *Scanner::get_id(char c)
{
    char *string_pointer = new char[1024];
    string_pointer[0] = c;
    int count = 0;
    char nextCharacter = fd->GetChar();
    TOKEN *myToken = new TOKEN();

    while (isalpha(nextCharacter) || nextCharacter == '_' || isdigit(nextCharacter))
    {
        string_pointer[++count] = nextCharacter;
        nextCharacter = fd->GetChar();
    }

    string_pointer[++count] = '\0';

    if (!isspace(nextCharacter) && (nextCharacter != EOF))
        fd->UngetChar(nextCharacter);

    myToken->str_ptr = string_pointer;
    bool isKeyword = checkKeyword(string_pointer);

    // Check if the identifier is a keyword

    if (!isKeyword)
        myToken->type = lx_identifier;

    else
    {
        if (strcmp(string_pointer, "and") == 0)
            myToken->type = kw_and;
        else if (strcmp(string_pointer, "begin") == 0)
            myToken->type = kw_begin;
        else if (strcmp(string_pointer, "boolean") == 0)
            myToken->type = kw_bool;
        else if (strcmp(string_pointer, "by") == 0)
            myToken->type = kw_by;
        else if (strcmp(string_pointer, "constant") == 0)
            myToken->type = kw_constant;
        else if (strcmp(string_pointer, "do") == 0)
            myToken->type = kw_do;
        else if (strcmp(string_pointer, "else") == 0)
            myToken->type = kw_else;
        else if (strcmp(string_pointer, "end") == 0)
            myToken->type = kw_end;
        else if (strcmp(string_pointer, "false") == 0)
            myToken->type = kw_false;
        else if (strcmp(string_pointer, "fi") == 0)
            myToken->type = kw_fi;
        else if (strcmp(string_pointer, "float") == 0)
            myToken->type = kw_float;
        else if (strcmp(string_pointer, "for") == 0)
            myToken->type = kw_for;
        else if (strcmp(string_pointer, "from") == 0)
            myToken->type = kw_from;
        else if (strcmp(string_pointer, "function") == 0)
            myToken->type = kw_function;
        else if (strcmp(string_pointer, "if") == 0)
            myToken->type = kw_if;
        else if (strcmp(string_pointer, "integer") == 0)
            myToken->type = kw_integer;
        else if (strcmp(string_pointer, "not") == 0)
            myToken->type = kw_not;
        else if (strcmp(string_pointer, "od") == 0)
            myToken->type = kw_od;
        else if (strcmp(string_pointer, "or") == 0)
            myToken->type = kw_or;
        else if (strcmp(string_pointer, "procedure") == 0)
            myToken->type = kw_procedure;
        else if (strcmp(string_pointer, "program") == 0)
            myToken->type = kw_program;
        else if (strcmp(string_pointer, "read") == 0)
            myToken->type = kw_read;
        else if (strcmp(string_pointer, "return") == 0)
            myToken->type = kw_return;
        else if (strcmp(string_pointer, "string") == 0)
            myToken->type = kw_string;
        else if (strcmp(string_pointer, "then") == 0)
            myToken->type = kw_then;
        else if (strcmp(string_pointer, "to") == 0)
            myToken->type = kw_to;
        else if (strcmp(string_pointer, "true") == 0)
            myToken->type = kw_true;
        else if (strcmp(string_pointer, "var") == 0)
            myToken->type = kw_var;
        else if (strcmp(string_pointer, "while") == 0)
            myToken->type = kw_while;
        else if (strcmp(string_pointer, "write") == 0)
            myToken->type = kw_write;
    }
    return myToken;
}

TOKEN *Scanner::get_string(char c)
{
    char *strPointer = new char[1024];
    int ct = -1;
    char nextCharacter = c;
    TOKEN *myToken = new TOKEN();

    // Read characters until the end of the string literal or end of line or end of file.
    while ((nextCharacter != '"' && nextCharacter != '\n' && nextCharacter != EOF))
    {
        strPointer[++ct] = nextCharacter;
        nextCharacter = fd->GetChar();
    }

    // Check if the string literal is properly closed with a double quote.
    if (nextCharacter == '\"')
    {
        strPointer[++ct] = '\0';
        myToken->str_ptr = strPointer;
        myToken->type = lx_string;
        return myToken;
    }
    // If the string is not properly closed, report an error.
    myToken->str_ptr = "error";
    return myToken;
}

TOKEN *Scanner::get_int(char c, char sign)
{
    int i = 0;
    char *str_ptr = new char[1024];

    // If there is a sign, store it in the buffer.
    if (sign != ' ')
    {
        str_ptr[0] = sign;
    }
    else
    {
        i = -1;
    }
    char nextChar = c;

    TOKEN *pToken = new TOKEN();

    // Read characters until the integer literal is complete.
    do
    {
        str_ptr[++i] = nextChar;
    }
    while (isdigit(nextChar = fd->GetChar()) != 0);

    // Check if the next character is an alphabet (invalid for integers).
    if (isalpha(nextChar))
    {
        fd->ReportError("Unrecognized Int");
        // Skip to the next line.
        char aChar = fd->GetChar();
        while (aChar != '\n' && aChar != EOF)
            aChar = fd->GetChar();
        return Scan();
    }

    // If the next character is a dot, it might be part of a float literal.
    else if (nextChar == '.')
    {
        return get_float(fd->GetChar(), str_ptr, i + 1);
    }
    else
    {
        str_ptr[++i] = '\0';

        if (!isSpace(nextChar) && (nextChar != EOF))
            fd->UngetChar(nextChar);

        pToken->type = lx_integer;
        pToken->str_ptr = str_ptr;

        return pToken;
    }
}

TOKEN *Scanner::get_float(char c, char *s, int k)
{
    s[k] = '.';
    char digit = c;
    int index = k;
    if (isdigit(c))
    {
        while (isdigit(digit) != 0)
        {
            s[++index] = digit;
            digit = fd->GetChar();
        }

        // If the next character after the float literal is not a space and not EOF, put it back in the input stream.
        if (!isSpace(digit) && (digit != EOF))
            fd->UngetChar(digit);

        // Check if the next character after the float literal is an alphabet (invalid for float literals).
        if (isalpha(digit))
        {
            fd->ReportError("Unrecognized Float");
            // Skip to the next line.
            char aChar = fd->GetChar();
            while (aChar != '\n' && aChar != EOF)
                aChar = fd->GetChar();
            return Scan();
        }
        else
        {
            s[++index] = '\0';
            TOKEN *token = new TOKEN();
            token->str_ptr = s;
            token->type = lx_float;

            return token;
        }
    }
    else
    {
        fd->ReportError("Expected The Value Should Be Integer");
        // Skip to the next line.
        char aChar = fd->GetChar();
        while (aChar != '\n' && aChar != EOF)
            aChar = fd->GetChar();
        return Scan();
    }
}

bool Scanner::checkKeyword(char *key)
{
    // Check if the given string matches any of the predefined keywords.
    for (int i = 0; i < 30; i++)
    {
        if (key == keyword[i])
        {
            return true;
        }
    }
    return false;
}

void Scanner::skipComments()
{
    while (true)
    {
        // Read characters until the closing double # is found or the end of the line or end of the file.
        char c = fd->GetChar();
        while (c != '#' && c != '\n' && c != EOF)
            c = fd->GetChar();

        if (c == '\n')
            return;
        if (c == EOF)
            return;

        if (c == '#')
        {
            c = fd->GetChar();
            if (c != '#')
            {
                fd->ReportError("Unexpected end of comment.");
            }
            return;
        }
    }
}

void Scanner::skipSpaces(char c)
{
    while (isSpace(c = fd->GetChar()));

}


bool Scanner::isSpace(char c)
{
    if ((c == ' ') || (c == '\n') || (c == '\t') || (c == '\f'))
        return true;
    else
        return false;
}

// Function to check if a character is a valid starting character for an identifier.
bool Scanner::isStartID(char c)
{
    if (c == '_' || isalpha(c))
        return true;
    else
        return false;
}


Scanner::~Scanner()
{

}


