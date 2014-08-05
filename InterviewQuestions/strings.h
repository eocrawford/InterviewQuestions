#pragma once
#include "stdafx.h"

void StringsTestCases();
void ReverseWords(char* pS);
bool myItoA(int i, char**ppA, int radix);
bool myAToI(char* a, /*out*/int* i);
void reverse(char* pHead, char* pTail);
int MaxContiguous(char* psz);

void SearchAndReplace(char* pszIn, char* pszSearch, char* pszReplace, char** ppszOut);
