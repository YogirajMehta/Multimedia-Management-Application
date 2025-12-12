/*
Name-Yogiraj Mehta
email-ymehta4@myseneca.ca
id-162867238
date-12-11-2025
I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
*/
#ifndef SENECA_MOVIE_H
#define SENECA_MOVIE_H
#include "mediaItem.h"
#include "settings.h"
#include <string>
#include <ostream>

namespace seneca
{

    class Movie : public MediaItem
    {
    public:
        Movie();
        Movie(const std::string& title, unsigned short year, const std::string& summary);
        void display(std::ostream& out) const override;
        static Movie* createItem(const std::string& strMovie);
    };

}
#endif
