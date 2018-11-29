#include <iostream>
#include "formula.h"
#include "variable.h"

using namespace std;

variable::variable(char variable)
{
    var = variable;
}

void variable::print()
{
    cout << var;
}

char variable::getVariable()
{
    return var;
}

bool variable::isEqual(formula *otherFormula)
{
    variable* newFormula = dynamic_cast<variable *> (otherFormula);
    if(newFormula != NULL)  // if the dynamic cast works
    {
        if(newFormula->getVariable() == getVariable())
        {
            return true;
        }  
    }
    return false;
}

formula* variable::substituteFormula(formula *from, formula *to)
{
    if(this->isEqual(from))
    {
        return to;
    }
    return NULL;
}

formula* variable::instantiateFormula(variable *toReplace, formula *newFormula)
{
    if(this->isEqual(toReplace))
    {
        return newFormula;
    }
    
    return NULL;
}

formula* variable::instFormula(formula *toReplace, formula *newFormula)
{
    if(this->isEqual(toReplace))
    {
        return newFormula;
    }
    
    return NULL;
}

int variable::getSize()
{
    return 1;
}

int variable::getOpSize()
{
    return 0;
}

bool variable::containsVariable(char variable)
{
    if(var == variable)
    {
        return true;
    }
    return false;
}