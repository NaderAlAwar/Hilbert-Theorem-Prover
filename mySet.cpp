#include "mySet.h"
#include <iterator>

using namespace std;

mySet::mySet(int numberOfTheorems)
{
    limit = numberOfTheorems;
    limitExists = true;
}

mySet::mySet()
{
    limitExists = false;
}

void mySet::push(formula *newFormula)
{
    if(limitExists)
    {
        if(contents.size() >= limit)
        {
            return;
        }
    }
    vector<formula*>::iterator it;
    for(it = contents.begin(); it != contents.end(); it++)
    {
        if((*it)->isEqual(newFormula))
        {
            return;
        }
    }
    contents.push_back(newFormula);
}

int mySet::getSize()
{
    return contents.size();
}

formula* mySet::at(int index)
{
    return contents.at(index);
}