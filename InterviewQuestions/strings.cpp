#include "stdafx.h"

void StringsTestCases()
{
    // MaxContiguous test cases
    if (MaxContiguous("google") != 2) throw;
    if (MaxContiguous("") != 0) throw;
    if (MaxContiguous("g") != 1) throw;
    if (MaxContiguous("googooogle") != 3) throw;
    if (MaxContiguous("gogole") != 1) throw;

	// Reverse Words test cases
    char rev1[] = "fox";
    char rev2[] = "the quick brown fox";
    char rev3[] = "the quick1 brown fox.";
    char rev4[] = "fox";
    char rev5[] = "";

    ReverseWords(rev2);
	ReverseWords(rev1);
	ReverseWords(rev3);
	ReverseWords(rev4);
	ReverseWords(rev5);
	ReverseWords(NULL);

	// atoi test cases
    char* invalidAToI = "1abc";
    char* positiveAToI = "123";
    char* negativeAToI = "-123";
    char* emptyAToI = "";
    char* nullAToI = NULL;
    int out = 0;

    if (!myAToI(positiveAToI, &out)) throw;
	if (!myAToI(negativeAToI, &out)) throw;
	if (myAToI(invalidAToI, &out)) throw;
	if (myAToI(emptyAToI, &out)) throw;
	if (myAToI(nullAToI, &out)) throw;

	// itoa test cases
    int positiveInt = 123;
    int negativeInt = -123;
    int zero = 0;
    int negativeZero = -0;
    int large = 2035567912;
    char* outStr = NULL;

    if (!myItoA(positiveInt, &outStr, 10)) throw;
	delete[] outStr;
    if (!myItoA(negativeInt, &outStr, 10)) throw;
	delete[] outStr;
    if (!myItoA(zero, &outStr, 10)) throw;
	delete[] outStr;
    if (!myItoA(negativeZero, &outStr, 10)) throw;
	delete[] outStr;
    if (!myItoA(large, &outStr, 10)) throw;
    delete[] outStr;
    if (!myItoA(large, &outStr, 16)) throw;
    delete[] outStr;
    if (!myItoA(large, &outStr, 2)) throw;
    delete[] outStr;
}

// Given a string of characters, find the longest string subsequence of a given character.
// Google tech screen, July 31, 2014
int MaxContiguous(char* psz)
{
    // Handle NULL
    if (!psz)
    {
        throw;
    }

    // Handle empty
    if (!*psz)
    {
        return 0;
    }

    // The first character is a subsequence of one.
    int maxSubsequence = 1;
    int curSubsequence = 1;

    while (*psz)
    {
        // Inspect each character. 
        // If the next character is the same as the previous, increment a counter
        if (*(psz + 1) == *psz)
        {
            curSubsequence++;
        }
        else
        {
            if (curSubsequence > maxSubsequence)
            {
                maxSubsequence = curSubsequence;
            }

            curSubsequence = 1;
        }

        psz++;
    }

    return maxSubsequence;
}


// Reverse the words in a sentence
void ReverseWords(char* pS)
{
	char* pHead = pS;
	char* pTail = pS;

	// null pointer check
	if (!pS)
		return;

	size_t cchS = strlen(pS);

	// 1 character or fewer is already reversed
	if (cchS < 2)
		return;

	// Advance pTail to the last character before the null;
	pTail = pHead + cchS - 1;

	// Reverse the string
	reverse(pHead, pTail);

	// each word must be treated as a separate reversable section
	pHead = pS;
	pTail = pS;

	// Find each word (character class [a-zA-z0-9] followed by 
	// anything outside that class (punctuation, whitespace, etc.)
	// and reverse them.
	// In ASCII, this can be accomplished by checking the char value against ranges.
	// In Unicode, this is significantly more complicated.
	while (true)
	{
		// reverse() needs a pointer to the first and last point in the string to reverse.
		// To know when to call reverse, we need to look ahead one character to detect word boundaries 
		// and end of string.
		char* pLookahead = pTail + 1;

		// Reverse each word; use any non-word characters as boundaries
		if ((*pLookahead >= '0' && *pLookahead <= '9') || (*pLookahead >= 'A' && *pLookahead <= 'z') && *pLookahead != '\0')
		{
			pTail++;
		}
		else
		{
			// reverse the word
			reverse(pHead, pTail);

			// Advance to the non-word character
			pTail++;

			// Handle end-of-string
			if (!*pTail)
				break;

			// skip the non-word character
			pTail++;

			// look for the next word
			pHead = pTail;
		}
	}
}

