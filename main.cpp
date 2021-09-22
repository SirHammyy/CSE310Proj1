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

void reverseString(string& a, int length)
{
    for (int i = 0; i < length / 2; i++)
    {
        char temp = a[i];
        a[i] = a[length - i - 1];
        a[length - i - 1] = temp;
    }
}

string encode(string input)
{
    string original = input;
    if (input == "\n")
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
    insertionSort(outputs, input.length());

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

        if (string(argv[1]) == "insertion")
        {
            ifstream inputFile;
            ofstream outputFile;
            outputFile.open(outputFileName);
            inputFile.open(inputFileName);

            string input;
            while(inputFile)
            {
                getline(inputFile, input);
                string output = encode(input);
                outputFile << output << endl;
            }
            outputFile.close();
            inputFile.close();
            return 0;
        }
        else if (string(argv[1]) == "mergesort")
        {
            //Merge sort
        }
    }

    else
    {
        string input;
        getline(cin, input);
        int length = input.length();
        string output = encode(input);
        cout << output << endl;
        return 0;
    }
}
