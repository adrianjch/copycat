#pragma once
#include <map>
#include <string>
#include <vector>

typedef std::map<std::string, int> WordList;
typedef std::map<std::string, WordList> Chain;

class MarkovChain
{
public:
	MarkovChain();
	void IncreaseWordCount(WordList& list, const std::string& word);
	std::string GenerateSentence();
	std::string GetRandomWord(WordList list);
private:
	Chain chain;
};