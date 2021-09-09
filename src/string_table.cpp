#include <stdexcept>
#include <ionshared/string_table.h>

namespace ionshared {
  StringTable::StringTable() {}

  StringIndex StringTable::add(std::string string) {
    if (this->stringMap.contains(string)) {
      return this->stringMap[string];
    }

    StringIndex index = this->indexMap.size() == 0
      ? 0
      : this->indexMap.size() + 1;

    this->stringMap[string] = index;
    this->indexMap.push_back(string);
    
    return index;
  }

  std::optional<std::string> StringTable::lookup(StringIndex index) {
    if (this->indexMap.empty() || this->indexMap.size() <= index) {
      return std::nullopt;
    }

    return this->indexMap[index];
  }

  std::string StringTable::forceLookup(StringIndex index) {
    std::optional<std::string> lookupResult = this->lookup(index);

    if (!lookupResult.has_value()) {
      throw std::runtime_error("String lookup returned null");
    }

    return *lookupResult;
  }
}
