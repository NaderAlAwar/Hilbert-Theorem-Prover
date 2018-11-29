#include <iostream>
#include <iterator>
#include "prover.h"
#include "formula.h"
#include "implOp.h"
#include "notOp.h"
#include "variable.h"
#include "mySet.h"

using namespace std;

prover::prover(int vars, int theorems)
{
    numberOfVariables = vars;
    numberOfTheorems = theorems;
    myVariables = new variable*[numberOfVariables];
    provedFormulas = mySet(numberOfTheorems);
    expressions = mySet();
    char v = 97;
    for(int i = 0; i < numberOfVariables; i++)
    {
        myVariables[i] = new variable(v++);
    }
    hilbertPS();
    boundExists = false;
    for(int i = 0; i < axiomSize; i++)  // add the axioms to the list of proved formulas
    {
        provedFormulas.push(axioms[i]);
    }
}

prover::prover(int vars, int theorems, int newBound) : prover::prover(vars, theorems)
{
    if(newBound > 0)
    {
        bound = newBound;
        boundExists = true;
    }
}

void prover::hilbertPS()
{
    axiomSize = 3;
    variableSize = 3;

    axioms = new formula*[3];
    variable *a = new variable('a');
    variable *b = new variable('b');
    variable *c = new variable('c');
    axiomVariables = new variable*[variableSize];
    axiomVariables[0] = a;
    axiomVariables[1] = b;
    axiomVariables[2] = c;

    implOp *ba = new implOp(b,a);   // q->p
    implOp *ax1 = new implOp(a,ba);  // p->(q->p)
    axioms[0] = ax1;  // axiom 1
    
    implOp *bc = new implOp(b,c);    // q->r
    implOp *abc = new implOp(a,bc);  // p->(q->r)
    implOp *ab = new implOp(a,b);    // p->q
    implOp *ac = new implOp(a,c);    // p->r
    implOp *abac = new implOp(ab,ac);    // (p->q)->(p->r)
    implOp *ax2 = new implOp(abc,abac);  // p->(q->r)->((p->q)->(p->r))
    axioms[1] = ax2;    // axiom 2

    notOp *nota = new notOp(a);  // !p
    notOp *notb = new notOp(b);  // !q
    implOp *notanotb = new implOp(nota,notb);    // !p->!q
    implOp *ax3 = new implOp(notanotb,ba);   // (!p->!q)->(q->p)
    axioms[2] = ax3;    // axiom 3
}

void prover::printAxioms()
{
    for(int i = 0; i < axiomSize; i++)
    {
        cout << "Axiom " << i+1 << ":" << endl;
        axioms[i]->print();
        cout << endl;
    }  
}

bool prover::modusPonens(formula *premise, formula *currentFormula) // returns true if MP was applied successfully and false otherwise
{
    implOp* checkCurrent = dynamic_cast<implOp*> (currentFormula);    // attempt to cast operand to a variable
    if(checkCurrent == NULL)
    {
        return false;
    }
    else
    {
        if(checkCurrent->getLeftOperand()->isEqual(premise))    // if the lhs of the current formula is the same as the premise
        {
            provedFormulas.push(checkCurrent->getRightOperand());  // the rhs is added to thr list of proved formulas
            return true;
        }
        else
        {
            return false;
        }
    }
}

void prover::addFormula(formula *newFormula)    // adds newFormula only if it is not NULL or if it not NULL and below the bound
{
    if(newFormula != NULL)
    {
        if(!boundExists)
        {
            provedFormulas.push(newFormula);
        }
        else
        {
            if(newFormula->getSize() <= bound)
            {
                provedFormulas.push(newFormula);
            }
        }
    }
}

