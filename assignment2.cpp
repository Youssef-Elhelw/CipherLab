// Authors      :                 Ahmed Ehab Salah                  |=========== Youssef Elhelw ============|         Mostafa tarek hassanin
// Lines        :                      19-650                       |              1086-1766                |                650-1086
// which cipher : Route-polybius-simpleSub+(main-takekey-binaryclac)|     RailFence-morse-xor+(main)        |       baconian-affine-Atbash-vignere
// Version      :                                                                   (2.22)v
// Date         :                                                           April.16th.2024



// including libraries
#include <iostream>
#include <string>
#include <stdio.h>
#include <algorithm>
#include <cctype>
#include <string.h>
#include <cmath>
#include <stdlib.h>
#include <bitset>
using namespace std;

//===========================================(Ahmed Ehab)=============================================//

int takeKey()
{
    string temp;
    bool isvalid;
    do
    {
        isvalid = true;
        cout << "(enter a NUMBER greater than 1): ";
        getline(cin, temp);
        for (int i = 0; i < temp.length(); i++)
        {
            if (!isdigit(temp[i]) || temp[i] == '1' || temp[i] == '0')
            {
                isvalid = false;
            }
        }
    } while (!isvalid);
    int rqm = stoi(temp);
    return rqm;
}
// Route encryption function
string encryptRoute()
{
    int key;
    string msgToEncrypt;
    cout << "Enter the message to encrypt :\n";
    getline(cin, msgToEncrypt);

    // exclude any other chars than letters
    for (int i = 0; i < msgToEncrypt.length(); i++)
    {
        if (!isalpha(msgToEncrypt[i]))
        {
            msgToEncrypt.erase(msgToEncrypt.begin() + i);
            i--;
            continue;
        }
        msgToEncrypt[i] = toupper(msgToEncrypt[i]);
    }

    cout << "Enter the key for encryption ";
    key = takeKey();
    while (key > msgToEncrypt.length() / 2)
    {
        cout << "Enter a valid key for encryption (should be less than or equal msg length / 2):\n";
        key = takeKey();
    }

    // fill X's to make it fit if needed
    int changeX = (key - (msgToEncrypt.length() % key));
    if (msgToEncrypt.length() % key != 0)
    {
        for (int i = 0; i < changeX; i++)
        {
            msgToEncrypt += 'X';
        }
    }

    // get the number of needed rows
    int rows;
    if (msgToEncrypt.length() % key == 0)
    {
        rows = msgToEncrypt.length() / key;
    }
    else
    {
        rows = floor(msgToEncrypt.length() / key) + 1;
    }
    // declare the matrix and fill it with the right order
    char letters[rows][key];
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < key; j++)
        {
            letters[i][j] = msgToEncrypt[j + (i * key)];
        }
    }
    // Output the matrix
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < key; j++)
        {
            cout << letters[i][j] << " ";
        }
        cout << "\n";
    }

    // setting important variables to the main loop
    int loopCounter = ceil(min(key, rows) / 2.f); // make a loop counter to determine how much i need to loop
    int temp = ceil(min(key, rows) / 2.f);        // make a temporary var to use later
    int innerCounter = 1;                         // inner counter to go inside the matrix by one every loop
    int yIndex = 1;                               // yIndex to get the needed row
    int xIndex = key;                             // xIndex to get the needed coulmn
    string msgToOutput = "";                      // the message to concatenate and output
    // main loop with nested loops each goes in a fixed way
    while (loopCounter)
    {

        while (yIndex < rows && letters[yIndex - 1][xIndex - 1] != '-')
        {
            msgToOutput += letters[yIndex - 1][xIndex - 1];
            letters[yIndex - 1][xIndex - 1] = '-';
            yIndex++;
        }

        while (xIndex - innerCounter && letters[yIndex - 1][xIndex - 1] != '-')
        {
            msgToOutput += letters[yIndex - 1][xIndex - 1];
            letters[yIndex - 1][xIndex - 1] = '-';
            xIndex--;
        }

        while (yIndex - innerCounter && letters[yIndex - 1][xIndex - 1] != '-')
        {
            msgToOutput += letters[yIndex - 1][xIndex - 1];
            letters[yIndex - 1][xIndex - 1] = '-';
            yIndex--;
        }

        while (xIndex < key && letters[yIndex - 1][xIndex - 1] != '-')
        {
            msgToOutput += letters[yIndex - 1][xIndex - 1];
            letters[yIndex - 1][xIndex - 1] = '-';
            xIndex++;
        }
        xIndex--; // to get closer to the center of the matrix
        yIndex++; // to get closer to the center of the matrix
        rows--;   // to exclude the last row
        key--;    // to exclude the last coulmn
        loopCounter--;
        innerCounter++;
    }

    // return the var to its intitial value
    key += temp;
    rows += temp;

    // condition to check if there is center element cause it won't be in the mag
    if (key % 2 != 0 && key == rows)
    {
        int indexToRemove = (key + 1) / 2;
        msgToOutput += letters[indexToRemove - 1][indexToRemove - 1];
        letters[indexToRemove - 1][indexToRemove - 1] = '-';
    }
    return "the encrypted message is => " + msgToOutput;
}

