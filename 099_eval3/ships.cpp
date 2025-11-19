#include "ships.hpp"

#include <iostream>

bool contains_container(const std::vector<std::string> & properties);

Ship::Ship() :
    name(),
    ship_type(),
    source(),
    dest(),
    total_capacity(),
    used_capacity(),
    capabilities(),
    cargos_carried() {
}

Ship::Ship(std::string name_,
           std::string ship_type_,
           std::string source_,
           std::string dest_,
           unsigned total_capacity_,
           unsigned used_capacity_,
           std::vector<std::string> capabilities_,
           std::vector<Cargo> cargos_carried_) :
    name(name_),
    ship_type(ship_type_),
    source(source_),
    dest(dest_),
    total_capacity(total_capacity_),
    used_capacity(used_capacity_),
    capabilities(capabilities_),
    cargos_carried(cargos_carried_) {
}

/* Returns the name of the ship */
const std::string & Ship::get_name() const {
  return name;
}

/* Returns the type of the ship */
const std::string & Ship::get_ship_type() const {
  return ship_type;
}

/* Returns the source of the ship */
const std::string & Ship::get_source() const {
  return source;
}

/* Returns the destination of the ship */
const std::string & Ship::get_dest() const {
  return dest;
}

/* Returns the total capacity of the ship */
unsigned Ship::get_total_capacity() const {
  return total_capacity;
}

/* Returns the remaining capacity of the ship */
unsigned Ship::get_used_capacity() const {
  return used_capacity;
}

/* Returns the capabilities of the ship */
const std::vector<std::string> & Ship::get_capabilities() const {
  return capabilities;
}

/* Returns the cargos that the ship is carrying */
const std::vector<Cargo> & Ship::get_cargos_carried() const {
  return cargos_carried;
}

void Ship::load_cargo(const Cargo & cargo) {
  used_capacity += cargo.get_capacity();
  cargos_carried.push_back(cargo);
}

bool ship_ptr_less(Ship * lhs, Ship * rhs) {
  return *lhs < *rhs;
}

bool Ship::operator<(const Ship & rhs) const {
  return name < rhs.name;
}

Container::Container() : Ship(), num_slots() {
}

Container::Container(std::string name_,
                     std::string ship_type_,
                     std::string source_,
                     std::string dest_,
                     unsigned total_capacity_,
                     unsigned used_capacity_,
                     std::vector<std::string> capabilities_,
                     std::vector<Cargo> cargos_carried_,
                     unsigned num_slots_) :
    Ship(name_,
         ship_type_,
         source_,
         dest_,
         total_capacity_,
         used_capacity_,
         capabilities_,
         cargos_carried_),
    num_slots(num_slots_) {
}

bool Container::can_load(const Cargo & cargo) const {
  const std::vector<std::string> & properties = cargo.get_properties();
  const std::vector<std::string> & capabilities = get_capabilities();

  bool same_route = cargo.get_source() == get_source() && cargo.get_dest() == get_dest();
  if (!same_route) {
    return false;
  }

  unsigned remaining_capacity = get_total_capacity() - get_used_capacity();
  bool enough_space = cargo.get_capacity() <= remaining_capacity && num_slots > 0;
  if (!enough_space) {
    return false;
  }

  bool has_container = contains_container(properties);
  if (!has_container) {
    return false;
  }

  if (properties.size() - 1 > 0) {
    bool found = false;
    for (size_t i = 0; i < properties.size(); ++i) {
      for (size_t j = 0; j < capabilities.size(); ++j) {
        if (properties[i] == capabilities[j]) {
          found = true;
          break;
        }
      }
    }
    if (!found) {
      return false;
    }
  }

  return true;
}

bool contains_container(const std::vector<std::string> & properties) {
  for (size_t i = 0; i < properties.size(); ++i) {
    if (properties[i] == "container") {
      return true;
    }
  }
  return false;
}

void Container::load_cargo(const Cargo & cargo) {
  Ship::load_cargo(cargo);
  num_slots--;
}

void Container::print_remaining_space() const {
  std::cout << "  (" << num_slots << ") slots remain\n";
}
