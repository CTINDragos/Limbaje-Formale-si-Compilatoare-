#include <iostream>
#include <unordered_set>
#include <set>
#include <vector>
#include <string>
#include <map>
#include <stack>
#include <fstream>

class PdAutomaton
{
public:

	void ReadAutomaton();
	void PrintAutomaton();
	bool CheckWord(std::string word);
	bool IsDeterministic();
	
private:
	std::set<int> stari;
	std::set<char> alfabet;
	std::set<char> stari_finale;
	std::map<std::pair<int, char>, std::pair<int,std::string>> tranziti;
	int stare_initiala;
	char primul_element_stiva;
};