// Route decryption function (do the same as the above but in reverse)
string decryptRoute()
{
    string msgToDecrypt;
    int key;
    cout << "Enter the key for decryption ";
    key = takeKey();
    cin.ignore();
    cout << "Enter the message to decrypt: ";
    bool dicryptable;
    // check if the msg is dicryptable or not
    do
    {
        dicryptable = true;
        getline(cin, msgToDecrypt);
        for (int i = 0; i < msgToDecrypt.length(); i++)
        {
            if (!isalpha(msgToDecrypt[i]))
            {
                dicryptable = false;
                cout << "\nEnter a valid msg (shouldn't have except letters):\nEnter a valid msg:";
                break;
            }
        }
        if (msgToDecrypt.length() % key != 0)
        {
            cout << "Wrong msg (the key doesn't fit the msg length)\nEnter a valid msg:";
            dicryptable = false;
        }

    } while (!dicryptable);
    int coulmns = key;
    int rows = msgToDecrypt.length() / key;
    string msgToOutput = "";
    char letters[rows][coulmns];
    int loopCounter = ceil(min(key, rows) / 2.f);
    int temp = ceil(min(key, rows) / 2.f);
    int innerCounter = 1;
    int yIndex = 1;
    int mainCounter = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < key; j++)
        {
            letters[i][j] = '-';
        }
    }

    while (loopCounter)
    {

        while (yIndex < rows && letters[yIndex - 1][coulmns - 1] == '-')
        {
            letters[yIndex - 1][coulmns - 1] = msgToDecrypt[mainCounter];
            mainCounter++;
            yIndex++;
        }
        while (coulmns - innerCounter && letters[yIndex - 1][coulmns - 1] == '-')
        {
            letters[yIndex - 1][coulmns - 1] = msgToDecrypt[mainCounter];
            mainCounter++;
            coulmns--;
        }

        while (yIndex - innerCounter && letters[yIndex - 1][coulmns - 1] == '-')
        {
            letters[yIndex - 1][coulmns - 1] = msgToDecrypt[mainCounter];
            mainCounter++;
            yIndex--;
        }

        while (coulmns < key && letters[yIndex - 1][coulmns - 1] == '-')
        {
            letters[yIndex - 1][coulmns - 1] = msgToDecrypt[mainCounter];
            mainCounter++;
            coulmns++;
        }
        coulmns--;
        yIndex++;
        rows--;
        key--;
        loopCounter--;
        innerCounter++;
    }

    key += temp;
    rows += temp;
    if (key % 2 != 0 && key == rows)
    {
        int indexToRemove = (key + 1) / 2;
        letters[indexToRemove - 1][indexToRemove - 1] = msgToDecrypt[msgToDecrypt.length() - 1];
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < key; j++)
        {
            cout << letters[i][j] << " ";
            if (i == rows - 1 && j != 0 && letters[i][j] == 'X')
            {
                continue;
            }
            msgToOutput += letters[i][j];
        }
        cout << "\n";
    }
    return "the decrypted message is => " + msgToOutput + "\n";
}

// Polybius Square encryption
string encryptPolybiusSquare()
{
    string key;
    bool keyAble;
    do
    {
        cout << "enter the key for encryption\n";
        cin >> key;
        for (int i = 0; i < 5; i++)
        {
            keyAble = true;
            if (key.find(to_string(i + 1)) >= key.length())
            {
                cout << "Error: Missing number '" << i + 1 << "' \n";
                keyAble = false;
                break;
            }
            if (!isdigit(key[i]) || key.length() != 5)
            {
                cout << "Error: Invalid char or length\n";
                keyAble = false;
                break;
            }
        }
    } while (!keyAble);

    char table[5][5];
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            int charToAdd = (65) + 5 * i + j;
            if ((i == 1 && j == 4) || i > 1)
            {
                table[i][j] = char(charToAdd + 1);
                continue;
            }
            table[i][j] = char(charToAdd);
        }
    }
    table[4][4] = char((65) + 25);

    cout << "\n    ";
    for (int i = 0; i < 5; i++)
    {
        cout << key[i] << " ";
    }
    cout << "\n";

    for (int i = 0; i < 5; i++)
    {
        cout << key[i] << " | ";
        for (int j = 0; j < 5; j++)
        {
            cout << table[i][j] << " ";
        }
        cout << "\n";
    }

    string msgToEncrypt;
    cout << "enter the msg to encrypt:\n";
    cin.ignore();
    getline(cin, msgToEncrypt);

    for (int i = 0; i < msgToEncrypt.length(); i++)
    {
        if (!isalpha(msgToEncrypt[i]) && msgToEncrypt[i] != ' ')
        {
            msgToEncrypt.erase(msgToEncrypt.begin() + i);
            i--;
            continue;
        }
        msgToEncrypt[i] = toupper(msgToEncrypt[i]);
    }

    string msgToOutput = "";

    for (int i = 0; i < msgToEncrypt.length(); i++)
    {
        if (msgToEncrypt[i] == ' ')
        {
            msgToOutput += ' ';
            continue;
        }

        int row = 0, coulmn = 0;
        int index = int(msgToEncrypt[i]) - 65;
        int minus = 0;

        if (msgToEncrypt[i] == 'J')
        {
            msgToEncrypt[i] = 'I';
            index -= 1;
        }
        else if (index > 8)
        {
            index -= 1;
        }

        while (index >= 5)
        {
            index -= 5;
            row += 1;
        }
        coulmn = index;
        char co = (key[index]);
        char ro = (key[row]);
        msgToOutput += ro;
        msgToOutput += co;
    }

    return "The encrypted msg is: " + msgToOutput + "\n";
}

