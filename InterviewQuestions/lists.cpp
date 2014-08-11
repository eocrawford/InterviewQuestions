#include "stdafx.h"

void ListTestCases()
{
	Node* pHead = new Node(1);
	pHead->pNext = new Node(2);
	pHead->pNext->pNext = new Node(3);
	pHead->pNext->pNext->pNext = new Node(4);
	pHead->pNext->pNext->pNext->pNext = new Node(5);
	pHead->pNext->pNext->pNext->pNext->pNext = new Node(6);

    // NthFromEnd test cases
    Node* nth;
    nth = NthFromEnd(pHead, 0);
    nth = NthFromEnd(NULL, 0);
    nth = NthFromEnd(pHead, 5);
    nth = NthFromEnd(pHead, 6);
    nth = NthFromEnd(pHead, 7);

    // Test circularly linked lists
    pHead->pNext->pNext->pNext->pNext->pNext->pNext = pHead;

	if (!HasCycle(pHead))
	{
		throw;
	}

	// Break the cycle to enable list deletion
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

// Write a function that returns the Nth node from the end of a linked list.
// E.g.: 1->2->3->4->NULL, 2, returns node 2.
Node* NthFromEnd(Node* pHead, unsigned int offset)
{
    if (!pHead)
        return NULL;

    Node* pOne = pHead;
    Node* pTwo = pHead;

    // Open a gap
    while (pTwo && offset > 0)
    {
        pTwo = pTwo->pNext;
        offset--;
    }

    // The provided offset is larger than the list length
    if (offset)
        return NULL;

    // Advance both pointers until pTwo goes to null
    // Check pOne->pNext for the 0 offset case (return last node)
    while (pOne->pNext && pTwo)
    {
        pOne = pOne->pNext;
        pTwo = pTwo->pNext;
    }

    return pOne;
}
