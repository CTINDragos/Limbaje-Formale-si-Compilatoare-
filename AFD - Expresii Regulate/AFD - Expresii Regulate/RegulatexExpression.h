#pragma once
#include<string>
#include<regex>
#include<unordered_set>	
#include"Automaton.h"
class RegulatexExpression
{private:
	std::string regex="";
	std::unordered_set<char> AllCharacters;

public:
	bool isValidRegex();
	RegulatexExpression(std::string& s);
	Automaton TransformAutomaton();
	void PrintRegex();

};

