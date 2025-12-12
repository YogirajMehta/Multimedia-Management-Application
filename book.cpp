#include "book.h"
#include "settings.h"
#include <sstream>

using namespace std;

namespace seneca
{
    Book::Book() : MediaItem("", "", 0), m_author(""), m_country(""), m_price(0.0) {}

    Book::Book(const string& title, const string& summary, unsigned short year,
        const string& author, const string& country, double price)
        : MediaItem(title, summary, year), m_author(author), m_country(country), m_price(price) {
    }

    // Display book details
    void Book::display(ostream& out) const
    {
        if (g_settings.m_tableView)
        {
            out << "B | ";
            out << std::left << std::setfill('.');
            out << std::setw(50) << this->getTitle() << " | ";
            out << std::right << std::setfill(' ');
            out << std::setw(2) << this->m_country << " | ";
            out << std::setw(4) << this->getYear() << " | ";
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
            out << this->getTitle() << " [" << this->getYear() << "] [";
            out << m_author << "] [" << m_country << "] [" << m_price << "]\n";
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

    // Factory method to create a book from a string
     Book* Book::createItem(const std::string& strBook)
    {
        if (strBook.empty() || strBook[0] == '#')
        {
            throw "Not a valid book.";
        }

        std::stringstream ss(strBook);
        std::string token;
        
        std::string author, title, country, strPrice, strYear, summary;

        try
        {
            std::getline(ss, author, ',');
            trim(author);

            std::getline(ss, title, ',');
            trim(title);

            std::getline(ss, country, ',');
            trim(country);

            std::getline(ss, strPrice, ',');
            trim(strPrice);
            double price = std::stod(strPrice);

            std::getline(ss, strYear, ',');
            trim(strYear);

            unsigned short year = static_cast<unsigned short>(std::stoi(strYear));

            std::getline(ss, summary);
            trim(summary);

            return new Book(title, summary, year, author, country, price);
        }
        catch (const std::invalid_argument& e)
        {
            throw "Not a valid book.";
        }
        catch (const std::out_of_range& e)
        {
            throw "Not a valid book.";
        }
        return nullptr;
    }

}
