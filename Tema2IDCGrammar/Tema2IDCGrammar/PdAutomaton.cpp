#include "PdAutomaton.h"

void PdAutomaton::ReadAutomaton()
{
	std::ifstream file("Automat.txt");
	if (file.is_open()) {
		int n;
		file >> n;
		for (int i = 0; i < n; i++) {
			int state;
			file >> state;
			stari.insert(state);
		}

		file >> n;
		for (int i = 0; i < n; i++) {
			char input;
			file >> input;
			alfabet.insert(input);
		}

		file >> n;
		for (int i = 0; i < n; i++) {
			char stackChar;
			file >> stackChar;
			stari_finale.insert(stackChar);
		}

		file >> stare_initiala >> primul_element_stiva;

		int m;
		file >> m;
		for (int i = 0; i < m; i++) {
			int state;
			char input;
			int stackChar;
			std::string stackString;
			file >> state >> input >> stackChar >> stackString;
			tranziti[{state, input}] = { stackChar, stackString };
		}
		file.close();
	}
	else {
		std::cout << "Unable to open file";
	}
}

void PdAutomaton::PrintAutomaton()
{
	std::cout << "Multimea starilor este Q={ ";
	for (auto it = stari.begin(); it != stari.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << "}\n";

	std::cout << "Multimea alfabetului este Sigma={ ";
	for (auto it = alfabet.begin(); it != alfabet.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << "}\n";

	std::cout << "Multimea starilor finale este F={ ";
	for (auto it = stari_finale.begin(); it != stari_finale.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << "}\n";

	std::cout << "Starea initiala este q0=" << stare_initiala << "\n";
	
	std::cout << "Primul element din stiva este:" << primul_element_stiva << "\n";

	std::cout << "Multimea tranzitiilor este Delta={ ";
	for (auto it = tranziti.begin(); it != tranziti.end(); it++)
	{
		std::cout << "(" << it->first.first << "," << it->first.second << ")={(";
		std::cout << it->second.first << "," << it->second.second << ")} ";
	}
	std::cout << "}\n";

}

bool PdAutomaton::CheckWord(std::string word)
{
	int stare = stare_initiala;
	std::stack<char> stiva;
	stiva.push(primul_element_stiva);
	for (int i = 0; i <= word.size(); i++) {
		char caracter = word[i];
		if (alfabet.find(caracter) == alfabet.end()) {
			return false;
		}
		
		char top_stiva = stiva.top();
		std::pair<int, char> tranzitie = { stare,caracter };
		if (tranziti.find(tranzitie) == tranziti.end()) {
			return false;
		}

		std::pair<int, std::string> rezultat_tranzitie = tranziti[tranzitie];
		stare = rezultat_tranzitie.first;
		std::string rezultat_string = rezultat_tranzitie.second;
		for (int j = 0; j < rezultat_string.size(); j++) {
			stiva.push(rezultat_string[j]);
		}
	}
	
	return stiva.top() == primul_element_stiva && stari_finale.find(stare) != stari_finale.end();
}

bool PdAutomaton::IsDeterministic()
{
	for (auto indexs : stari) {
		for (auto indexa : alfabet) {
			std::pair<int, char> tranzitie = { indexs, indexa };
			if (tranziti.count(tranzitie) > 1)
				return false;
		}
	}
	return true;
}
