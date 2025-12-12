#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H

#include "mediaItem.h"
#include <string>
#include <vector>

namespace seneca
{
    class Collection
    {
        std::string m_name;
        std::vector<MediaItem*> m_items;
        void (*m_observer)(const Collection&, const MediaItem&) {};

    public:
        Collection(const std::string& name);
        ~Collection();

        Collection(const Collection&) = delete;
        Collection& operator=(const Collection&) = delete;
        Collection(Collection&& other) noexcept = delete;
        Collection& operator=(Collection&& other) noexcept = delete;

        const std::string& name() const;
        size_t size() const;
        void setObserver(void (*observer)(const Collection&, const MediaItem&));

        Collection& operator+=(MediaItem* item);

        MediaItem* operator[](size_t idx) const;
        MediaItem* operator[](const std::string& title) const;

        void removeQuotes();
        void sort(const std::string& field);

        friend std::ostream& operator<<(std::ostream& out, const Collection& coll);
    };

    std::ostream& operator<<(std::ostream& out, const Collection& coll);
}


#endif // SENECA_COLLECTION_H
