#pragma once

#include <string>
#include <ctime>
#include <stdint.h>

/**
 * @brief this class is for calculating the corent time.
 */
class CurrentTime {
public:
    static constexpr auto TIME_STRING_LENGTH = 14;

    /**
     * @brief Construct a new Current Time object.
     * 
     */
    CurrentTime();

    /**
     * @brief Get the Time object.
     * 
     * @return std::string rturn string that
     * stands for the time & date.
     */
    std::string getTime() const;
private:
    std::string _time = "";
};