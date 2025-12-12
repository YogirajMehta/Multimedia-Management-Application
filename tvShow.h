#ifndef SENECA_TVSHOW_H
#define SENECA_TVSHOW_H
#include <sstream>
#include <iomanip>
#include <numeric>
#include <algorithm>
#include <string>
#include <vector>
#include <list>
#include "mediaItem.h"
#include "collection.h"

namespace seneca
{
    class TvShow;
    struct TvEpisode
    {
        const TvShow* m_show{};
        unsigned short m_numberOverall{};
        unsigned short m_season{};
        unsigned short m_numberInSeason{};
        std::string m_airDate{};
        unsigned int m_length{};
        std::string m_title{};
        std::string m_summary{};
    };

    class TvShow : public MediaItem
    {
        std::string m_id;
        std::list<TvEpisode> m_episodes;

        TvShow();
        TvShow(const std::string& id, const std::string& title, unsigned short year, const std::string& summary);

    public:
        virtual ~TvShow() = default;

        void display(std::ostream& out) const override;
        static TvShow* createItem(const std::string& strShow);

        template<typename Collection_t>
        static void addEpisode(Collection_t& col, const std::string& strEpisode);

        double getEpisodeAverageLength() const;
        std::list<std::string> getLongEpisodes() const;

        static unsigned int calculateSeconds(std::string strTime);

        const std::string& getId() const { return m_id; }
    };

    template <typename Collection_t>
    void TvShow::addEpisode(Collection_t& col, const std::string& strEpisode)
    {
        std::string line = strEpisode;
        MediaItem::trim(line);
        if (line.empty() || line[0] == '#')
        {
            throw "Not a valid episode.";
        }

        std::stringstream ss(line);
        std::string token;
        std::string showId;

        std::getline(ss, showId, ',');
        MediaItem::trim(showId);

        TvShow* targetShow = nullptr;
        for (size_t i = 0; i < col.size(); ++i)
        {
            TvShow* show = dynamic_cast<TvShow*>(col[i]);
            if (show && show->getId() == showId)
            {
                targetShow = show;
                break;
            }
        }

        if (targetShow == nullptr)
        {
            throw std::runtime_error("Show ID not found: " + showId);
        }

        TvEpisode episode;
        episode.m_show = targetShow;

        std::getline(ss, token, ',');
        MediaItem::trim(token);
        episode.m_numberOverall = static_cast<unsigned short>(std::stoi(token));

        std::getline(ss, token, ',');
        MediaItem::trim(token);
        episode.m_season = token.empty() ? 1 : static_cast<unsigned short>(std::stoi(token));

        std::getline(ss, token, ',');
        MediaItem::trim(token);
        episode.m_numberInSeason = static_cast<unsigned short>(std::stoi(token));

        std::getline(ss, token, ',');
        MediaItem::trim(token);
        episode.m_airDate = token;

        std::getline(ss, token, ',');
        MediaItem::trim(token);
        episode.m_length = calculateSeconds(token);

        std::getline(ss, token, ',');
        MediaItem::trim(token);
        episode.m_title = token;

        std::getline(ss, token);
        MediaItem::trim(token);
        episode.m_summary = token;

        targetShow->m_episodes.push_back(episode);
    }
}


#endif
