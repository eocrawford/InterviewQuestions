#pragma once

struct Node
{
	int payload;
	Node* pNext;
};

void ListTestCases();
bool HasCycle(Node* pHead);
void DeleteList(Node* pHead);
