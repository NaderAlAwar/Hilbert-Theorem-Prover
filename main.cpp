#include <iostream>
#include "prover.h"
#include "formula.h"
#include "implOp.h"
#include "notOp.h"
#include "variable.h"

using namespace std;

int main()
{
	int numberOfTheorems;
	int numberOfVariables;
	int bound;

	cout << "Enter the number of theorems to prove" << endl;
	cin >> numberOfTheorems;
	cout << "Enter the number of variables (max 7)" << endl;
	cin >> numberOfVariables;
	cout << "Enter a bound for the number of operations in a formula (max 10)" << endl;
	cin >> bound;

	if(numberOfVariables >= 8)
	{
	 	cout << "The number of variables will be set to 7";
		numberOfVariables = 7;
	}

	if(numberOfVariables <= 0)
	{
		cout << "The numer of variables will be set to 1";
		numberOfVariables = 1;
	}

	if(bound >= 10)
	{
	 	cout << "The bound will be set to 10";
		bound = 10;
	}

	if(bound <= 0)
	{
		cout << "The bound will be set to 1";
		bound = 5;
	}

	prover hilbert = prover(numberOfVariables, numberOfTheorems, bound);
	hilbert.formExpressions();
	// hilbert.printExpressions();
	hilbert.proveTheorems();
	hilbert.printProvedFormulas();

}