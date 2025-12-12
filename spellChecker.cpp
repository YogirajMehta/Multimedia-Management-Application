#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include "spellChecker.h"

using namespace std;

namespace seneca
{
    SpellChecker::SpellChecker(const char* filename)
    {
        std::ifstream file(filename);
        if (!file.is_open())
        {
            throw "Bad file name!";
        }

        for (size_t i = 0; i < WORD_COUNT; ++i)
        {
            file >> m_badWords[i] >> m_goodWords[i];

            if (file.fail())
            {
                break;
            }
        }
    }

    void SpellChecker::operator()(std::string& text)
    {
        for (size_t i = 0; i < WORD_COUNT; ++i)
        {
            size_t pos = 0;
            while ((pos = text.find(m_badWords[i], pos)) != std::string::npos)
            {
                text.replace(pos, m_badWords[i].length(), m_goodWords[i]);
                m_replacementCounts[i]++;
                pos += m_goodWords[i].length();
            }
        }
    }

    void SpellChecker::showStatistics(std::ostream& out) const
    {
        out << "Spellchecker Statistics\n";
        for (size_t i = 0; i < WORD_COUNT; ++i)
        {
            out << std::left << std::setw(15) << m_badWords[i]
                << ": " << m_replacementCounts[i] << " replacements\n";
        }
    }

}
