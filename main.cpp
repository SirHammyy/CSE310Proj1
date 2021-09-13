#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void merge(int a[], int l, int m, int r)
{
    int i, j, k;
    int lower = m - l + 1;
    int upper = r - m;
    int* left = new int[lower];
    int* right  = new int[upper];

    for (i = 0; i < lower; i++)
    {
        //TODO Merge
    }
}

void mergeSort(int a[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        mergeSort(a, l, m);
        mergeSort(a, m + 1, r);
        merge(a, l, m, r);
    }
}


void insertionSort(int a[], int length)
{
    int key, j;
    for (int i = 1; i < length; i++)
    {
        key = a[i];
        j = i - 1;
        while (j >= 0 && a[j] > key)
        {
            a[j + 1] = a[j];
            j = j - 1;
        }
        a[j + 1] = key;
    }
}

string* recoverStrings(string* a, int* b, int length)
{
    string* output = new string[length];
    for (int i = 0; i < length; i++)
    {
        if (b[i] != b[i + 1])
        {
            int j = 0;
            while (b[i] != int(a[j][length - 1]))
            {
                j++;
            }
            output[i] = a[j];
        }

        else
        {
            int* matches = new int[length];
            string* options = new string[length];
            matches[0] = i;
            int j = i + 1;
            int counter = 1;
            while (b[i] == b[j])
            {
                options[i] = a[i];
                matches[counter - 1] = b[j]; 
                counter++;
                j++;
                i++;
            }
            cout << counter - 1 << endl;
            for (int i = matches[0]; i < counter - 1; i++)
            { 
                matches[i] = (int)a[i][length - 1];
            }
            insertionSort(matches, counter - 1);
            for (int i = 0; i < counter - 1; i++)
            {
                //cout << (char)matches[i] << endl;
            }
            recoverStrings(options, matches, counter - 1); 
        }
    }

    return output;
}

string* encode(string input)
{
    //Iterate through the string, shifting one space right
    int iterations = 1;
    int length = input.length();
    string* output = new string[length];
    output[0] = input;
    while (iterations < length)
    {
        char temp;
        char last = input[length - 1];
        for (int i = length - 1; i > 0; i--)
        {
            temp = input[i - 1];
            input[i - 1] = input[i];
            input[i] = temp;
        }
        input[0] = last;
        output[iterations] = input;
        iterations++;
    }
    cout << endl;

    //Sort
    int* ascii = new int[input.length()];
    for (int i = 0; i < length; i++)
    {
        ascii[i] = int(output[i][input.length() - 1]);
    }
    //mergeSort(ascii, ascii[0], ascii[length - 1]);
    insertionSort(ascii, input.length());
    return recoverStrings(output, ascii, input.length());
}

int main(int argc, char* argv[])
{
    string input;
    getline(cin, input);
    int length = input.length();
    string* output = encode(input);
    for (int i = 0; i < length; i++)
    {
        cout << output[i] << endl;
    }
    return 0;
}
