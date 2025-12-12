#include "movie.h"
#include "settings.h"
#include <sstream>
#include <iomanip>

using namespace std;

namespace seneca
{
    Movie::Movie() : MediaItem("", "", 0) {}

    Movie::Movie(const string& title, unsigned short year, const string& summary)
        : MediaItem(title, summary, year) {
    }

    void Movie::display(ostream& out) const
    {
        if (g_settings.m_tableView)
        {
            out << "M | ";
            out << std::left << std::setfill('.');
            out << std::setw(50) << this->getTitle() << " | ";
            out << std::right << std::setfill(' ');
            out << std::setw(9) << this->getYear() << " | ";
            out << std::left;
            if (g_settings.m_maxSummaryWidth > -1)
            {
                if (static_cast<short>(this->getSummary().size()) <= g_settings.m_maxSummaryWidth)
                    out << this->getSummary();
                else
                    out << this->getSummary().substr(0, g_settings.m_maxSummaryWidth - 3) << "...";
            }
            else
                out << this->getSummary();
            out << std::endl;
        }
        else
        {
            size_t pos = 0;
            out << this->getTitle() << " [" << this->getYear() << "]\n";
            out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << "" << '\n';
            while (pos < this->getSummary().size())
            {
                out << "    " << this->getSummary().substr(pos, g_settings.m_maxSummaryWidth) << '\n';
                pos += g_settings.m_maxSummaryWidth;
            }
            out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << ""
                << std::setfill(' ') << '\n';
        }
    }

    Movie* Movie::createItem(const string& strMovie)
    {
        if (strMovie.empty() || strMovie[0] == '#')
        {
            throw "Not a valid movie.";
        }

        std::string temp = strMovie;
        size_t pos = 0;

        try
        {
            pos = temp.find(',');
            if (pos == std::string::npos) throw "Not a valid movie.";
            std::string strTitle = temp.substr(0, pos);
            trim(strTitle);
            temp = temp.substr(pos + 1); 
            pos = temp.find(',');
            if (pos == std::string::npos) throw "Not a valid movie.";
            std::string strYear = temp.substr(0, pos);
            trim(strYear); 
            unsigned short year = static_cast<unsigned short>(std::stoi(strYear));
            temp = temp.substr(pos + 1); 
            trim(temp);
            std::string summary = temp;
            if (summary.empty()) throw "Not a valid movie.";
            return new Movie(strTitle, year, summary);
        }
        catch (...) 
        {
            throw "Not a valid movie.";
        }
    }

}