// Polybius Square decryption
string decryptPolybiusSquare()
{

    string key;
    bool keyAble;
    do
    {
        cout << "enter the key for decryption:\n";
        cin >> key;
        for (int i = 0; i < 5; i++)
        {
            keyAble = true;
            if (key.find(to_string(i + 1)) >= key.length())
            {
                cout << "Error: Missing number '" << i + 1 << "' \n";
                keyAble = false;
                break;
            }
            if (!isdigit(key[i]) || key.length() != 5)
            {
                cout << "Error: Invalid char or length\n";
                keyAble = false;
                break;
            }
        }
    } while (!keyAble);

    char table[5][5];
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            int charToAdd = (65) + 5 * i + j;
            if ((i == 1 && j == 4) || i > 1)
            {
                table[i][j] = char(charToAdd + 1);
                continue;
            }
            table[i][j] = char(charToAdd);
        }
    }
    table[4][4] = char((65) + 25);

    cout << "\n    ";
    for (int i = 0; i < 5; i++)
    {
        cout << key[i] << " ";
    }
    cout << "\n";

    for (int i = 0; i < 5; i++)
    {
        cout << key[i] << " | ";
        for (int j = 0; j < 5; j++)
        {
            cout << table[i][j] << " ";
        }
        cout << "\n";
    }

    string msgToDecrypt;

    bool msgable;
    do
    {
        cout << "enter the msg to decrypt:\n";
        msgable = true;
        cin.ignore();
        getline(cin, msgToDecrypt);
        for (int i = 0; i < msgToDecrypt.length(); i++)
        {
            if (msgToDecrypt[i] != '1' && msgToDecrypt[i] != '2' && msgToDecrypt[i] != '3' && msgToDecrypt[i] != '4' && msgToDecrypt[i] != '5' && msgToDecrypt[i] != ' ')
            {
                cout << "Error: wrong char '" << msgToDecrypt[i] << "' \n";
                msgable = false;
                break;
            }
        }
    } while (!msgable);

    string msgToOutput = "";

    for (int i = 0; i < msgToDecrypt.length() - 1; i++)
    {
        if (msgToDecrypt[i] == ' ')
        {
            msgToOutput += ' ';
            continue;
        }
        else
        {
            int yIndex = key.find(msgToDecrypt[i]);
            int xIndex = key.find(msgToDecrypt[i + 1]);
            msgToOutput += table[yIndex][xIndex];
            i++;
        }
    }

    return "The decrypted msg is: " + msgToOutput + "\n";
}

// function that takes the uniqe word for the simple substitution cipher
void takeUniqe(string &key)
{
    bool isValid;
    string txt;
    do
    {
        isValid = true;
        cout << "Enter the UNIQE 5 letter key: \n";
        cin >> txt;

        if (txt.length() > 5)
        {
            isValid = false;
            cout << "Error: key length isn't right\n";
        }
        int start = 0;
        while (start != 5)
        {
            string sub = txt.substr(start + 1, txt.length());
            if (sub.find(txt[start]) < sub.length())
            {
                cout << "Error: found repeated char '" << txt[start] << "'\n";
                isValid = false;
                break;
            }
            start++;
        }
    } while (!isValid);
    key = txt;
}

// simple substitution encryption
string encryptSimpleSub()
{
    // take the key for decryption
    string key;
    takeUniqe(key);
    // setting the array of chars and filling it to use in substitution
    char letters[26];
    string letterS = "";
    for (int i = 97; i < 123; i++)
    {
        letterS += i;
        letters[i - 97] = i;
    }
    char cipherLetters[26];
    for (int i = 0; i < 5; i++)
    {
        cipherLetters[i] = key[i];
    }
    int count = 0;
    for (int i = 0; i < 26; i++)
    {
        if (key.find(letters[i]) < key.length())
        {
            count++;
            continue;
        }
        else
        {
            cipherLetters[i - count + 5] = letters[i];
        }
    }
    // take the msg and removing digits and non alphabitic cahrs
    string msgToEncrypt;
    cout << "Enter the msg to encrypt it:\n";
    cin.ignore();
    getline(cin, msgToEncrypt);

    for (int i = 0; i < msgToEncrypt.length(); i++)
    {
        if (!isalpha(msgToEncrypt[i]) && msgToEncrypt[i] != ' ')
        {
            msgToEncrypt.erase(msgToEncrypt.begin() + i);
            i--;
            continue;
        }
        msgToEncrypt[i] = tolower(msgToEncrypt[i]);
    }

    // add the right letters to the final var and return it
    string msgToOutput = "";
    for (int i = 0; i < msgToEncrypt.length(); i++)
    {
        if (msgToEncrypt[i] == ' ')
        {
            msgToOutput += ' ';
            continue;
        }
        msgToOutput += cipherLetters[letterS.find(msgToEncrypt[i])];
    }

    return "The encrypted msg is " + msgToOutput + "\n";
}

// simple substitution decryption (same like above but in reverse)
string decryptSimpleSub()
{
    string key;
    takeUniqe(key);
    char letters[26];
    string letterS = "";
    for (int i = 97; i < 123; i++)
    {
        letters[i - 97] = i;
    }
    char cipherLetters[26];
    for (int i = 0; i < 5; i++)
    {
        letterS += key[i];
        cipherLetters[i] = key[i];
    }
    int count = 0;
    for (int i = 0; i < 26; i++)
    {
        if (key.find(letters[i]) < key.length())
        {
            count++;
            continue;
        }
        else
        {
            letterS += i + 97;
            cipherLetters[i - count + 5] = letters[i];
        }
    }
    string msgTodecrypt;
    cout << "Enter the msg to decrypt it:\n";
    cin.ignore();
    getline(cin, msgTodecrypt);

    for (int i = 0; i < msgTodecrypt.length(); i++)
    {
        if (!isalpha(msgTodecrypt[i]) && msgTodecrypt[i] != ' ')
        {
            msgTodecrypt.erase(msgTodecrypt.begin() + i);
            i--;
            continue;
        }
        msgTodecrypt[i] = tolower(msgTodecrypt[i]);
    }
    cout << letterS << "\n\n";
    string msgToOutput = "";
    for (int i = 0; i < msgTodecrypt.length(); i++)
    {
        if (msgTodecrypt[i] == ' ')
        {
            msgToOutput += ' ';
            continue;
        }
        msgToOutput += letters[letterS.find(msgTodecrypt[i])];
    }
    return msgToOutput;
}

