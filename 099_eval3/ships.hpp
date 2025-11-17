#ifndef SHIPS_HPP
#define SHIPS_HPP

#include <ostream>
#include <string>
#include <vector>

class Ship {
 private:
  std::string name;
  std::vector<std::string> info;
  std::string source;
  std::string dest;
  unsigned capacity;

 public:
  Ship();
  Ship(std::string name_,
       std::vector<std::string> info_,
       std::string source_,
       std::string dest_,
       unsigned capacity_);
  const std::string & get_name() const;
  const std::string & get_source() const;
  const std::vector<std::string> & get_info() const;
  const std::string & get_dest() const;
  unsigned get_capacity() const;
};

class Container : public Ship {
 private:
  unsigned slots;
  std::vector<std::string> capabilities;

 public:
  unsigned get_slots() const;
  const std::vector<std::string> get_capabilities() const;
};

class Tanker : public Ship {
 private:
 public:
};

#endif
