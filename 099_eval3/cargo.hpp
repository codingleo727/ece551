#ifndef CARGO_HPP
#define CARGO_HPP

#include <string>
#include <vector>

class Cargo {
 private:
  std::string name;
  std::string source;
  std::string dest;
  unsigned capacity;
  std::vector<std::string> properties;

 public:
  Cargo();
  Cargo(const std::string & name_,
        const std::string & source_,
        const std::string & dest_,
        unsigned capacity_,
        const std::vector<std::string> & properties_);
  const std::string & get_name() const;
  const std::string & get_source() const;
  const std::string & get_dest() const;
  unsigned get_capacity() const;
  const std::vector<std::string> & get_properties() const;
};

#endif
