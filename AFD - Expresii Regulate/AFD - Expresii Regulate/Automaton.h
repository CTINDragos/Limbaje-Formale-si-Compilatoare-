#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <fstream>
#include <time.h>
class Automaton
{
private:
	std::string states;
	std::string alphabet;
	std::string final_state;
	std::string initial_state;
	std::vector<std::tuple<std::string, std::string, std::string>> transitions;
public:
	bool VerifyAutomaton();
	bool IsDeterministic();
	bool CheckWord(std::string word);
	void ReadAutomaton();
	void PrintAutomaton();
	std::vector<std::tuple<std::string, std::string, std::string>> UseTransitions(char c, std::string current_state);
	void SetAlphabet(std::string alph);
	void SetStates(std::string sts);
	void SetFinalState(std::string finalSt);
	void SetTransitions(std::vector<std::tuple<std::string, std::string, std::string>>tranzitii);
	void SetInitialState(std::string initialst);
	int TransitionDoesntExist(std::vector<std::tuple<std::string, std::string, std::string>> transitions,std::tuple<std::string, std::string, std::string>existent);
	std::string GetFinalState();
};


