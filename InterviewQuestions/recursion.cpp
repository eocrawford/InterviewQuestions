#include "recursion.h"

void RecursionTests()
{
    char one[] = "abcd";
    char two[] = "racecar";
    PrintStringPermutations(one);
}

void swap(char* p1, char* p2)
{
    char temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

void PrintBoolArray(bool* pUsedValues, int cElements)
{
    cout << "Bool array: " << endl;
    for (int i = 0; i < cElements; i++)
    {
        cout << "Element " << i << ": " << pUsedValues[i] << endl;
    }
}

// Each iteration of this function that doesn't print copies a permuted character into the new buffer
void PermuteRecursively(char* psz, char* pNew, bool* pUsedValues, int cch, int currentIndex)
{
    cout << "Recursion depth: " << currentIndex + 1 << endl;
    cout << "Before: " << pNew << endl;
//    PrintBoolArray(pUsedValues, cch);

    if (currentIndex == cch)
    {
        cout << "New permutation: " << pNew << endl << endl;
        return;
    }

    // For each character in the original string,
    for (int i = 0; i < cch; i++)
    {
        // Check a "used" array to determine if we've already copied this character into the permuted string
        if (pUsedValues[i])
            continue;

        // If not, copy it, and mark it as used
        pNew[currentIndex] = psz[i];
        pUsedValues[i] = true;
        PermuteRecursively(psz, pNew, pUsedValues, cch, currentIndex + 1);
        pUsedValues[i] = false;
    }
}

// Write a function that prints the unique combinations of letters in the provided string
// E.g.: cat, act, atc, tac
void PrintStringPermutations(char* psz)
{
    // act on 2 or more characters
    if (!psz || !*(psz) || !*(psz + 1))
        return;

    int cch = strlen(psz);
    char* pNew = new char[cch + 1];
    pNew[cch] = '\0';

    bool* pUsedValues = new bool[cch + 1];
    memset(pUsedValues, 0, sizeof(bool) * (cch + 1));

    PermuteRecursively(psz, pNew, pUsedValues, cch, 0);

    delete[] pNew;
    delete[] pUsedValues;
}
