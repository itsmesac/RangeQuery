/**
 * \file    RangeQueryDriver.cpp
 *
 * \brief   Driver program to test RangeQuery class
 *
 * \author  Shachindra Chandrashekar
 *
 * \version 1.0,04022014,SAC Initial version
 */
 
#include"RangeQuery.h"

int main()
{
    RangeQuery rq;
#if 0
    rq.addRange(50,60);
    rq.addRange(20,40);
    rq.addRange(25,45);
    rq.addRange(20,80);
    rq.addRange(10,90);
    rq.delRange(0,100);
#endif

    bool contains = false;

#if 0
    rq.addRange(100,200);
    rq.addRange(50,80);
    rq.addRange(40,60);
    contains = rq.queryPoint(65);
    rq.delRange(60,90);
    contains = rq.queryPoint(65);
    rq.addRange(70,120);
    contains = rq.queryPoint(130);
    rq.delRange(80,150);
    contains = rq.queryPoint(130);
    rq.delRange(0,1500);
#endif
    return 0;
}