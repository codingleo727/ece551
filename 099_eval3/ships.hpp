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
  virtual ~Ship(){};
};

class Container : public Ship {
 private:
  unsigned num_slots;
  std::vector<std::string> capabilities;

 public:
  Container();
  Container(std::string name_,
            std::vector<std::string> info_,
            std::string source_,
            std::string dest_,
            unsigned capacity_,
            unsigned num_slots_,
            std::vector<std::string> capabilities_);
  unsigned get_slots() const;
  const std::vector<std::string> & get_capabilities() const;
  virtual ~Container(){};
};

class Tanker : public Ship {
 private:
  signed min_temp;
  signed max_temp;
  unsigned num_tanks;
  std::vector<std::string> capabilities;

 public:
  Tanker();
  Tanker(std::string name_,
         std::vector<std::string> info_,
         std::string source_,
         std::string dest_,
         unsigned capacity_,
         signed min_temp_,
         signed max_temp_,
         unsigned num_tanks_,
         std::vector<std::string> capabilities_);
  signed get_min_temp() const;
  signed get_max_temp() const;
  unsigned get_tanks() const;
  const std::vector<std::string> & get_capabilities() const;
  virtual ~Tanker(){};
};

class Animal : public Ship {
 private:
  unsigned size;

 public:
  Animal();
  Animal(std::string name_,
         std::vector<std::string> info_,
         std::string source_,
         std::string dest_,
         unsigned capacity_,
         unsigned size_);
  unsigned get_size() const;
  virtual ~Animal(){};
};

#endif
