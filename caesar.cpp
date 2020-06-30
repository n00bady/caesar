#include <iostream>
#include <string>
#include <unistd.h>

using namespace std;

void show_usage()
{
    cout << "Usage: caesar <option> <text> <key>" << endl;
    cout << "Options: " << endl;
    cout << "\t -e,  Encrypts a string with a key." << endl;
    cout << "\t -d,  Decrypts a string if provided a key. " << endl;
    cout << "Key must be an int number between 1-25!" << endl;
}

// Encrypt function
int encrypt(string text, int key)
{
    char ch;

    for (size_t i=0; i<text.size(); i++)
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
int decrypt(string text, int key)
{
    char ch;
    
    for (size_t i=0; i<text.size(); i++)
    {
        ch = text[i];

        if (ch >= 'a' && ch <= 'z')
        {
            int tmp = int(ch) - key;

            if (tmp < int('a'))
            {
                tmp = tmp + int('z') - int('a') + 1;
                ch = char(tmp);
            }
            else
            {
                ch = ch -key;
            }
            text[i] = ch;
        }
        else if (ch  >= 'A' && ch <= 'Z')
        {
            int tmp = int(ch) - key;

            if (tmp < int('A'))
            {
                tmp = tmp + int('Z') - int('A') + 1;
                ch = char(tmp);
            }
            else
            {
                ch = ch - key;
            }
            text[i] = ch;
        }
    }
    cout << "Decrypted message: " << endl;
    cout << text << endl;

    return 0;
}

// Easiest brute force way of cracking it.
// there are only 25 possible shifts to try so why not print them all
// and let the user decide which one is correct :)
int easycrack(string text)
{
    int i;

    for(i=1; i<=25; i++)
    {
        cout << "Trying Key: " << i << endl;
        decrypt(text, i);
        cout << "----------------" << endl;
    }
    cout << "Now read them all and see which one makes sense :D" << endl;

    return 0;
}

// Main arguments and function call are here...
int main(int argc, char* argv[])
{
    if (argc < 2 || argc > 4)
    {
        show_usage();
        exit(1);
    }
// We can't have this before we know if we encrypt/decrypt/crack because some
// of the options need less arguments.
    // Make the 4th argument int
    // This throws an error when not supplied with a number
    // need to find a way to catch it and return a better one or show_usage()
//    string str = argv[3];
//    std::string::size_type sz;
//    int x = stoi(str, &sz);

    // If option -e encrypt
    if (string(argv[1]) == "-e")
    {
        // Change the 3rd argument which is the key to int
        string str = argv[3];
        std::string::size_type sz;
        int x = stoi(str, &sz);
        // Check the key's value there is no point for negative, 0 or higher
        // than 25 shifts. :-|
        if(x <= 0 || x > 25)
        {
            cout << "There is no point in doing that..." << endl;
            exit(1);
        }

        encrypt(argv[2], x);
    }
    // If option -d decrypt
    else if (string(argv[1]) == "-d")
    {
        // Change the 3rd argument which is the key to int
        string str = argv[3];
        std::string::size_type sz;
        int x = stoi(str, &sz);
        // Check the key's value there is no point for negative, 0 or higher
        // than 25 shifts. :-|
        if(x <= 0 || x > 25)
        {
            cout << "There is no point in doing that..." << endl;
            exit(1);
        }

        decrypt(argv[2], x);
    }
    // For anything else print the usage
    // TODO: Add better cracking ways... maybe some way of recognizing 
    // when it's cracked and only printing the right one.
    else if (string(argv[1]) == "--easy-crack")
    {
        if(isatty(fileno(stdin)))
        {
            easycrack(argv[2]);
        }
        else
        {
            string line;
            string str;
            while(getline(cin, line) && !line.empty())
            {
                str += line + " ";
            }
            easycrack(str);
        }
    }
    else
    {
        show_usage();
        exit(1);
    }
}

