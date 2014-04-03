/**
 * \file    RangeQuery.cpp
 *
 * \brief   RangeQuery class member functions defined
 *
 * \author  Shachindra Chandrashekar
 *
 * \version 1.0,04022014,SAC Initial version
 */
 
#include "RangeQuery.h"

int num_nodes;

tnode* allocNode(int min, int max, tnode* l, tnode* r)
{
    if(min > max)
    {
        printf("\nError : min > max for a new node");
        while(1);
    }
    num_nodes++;
    tnode* retVal = (tnode*)malloc(sizeof(tnode));
    retVal->left = l;
    retVal->right = r;
    retVal->max = max;
    retVal->min = min;
    return retVal;
}

void freeNode(tnode* node)
{
    if(node == NULL)
    {
        printf("\nError : Freeing node is NULL");
        while(1);
    }
    num_nodes--;
    free(node);
}

RangeQuery::RangeQuery()
{
    root = allocNode(MAX,MAX,NULL,NULL);
}

RangeQuery::~RangeQuery()
{
    deleteTree(root);
    root = NULL;
}

tnode* RangeQuery::addRange(tnode* curr, int min, int max)
{
    if(curr == NULL)
    {
        curr = allocNode(min,max,NULL,NULL);
        return curr;
    }

    bool isMinInRange = contains(curr,min);
    bool isMaxInRange = contains(curr,max);
    if(isMinInRange && isMaxInRange)
    {
        return curr;
    }
    else if(isMinInRange && !isMaxInRange)
    {
        curr->right = addRange(curr->right,curr->max + 1,max);
    }
    else if(!isMinInRange && isMaxInRange)
    {
        curr->left = addRange(curr->left,min,curr->min - 1);
    }
    else
    {
        if(max < curr->min)
        {
            curr->left = addRange(curr->left,min,max);
        }
        else if(min > curr->max)
        {
            curr->right = addRange(curr->right,min,max);
        }
        else//max > curr->max && min < curr->min
        {
            curr->left = addRange(curr->left,min,curr->min - 1);
            curr->right = addRange(curr->right,curr->max + 1, max);
        }
    }
    return curr;
}

void RangeQuery::addRange(int min, int max)
{
    root = addRange(root,min,max);
}

tnode* RangeQuery::delRange(tnode* curr, int min, int max)
{
    if(curr == NULL)
        return NULL;

    bool isMinInRange = contains(curr,min);
    bool isMaxInRange = contains(curr,max);

    if(isMinInRange && isMaxInRange)
    {
        if(min == curr->min && max == curr->max)
        {
            freeNode(curr);
            curr = NULL;
        }
        else if(min == curr->min && max > curr->min)
        {
            curr->min = max + 1;
        }
        else if(min == curr->min && max == curr->min)
        {
            curr->min = curr->min + 1;
        }
        else if(min > curr->min && max == curr->max)
        {
            curr->max = min - 1;
        }
        else if(min == curr->max && max == curr->max)
        {
            curr->max = curr->max - 1;
        }
        else if(min > curr->min && max < curr->max)
        {
            tnode* myLeft = allocNode(curr->min,min-1,curr->left,NULL);
            curr->left = myLeft;
            curr->min = max + 1;
        }
        else
        {
            //cant happen
            printf("\nError : Invalid condition");
            while(1);
        }
    }
    else if(isMinInRange && !isMaxInRange)
    {
        if(min == curr->min)
        {
            tnode* retVal = delRange(curr->right,curr->max + 1,max);
            if(retVal)
            {
                retVal->left = curr->left;
            }
            else
            {
                retVal = curr->left;
            }
            freeNode(curr);
            curr = NULL;
            return retVal;
        }
        else if((min > curr->min)||(min == curr->max))
        {
            curr->right = delRange(curr->right,curr->max + 1,max);
            curr->max = min - 1;
        }
        else
        {
            //cant happen
            printf("\nError : Invalid condition");
            while(1);
        }
    }
    else if(!isMinInRange && isMaxInRange)
    {
        if(max == curr->max)
        {
            tnode* retVal = delRange(curr->left,min,curr->min - 1);
            if(retVal)
            {
                retVal->right = curr->right;
            }
            else
            {
                retVal = curr->right;
            }
            freeNode(curr);
            curr = NULL;
            return retVal;
        }
        else if((max < curr->max) || (max == curr->min))
        {
            curr->left = delRange(curr->left,min,curr->min - 1);
            curr->min = max + 1;
        }
        else
        {
            //cant happen
            printf("\nError : Invalid condition");
            while(1);
        }
    }
    else//max > curr->max && min < curr->min
    {
        if(max < curr->min)
        {
            curr->left = delRange(curr->left,min,max);
        }
        else if(min > curr->max)
        {
            curr->right = delRange(curr->right,min,max);
        }
        else//max > curr->max && min < curr->min
        {
            tnode* retVal = delRange(curr->right,curr->max + 1, max);
            if(retVal)
            {
                retVal->left = delRange(curr->left,min,curr->min - 1);
            }
            else
            {
                retVal = delRange(curr->left,min,curr->min - 1);
            }
            freeNode(curr);
            curr = NULL;
            return retVal;
        }
    }
    return curr;
}

void RangeQuery::delRange(int min, int max)
{
    root = delRange(root,min,max);
}

bool RangeQuery::queryPoint(int val)
{
    tnode* curr = root->left;
    while(curr)
    {
        if(contains(curr,val))
            return true;

        curr = (val < curr->min) ? curr->left : curr->right;
    }
    return false;
}

bool RangeQuery::contains(tnode* node, int val)
{
    if(val >= node->min && val <= node->max)
        return true;
    return false;
}

void RangeQuery::clear()
{
    deleteTree(root);
    root = NULL;
    RangeQuery();
}

void RangeQuery::deleteTree(tnode* node)
{
    if(node == NULL)
        return;
    deleteTree(node->left);
    deleteTree(node->right);
    freeNode(node);
    node = NULL;
}


