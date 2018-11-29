#ifndef PROVER_H
#define PROVER_H

#include "variable.h"
#include "mySet.h"
class prover
{
    private:
        int numberOfVariables;
        int numberOfTheorems;
        int numberOfAxiomVariables;
        variable **myVariables;
        variable **axiomVariables;
        formula **axioms;
        int axiomSize;
        int variableSize;
        mySet provedFormulas;
        int bound;
        bool boundExists;
        void addFormula(formula *newFormula);
        void instantiateFromAxioms();
        mySet expressions;

    public:
        prover(int vars, int theorems);
        prover(int vars, int theorems, int bound);
        void hilbertPS();
        void printAxioms();
        bool modusPonens(formula *premise, formula *currentFormula);
        void prove();
        void printProvedFormulas();
        void formExpressions();
        void printExpressions();
        void proveTheorems();
};

#endif