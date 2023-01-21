#include "Grammar.h"

Grammar::Grammar()
{
	m_Vn.resize(0);
	m_Vt.resize(0);
	m_S = ' ';
	m_P.resize(0);
}

void Grammar::ReadGrammar(Grammar& G)
{
	std::ifstream FileInput("DateDeIntrare.txt");
	if (!FileInput)
	{
		std::cout << "Eroare! Nu s-a putut deschide fisierul ";
		return;
	}
	int numberofrules, Index;

	//Citirea din fisier a neterminalelor
	std::string Vn;
	getline(FileInput, Vn);
	WordSeparator(Vn, m_Vn);

	//Citirea din fisier a terminalelor
	std::string Vt;
	getline(FileInput, Vt);
	WordSeparator(Vt, m_Vt);


	//Citirea din fisier a simbolului de Start
	FileInput >> m_S;

	//Citirea din fisier a regulilor
	Rules rules;
	FileInput >> numberofrules;
	FileInput.get();
	char ConditiaDeOprire = ' ';
	for (Index = 0; Index < numberofrules; Index++)
	{
		getline(FileInput, rules.m_Stanga, ConditiaDeOprire);
		getline(FileInput, rules.m_Dreapta);

		m_P.push_back(rules);
	}
}

void Grammar::PrintGrammar()
{

	int Index;
	std::cout << "G=(Vn,Vt,S,P), unde:\n";

	std::cout << "Multimea Neterminalelor este Vn={ ";
	std::cout << m_Vn[0];
	for (Index = 1; Index < m_Vn.size(); Index++)
		std::cout << " , " << m_Vn[Index];
	std::cout << " }\n";

	std::cout << "Multimea Terminalelor este Vt={ ";
	std::cout << m_Vt[0];
	for (Index = 1; Index < m_Vt.size(); Index++)
		std::cout << " , " << m_Vt[Index];
	std::cout << " }\n";

	std::cout << "Simbolul de start este S = " << m_S << "\n";

	std::cout << "Regulile acestei gramatici sunt \nP=";
	Index = 0;
	for (Index = 0; Index < m_P.size(); Index++) {
		std::cout << "\n" << m_P[Index].m_Stanga << " ---> " << m_P[Index].m_Dreapta;
	}

	std::cout << std::endl;
}

bool Grammar::VerifyGrammar()
{
	//VN  VT = 
	for (auto& index1 : m_Vn) {
		for (auto& index2 : m_Vt) {
			if (index1 == index2)
				return false;
		}

	}
	//S  VN
	uint8_t contor = 0;
	for (auto& index : m_Vn) {
		if (index.find(m_S) != std::string::npos) {
			contor++;
		}
	}
	if (contor == 0) {
		return false;
	}
	//pentru fiecare regulă, membrul stâng conține cel puțin un neterminal
	contor = 0;
	for (auto& index1 : m_P) {
		for (auto& index2 : m_Vn) {
			if (index1.m_Stanga == index2) {
				contor++;
			}
		}
		if (contor == 0) {
			return false;
		}
	}
	// există cel puțin o producție care are în stânga doar S
	contor = 0;
	for (auto& index1 : m_P) {
		if (index1.m_Stanga.find(m_S) != std::string::npos and index1.m_Stanga.size() == 1) {
			contor++;
		}
	}
	if (contor == 0) {
		return false;
	}
	//fiecare producție conține doar elemente din VN și VT
	std::vector<std::string> Chars = m_Vn;
	Chars.insert(Chars.end(), m_Vt.begin(), m_Vt.end());
	for (uint16_t Index = 0; Index < m_P.size(); Index++)
	{
		if (CheckProductionChar(m_P[Index].m_Stanga, Chars) == false || CheckProductionChar(m_P[Index].m_Dreapta, Chars) == false)
		{
			return false;
		}
	}
	return true;
}

bool Grammar::isIDC()
{
	for (auto& index : m_P)
	{
		int nonterminals = 0;
		for (auto c : index.m_Stanga)
		{
			if (isupper(c))
			{
				nonterminals++;
			}
		}
		if (nonterminals != 1) {
			return false;
		}
		
	}
	std::vector<std::string> nonterminals;
	for (auto& index : m_P)
	{
		if (isupper(index.m_Stanga[0])) {
			nonterminals.push_back(index.m_Stanga);
		}
	}

	for (auto& indexn : nonterminals) {
		bool derivate = false;
		for(auto& index : m_P){
			if (index.m_Stanga == indexn) {
				for (int i = 0; i < index.m_Dreapta.size(); i++) {
					if (islower(index.m_Dreapta[i])) {
						derivate = true;
						break;
					}
					
				}
				
			}
		}
		if (derivate) {
			break;
		}
		if (!derivate) {
			return false;
		}
		
	}
	return true;
}

