#include <iostream>
#include <string>

using namespace std;

void show_usage()
{
    cout << "Usage: caesar <option> <text> <key>" <<endl;
    cout << "Options: " <<endl;
    cout << "\t -e,  Encrypts a string with a key." << endl;
    cout << "\t -d,  Decrypts a string if provided a key. " << endl;
    cout << "Key must be an int number between 1-25!" << endl;
}

// Encrypt function
int encrypt(char text[256], int key)
{
    char ch;
    int i;

    for ( i = 0; i < text[i] != '\0'; i++ )
    {
        ch = text[i];
        // I don't really understand it but for some reason if
        // the ascii value + the key is bigger than 127 it gets negative
        // and cannot be displayed as a character because there are no
        // negative ascii.
        // Instead I temporary turn then to int and test to see if they are
        // bigger than the int asciivalue of z then make the calculations
        // and turn into char again.
        // There is probably a better solution or maybe I should have 
        // convert it them all to int in the beggining and turn them to chars
        // at the end...
        // Need more researching.
        if ( ch >= 'a' && ch <= 'z')
        {
            int tmp = int(ch) + key;

            if (tmp > int('z'))
            {
                tmp = tmp - int('z') + int('a') - 1;
                ch = char(tmp);
            }
            else
            {
                ch = ch + key;
            }
            text[i] = ch;
        }
        else if (ch >= 'A' && ch <= 'Z')
        {
            int tmp = int(ch) + key;

            if (tmp > int('Z'))
            {
                tmp = tmp - int('Z') + int('A') - 1;
                ch = char(tmp);
            }
            else
            {
                ch = ch + key;
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


// Main arguments and function call are here...
int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        show_usage();
        exit(1);
    }
    // Make the 4th argument int
    // This throws an error when not supplied with a number
    // need to find a way to catch it and return a better one or show_usage()
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
        show_usage();
        exit(1);
    }
}