//============================================(Mostafa Tarek)==========================================//

int takenum()
{
    string temp;
    bool isvalid;
    do
    {
        isvalid = true;
        cout << "enter a number:\n";
        getline(cin, temp);
        for (int i = 0; i < temp.length(); i++)
        {
            if (!isdigit(temp[i]))
            {
                isvalid = false;
            }
        }
    } while (!isvalid);
    int rqm = stoi(temp);
    cout << "\n";
    return rqm;
}

// Atbash for both encryption and decryption
void atbash()

{ // list contain A to Z
    char list[26];
    for (int i = 0; i < 26; i++)
    {
        list[i] = char(int(65 + i));
    }
    // list contain Z to A
    char revlist[26];
    for (int i = 25, j = 0; i >= 0; i--, j++)
    {
        revlist[j] = list[i];
    }

    // take the line from the user
    string text;
    cout << "Enter line " << endl;
    getline(cin, text);

    // loop that delete every element excpt char and make every char to upper
    for (int i = 0; i < size(text); i = i + 1)
    {
        if (!isalpha(text[i]))
        {
            text.erase(text.begin() + i);
            i--;
            continue;
        }
        text[i] = toupper(text[i]);
    }

    // encryption: for loop in text that user insert and for loop in list ,,,if element in text == element in list , so make element in text == element in reverse list
    for (int i = 0; i < text.size(); i++)
    {
        for (int x = 0; x < 26; x++)
        {
            if (text[i] == list[x])
            {
                text[i] = revlist[x];
                break;
            }
        }
    }
    cout << "The output message is: " << text << "\n";
}

// function that Decrypt the massage
void vigneredec()
{

    string text;
    string keyword;

    // take line from user
    cout << "enter text to decipher (up to 80 characters): \n ";
    getline(cin, text);

    // check that the line lenght <= 80
    while (text.length() > 80)
    {
        cout << "enter valid text to decipher (up to 80 characters): \n ";
        getline(cin, text);
    }

    // take keyword from user
    cout << "enter keyword (up to 8 characters): \n ";
    getline(cin, keyword);

    // check that every element in keyword is alpha and its length is <=8
    for (int i = 0; i < keyword.length(); i++)
    {
        while (!isalpha(keyword[i]) || keyword.length() > 8)
        {
            cout << "enter valid keyword (up to 8 characters): \n ";
            getline(cin, keyword);
        }
    }

    // repeat the elements of the keyword
    int l = keyword.length();
    for (int i = 0; i < (text.length() - l); i++)
    {
        keyword += keyword[i];
    }

    // make the elements of the keyword and text toupper
    for (int i = 0; i < text.length(); i++)
    {
        keyword[i] = toupper(keyword[i]);
        if (!isalpha(text[i]))
        {
            continue;
        }
        else
        {
            text[i] = toupper(text[i]);
        }
    }

    // for loop in text that check if the element is alpha and decrypt it
    for (int i = 0; i < text.length(); i++)
    {
        if (!isalpha(text[i]))
        {
            continue;
        }
        else
        {
            text[i] = (text[i] - keyword[i] + 26) % 26 + 'A';
        }
    }

    cout << text << "\n";
}

// function that encrypt the massage
void vignereenc()
{
    string text;
    string keyword;

    // take line from user
    cout << "enter text to cipher (up to 80 characters): \n ";
    getline(cin, text);

    // check that the line lenght <= 80
    while (text.length() > 80)
    {
        cout << "enter valid text to cipher (up to 80 characters): \n ";
        getline(cin, text);
    }

    // take keyword from user
    cout << "enter keyword (up to 8 characters): \n ";
    getline(cin, keyword);

    // check that every element in keyword is alpha and its length is <=8
    for (int i = 0; i < keyword.length(); i++)
    {
        while (!isalpha(keyword[i]) || keyword.length() > 8)
        {
            cout << "enter valid keyword (up to 8 characters): \n ";
            getline(cin, keyword);
        }
    }

    // repeat the elements of the keyword
    int l = keyword.length();
    for (int i = 0; i < (text.length() - l); i++)
    {
        keyword += keyword[i];
    }

    // make the elements of the keyword and text toupper
    for (int i = 0; i < text.length(); i++)
    {
        keyword[i] = toupper(keyword[i]);
        if (!isalpha(text[i]))
        {
            continue;
        }
        else
        {
            text[i] = toupper(text[i]);
        }
    }

    // for loop in text that check if the element is alpha and encrypt it
    for (int i = 0; i < text.length(); i++)
    {
        if (!isalpha(text[i]))
        {
            continue;
        }
        else
        {
            text[i] = ((text[i] + keyword[i]) % 26) + 'A';
        }
    }

    cout << text << "\n";
}

// affine encryption function
void affineenc()
{
    int a, b;
    cout << "Enter a for encryption:\n";
    a = takenum();
    cout << "Enter b for encryption:\n";
    b = takenum();
    // take text from user
    string text;
    cout << "enter text to cipher:\n ";
    cin.ignore();
    getline(cin, text);

    // delete every element != alpha and make every alpha toupper
    for (int i = 0; i < text.length(); i++)
    {
        if (!isalpha(text[i]))
        {
            text.erase(text.begin() + i);
            i--;
            continue;
        }
        text[i] = toupper(text[i]);
    }

    // list from A to B
    char list[26];
    for (int i = 0; i < 26; i++)
    {
        list[i] = 'A' + i;
    }

    // list from 0 to 25
    int list1[26];
    for (int i = 0; i < 26; i++)
    {
        list1[i] = i;
    }

    // for loops if char in text == char in list , convert char in text in this equation
    for (int i = 0; i < text.length(); i++)
    {
        for (int j = 0; j < 26; j++)
        {
            if (list[j] == text[i])
            {
                int index = ((a * list1[j]) + b) % 26;
                text[i] = list[index];
                break;
            }
        }
    }

    cout << text << "\n";
}

