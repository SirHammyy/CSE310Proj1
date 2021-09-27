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

string decode(string input, bool type)
{
    if (input == "\n")
    {
        return "\n";
    }

    string original, first;
    bool alt = false;
    char current;
    int amount;

    //First Letter
    for (int i = 0; i < input.length(); i++)
    {
        if (!alt)
        {
            amount = input[i] - 48;
        }
        else
        {
            current = input[i];
            for (int j = 0; j < amount; j++)
            {
                first += current;
            }
        }
        alt = !alt;
    }

    //Last Letter
    int length = first.length();
    string last = first;
    last = insertionSort(last, last.length());

    //Prev                  <--This is where I got stuck
    int prev[length];
    bool used[length];

    for (int i = 0; i < length; i++)
        used[i] = false;

    for (int i = 0; i < length; i++)
    {
        int j = 0;
        if (last[i] != (last[i+1] || last[i-1]))
        {
            while (last[i] != first[j])
            {
                j++;
            }
            prev[i] = j;
            used[j] = true;
        }
    }

    for (int i = 0; i < length; i++)
        cout << first[i] << " ";
    cout << endl;
    for (int i = 0; i < length; i++)
        cout << last[i] << " ";
    cout << endl;
    for (int i = 0; i < length; i++)
        cout << prev[i] << " ";
    cout << endl;
    for (int i = 0; i < length; i++)
        cout << used[i] << " ";

    return original;
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
                string output = decode(input, 0);
                outputFile << output << endl;
            }
            outputFile.close();
            inputFile.close();
            return 0;
        } else if (string(argv[1]) == "merge") {
            string input;
            while (getline(inputFile, input)) {
                string output = decode(input, 1);
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
        string output = decode(input, 0);
        return 0;
    }
}