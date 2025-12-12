#ifndef SENECA_SPELLCHECKER_H
#define SENECA_SPELLCHECKER_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdexcept>

namespace seneca
{
    class SpellChecker
    {
        static const size_t WORD_COUNT = 6;

        std::string m_badWords[WORD_COUNT];
        std::string m_goodWords[WORD_COUNT];

        size_t m_replacementCounts[WORD_COUNT]{};

    public:
        SpellChecker(const char* filename);
        void operator()(std::string& text);
        void showStatistics(std::ostream& out) const;
    };
}


#endif 
