#include <iostream>
#include "Scanner.h"
#include "FileDescriptor.h"
#include <iomanip> // For setw()

using namespace std;

int main()
{
    Scanner *scanner;
    TOKEN *token;
    int i = 0;
    ifstream file("C:\\Users\\AB\\CLionProjects\\Scanner\\talamira.txt");
    if (!file) {
        cerr << "Error opening the file." << endl;
        return 1;
    }
    FileDescriptor *fd = new FileDescriptor("C:\\Users\\AB\\CLionProjects\\Scanner\\talamira.txt");

    scanner = new Scanner(fd);
    string tokens[] = { "lx_identifier", "lx_integer", "lx_string", "lx_float",
                        "kw_program", "kw_var", "kw_constant", "kw_integer", "kw_boolean", "kw_string", "kw_float",
                       "kw_true", "kw_false", "kw_if", "kw_fi", "kw_then", "kw_else", "kw_while", "kw_do", "kw_od",
                       "kw_and", "kw_or", "kw_read", "kw_write", "kw_for", "kw_from", "kw_to", "kw_by",
                       "kw_function", "kw_procedure", "kw_return", "kw_not", "kw_begin", "kw_end",
                       "lx_lparen", "lx_rparen", "lx_lbracket", "lx_rbracket", "lx_lsbracket", "lx_rsbracket",
                       "Ix_colon", "lx_dot", "lx_semicolon", "lx_comma", "Ix_colon_eq",
                       "lx_plus", "lx_minus", "lx_star", "lx_slash",
                       "lx_eq", "lx_neq", "lx_lt", "lx_le", "lx_gt", "lx_ge", "lx_eof",
                       "illegal_token"
    };

    // Calculate the maximum length of the token names
    int maxTokenTypeLength = 0;
    for (const string& t : tokens) {
        maxTokenTypeLength = max(maxTokenTypeLength, static_cast<int>(t.length()));
    }

    // Print Type & Value
    cout << left << setw(maxTokenTypeLength + 2) << "TYPE:" << "VALUE:" << endl;
    cout << setfill('-') << setw(maxTokenTypeLength + 14) << "" << setfill(' ') << endl;

    do {
        token = scanner->Scan();
        if (token->type == lx_eof)
        {
            cout << left << setw(maxTokenTypeLength + 2) << tokens[token->type];
            break;
        }

        // Print the TYPE and VALUE with proper alignment
        cout << left << setw(maxTokenTypeLength + 2) << tokens[token->type];
        if (token->str_ptr != "")
            cout << token->str_ptr;
        cout << endl;

    } while(true);

    delete scanner;
    delete fd;

    return 0;
}
