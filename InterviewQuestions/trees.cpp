#include "trees.h"
/*
*/

// Use reservoir sampling with a sample collection size of one. 

void TreeTests()
{
    int array[] = { 1, 4, 9, 7, 3, 9, 4, 7, 2, 7, 3, 0, 1, 2, 9, 6, 5, 7, 8, 9 };
    for (int i = 0; i < 10000; i++)
    {
        int largestIndex = ReturnMaxArrayIndexRandomly(array, sizeof(array) / sizeof(int));
        cout << "Largest index in the array (random) is: " << largestIndex << "; value is: " << array[largestIndex] << endl;
    }
}

// This is an array problem, not a tree problem. Needs a new source file.
// Given an array of integers, find the max element in the array, which is at multiple places.Return any one of the indices randomly.
int ReturnMaxArrayIndexRandomly(int* pInts, int cElements)
{
    int largestIndex;
    int largestValue;
    int cLargest = 0;

    largestIndex = 0;
    largestValue = pInts[0];

    srand((unsigned)time(NULL));

    for (int i = 1; i < cElements; i++)    
    {
        if (pInts[i] > largestValue)
        {
            largestIndex = i;
            largestValue = pInts[i];
            cLargest = 1;
        }
        else if (pInts[i] == largestValue)
        {
            cLargest++;

            double p = ((double)1 / cLargest);
            double randomP = (double)rand() / RAND_MAX;

            if (p >= randomP)
            {
                largestIndex = i;
            }
        }
    }

    return largestIndex;
    // Use reservoir sampling and iterate on the entire list to randomly find a largest element.
    // This doesn't guarantee the largest index being found, so it's not the right solution.
    /*
    // Establish a sample array; in this problem, it is of size 1
    int samples[1];
    *samples = 0;
    int i = 0;
    int ret = i;

    // Insert the first element of the array into samples (take the first sample from the reservoir)
    *samples = pInts[i++];

    // Init the random number generator
    srand((unsigned)time(NULL));

    // Inspect each value in the array. 
    for (; i < cElements; i++)
    {
        // Select a value at random from the iterated portion of the list
        int randomIndex = rand() % (i + 1);

        // If it's bigger, store the index. This code also stores the 
        // actual sample, although it doesn't do anything with it.
        if (pInts[randomIndex] > *samples)
        {
            *samples = pInts[randomIndex];
            ret = randomIndex;
        }
    }

    if (pInts[ret] < 9)
        throw;

    return ret;
    */
}

// Organize a contact database for quick search using phone dialpad (e.g., 726 brings up SAM)
/*
Data:
133
Aggressive Aardvark
133
Chhatty Camel
142 
Clear Camel

Clean Comet

Build a trie of contacts; leaf nodes contain a list of matching contacts
Build a mapping between number and letter

mapping table of numbers to candidate letters

array of linked lists:

char** mapping = new char['z'];
['a'] = 1;
[2] d->e->f->null
[3] g->h->i->null
[4] j->k->l->null
[5] m->n->o->null
[6] p->q->r->s->null
[7] t->u->v->null

trie of contacts
                                                 []
                                [1]                     [2]
                       [a]     [b]     [c]...
                    [ag]     [bo]   [ch] [cl]
                                          [cle]
                                           [clea]
                                      [clean] [clear]

FindCandidates(int* pDigits, int cDigits, int maxCandidates, char** prgCandidates, int* cCandidates)
{
    for (int i = 0; i < cDigits; i++)
    {
        char* charsToCheck = mapping[pDigits[0]];
    }
}
                                 
algorithm:
As a key is entered, map it to a list of alphabetical candidates. For each candidate, traverse the trie to
the maximum available depth and return all candidates for that combination. 

struct Node
{
    char* psz;
    std::vector<Node> nodes;
};


*/
