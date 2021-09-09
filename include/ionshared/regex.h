#pragma once

#include <regex>

namespace ionshared::regex {
    static const std::regex identifier = std::regex("^([_a-zA-Z]+[\\w]*)");

    static const std::regex string = std::regex("^\"([^\\\"]*)\"");

    static const std::regex decimal = std::regex("^([0-9]+\\.[0-9]+)");

    static const std::regex integer = std::regex("^([0-9]+)");

    static const std::regex character = std::regex("^'([^'\\n\\\\]{0,1})'");

    static const std::regex whitespace = std::regex("^([\\s]+)");
}
