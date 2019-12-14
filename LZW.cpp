#include "LZW.h"

namespace glob {
	Code out = numeric_limits<Code>::max();
}

vector<char> RebuildString(vector<pair<Code, char>>& dictionary, Code k)
{
	std::vector<char> s; // String

	while (k != glob::out)
	{
		s.push_back(dictionary.at(k).second);
		k = dictionary.at(k).first;
	}

	std::reverse(s.begin(), s.end());
	return s;
}

void ResetDecodeDictionary(vector<pair<Code, char>>& dictionary)
{
	dictionary.clear();
	dictionary.reserve(glob::out);

	const long int minc = std::numeric_limits<char>::min();
	const long int maxc = std::numeric_limits<char>::max();

	for (long int c = minc; c <= maxc; ++c)
		dictionary.push_back({glob::out, static_cast<char> (c) });
}

void ResetEncodeDictionary(map<pair<Code, char>, Code> &dictionary)
{
	dictionary.clear();

	const long int minc = std::numeric_limits<char>::min();
	const long int maxc = std::numeric_limits<char>::max();

	for (long int c = minc; c <= maxc; ++c)
	{
		const Code dictionary_size = dictionary.size();

		dictionary[{glob::out, static_cast<char> (c)}] = dictionary_size;
	}
}

void LZWEncoder(istream& input, ostream& output)
{
	map<pair<Code, char>, Code> dictionary;

	ResetEncodeDictionary(dictionary);

	char c;
	Code i = glob::out;

	while (input.get(c))
	{
		if (dictionary.size() == glob::out)
			ResetEncodeDictionary(dictionary);

		if (dictionary.count({ i, c }) == 0)
		{
			const Code dictionary_size = dictionary.size();

			dictionary[{i, c}] = dictionary_size;
			output.write(reinterpret_cast<const char*> (&i), sizeof(Code));
			i = dictionary.at({glob::out, c});
		}
		else
			i = dictionary.at({ i, c });
	}

	if (i != glob::out)
		output.write(reinterpret_cast<const char*> (&i), sizeof(Code));
}

void LZWDecoder(istream& input, ostream& output)
{
	vector<pair<Code, char>> dictionary;

	ResetDecodeDictionary(dictionary);

	Code i = glob::out;
	Code k;

	while (input.read(reinterpret_cast<char*> (&k), sizeof(Code)))
	{
		// dictionary's maximum size was reached
		if (dictionary.size() == glob::out)
			ResetDecodeDictionary(dictionary);

		if (k > dictionary.size())
			throw std::runtime_error("invalid compressed code");

		vector<char> s; // String

		if (k == dictionary.size())
		{
			dictionary.push_back({ i, RebuildString(dictionary, i).front() });
			s = RebuildString(dictionary, k);
		}
		else
		{
			s = RebuildString(dictionary, k);

			if (i != glob::out)
				dictionary.push_back({ i, s.front() });
		}

		output.write(&s.front(), s.size());
		i = k;
	}

	if (!input.eof() || input.gcount() != 0)
		throw std::runtime_error("corrupted compressed file");
}