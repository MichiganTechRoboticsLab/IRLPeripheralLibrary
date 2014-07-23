#include <Util/util.hpp>

#include <string>
#include <algorithm>

namespace IRL
{
    namespace Util
    {

        std::string lowercase(const std::string str)
        {
            std::string retStr(str);
            std::transform(retStr.begin(), retStr.end(), retStr.begin(), ::tolower);
            return retStr;
        }

        bool isInt(const std::string str)
        {
            try
            {
                std::stoi(str);
            }
            catch(std::invalid_argument)
            {
                return false;
            }
            return true;
        }
    }
}
