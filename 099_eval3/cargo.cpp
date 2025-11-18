#include "cargo.hpp"

Cargo::Cargo() : name(), source(), dest(), capacity(0), properties() {
}

Cargo::Cargo(std::string name_,
             std::string source_,
             std::string dest_,
             unsigned capacity_,
             std::vector<std::string> properties_) :
    name(name_),
    source(source_),
    dest(dest_),
    capacity(capacity_),
    properties(properties_) {
}

const std::string & Cargo::get_name() const {
  return name;
}

const std::string & Cargo::get_source() const {
  return source;
}

const std::string & Cargo::get_dest() const {
  return dest;
}

unsigned Cargo::get_capacity() const {
  return capacity;
}

const std::vector<std::string> & Cargo::get_properties() const {
  return properties;
}