// Integer to string, handles base 2, 10, and 16
// Caller deallocates *ppA.
bool myItoA(int i, char** ppA, int radix)
{
    char map[] = {"0123456789ABCDEF"};
	bool ret = true;
	bool fIsNegative = false;

	// Allocate sufficient space to store the string representation of the largest possible int in any base (bits in an int + sign + a null)
	char* pStr = new char[sizeof(int) * 8 + 2];
	char* pStr2 = pStr;
	char* pRet = pStr;

    if (radix > (sizeof(map) / sizeof(*map)))
    {
        return false;
    }
    
    // Handle negative
	if (i < 0 && radix == 10)
	{
		fIsNegative = true;
		i = -i;
	}

	// Handle zero, as there's no work to do.
	if (i == 0)
	{
		*pStr++ = '0';
	}

    // Insert the sign
    // Build the string in reverse
	while (i != 0)
	{
		// get least significant digit
        // This can either be looked up from a table or calculated with offsets into 
        // '0' and 'A' (remainder + '0' or remainder - 10 + 'A', for hex)
        *pStr++ = map[i % radix];
        i /= radix;
	}

    if (fIsNegative)
    {
        *pStr++ = '-';
    }

    // zero-terminate
	*pStr = '\0';

	reverse(pStr2, pStr - 1);

	*ppA = pRet;
	return ret;
}

// string to integer. This implementation supports base-10 integers only.
bool myAToI(char* a, /*out*/int* i)
{
	int ret = 0;
	bool isNegative = false;

	if (!a || !i || !(*a))
		return false;

	while (*a)
	{
		if (*a == '-')
		{
			isNegative = true;
		}
		else if ((*a < '0') || (*a > '9'))
		{
			return false;
		}
		else
		{
			int currentVal = 0;
			currentVal = *a - '0';
			ret *= 10;
			ret += currentVal;
		}
		a++;
	}

	if (isNegative)
	{
		ret = -ret;
	}

	*i = ret;
	return true;
}

// Reverse the characters between head and tail
void reverse(char* pHead, char* pTail)
{
	if (!pHead || !pTail)
		return;

	while (true)
	{
		// Go halfway, then stop
		if (pTail <= pHead)
			break;

		// swap
		char c = *pHead;
		*pHead = *pTail;
		*pTail = c;
		pTail--;
		pHead++;
	}
}


// Replace all instances of pszSub in pszIn, returning the results in ppszOut
// TODO: complete this implementation; should use strstr instead of implementing its own
void SearchAndReplace(char* pszIn, char* pszSearch, char* pszReplace, char** ppszOut)
{
	// This code will return a new block of memory, which is the string containing the search/replace code
	// The second step is allocating the memory and performing the string transformation.

	int cchSearch, cchReplace = 0;

	cchSearch = strlen(pszSearch);
	cchReplace = strlen(pszReplace);

	// The first step to allocating this string is to determine how long it must be (e.g., how many substitutions need to take place.)
	// If the search and replace strings are the same length, this step can be skipped.
	if (cchReplace != cchSearch)
	{
		int strLen = 0;
		char* pIn2 = pszIn;

		// Check each character
		while (*pIn2)
		{
			// If the first character of a substring appears, attempt to match the subsequent characters.
			if (*pIn2 == *pszSearch)
			{
				char* pIn3 = pIn2;
				char* pS = pszSearch;

				// If they match, we have a substring. Add the count of characters of the replace string and 
				// move the pointer past the search string. If not, keep inspecting the string.
				while (*pIn3)
				{
					// Implement strstr
					// This is a match. Add the count of characters to be replaced in the second pass to the accumulator and move the loop pointer.
					if (!*pS)
					{
						strLen += cchReplace;
						pIn2 += cchSearch;
						break;
					}

					// Advance the pointer while the string matches the substring
					if (*pIn3 == *pS)
					{
						pIn3++;
						pS++;
					}
					// As soon as the string stops matching the substring, bail; we have nothing to do here.
					else
					{
						strLen++;
						pIn2++;
						break;
					}
				}
			}
			// No chance of this matching a substring; aggregate it for the future.
			else
			{
				strLen++;
				pIn2++;
			}
		}

		int temp = strlen(pszIn);
		int foo = strLen - temp;
	}
}
