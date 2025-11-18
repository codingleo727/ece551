#include "ships.hpp"

#include <iostream>

Ship::Ship() : name(), info(), source(), dest(), capacity() {
}

Ship::Ship(std::string name_,
           std::vector<std::string> info_,
           std::string source_,
           std::string dest_,
           unsigned capacity_) :
    name(name_), info(info_), source(source_), dest(dest_), capacity(capacity_) {
}

/* Returns the name of the ship */
const std::string & Ship::get_name() const {
  return name;
}

/* Returns the type info of the ship */
const std::vector<std::string> & Ship::get_info() const {
  return info;
}

/* Returns the source of the ship */
const std::string & Ship::get_source() const {
  return source;
}

/* Returns the destination of the ship */
const std::string & Ship::get_dest() const {
  return dest;
}

/* Returns the capacity of the ship */
unsigned Ship::get_capacity() const {
  return capacity;
}

Container::Container() : Ship(), num_slots(), capabilities() {
}

Container::Container(std::string name_,
                     std::vector<std::string> info_,
                     std::string source_,
                     std::string dest_,
                     unsigned capacity_,
                     unsigned num_slots_,
                     std::vector<std::string> capabilities_) :
    Ship(name_, info_, source_, dest_, capacity_),
    num_slots(num_slots_),
    capabilities(capabilities_) {
}

unsigned Container::get_slots() const {
  return num_slots;
}

const std::vector<std::string> & Container::get_capabilities() const {
  return capabilities;
}
