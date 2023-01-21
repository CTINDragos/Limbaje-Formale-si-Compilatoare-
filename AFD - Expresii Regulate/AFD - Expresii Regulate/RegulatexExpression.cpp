#include "RegulatexExpression.h"
#include"Automaton.h"
bool RegulatexExpression::isValidRegex()
{
    {
        try
        {
            std::regex r(regex);
        }
        catch (const std::regex_error& e)
        {
            return false;
        }
        return true;
    }

}

RegulatexExpression::RegulatexExpression(std::string& s)
{
    this->regex = s;
}
Automaton RegulatexExpression::TransformAutomaton()
{
    std::string TransformWord="";
    std::string  word = regex;
    for (int i = 0; i < regex.size(); i++)
    {
        if (AllCharacters.find(word[i]) == AllCharacters.end())
            AllCharacters.insert(word[i]);
    }
    std::string alphabet;
    for (auto i : AllCharacters)
    {
        if (isalpha(i))
        {
            alphabet.push_back(i);
       
        }
    }
    for (int i = 0; i < word.size(); i++)
    {
        if (word[i] == '(')
        {
            if (word[i + 1] == ')')
            {
                if (word[i + 2] == '*')
                {
                    word.erase(i, i + 2); i--;
                }
                else {
                    word.erase(i, i + 1); i--;
                }
            }
            else {
                int copyiterator = i + 1;
                while (word[copyiterator] != ')')
                {
                    copyiterator++;
                }
                
                    if (word[copyiterator + 1] != '*') {
                        word.erase(word.begin() + i, word.begin() + i + 1);
                        word.erase(word.begin() + copyiterator - 1, word.begin() + copyiterator); i - 2;
                    }
                
            }
           
        }
    }

    std::vector<std::tuple<std::string, std::string, std::string>>tranzitii;
    int iterator = 0;
    int nbStates = 0;
    Automaton automaton;
    int afterJumpOnRepeted = 0;
    while (iterator < word.size())
    {
        if (isalpha(word[iterator]))
        {
            std::string q = "q";
            char c = nbStates + '0';
            q.push_back(c);
            c = word[iterator];
            nbStates++;
            std::string q1;
            q1.push_back(c);
            std::string q2 = "q";
            c = nbStates + '0'+afterJumpOnRepeted;
            q2.push_back(c);
            if (automaton.TransitionDoesntExist(tranzitii, std::make_tuple(q, q1, q2)) == 0)
            {
                tranzitii.push_back(std::make_tuple(q, q1, q2));
                nbStates = nbStates + afterJumpOnRepeted;
                afterJumpOnRepeted = 0;
            }
            else {
                automaton.SetFinalState(std::get<2>(tranzitii[automaton.TransitionDoesntExist(tranzitii, std::make_tuple(q, q1, q2))]));
            }
        }
        if (word[iterator] == '(')
        {
            int copyiterator = iterator + 1;
            while (word[copyiterator] != ')')
                copyiterator++;
            iterator++;
            std::string qpararel = std::get<2>(tranzitii[tranzitii.size() - 1]);
            if (qpararel =="") qpararel = "q0";
            int nbreturned = nbStates;
            while (iterator < copyiterator-1)
            {
                std::string q = "q";
                char c = nbStates + '0';
                q.push_back(c);
                c = word[iterator];
                nbStates++;
                std::string q1;
                q1.push_back(c);
                std::string q2 = "q";
                c = nbStates + '0';
                q2.push_back(c);
                tranzitii.push_back(std::make_tuple(q, q1, q2));
                iterator++;
            }
            std::string q = "q";
            char c = nbStates + '0';
            q.push_back(c);
            c = word[nbStates+1];
            std::string q1;
            q1.push_back(c);
            tranzitii.push_back(std::make_tuple(q, q1, qpararel));
            afterJumpOnRepeted = nbStates - nbreturned;
            nbStates = nbreturned;
        }

            
        
        iterator++;
    }
   
    automaton.SetTransitions(tranzitii);
    automaton.SetAlphabet(alphabet);
    if (automaton.GetFinalState() == "") automaton.SetFinalState(std::get<2>(tranzitii[tranzitii.size() - 1]));
    automaton.SetInitialState("q0");
    automaton.SetStates("");
    int max = 0;
    for (int i = 0; i < tranzitii.size(); i++)
    {

    }
    return automaton;
}

void RegulatexExpression::PrintRegex()
{
    for (int i = 0; i < regex.size(); i++)
        std::cout << regex[i] << " ";
    std::cout << std::endl;
}

