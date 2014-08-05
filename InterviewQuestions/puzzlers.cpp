#include "stdafx.h"

void TestPuzzlers()
{
    // Longest subsequence of ones and zeros test cases
    LongestSubsequence("aaabbb");
    LongestSubsequence("aaab");
    LongestSubsequence("abba");

    // Array of products test cases
    int productArray1[] = { 2, 3, 1, 4 }; /* expected output: {12, 8, 24, 6} */
    int productArray2[] = { 2, 0, 1, 4 }; /* expected output: {0, 8, 0, 0} */
    int* pOut;
    ArrayOfProducts(productArray1, sizeof(productArray1) / sizeof(*productArray1), &pOut); delete[] pOut;
    ArrayOfProducts(productArray2, sizeof(productArray2) / sizeof(*productArray2), &pOut); delete[] pOut;

    // Angle test cases
    int angle;
    angle = AngleBetweenHourAndMinute(12, 40);
    angle = AngleBetweenHourAndMinute(4, 30);
    angle = AngleBetweenHourAndMinute(4, 40);
    angle = AngleBetweenHourAndMinute(12, 30);
    angle = AngleBetweenHourAndMinute(12, 00);

        // CheckIfPrime
    if (!CheckIfPrime(37))
        throw;

    // SumOfTwo
    int valid[] = { -10, -1, 1, 3, 3, 4, 4, 4, 7, 9, 13 };
    int oneElement[] = { 7 };

    // base functionality with match
    if (!TwoElementsSumToTarget(valid, (sizeof(valid) / sizeof(int)), 5)) throw;

    // Valid array but no match
    if (TwoElementsSumToTarget(valid, (sizeof(valid) / sizeof(int)), 50)) throw;

    // One element, match, but false return expected (function only works on arrays of 2 or greater)
    if (TwoElementsSumToTarget(oneElement, (sizeof(oneElement) / sizeof(int)), 7)) throw;

    // One element, no match
    if (TwoElementsSumToTarget(oneElement, (sizeof(oneElement) / sizeof(int)), 2)) throw;

    // NULL input
    if (TwoElementsSumToTarget(NULL, 3, 2)) throw;
}

// In the form hh::mm
int AngleBetweenHourAndMinute(int hour, int minute)
{
    int minuteAngle = 6 * minute;
    int hourAngle = ((60 * (hour % 12)) + minute) / 2;

    return hourAngle - minuteAngle;
}

/*
Given an array of numbers, nums, return an array of numbers products, where products[i] is the product of all nums[j], j != i.
Input : [1, 2, 3, 4, 5]
Output: [(2*3*4*5), (1*3*4*5), (1*2*4*5), (1*2*3*5), (1*2*3*4)]
= [120, 60, 40, 30, 24]
O(N) complexity with no division.
*/
void ArrayOfProducts(int* pIn, int cElements, int** ppOut)
{
    int* rgProducts = new int[cElements];
    int n = 1;

    // First time through, init the array from left to right with the products of in[0] through in[count]
    for (int i = 0; i < cElements; i++)
    {
        rgProducts[i] = n;
        n *= pIn[i];
    }

    n = 1;

    // Next time through, modify the array elements from right to left, multiplying the products array by n, 
    // and then n multiplied by successive values of pIn[i]
    for (int i = cElements - 1; i >= 0; i--)
    {
        rgProducts[i] *= n;
        n *= pIn[i];
    }

    *ppOut = rgProducts;
}

bool CheckIfPrime(int target)
{
    for (int i = 2; i * i <= target; i++)
    {
        if (target % i == 0)
        {
            return false;
        }
    }

    return true;
}

bool BinarySearch(int* prgInt, int startIndex, int endIndex, int searchValue)
{
    int middle = (endIndex - startIndex) / 2 + startIndex;

    // Item not found, return false
    if (endIndex < startIndex)
    {
        return false;
    }

    // We are down to a single item, return it
    if (endIndex == startIndex)
    {
        return true;
    }

    // Search is greater than middle of the current block, so search the smaller half
    if (searchValue > prgInt[middle])
    {
        return BinarySearch(prgInt, startIndex, middle - 1, searchValue);
    }
    else
    {
        return BinarySearch(prgInt, middle + 1, endIndex, searchValue);
    }
}

// Given a string that contains either 'y's or t's, implement a function that will print the longest subsequence 
// containing an equal number of each character.
// E.g. "yyytttyyy" prints "yyyttt" or "tttyyy"
// "ytt" prints "yt"
// "tt" prints ""
// "" prints ""
// NULL prints ""

void LongestSubsequence(char* pIn)
{
    // null ptr
    if (!pIn)
        return;

    int cch = strlen(pIn);

    // need at least two characters to achieve balance
    if (cch < 2)
        return;

    // This array stores the max and min running sums in its index and the index 
    // at which that sum was seen in the value. This includes the range -n to n and includes 0.
    int arrayLen = cch * 2 + 1;
    char** sumMap = new char*[arrayLen];
    memset(sumMap, NULL, arrayLen * sizeof(*sumMap));
    sumMap[cch] = pIn;

    char* pStart = NULL;
    char* pEnd = NULL;
    // Store the running sum in an array, where the index is the running sum 
    // and the value is the pointer to the position in the array where the running sum occurs.
    int sum = 0;

    while (*pIn)
    {
        if (*pIn == 'a')
            sum++;
        else
            sum--;

        int offset = cch + sum;

        if (!sumMap[offset])
            sumMap[offset] = pIn;

        // If this sumMap offset already has a value, then use it to calculate the start and
        // end pointers
        else if ((pIn - sumMap[offset]) > (pEnd - pStart))
        {
            pStart = sumMap[offset] + 1;
            pEnd = pIn;
        }

        pIn++;
    }

    while (pStart <= pEnd)
    {
        cout << pStart;
        pStart++;
    }

    cout << endl;

    delete[] sumMap;
}

// Determine if any two elements in prgInt sum to targetSum.
// x + y = targetSum
// y = targetSum - x
// Three ways to implement this:
// O(N^2), with nested for loops
// O(N log N), with a sort and a binary search for (targetSum - prgInt[i])
// O(N), with a hash map (unordered_set or similar object); solve "x + y = target" for y and check the set
// for that value. If it does not exist, add it, else, return true.
// amazon.com tech screen, July 25, 2014, 15:00
bool TwoElementsSumToTarget(int* prgInt, int cElements, int targetSum)
{
    // Empty list or fewer than two elements means we can't sum two elements in the array
    if (!prgInt || cElements < 2)
    {
        return false;
    }

    // Use an unordered set (based on hash map)
    std::unordered_set<int> s;

    for (int i = 0; i < cElements; i++)
    {
        // Algebra: x + y = target
        // y = target - x
        if (s.count(targetSum - *prgInt))
        {
            return true;
        }
        else
        {
            s.insert(*prgInt);
        }

        prgInt++;
    }

    return false;
}
