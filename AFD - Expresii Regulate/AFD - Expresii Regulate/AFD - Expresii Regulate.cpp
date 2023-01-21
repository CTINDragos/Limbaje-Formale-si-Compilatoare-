
#include <iostream>
#include<regex>
#include<fstream>
#include"RegulatexExpression.h"
int main()
{
	std::ifstream f("tx.txt");
	std::string text;
	f >> text;
	f.close();
	RegulatexExpression* re = new RegulatexExpression(text);
	if (re->isValidRegex() == false) { std::cout << "Expresia regulata nu este valida"; }
	else {
		re->TransformAutomaton();
		Automaton a = re->TransformAutomaton(); 
		std::cout << "Pentru afisarea automatului M apasati tasta 1"<<std::endl;
		std::cout << "Pentru afisarea inteligibila a expresiei regulate r din fisier apasati tasta 2" << std::endl;
		std::cout << "Pentru verificarea unui cuvant in automat apasati tasta 3 " << std::endl;
		char x;
		std::cin >> x;
		switch (x)
		{
		case ('1'): {
			a.PrintAutomaton();
		}break;
		case('2'):
		{	re->PrintRegex();
		}break;
		case('3'):
		{std::cout << "Dati cuvantul:";
		std::string cuvant;
		std::cin >> cuvant;
		std::cout << "  ";
		if (a.CheckWord(cuvant) == true) std::cout << "Cuvant acceptat" << std::endl;
		else std::cout << "Cuvant neacceptat";
		}break;
		default:std::cout << "Closed"<<std::endl;
			break;
		}
	}
}
