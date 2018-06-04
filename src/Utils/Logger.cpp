//
// Created by lucas on 03/06/2018.
//

#include <ctime>
#include <iostream>
#include <iomanip>
#include <time.h>
#include "Logger.hpp"

#define RED "\033[0;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define RESET "\033[0m"


void Logger::logMessage(const std::string &msg, logLevel level)
{
    auto time = std::time(nullptr);
    struct tm info;

    localtime(&time);
    std::cout << std::put_time(&info, "%T");
    if (level == logLevel::SUCCESS)
        std::cout << " | Success : ";
    else if (level == logLevel::WARNING)
        std::cout << " | Warning : ";
    std::cout << msg << std::endl;
}