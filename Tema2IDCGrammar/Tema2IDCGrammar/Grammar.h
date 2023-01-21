#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <random>


#include "Rules.h"

class Grammar
{
public:
	Grammar();

	void ReadGrammar(Grammar& G);
	void PrintGrammar();

	bool VerifyGrammar();
	
	bool isIDC();
	
	void SimplifyGrammar();
	void TransformInFNG();

	std::vector<std::string>GetVn();
	std::vector<std::string>GetVt();
	std::vector<Rules>GetP();
	char GetS();

	std::string GenerateWord(int words);

	
	

	std::vector<Rules>Solutions(const std::string& word);
	void WordSeparator(const std::string& word, std::vector<std::string>& words);
	bool CheckProductionChar(const std::string& Product, const std::vector<std::string>& VnSiVt);

private:
	std::vector<std::string>m_Vn;
	std::vector<std::string>m_Vt;
	char m_S;
	std::vector<Rules>m_P;

};