void prover::prove()
{
    int myIterator = 0; // iterates over provedFormulas
    formula *newFormula = NULL;
    int previousSize = 0;
    int currentSize = provedFormulas.getSize();

    while(provedFormulas.getSize() < numberOfTheorems)  // apply string substitutions and modus ponens
    {
        for(int myIterator = 0; myIterator < currentSize; myIterator++){  
            for(int i = 0; i < numberOfVariables; i++)  // substitute variables with other variables and other formulas
            {
                for(int j = 0; j < numberOfVariables; j++)
                {
                    newFormula = provedFormulas.at(myIterator)->instantiateFormula(myVariables[i],myVariables[j]);
                    addFormula(newFormula);
                    newFormula = provedFormulas.at(myIterator)->instantiateFormula(myVariables[i],new notOp(myVariables[j])); // substitute variables with negations of variables
                    addFormula(newFormula);
                }
                for(int k = 0; k < currentSize; k++)
                {
                    newFormula = provedFormulas.at(myIterator)->instantiateFormula(myVariables[i],provedFormulas.at(k));    // substitute variables with already proved formulas  
                    addFormula(newFormula);
                    newFormula = provedFormulas.at(myIterator)->instantiateFormula(myVariables[i],new notOp(provedFormulas.at(k))); // subtitute variables with negations of proved formulas
                    addFormula(newFormula);        
                }
            }
        }

        for(int i = 0; i < currentSize; i++)   // applying modus ponens
        {
            for(int j = 0; j < currentSize; j++)
            {
                modusPonens(provedFormulas.at(i),provedFormulas.at(j));  // if MP returns true, it adds the new formula internally. no need to check bound
            }
        }

        previousSize = currentSize;
        currentSize = provedFormulas.getSize();
        if(previousSize == currentSize) // if no more theorems can be generated
        {
            break;
        }
    }
}

void prover::printProvedFormulas()
{
    for(int i = 0; i < provedFormulas.getSize(); i++)
    {
        provedFormulas.at(i)->print();
        cout << endl;
    }
    cout << "Generated " << provedFormulas.getSize() << " formulas" << endl;
}

void prover::formExpressions()  // this will not terminate unless a bound is specified
{
    int previousSize = 0;
    int currentSize = numberOfVariables;
    for(int i = 0; i < numberOfVariables; i++)
    {
        expressions.push(myVariables[i]);
    }
    while(previousSize < currentSize)
    {
        formula *newFormula;
        for(int i = 0; i < currentSize; i++)    // iterate over all current expressions
        {
            for(int j = 0; j < currentSize; j++)
            {
                newFormula = new implOp(expressions.at(i), expressions.at(j));  // add ex1->ex2
                if(newFormula->getOpSize() <= bound)
                {
                        expressions.push(newFormula);
                }
                else
                {
                    if(!boundExists)
                    {
                        expressions.push(newFormula);
                    }
                }
            }
            newFormula = new notOp(expressions.at(i));  // add !ex1
            if(newFormula->getOpSize() <= bound)
            {
                    expressions.push(newFormula);
            }
            else
            {
                if(!boundExists)
                {
                    expressions.push(newFormula);
                }
            }
        }
        previousSize = currentSize;
        currentSize = expressions.getSize();
    }
}

void prover::printExpressions()
{
    for(int i = 0; i < expressions.getSize(); i++)
    {
        expressions.at(i)->print();
        cout << endl;
    }
    cout << "Formed " << expressions.getSize() << " expressions";
}

void prover::proveTheorems()
{
    int previousSize = 0;
    int currentSize = axiomSize;    // the axioms were added in the constructor to the list of proved formulas
    formula *newFormula;
    while(provedFormulas.getSize() < numberOfTheorems)
    {
        for(int i = 0; i < expressions.getSize(); i++)
        {
            for(int j = 0; j < currentSize; j++)
            {
                for(int k = 0; k < numberOfVariables; k++)
                {
                    newFormula = provedFormulas.at(j)->instantiateFormula(myVariables[k], expressions.at(i));
                    if(newFormula != NULL)
                    {
                        provedFormulas.push(newFormula);
                    }                    
                }
            }
        }
        for(int i = 0; i < currentSize; i++)    // for every theorem proved so far
        {
            for(int j = 0; j < currentSize; j++)
            {
                modusPonens(provedFormulas.at(i),provedFormulas.at(j));  // if MP returns true, it adds the new formula internally
            }
        }
        previousSize = currentSize;
        currentSize = expressions.getSize();
    }
}