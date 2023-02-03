#include "MarkovChain.h"

#include <ctime>
#include <fstream>
#include <regex>
#include <sstream>

MarkovChain::MarkovChain()
{
	srand(time(nullptr));
	
	std::ifstream file("chat.txt");
	std::string line;
	while (std::getline(file, line))
	{
		std::smatch matches;
		std::regex regex(R"(\d{2}\/\d{2}\/\d{4}, \d{2}:\d{2} - (.*): (.*))");
		if (std::regex_search(line, matches, regex))
		{
			std::string user = matches[1].str(); //TODO
			std::string message = matches[2].str();
			if (message.empty() || message == "<Media omitted>" || message == "null")
			{
				continue;
			}
			// Word to lowercase
			std::transform(message.begin(), message.end(), message.begin(), ::tolower);

			std::istringstream iss(message);
			std::string previousWord, currentWord;
			while (iss >> currentWord)
			{
				IncreaseWordCount(chain[previousWord], currentWord);
				previousWord = currentWord;
			}
			IncreaseWordCount(chain[previousWord], "");
		}
	}
}

void MarkovChain::IncreaseWordCount(WordList& list, const std::string& word)
{
	// If next word already exists, increase counter by 1
	auto it = list.find(word);
	if (it != list.end())
	{
		it->second++;
	}
	// If next word is not registered yet, set counter to 1
	else
	{
		list[word] = 1;
	}
}

std::string MarkovChain::GenerateSentence()
{
	std::string sentence;
	std::string currentWord;
	while (true)
	{
		currentWord = GetRandomWord(chain[currentWord]);
		if (currentWord.empty())
		{
			break;
		}
		sentence += " " + currentWord;
	}
	return sentence;
}

std::string MarkovChain::GetRandomWord(WordList list)
{
	std::vector<std::string> words;
	for (auto it = list.begin(); it != list.end(); ++it)
	{
		// Ignore words that only have 1 match (typos, random letters, etc)
		if (it->second > 1)
		{
			words.push_back(it->first);
		}
	}

	if (words.empty())
	{
		return "";
	}
	return words[rand() % words.size()];
}
