/**
 * \file    RangeQuery.h
 *
 * \brief   RangeQuery class defined
 *
 * \author  Shachindra Chandrashekar
 *
 * \version 1.0,04022014,SAC Initial version
 */

#include<stdio.h>
#include<stdlib.h>

#define MAX 999999
#define MIN -1 * MAX

typedef struct _tnode
{
    int min;
    int max;

    _tnode *left;
    _tnode *right;

    _tnode()
    {
        min = MAX;
        max = MIN;

        left = NULL;
        right = NULL;
    }
}tnode;

tnode* allocNode(int min, int max, bool isVal, tnode* l, tnode* r);
void freeNode(tnode* node);

class RangeQuery
{
private:
    tnode* root;
    tnode* addRange(tnode* curr, int min, int max);
    tnode* delRange(tnode* curr, int min, int max);
    bool contains(tnode* node, int val);
    void deleteTree(tnode* node);

public:
    RangeQuery();
    ~RangeQuery();
    void addRange(int min, int max);
    void delRange(int min, int max);
    bool queryPoint(int val);
    void clear();
};