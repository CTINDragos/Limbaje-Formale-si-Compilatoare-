#include "Grammar.h"
#include "PdAutomaton.h"

void Meniu(Grammar G, PdAutomaton M) {
	int option;
	std::string cuvant;
	std::cout << "0. Stop program" << "\n";
	std::cout << "1. afisarea gramaticii G:" << "\n";
	std::cout << "2. generarea unui numar de cuvinte din G:" << "\n";
	std::cout << "3. afisarea gramaticii simplificate" << "\n";
	std::cout << "4. afisarea gramaticii in FNG" << "\n";
	std::cout << "5. generare cuvant in G + verifica daca e acceptat de catre automat:" << "\n";
	std::cout << "6. verifica daca un cuvant este acceptat de automaton:" << "\n";
	std::cout << "7. afisarea automatului M generat din G:" << "\n";

	std::cout << "\n" << "Introduceti optiune:";
	std::cin >> option;

	switch (option != 0)
	{
	case 0:
		break;
	case 1:
		G.PrintGrammar();
		std::cout << "\n" << "Introduceti optiune:";
		std::cin >> option;
	case 2:
		int nr;
		std::cout << "Introduceti numarul de cuvinte pe care doriti sa il generati: ";
		std::cin >> nr;
		G.GenerateWord(nr);
		std::cout << "\n" << "Introduceti optiune:";
		std::cin >> option;
	case 3:
		G.SimplifyGrammar();
		G.PrintGrammar();
		std::cout << "\n" << "Introduceti optiune:";
		std::cin >> option;
	case 4:
		G.TransformInFNG();
		G.PrintGrammar();
		std::cout << "\n" << "Introduceti optiune:";
		std::cin >> option;
	case 5:
		if (M.CheckWord(G.GenerateWord(1))) {
			std::cout << " Cuvantul este accept de autonom" << "\n";
		}
		else {
			std::cout << " Cuvantul nu este accept de autonom" << "\n";
		}
		std::cout << "\n" << "Introduceti optiune:";
		std::cin >> option;
	case 6:
		std::cin >> cuvant;
		if (M.CheckWord(cuvant)) {
			std::cout << "Cuvantul este acceptat de automat" << "\n";
		}
		else {
			std::cout << "Cuvantul nu este acceptat de automat" << "\n";
		}
		std::cout << "\n" << "Introduceti optiune:";
		std::cin >> option;
	case 7:
		M.PrintAutomaton();
		std::cout << "\n" << "Introduceti optiune:";
		std::cin >> option;
	}
}

int main() {
	Grammar G;
	PdAutomaton M;
	G.ReadGrammar(G);
	M.ReadAutomaton(); 
		Meniu(G, M);
	
}