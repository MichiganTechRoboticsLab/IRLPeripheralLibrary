#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>

namespace IRL
{
    namespace Util
    {

        template <typename T>
        struct triple
        {
            T v1;
            T v2;
            T v3;
        };

        std::string lowercase(const std::string& str);

        bool isInt(const std::string& str);


    }
}

#endif // UTIL_HPP

