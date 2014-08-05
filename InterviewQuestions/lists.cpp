#include "stdafx.h"

void ListTestCases()
{
	// Test circularly linked lists
	Node* pHead = new Node();
	pHead->pNext = new Node();
	pHead->pNext->pNext = new Node();
	pHead->pNext->pNext->pNext = new Node();
	pHead->pNext->pNext->pNext->pNext = new Node();
	pHead->pNext->pNext->pNext->pNext->pNext = new Node();
	pHead->pNext->pNext->pNext->pNext->pNext->pNext = pHead;

	if (!HasCycle(pHead))
	{
		throw;
	}

	// Un-circular the list to enable deleting it
	pHead->pNext->pNext->pNext->pNext->pNext->pNext = NULL;
	DeleteList(pHead);
}

bool HasCycle(Node* pHead)
{
	Node* pSingle = pHead;
	Node* pDouble = pHead;
	bool fIsCycle = false;

	if (!pHead)
		return false;

	// Create two pointers to pHead. The first will be advanced by a single node on each iteration.
	// The second will be advanced by two nodes. If the pointers are ever the same, there is a cycle
	// in the list. If there is no cycle, this loop will terminate naturally.
	while (pSingle && pDouble && pDouble->pNext)
	{
		pSingle = pSingle->pNext;
		pDouble = pDouble->pNext->pNext;

		if (pSingle == pDouble)
		{
			fIsCycle = true;
			break;
		}
	}

	return fIsCycle;
}

void DeleteList(Node* pHead)
{
	if (!pHead)
		return;

	Node* pCur = pHead;
	while (pCur)
	{
		Node* pDel = pCur;
		pCur = pCur->pNext;
		delete pDel;
	}
}
