#include "Automaton.h"
#include<fstream>
#include<queue>
bool Automaton::VerifyAutomaton()
{
	for (int i = 0; i < transitions.size(); i++) {
		if (states.find(std::get<0>(transitions[i])) == std::string::npos) {
			return false;
		}
		if (alphabet.find(std::get<1>(transitions[i])) == std::string::npos) {
			return false;
		}
		if (states.find(std::get<2>(transitions[i])) == std::string::npos) {
			return false;
		}
	}
	return true;
}

bool Automaton::CheckWord(std::string word)
{
	std::string stare_actuala = initial_state;
	std::string cuvant_actual = word;
	std::queue<std::tuple<std::string, std::string>> tranzitii_bune;
	for (int j = 0; j < transitions.size(); j++)
	{
		if (stare_actuala == std::get<0>(transitions[j]) && cuvant_actual[0] == std::get<1>(transitions[j])[0])
		{
			tranzitii_bune.push(std::make_tuple(cuvant_actual.substr(1), std::get<2>(transitions[j])));
		}
	}
	if (tranzitii_bune.size() == 0)
		return false;
	cuvant_actual = std::get<0>(tranzitii_bune.front());
	stare_actuala = std::get<1>(tranzitii_bune.front());
	while (cuvant_actual != "")
	{
		for (int j = 0; j < transitions.size(); j++)
		{
			if (stare_actuala == std::get<0>(transitions[j]) && cuvant_actual[0] == std::get<1>(transitions[j])[0])
			{
				tranzitii_bune.push(std::make_tuple(cuvant_actual.substr(1), std::get<2>(transitions[j])));
			}
		}
		tranzitii_bune.pop();
		if (tranzitii_bune.size() == 0)
			return false;
		cuvant_actual = std::get<0>(tranzitii_bune.front());
		stare_actuala = std::get<1>(tranzitii_bune.front());
	}
	while (tranzitii_bune.size() > 0)
	{
		if (final_state.find(std::get<1>(tranzitii_bune.front())) != std::string::npos)
			return true;
		tranzitii_bune.pop();
	}
	return false;
}
void Automaton::ReadAutomaton()
{
	std::ifstream f("automaton.txt");
	f >> states >> alphabet >> initial_state >> final_state;
	std::string e1, e2, e3;
	while (!f.eof()) {
		f >> e1 >> e2 >> e3;
		transitions.push_back(std::make_tuple(e1, e2, e3));
	}
	f.close();
}

void Automaton::PrintAutomaton()
{
	std::cout << "M = (";
	std::cout << "{";
	for (int i = 0; i < alphabet.size(); i++) {
		std::cout << alphabet[i];
		if (i < alphabet.size() - 1) {
			std::cout << ",";
		}
	}
	std::cout << "}, " << initial_state << ", {";
	for (int i = 0; i < final_state.size(); i += 2) {
		std::cout << final_state[i] << final_state[i + 1];
		if (i < final_state.size() - 2) {
			std::cout << ",";
		}
	}
	std::cout << "})" << std::endl;
	for (int i = 0; i < transitions.size(); i++) {
		std::cout << "(" << std::get<0>(transitions[i])
			<< "," << std::get<1>(transitions[i])
			<< ") = " << std::get<2>(transitions[i]) << std::endl;
	}
	std::cout << std::endl << std::endl;
}

std::vector<std::tuple<std::string, std::string, std::string>> Automaton::UseTransitions(char c, std::string current_state)
{
	std::string word(1, c);
	std::vector<std::tuple<std::string, std::string, std::string>>use_transitions;
	for (auto& index : transitions) {
		if ((std::get<0>(index) == current_state) and (std::get<1>(index) == word)) {
			use_transitions.push_back(index);
		}
	}
	return use_transitions;
}

void Automaton::SetAlphabet(std::string alph)
{
	alphabet = alph;
}

bool Automaton::IsDeterministic()
{
	for (int i = 0; i < transitions.size() - 1; i++)
	{
		for (int j = i + 1; j < transitions.size(); j++)
			if ((std::get<0>(transitions[i]) == std::get<0>(transitions[j])) && (std::get<1>(transitions[i]) == std::get<1>(transitions[j]))) {
				return false;
			}
	}
	return true;
}

int Automaton::TransitionDoesntExist(std::vector<std::tuple<std::string, std::string, std::string>> transition,std::tuple<std::string,std::string,std::string>existent)
{
	for (int i = 0; i < transition.size() ; i++)
	{
		
			if ((std::get<0>(transition[i]) == std::get<0>(existent)) && (std::get<1>(transition[i]) == std::get<1>(existent))) {
				return i;
			}
	}
	return 0;
}

std::string Automaton::GetFinalState()
{
	return final_state;
}


void Automaton::SetStates(std::string sts)
{
	states = sts;
}

void Automaton::SetFinalState(std::string finalSt)
{
	final_state = finalSt;
}

void Automaton::SetTransitions(std::vector<std::tuple<std::string, std::string, std::string>> tranzitii)
{
	transitions.resize(tranzitii.size());
	for (int i = 0; i < transitions.size(); i++)
	{
		std::get<0>(transitions[i]) = std::get<0>(tranzitii[i]);
		std::get<1>(transitions[i]) = std::get<1>(tranzitii[i]);
		std::get<2>(transitions[i]) = std::get<2>(tranzitii[i]);
	}
}

void Automaton::SetInitialState(std::string initialst)
{
	initial_state = initialst;
}
