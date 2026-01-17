#include <iostream>
#include "LinkData.h"

void LinkData::setDigits(int u, int d, int l, int r)
{
    //u,l,d,r
    digits[0] = u;
    digits[1] = d;
    digits[2] = l;
    digits[3] = r;
}
int LinkData::getDigit(int pos)
{
    return digits[pos];
}
