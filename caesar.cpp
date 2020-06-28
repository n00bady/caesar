#include <iostream>
#include <string>

using namespace std;

// Encrypt function
int encrypt(char text[256], int key)
{
    char ch;
    int i;

    for ( i = 0; i < text[i] != '\0'; i++ )
    {
        ch = text[i];

        if ( ch >= 'a' && ch <= 'z')
        {
            ch = ch + key;
            if ( ch > 'z' )
            {
                ch = ch - 'z' + 'a' - 1;
            }
            text[i] = ch;
        }
        else if (ch >= 'A' && ch <= 'Z')
        {
            ch = ch + key;

            if ( ch > 'Z')
            {
                ch = ch - 'Z' + 'A' - 1;
            }
            text[i] = ch;
        }
    }
    cout << "Encrypted message: " << endl;
    cout << text << endl;

    return 0;
}

// Decrypt function
int decrypt(char text[256], int key)
{
    char ch;
    int i;
    
    for (i = 0; i < text[i] != '\0'; i++)
    {
        ch = text[i];

        if (ch >= 'a' && ch <= 'z')
        {
            ch = ch - key;
            if (ch < 'a')
            {
                ch = ch + 'z' - 'a' + 1;
            }
            text[i] = ch;
        }
        else if (ch  >= 'A' && ch <= 'Z')
        {
            ch = ch - key;
            if (ch < 'A')
            {
                ch = ch + 'Z' - 'A' + 1;
            }
            text[i] = ch;
        }
    }
    cout << "Decrypted message: " << endl;
    cout << text << endl;

    return 0;
}

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        cout << "Usage: ceasar <option> <text> <key>" << endl;
        exit(1);
    }
    // Make the 4th argument int
    string str = argv[3];
    std::string::size_type sz;
    int x = stoi(str, &sz);

    // TODO: Add decrypt and cracking functions
    if (string(argv[1]) == "-e")
    {
        encrypt(argv[2], x);
    }
    else if (string(argv[1]) == "-d")
    {
        decrypt(argv[2], x);
    }
    else
    {
        cout << "WTF?! is wrong?!" << endl;
    }
}

