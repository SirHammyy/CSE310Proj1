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

    //Sort
    int* ascii = new int[input.length()];
    for (int i = 0; i < length; i++)
    {
        ascii[i] = int(output[i][0]);
    }
    mergeSort(ascii, ascii[0], ascii[length - 1]);

    for (int i = 0; i < length; i++)
    {
        cout << ascii[i] << endl;
    }


    return output;
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
