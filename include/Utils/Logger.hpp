//
// Created by lucas on 03/06/2018.
//

#ifndef INDIESTUDIO_LOGGER_HPP
#define INDIESTUDIO_LOGGER_HPP

#include <string>

enum logLevel {
    WARNING,
    SUCCESS,
    STATUT
};

class Logger {
public:
    static void logMessage(const std::string &msg, logLevel);
};

#endif //INDIESTUDIO_LOGGER_HPP
