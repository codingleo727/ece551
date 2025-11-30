#include "cargo.hpp"

Cargo::Cargo() : name(), source(), dest(), capacity(0), properties() {
}

Cargo::Cargo(const std::string & name_,
             const std::string & source_,
             const std::string & dest_,
             unsigned capacity_,
             const std::vector<std::string> & properties_) :
    name(name_),
    source(source_),
    dest(dest_),
    capacity(capacity_),
    properties(properties_) {
}

/* Returns the name of the cargo */
const std::string & Cargo::get_name() const {
  return name;
}

/* Returns the source of the cargo */
const std::string & Cargo::get_source() const {
  return source;
}

/* Returns the destination of the cargo */
const std::string & Cargo::get_dest() const {
  return dest;
}

/* Returns the capacity of the cargo */
unsigned Cargo::get_capacity() const {
  return capacity;
}

/* Returns a vector of properties of the cargo */
const std::vector<std::string> & Cargo::get_properties() const {
  return properties;
}
