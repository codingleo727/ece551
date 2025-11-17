#include "ship.hpp"

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

const std::string & Ship::get_name() const {
  return name;
}

const std::vector<std::string> & Ship::get_info() const {
  return info;
}

const std::string & Ship::get_source() const {
  return source;
}

const std::string & Ship::get_dest() const {
  return dest;
}

unsigned Ship::get_capacity() const {
  return capacity;
}
