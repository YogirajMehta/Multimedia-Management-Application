/*
Name-Yogiraj Mehta
email-ymehta4@myseneca.ca
id-162867238
date-12-11-2025
I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
*/
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