// affine decryption function
void affinedec()
{
    int b, c;
    cout << "Enter b for decryption:\n";
    b = takenum();
    cout << "Enter c for decryption:\n";
    c = takenum();
    // take text from user
    string text;
    cout << "enter text to decipher:\n ";
    cin.ignore();
    getline(cin, text);

    // delete every element != alpha and make every alpha toupper
    for (int i = 0; i < text.length(); i++)
    {
        if (!isalpha(text[i]))
        {
            text.erase(text.begin() + i);
            i--;
            continue;
        }
        text[i] = toupper(text[i]);
    }

    // list from A to B
    char list[26];
    for (int i = 0; i < 26; i++)
    {
        list[i] = 'A' + i;
    }

    // list from 0 to 25
    int list1[26];
    for (int i = 0; i < 26; i++)
    {
        list1[i] = i;
    }

    // for loops if char in text == char in list , convert char in text in this equation
    for (int i = 0; i < text.length(); i++)
    {
        for (int j = 0; j < 26; j++)
        {
            if (list[j] == text[i])
            {
                int index = ((c * (list1[j] - b))) % 26;
                if (index < 0)
                {
                    index += 26;
                }
                text[i] = list[index];
                break;
            }
        }
    }
    cout << text << "\n";
}

// function that calculate the decimal of a binary number
int binarycalc(string s, int l) // Made by (Ahmed Ehab)
{
    string sub = s.substr(0, l);
    if (sub.length() == 1)
    {
        return pow(2, s.length() - 1) * (sub[sub.length() - 1] - 48);
    }
    else
    {
        return pow(2, s.length() - sub.length()) * (sub[sub.length() - 1] - 48) + binarycalc(s, l - 1);
    }
}

// baconian encryption funtion
void Baconianenc()
{
    // take text from user
    string text;
    cout << "enter text to cipher: ";
    getline(cin, text);

    // delete every element != alpha and make all alphas toupper
    for (int i = 0; i < text.length(); i++)
    {
        if (!isalpha(text[i]))
        {
            text.erase(text.begin() + i);
            i--;
            continue;
        }
        text[i] = toupper(text[i]);
    }

    // list from A to Z
    char list[26];
    for (int i = 0; i < 26; i++)
    {
        list[i] = 'A' + i;
    }

    // make every char to integar and to binary number and make every 1 == b and every 0  == a
    for (int i = 0; i < text.length(); i++)
    {
        int num = text[i] - 65;
        bitset<5> number(num);
        string val = number.to_string('a', 'b');
        cout << val;
    }
    cout << "\n";
}

// baconian decryption funtion
void Baconiandec()
{
    // take text from user
    string text;
    cout << "enter text to decipher: ";
    getline(cin, text);

    // delete every element not alpha and make all alphas toupper
    for (int i = 0; i < text.length(); i++)
    {
        if (!isalpha(text[i]))
        {
            text.erase(text.begin() + i);
            i--;
            continue;
        }
        text[i] = toupper(text[i]);
    }

    // check if the encrypted message is valid or not
    for (int i = 0; i < text.length(); i++)
    {
        while (((text[i] != 'A') && (text[i] != 'B')) && (text.length() % 5 != 0))
        {
            cout << "enter valid text to decipher:\n ";
            getline(cin, text);
        }
    }
    // replacing each 'A' with '0' and each 'B' with '1'
    for (int i = 0; i < text.length(); i++)
    {
        if (text[i] == 'A')
        {
            text[i] = '0';
        }
        else
        {
            text[i] = '1';
        }
    }
    int count = 0;
    string last = "";

    // this for loop for turning every 5 (string-numbers) to binary then to a single char
    for (int i = 0; i < text.length(); i++)
    {
        count++;
        last += text[i];
        if (count == 5)
        {
            cout << char(binarycalc(last, 5) + 65);
            last = "";
            count = 0;
        }
    }
}

//===========================================(Youssef elhelw)========================================//

