#pragma once

struct Node
{
    Node(){}
    Node(int p) : payload(p), pNext(NULL){}

	int payload;
	Node* pNext;
};

Node* NthFromEnd(Node* pHead, unsigned int offset);
void ListTestCases();
bool HasCycle(Node* pHead);
void DeleteList(Node* pHead);
