#include <iostream>

#include "ships.hpp"

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