// encryption function:
int encryption_Rail_fence()
{
    string sentence;
    cout << "Enter the message u want to encrypt: ";
    getline(cin, sentence);
    int key;
    cout << "please insert the number of key: ";
    key = takeKey();

    // now preparing an empty string so we take the original sentence without any non-alpha char
    string nospace = "";
    for (int i = 0; i < sentence.length(); i++)
    {
        if (isalpha(sentence[i]))
        {
            nospace += sentence[i];
        }
    }

    // making 2 dimentional array its rows will be the key and its columns will be the length of nospace string
    char arr[key][nospace.length()];
    for (int i = 0; i < key; i++)
    {
        for (int j = 0; j < nospace.length(); j++)
        {
            arr[i][j] = '.';
        }
    }
    int letter = 0;
    int temp = 0;

    // a while loop until we use all letters of the string:
    while (letter < nospace.size())
    {

        // a for loop gonna go down diagonally untill we reach the penultimate(before the last row) row
        for (int i = 0, j = temp; letter < nospace.length(); j++, i++)
        {
            temp = j;
            if (i == key - 1)
            {
                break;
            }
            arr[i][j] = nospace[letter]; // we will fill this index with letters
            letter++;
        }

        // like the previous(for loop) but now we will go up :)
        for (int i = key - 1, j = temp; letter < nospace.length(); j++, i--)
        {
            temp = j;
            if (i == 0)
            {
                break;
            }
            arr[i][j] = nospace[letter];
            letter++;
        }
        // We will repeat this process until the letters are finished
    }

    // printiong the final shape of the array
    for (int i = 0; i < key; i++)
    {
        for (int j = 0; j < nospace.length(); j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";

    // printing the encrypted message :)
    for (int i = 0; i < key; i++)
    {
        for (int j = 0; j < nospace.length(); j++)
        {
            if (isalpha(arr[i][j]))
            {
                // i added a space after each char so the final shape be good
                cout << arr[i][j];
            }
        }
    }
    return 0;
}

// decryption function:
int decryption_Rail_fence()
{
    string original;
    cout << "\nEnter the message u want to decrypt: ";
    getline(cin, original);
    int key;
    cout << "\nplease insert the number of key: ";
    key = takeKey();

    // now preparing an empty string so we take the original sentence without any non-alpha char (just in case 0_0)
    string org_nospace = "";
    for (int i = 0; i < original.length(); i++)
    {
        if (isalpha(original[i]))
        {
            org_nospace += original[i];
        }
    }
    // making 2 dimentional array its rows will be the key and its columns will be the length of nospace string
    char arr2[key][org_nospace.length()];
    for (int i = 0; i < key; i++)
    {
        for (int j = 0; j < org_nospace.length(); j++)
        {
            arr2[i][j] = '.';
        }
    }
    cout << "\n";
    int letter = 0;
    int temp = 0;

    // a while loop until we use all letters of the string:
    while (letter < org_nospace.size())
    {

        // a for loop gonna go down diagonally untill we reach the penultimate(before the last row) row
        for (int i = 0, j = temp; letter < org_nospace.length(); j++, i++)
        {
            temp = j;
            if (i == key - 1)
            {
                break;
            }
            arr2[i][j] = '#'; // we will mark this index so we can replace it with the encrypted message letter
            letter++;
        }

        // like the previous(for loop) but now we will go up :)
        for (int i = key - 1, j = temp; letter < org_nospace.length(); j++, i--)
        {
            temp = j;
            if (i == 0)
            {
                break;
            }
            arr2[i][j] = '#'; // i don't have to tell you what this line does right?
            letter++;
        }
    }
    cout << "\n";
    int letter2 = 0;
    // now we are ready to replace all '#'s with letters
    for (int i = 0; i < key; i++)
    {
        for (int j = 0; j < org_nospace.size(); j++)
        {
            if (arr2[i][j] == '#')
            {
                arr2[i][j] = org_nospace[letter2];
                letter2++;
            }
        }
    }
    // printing the final shape of the array
    for (int i = 0; i < key; i++)
    {
        for (int j = 0; j < org_nospace.size(); j++)
        {
            cout << arr2[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
    temp = 0;
    letter = 0;

    // now the only function of this while loop is just printing the decrypted message:
    while (letter < org_nospace.size())
    {

        // for loop to go down diagonally to print letters
        for (int i = 0, j = temp; letter < org_nospace.length(); j++, i++)
        {
            temp = j;
            if (i == key - 1)
            {
                break;
            }
            // i added a space after each char so the final shape be good
            cout << arr2[i][j];
            letter++;
        }
        // for loop to go up diagonally to print letters
        for (int i = key - 1, j = temp; letter < org_nospace.length(); j++, i--)
        {
            temp = j;
            if (i == 0)
            {
                break;
            }
            // i added a space after each char so the final shape be good
            cout << arr2[i][j];
            letter++;
        }
        // We will repeat this process until the letters are finished
    }
    return 0;
}

// xor encryption function
void xOR_encryption()
{
    string plain_text, key;
    cout << "enter the plain text: ";
    getline(cin, plain_text);
    cout << "\nenter the key: ";
    getline(cin, key);
    int result;
    // xor opperation for each char with the char of the key
    for (int i = 0, j = 0; i < plain_text.length(); i++, j++)
    {
        if (j == key.length())
        {
            j = 0;
        }
        result = plain_text[i] ^ key[j];
        cout << hex << (result) << " ";
    }
    cout << "\n";
}

// xor decryption function
void xOR_decryption()
{
    string encrypted_message, key;
    cout << "enter the encrypted message (Hexadecimal numbers should be separated by spaces): ";
    getline(cin, encrypted_message);
    cout << "\nenter the key: ";
    getline(cin, key);
    string result;
    for (int i = 0, j = 0; i < encrypted_message.length(); i++, j++)
    {
        string newchar = "";
        // before each space there would be hexadecimal that will turn into a char
        while (encrypted_message[i] != ' ')
        {
            newchar += encrypted_message[i];
            i++;
            if (i == encrypted_message.length())
            {
                break;
            }
        }
        if (newchar.length() == 1)
        {
            if (!isxdigit(newchar[0]))
            {
                cout << "enter the encrypted message (valid hexadecimal number): ";
                getline(cin, encrypted_message);
                i = 0;
                j = 0;
                continue;
            }
        }
        else if (newchar.length() == 2)
        {
            if (!isxdigit(newchar[0]) || !isxdigit(newchar[1]))
            {
                cout << "\nenter a right encrypted message (valid hexadecimal number) '" << newchar << "' is not a hexadecimal: ";
                getline(cin, encrypted_message);
                i = 0;
                j = 0;
                continue;
            }
        }
        else if (newchar.length() == 3)
        {
            if (!isxdigit(newchar[0]) || !isxdigit(newchar[1] || !isxdigit(newchar[2])))
            {
                cout << "\nenter a right encrypted message (valid hexadecimal number) '" << newchar << "' dose not represent a char: ";
                getline(cin, encrypted_message);
                i = 0;
                j = 0;
                continue;
            }
        }
        else
        {
            cout << "\nenter a right encrypted message '" << newchar << "' is not a valid ascii char: ";
            getline(cin, encrypted_message);
            i = 0;
            j = 0;
            continue;
        }
        // turning string to hexadecimal (base 16)
        int inth = stoi(newchar, 0, 16);
        if (j == key.length())
        {
            j = 0;
        }
        result += char(inth ^ int(key[j]));
    }
    cout << result;
    cout << "\n";
}

void morse_encryption()
{
    string sentence;
    cout << "wlecome to Morse Cipher\nplease enter the message you want to encrypt: ";
    getline(cin, sentence);
    cout << "\n";
    string morse = "";
    for (int i = 0; i < sentence.length(); i++)
    {
        if (isalpha(sentence[i]))
        {
            sentence[i] = tolower(sentence[i]);
        }
        if (sentence[i] == 'a')
        {
            morse += ".- ";
        }
        else if (sentence[i] == 'b')
        {
            morse += "-... ";
        }
        else if (sentence[i] == 'c')
        {
            morse += "-.-. ";
        }
        else if (sentence[i] == 'd')
        {
            morse += "-.. ";
        }
        else if (sentence[i] == 'e')
        {
            morse += ". ";
        }
        else if (sentence[i] == 'f')
        {
            morse += "..-. ";
        }
        else if (sentence[i] == 'g')
        {
            morse += "--. ";
        }
        else if (sentence[i] == 'h')
        {
            morse += ".... ";
        }
        else if (sentence[i] == 'i')
        {
            morse += ".. ";
        }
        else if (sentence[i] == 'j')
        {
            morse += ".--- ";
        }
        else if (sentence[i] == 'k')
        {
            morse += "-.- ";
        }
        else if (sentence[i] == 'l')
        {
            morse += ".-.. ";
        }
        else if (sentence[i] == 'm')
        {
            morse += "-- ";
        }
        else if (sentence[i] == 'n')
        {
            morse += "-. ";
        }
        else if (sentence[i] == 'o')
        {
            morse += "--- ";
        }
        else if (sentence[i] == 'p')
        {
            morse += ".--. ";
        }
        else if (sentence[i] == 'q')
        {
            morse += "--.- ";
        }
        else if (sentence[i] == 'r')
        {
            morse += ".-. ";
        }
        else if (sentence[i] == 's')
        {
            morse += "... ";
        }
        else if (sentence[i] == 't')
        {
            morse += "- ";
        }
        else if (sentence[i] == 'u')
        {
            morse += "..- ";
        }
        else if (sentence[i] == 'v')
        {
            morse += "...- ";
        }
        else if (sentence[i] == 'w')
        {
            morse += ".-- ";
        }
        else if (sentence[i] == 'x')
        {
            morse += "-..- ";
        }
        else if (sentence[i] == 'y')
        {
            morse += "-.-- ";
        }
        else if (sentence[i] == 'z')
        {
            morse += "--.. ";
        }
        else if (sentence[i] == '0')
        {
            morse += "----- ";
        }
        else if (sentence[i] == '1')
        {
            morse += ".---- ";
        }
        else if (sentence[i] == '2')
        {
            morse += "..--- ";
        }
        else if (sentence[i] == '3')
        {
            morse += "...-- ";
        }
        else if (sentence[i] == '4')
        {
            morse += "....- ";
        }
        else if (sentence[i] == '5')
        {
            morse += "..... ";
        }
        else if (sentence[i] == '6')
        {
            morse += "-.... ";
        }
        else if (sentence[i] == '7')
        {
            morse += "--... ";
        }
        else if (sentence[i] == '8')
        {
            morse += "---.. ";
        }
        else if (sentence[i] == '9')
        {
            morse += "----. ";
        }
        else if (sentence[i] == ' ')
        {
            morse += "   ";
        }
    }
    cout << "morse encrypted message: " << morse << "\n";
}

void morse_decryption()
{
    string sentence;
    cout << "wlecome to Morse Decipher\nplease enter the message you want to decrypt: ";
    getline(cin, sentence);
    cout << "\n";
    string morse = "";
    for (int i = 0; i < sentence.length(); i++)
    {
        string newchar = "";
        while (sentence[i] != ' ')
        {
            newchar += sentence[i];
            i++;
            if (i == sentence.length())
            {
                break;
            }
        }
        if (newchar == ".-")
        {
            morse += 'a';
            continue;
        }
        else if (newchar == "-...")
        {
            morse += 'b';
            continue;
        }
        else if (newchar == "-.-.")
        {
            morse += 'c';
            continue;
        }
        else if (newchar == "-..")
        {
            morse += 'd';
            continue;
        }
        else if (newchar == ".")
        {
            morse += 'e';
            continue;
        }
        else if (newchar == "..-.")
        {
            morse += 'f';
            continue;
        }
        else if (newchar == "--.")
        {
            morse += 'g';
            continue;
        }
        else if (newchar == "....")
        {
            morse += 'h';
            continue;
        }
        else if (newchar == "..")
        {
            morse += 'i';
            continue;
        }
        else if (newchar == ".---")
        {
            morse += 'j';
            continue;
        }
        else if (newchar == "-.-")
        {
            morse += 'k';
            continue;
        }
        else if (newchar == ".-..")
        {
            morse += 'l';
            continue;
        }
        else if (newchar == "--")
        {
            morse += 'm';
            continue;
        }
        else if (newchar == "-.")
        {
            morse += 'n';
            continue;
        }
        else if (newchar == "---")
        {
            morse += 'o';
            continue;
        }
        else if (newchar == ".--.")
        {
            morse += 'p';
            continue;
        }
        else if (newchar == "--.-")
        {
            morse += 'q';
            continue;
        }
        else if (newchar == ".-.")
        {
            morse += 'r';
            continue;
        }
        else if (newchar == "...")
        {
            morse += 's';
            continue;
        }
        else if (newchar == "-")
        {
            morse += 't';
            continue;
        }
        else if (newchar == "..-")
        {
            morse += 'u';
            continue;
        }
        else if (newchar == "...-")
        {
            morse += 'v';
            continue;
        }
        else if (newchar == ".--")
        {
            morse += 'w';
            continue;
        }
        else if (newchar == "-..-")
        {
            morse += 'x';
            continue;
        }
        else if (newchar == "-.--")
        {
            morse += 'y';
            continue;
        }
        else if (newchar == "--..")
        {
            morse += 'z';
            continue;
        }
        else if (newchar == "-----")
        {
            morse += '0';
            continue;
        }
        else if (newchar == ".----")
        {
            morse += '1';
            continue;
        }
        else if (newchar == "..---")
        {
            morse += '2';
            continue;
        }
        else if (newchar == "...--")
        {
            morse += '3';
            continue;
        }
        else if (newchar == "....-")
        {
            morse += '4';
            continue;
        }
        else if (newchar == ".....")
        {
            morse += '5';
            continue;
        }
        else if (newchar == "-....")
        {
            morse += '6';
            continue;
        }
        else if (newchar == "--...")
        {
            morse += '7';
            continue;
        }
        else if (newchar == "---..")
        {
            morse += '8';
            continue;
        }
        else if (newchar == "----.")
        {
            morse += '9';
            continue;
        }
        else if (sentence[i] == ' ' && sentence[i - 2] != ' ')
        {
            morse += ' ';
            continue;
        }
    }
    cout << "morse decrypted message: " << morse << "\n";
}

//===================================================================================================//
int main()
{
    int again = 1;
    while (again)
    {
        cout << "welcome to our program :)\n\n\nwhat do you want to do today?\nA)Cipher a message\nB)Decipher a message\nC)End\n";
        string op;
        getline(cin, op);
        cout << "\n";
        op[0] = tolower(op[0]);
        while ((op != "a" && op != "b" && op != "c") || (op.size() > 1))
        {
            cout << "Please insert a valid char\nA)Cipher a message\nB)Decipher a message\nC)End\n";
            getline(cin, op);
            cout << "\n";
            op[0] = tolower(op[0]);
        }
        if (op == "a")
        {
            string choice;
            cout << "okay now which Cipher do you want?\nA)Affine Cipher\nB)Route Cipher\nC)Atbash Cipher\nD)Vignere Cipher\nE)Baconian Cipher\nF)Simple Substitution Cipher\nG)Polybius Square Cipher\nH)Morse Code\nI)XOR Cipher\nJ)Rail-fence Cipher\nK)Return\n";
            getline(cin, choice);
            cout << "\n";
            choice[0] = tolower(choice[0]);
            string validChoice = "abcdefghijk";
            while (!(validChoice.find(choice) < validChoice.length()) || (choice.length() != 1))
            {
                cout << "Please insert a valid char:\n";
                getline(cin, choice);
                choice[0] = tolower(choice[0]);
            }
            // ============================================ //
            if (choice == "a")
            {
                affineenc();
            }
            else if (choice == "b")
            {
                cout << encryptRoute();
            }
            else if (choice == "c")
            {
                atbash();
            }
            else if (choice == "d")
            {
                vignereenc();
            }
            else if (choice == "e")
            {
                Baconianenc();
            }
            else if (choice == "f")
            {
                cout << encryptSimpleSub();
            }
            else if (choice == "g")
            {
                cout << encryptPolybiusSquare();
            }
            else if (choice == "h")
            {
                morse_encryption();
            }
            else if (choice == "i")
            {
                xOR_encryption();
            }
            else if (choice == "j")
            {
                encryption_Rail_fence();
            }
        }

        else if (op == "b")
        {
            string choice;
            cout << "okay now which Decipher do you want?\nA)Affine deCipher\nB)Route deCipher\nC)Atbash deCipher\nD)Vignere deCipher\nE)Baconian deCipher\nF)Simple Substitution deCipher\nG)Polybius Square deCipher\nH)Morse deCode\nI)XOR deCipher\nJ)Rail-fence deCipher\nK)Return\n";
            getline(cin, choice);
            cout << "\n";
            choice[0] = tolower(choice[0]);
            string validChoice = "abcdefghijk";
            while (!(validChoice.find(choice) < validChoice.length()) || (choice.length() != 1))
            {
                cout << "Please insert a valid char:\n";
                getline(cin, choice);
                choice[0] = tolower(choice[0]);
            }

            if (choice == "a")
            {
                affinedec();
            }
            else if (choice == "b")
            {
                cout << decryptRoute();
            }
            else if (choice == "c")
            {
                atbash();
            }
            else if (choice == "d")
            {
                vigneredec();
            }
            else if (choice == "e")
            {
                Baconiandec();
            }
            else if (choice == "f")
            {
                cout << decryptSimpleSub();
            }
            else if (choice == "g")
            {
                cout << decryptPolybiusSquare();
            }
            else if (choice == "h")
            {
                morse_decryption();
            }
            else if (choice == "i")
            {
                xOR_decryption();
            }
            else if (choice == "j")
            {
                decryption_Rail_fence();
            }
        }
        else if (op == "c")
        {
            cout << "Bye :)";
            return 0;
        }

        cout << "\nthank you for using our program\nA)Again\nB)Exit\n";
        string goOut;
        getline(cin, goOut);
        cout << "\n";
        goOut[0] = tolower(goOut[0]);
        while (goOut != "a" && goOut != "b" || (goOut.length() != 1))
        {
            cout << "\nPlease insert a valid char\nA)Again\nB)Exit\n";
            getline(cin, goOut);
            goOut[0] = tolower(goOut[0]);
        }
        if (goOut == "b")
        {
            again = 0;
            cout << "Bye :)";
        }
    }
    return 0;
}
