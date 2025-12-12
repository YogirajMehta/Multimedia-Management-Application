#include <iostream>
#include <algorithm>
#include "collection.h"
#include "mediaItem.h"

using namespace std;

namespace seneca
{
    Collection::Collection(const string& name)
        : m_name{ name }, m_observer{ nullptr } {
    }
    Collection::~Collection()
    {
        for (auto item : m_items)
        {
            delete item;
        }
    }
    const string& Collection::name() const { return m_name; }
    size_t Collection::size() const { return m_items.size(); }

    void Collection::setObserver(void (*observer)(const Collection&, const MediaItem&))
    {
        m_observer = observer;
    }

    Collection& Collection::operator+=(MediaItem* item)
    {
        bool exists = false;
        for (const auto& existingItem : m_items)
        {
            if (existingItem->getTitle() == item->getTitle())
            {
                exists = true;
                break;
            }
        }
        if (exists)
        {
            delete item;
        }
        else
        {
            m_items.push_back(item);
            if (m_observer)
            {
                m_observer(*this, *item);
            }
        }
        return *this;
    }
    MediaItem* Collection::operator[](size_t idx) const
    {
        if (idx >= m_items.size())
        {
            std::string msg = "Bad index [" + std::to_string(idx) +
                "]. Collection has [" + std::to_string(m_items.size()) +
                "] items.";
            throw std::out_of_range(msg);
        }
        return m_items[idx];
    }

    MediaItem* Collection::operator[](const string& title) const
    {
        auto it = std::find_if(m_items.begin(), m_items.end(), [title](const MediaItem* item)
            {
                return item->getTitle() == title;
            });

        if (it != m_items.end())
        {
            return *it;
        }
        else
        {
            return nullptr;
        }
    }

    void Collection::removeQuotes()
    {
        std::for_each(m_items.begin(), m_items.end(), [](MediaItem* item)
            {
                auto cleanString = [](std::string& str)
                    {
                        if (!str.empty())
                        {
                            if (str.front() == '\"')
                                str.erase(0, 1);
                        }
                        if (!str.empty())
                        {
                            if (str.back() == '\"')
                                str.pop_back();
                        }
                    };
                std::string title = item->getTitle();
                std::string summary = item->getSummary();

                cleanString(title);
                cleanString(summary);

                item->setTitle(title);
                item->setSummary(summary);
            });
    }

    void Collection::sort(const string& field)
    {
        std::sort(m_items.begin(), m_items.end(), [field](const MediaItem* a, const MediaItem* b)
            {
                if (field == "title")
                {
                    return a->getTitle() < b->getTitle();
                }
                if (field == "year")
                {
                    return a->getYear() < b->getYear();
                }
                if (field == "summary")
                {
                    return a->getSummary() < b->getSummary();
                }
                return false;
            });
    }

    std::ostream& operator<<(std::ostream& out, const Collection& coll)
    {
        std::for_each(coll.m_items.begin(), coll.m_items.end(), [&out](const MediaItem* item)
            {
                item->display(out);
            });
        return out;
    }

}
