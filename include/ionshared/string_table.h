#pragma once

#include <string>
#include <vector>
#include <map>

namespace ionshared {
  typedef uint32_t StringIndex;

  struct StringTable {
  private:
    std::vector<std::string> indexMap;

    std::map<std::string, StringIndex> stringMap;

  public:
    explicit StringTable();

    StringIndex add(std::string string);

    std::optional<std::string> lookup(StringIndex index);

    std::string forceLookup(StringIndex index);
  };
}