void Grammar::SimplifyGrammar()
{
	int marime = m_P.size();
	int i = 0;
	while (i < marime) {
		//Eliminare productiilor lambda
		if (m_P[i].m_Dreapta == "lambda")
		{
			m_P.erase(m_P.begin() + i);
			marime--;
		}
		//Eliminarea productiilor unitare
		if (m_P[i].m_Dreapta.size() == 1 && isupper(m_P[i].m_Dreapta[0]))
		{
			for (int j = 0; j <= marime; i++)
			{
				if (m_P[i].m_Dreapta == m_P[j].m_Stanga)
				{
					m_P.erase(m_P.begin() + i);
					marime--;
				}
			}
		}
		i++;
	}
	
}

void Grammar::TransformInFNG()
{
	SimplifyGrammar();
	for (auto& indexT : m_Vt) {
		int contor = 0;
		for (auto& indexN : m_Vn) {
			if (toupper(indexT[0]) == indexN[0]) {
				contor++;
			}
		}
			if (contor==0){
				std::string prelucrare = indexT;
				//Adaugarea terminalului in lista 
				prelucrare[0] = toupper(prelucrare[0]);
				m_Vn.push_back(prelucrare);
				//Adaugarea regulei
				Rules regula;
				regula.m_Stanga = prelucrare;
				prelucrare[0] = tolower(prelucrare[0]);
				regula.m_Dreapta = prelucrare;
				m_P.push_back(regula);
			}
	}

	for (auto& index : m_P) {
		if(islower(index.m_Dreapta[0])){
			for (int i = 1; i < index.m_Dreapta.size(); i++) {
				if (islower(index.m_Dreapta[i])) {
					index.m_Dreapta[i] = toupper(index.m_Dreapta[i]);
				}
			}
		}
	}
}



std::vector<std::string> Grammar::GetVn()
{
	return m_Vn;
}

std::vector<std::string> Grammar::GetVt()
{
	return m_Vt;
}

std::vector<Rules> Grammar::GetP()
{
	return m_P;
}

char Grammar::GetS()
{
	return m_S;
}

std::string Grammar::GenerateWord(int words)
{
	srand(time(0));
	std::string word;
	while (words != 0) {
		word = m_S;
		std::vector<Rules> solutions = Solutions(word);
		std::cout << word << " ";
		while (solutions.size() != 0) {
			std::cout << "-->" << " ";
			int random = rand() % solutions.size();
			word.replace(word.find(solutions[random].m_Stanga), solutions[random].m_Stanga.size(), solutions[random].m_Dreapta);
			std::cout << word << " ";
			solutions = Solutions(word);
		}
		words--;
		std::cout << std::endl;
	}
	return word;
}

std::vector<Rules> Grammar::Solutions(const std::string& word)
{
	std::vector<Rules> solutions;
	for (auto& index : m_P) {
		if (word.find(index.m_Stanga) != std::string::npos) {
			solutions.push_back(index);
		}
	}
	return solutions;
}

void Grammar::WordSeparator(const std::string& word, std::vector<std::string>& words)
{
	std::string curentword;

	for (size_t i = 0; i < word.size(); ++i)
	{
		char curentchar = word[i];
		if (curentchar == ' ' && curentword.empty() == 0)
		{
			words.push_back(curentword);
			curentword = "";
		}
		else
			curentword += curentchar;
	}
	words.push_back(curentword);
}

bool Grammar::CheckProductionChar(const std::string& Product, const std::vector<std::string>& Chars)
{
	int Index = 0, Start = -1;
	std::vector<uint16_t> ProductionCharVector;
	ProductionCharVector.assign(Product.size(), 0);
	for (Index = 0; Index < Chars.size(); Index++)
	{
		Start = -1;
		while (std::find(ProductionCharVector.begin(), ProductionCharVector.end(), 0) != ProductionCharVector.end())
		{
			Start = Product.find(Chars[Index], Start + 1);
			if (Start == -1) break;
			else
			{
				for (int Index2 = Start; Index2 < Start + Chars[Index].size(); Index2++)
					ProductionCharVector[Index2] = 1;
			}
		}

	}
	if (std::find(ProductionCharVector.begin(), ProductionCharVector.end(), 0) != ProductionCharVector.end())
		return false;
	else
		return true;
}