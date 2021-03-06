#include <iostream>
#include <fstream>
#include "string.h"

using namespace std;

void merge(string *a, int l, int m, int r)
{
    int i, j, k;
    int lower = m-l+1;
    int upper = r-m;
    string* left = new string[lower];
    string* right = new string[upper];

    for(i = 0; i<lower; i++)
        left[i] = a[l+i];
    for(j = 0; j<upper; j++)
        right[j] = a[m+1+j];

    i = 0; j = 0; k = l;

    while(i < lower && j<upper)
    {
        if(left[i] <= right[j])
        {
            a[k] = left[i];
            i++;
        }
        else
        {
            a[k] = right[j];
            j++;
        }
        k++;
    }
    while(i<lower)
    {
        a[k] = left[i];
        i++;
        k++;
    }
    while(j<upper)
    {
        a[k] = right[j];
        j++;
        k++;
    }
}

void mergeSort(string *a, int l, int r)
{
    if (l < r)
    {
        int m = (r + l) / 2;
        mergeSort(a, l, m);
        mergeSort(a, m + 1, r);
        merge(a, l, m, r);
    }
}

void insertionSort(string* a, int length)
{
    string key;
    int j;
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

string insertionSort(string a, int length)
{
    char key;
    int j;
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

    return a;
}

void reverseString(string& a, int length)
{
    for (int i = 0; i < length / 2; i++)
    {
        char temp = a[i];
        a[i] = a[length - i - 1];
        a[length - i - 1] = temp;
    }
}

string encode(string input, bool type)
{
    string original = input;
    if (input == "")
    {
        return "\n";
    }
    //Iterate through the string, shifting one space right
    int iterations = 1;
    int length = input.length();
    string* outputs = new string[length];
    string output;
    outputs[0] = input;
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
        outputs[iterations] = input;
        iterations++;
    }
    cout << endl;

    //Reverse Strings
    for (int i = 0; i < length; i++)
    {
        reverseString(outputs[i], length);
    }

    //Sort
    if (type == 0)
        insertionSort(outputs, input.length());
    else
        mergeSort(outputs, 0, input.length() - 1);

    //Rereverse Strings and find correct line
    int correctPos = 0;
    for (int i = 0; i < length; i++)
    {
        reverseString(outputs[i], length);
        if (outputs[i] == original)
        {
            correctPos = i;
        }

    }

    output.append(to_string(correctPos));
    output.append("\n");


    //Find second line of output
    int i = 0;
    int counter = 1;
    while(i < length - 1) {
        if (outputs[i][0] != outputs[i + 1][0]) {
            output += to_string(counter);
            output += outputs[i][0];
            counter = 1;
            i++;
        }
        else
        {
            counter++;
            i++;
        }
    }
    output += to_string(counter);
    output += outputs[i][0];

    return output;
}

int main(int argc, char* argv[])
{
    if (argc > 1)
    {
        string inputFileName = string(argv[2]);
        string outputFileName = string(argv[3]);

        ifstream inputFile;
        ofstream outputFile;
        outputFile.open(outputFileName);
        inputFile.open(inputFileName);

        if (string(argv[1]) == "insertion") {
            string input;
            while (getline(inputFile, input)) {
                string output = encode(input, 0);
                outputFile << output << endl;
            }
            outputFile.close();
            inputFile.close();
            return 0;
        } else if (string(argv[1]) == "merge") {
            string input;
            while (getline(inputFile, input)) {
                string output = encode(input, 1);
                outputFile << output << endl;
            }
            outputFile.close();
            inputFile.close();
            return 0;
        }
    }

    else
    {
        string input;
        getline(cin, input);
        string output = encode(input, 0);
        return 0;
    }
}