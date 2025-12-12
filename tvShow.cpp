#include <iomanip>
#include <algorithm>
#include <numeric>
#include "tvShow.h"
#include "settings.h"

using namespace std;

namespace seneca
{
    TvShow::TvShow() : MediaItem("", "", 0), m_id("") {}

    TvShow::TvShow(const string& id, const string& title, unsigned short year, const string& summary)
        : MediaItem(title, summary, year), m_id(id) {
    }

    void TvShow::display(std::ostream& out) const
    {
        if (g_settings.m_tableView)
        {
            out << "S | ";
            out << std::left << std::setfill('.');
            out << std::setw(50) << this->getTitle() << " | ";
            out << std::right << std::setfill(' ');
            out << std::setw(2) << this->m_episodes.size() << " | ";
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
            out << this->getTitle() << " [" << this->getYear() << "]\n";
            out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << "" << '\n';
            while (pos < this->getSummary().size())
            {
                out << "    " << this->getSummary().substr(pos, g_settings.m_maxSummaryWidth) << '\n';
                pos += g_settings.m_maxSummaryWidth;
            }
            for (auto& item : m_episodes)
            {
                out << std::setfill('0') << std::right;
                out << "    " << 'S' << std::setw(2) << item.m_season
                    << 'E' << std::setw(2) << item.m_numberInSeason << ' ';
                if (item.m_title != "")
                    out << item.m_title << '\n';
                else
                    out << "Episode " << item.m_numberOverall << '\n';

                pos = 0;
                while (pos < item.m_summary.size())
                {
                    out << "            " << item.m_summary.substr(pos, g_settings.m_maxSummaryWidth - 8) << '\n';
                    pos += g_settings.m_maxSummaryWidth - 8;
                }
            }
            out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << ""
                << std::setfill(' ') << '\n';
        }
    }
    TvShow* TvShow::createItem(const std::string& strShow)
    {
        std::string line = strShow;
        MediaItem::trim(line);
        if (line.empty() || line[0] == '#')
        {
            throw "Not a valid show.";
        }

        std::stringstream ss(line);
        std::string id, title, strYear, summary, token;

        std::getline(ss, id, ',');
        MediaItem::trim(id);

        std::getline(ss, title, ',');
        MediaItem::trim(title);

        std::getline(ss, strYear, ',');
        MediaItem::trim(strYear);

        std::getline(ss, summary);
        MediaItem::trim(summary);

        unsigned short year = static_cast<unsigned short>(std::stoi(strYear));

        return new TvShow(id, title, year, summary);
    }

    double TvShow::getEpisodeAverageLength() const
    {
        if (m_episodes.empty())
        {
            return 0.0;
        }

        double totalLength = std::accumulate(m_episodes.begin(), m_episodes.end(), 0.0,
            [](double sum, const TvEpisode& ep) {
                return sum + ep.m_length;
            });

        return totalLength / m_episodes.size();
    }

    std::list<std::string> TvShow::getLongEpisodes() const
    {
        std::list<std::string> longEpisodes;

        std::transform(m_episodes.begin(), m_episodes.end(), std::back_inserter(longEpisodes),
            [](const TvEpisode& ep) {
                return (ep.m_length >= 3600) ? ep.m_title : "";
            });

        longEpisodes.remove("");
        return longEpisodes;
    }

    unsigned int TvShow::calculateSeconds(std::string strTime)
    {
        std::replace(strTime.begin(), strTime.end(), ':', ' ');
        std::stringstream ss(strTime);
        unsigned int hours = 0, minutes = 0, seconds = 0;
        ss >> hours >> minutes >> seconds;
        return hours * 3600 + minutes * 60 + seconds;
    }

}
