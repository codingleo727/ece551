#include "ships.hpp"

#include <iostream>

#include "util.hpp"

namespace {
  /* Helper function check if a ship can handle the hazardous properties of the cargo */
  bool check_hazard(const std::vector<std::string> & properties,
                    const std::vector<std::string> & capabilities) {
    size_t hazard_amount = 0;
    size_t found_capabilities = 0;
    for (size_t i = 0; i < properties.size(); ++i) {
      std::string word_to_find = "hazardous-";
      size_t pos = properties[i].find(word_to_find);
      if (pos == std::string::npos) {
        continue;
      }
      else {
        hazard_amount++;
      }

      for (size_t j = 0; j < capabilities.size(); ++j) {
        if (properties[i].substr(pos + word_to_find.length()) == capabilities[j]) {
          found_capabilities++;
        }
      }
    }

    return found_capabilities == hazard_amount;
  }

  /* Helper function to check if the ship contains a property */
  bool contains_property(const std::vector<std::string> & properties,
                         std::string property) {
    for (std::vector<std::string>::const_iterator it = properties.begin();
         it != properties.end();
         ++it) {
      if (it->find(property) != std::string::npos) {
        return true;
      }
    }
    return false;
  }
}  // namespace

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

Ship::Ship(const std::string & name_,
           const std::string & ship_type_,
           const std::string & source_,
           const std::string & dest_,
           unsigned total_capacity_,
           unsigned used_capacity_,
           const std::vector<std::string> & capabilities_,
           const std::vector<Cargo> & cargos_carried_) :
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

unsigned Ship::get_remaining_capacity() const {
  return total_capacity - used_capacity;
}

/* Returns the capabilities of the ship */
const std::vector<std::string> & Ship::get_capabilities() const {
  return capabilities;
}

/* Returns the cargos that the ship is carrying */
const std::vector<Cargo> & Ship::get_cargos_carried() const {
  return cargos_carried;
}

/* Loads the cargo onto the ship */
void Ship::load_cargo(const Cargo & cargo) {
  used_capacity += cargo.get_capacity();
  cargos_carried.push_back(cargo);
}

bool Ship::operator<(const Ship & rhs) const {
  return name < rhs.name;
}

Container::Container() : Ship(), num_slots() {
}

Container::Container(const std::string & name_,
                     const std::string & ship_type_,
                     const std::string & source_,
                     const std::string & dest_,
                     unsigned total_capacity_,
                     unsigned used_capacity_,
                     const std::vector<std::string> & capabilities_,
                     const std::vector<Cargo> & cargos_carried_,
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

/* Checks if the current ship can load the cargo */
bool Container::can_load(const Cargo & cargo) const {
  const std::vector<std::string> & properties = cargo.get_properties();
  const std::vector<std::string> & capabilities = get_capabilities();

  bool same_route = cargo.get_source() == get_source() && cargo.get_dest() == get_dest();
  if (!same_route) {
    return false;
  }

  unsigned remaining_capacity = get_remaining_capacity();
  bool enough_space = cargo.get_capacity() <= remaining_capacity && num_slots > 0;
  if (!enough_space) {
    return false;
  }

  bool has_container = contains_property(properties, "container");
  if (!has_container) {
    return false;
  }

  bool hazard_carriable = check_hazard(properties, capabilities);
  if (!hazard_carriable) {
    return false;
  }

  return true;
}

/* Loads the cargo onto the Container ship */
void Container::load_cargo(const Cargo & cargo) {
  Ship::load_cargo(cargo);
  num_slots--;
}

/* Prints the remaining number of slots on the ship */
void Container::print_remaining_space() const {
  std::cout << "  (" << num_slots << ") slots remain\n";
}

Tanker::Tanker() : Ship(), min_temp(), max_temp(), tanks() {
}

Tanker::Tanker(const std::string & name_,
               const std::string & ship_type_,
               const std::string & source_,
               const std::string & dest_,
               unsigned total_capacity_,
               unsigned used_capacity_,
               const std::vector<std::string> & capabilities_,
               const std::vector<Cargo> & cargos_carried_,
               signed min_temp_,
               signed max_temp_,
               unsigned num_tanks_) :
    Ship(name_,
         ship_type_,
         source_,
         dest_,
         total_capacity_,
         used_capacity_,
         capabilities_,
         cargos_carried_),
    min_temp(min_temp_),
    max_temp(max_temp_),
    tanks() {
  capacity_per_tank = get_total_capacity() / num_tanks_;
  for (unsigned i = 0; i < num_tanks_; ++i) {
    tanks.push_back(std::make_pair(
        capacity_per_tank,
        ""));  // Creates a pair that represents the remaining capacity and content inside the tank
  }
}

/* Checks if the current ship can load the cargo */
bool Tanker::can_load(const Cargo & cargo) const {
  const std::vector<std::string> & properties = cargo.get_properties();
  const std::vector<std::string> & capabilities = get_capabilities();

  bool same_route = cargo.get_source() == get_source() && cargo.get_dest() == get_dest();
  if (!same_route) {
    return false;
  }

  bool enough_space = check_tank_capacity(cargo);
  if (!enough_space) {
    return false;
  }

  bool safe_temp = check_temps(properties);
  if (!safe_temp) {
    return false;
  }

  bool has_liquid_or_gas =
      contains_property(properties, "liquid") || contains_property(properties, "gas");
  if (!has_liquid_or_gas) {
    return false;
  }

  bool hazard_carriable = check_hazard(properties, capabilities);
  if (!hazard_carriable) {
    return false;
  }

  return true;
}

/* Checks for 2 conditions:
     1. Does the ship have enough remaining capacity
     2. Checks if there are empty tanks or enough existing tanks for the cargo */
bool Tanker::check_tank_capacity(const Cargo & cargo) const {
  unsigned remaining_capacity = get_remaining_capacity();
  if (remaining_capacity < cargo.get_capacity()) {
    return false;
  }

  unsigned remaining_cargo = cargo.get_capacity();
  for (std::vector<std::pair<unsigned, std::string> >::const_iterator it = tanks.begin();
       it != tanks.end();
       ++it) {
    if (it->first == 0) {
      continue;
    }

    if (!(it->second == "" || it->second == cargo.get_name())) {
      continue;
    }

    unsigned put_cargo = it->first;
    if (put_cargo >= remaining_cargo) {
      return true;
    }

    remaining_cargo -= put_cargo;
  }

  return false;
}

/* Checks if the ship has the correct temperature capability to transport the cargo */
bool Tanker::check_temps(const std::vector<std::string> & properties) const {
  std::string cargo_min_temp;
  std::string cargo_max_temp;
  signed min = 0;
  signed max = 0;
  for (std::vector<std::string>::const_iterator it = properties.begin();
       it != properties.end();
       ++it) {
    if (it->find("mintemp") != std::string::npos) {
      cargo_min_temp = *it;
    }

    if (it->find("maxtemp") != std::string::npos) {
      cargo_max_temp = *it;
    }
  }

  if (cargo_min_temp.find("=") == std::string::npos ||
      cargo_min_temp.substr(cargo_min_temp.find("=") + 1) == "") {
    min = 0;
  }
  else {
    min = to_number<signed>(cargo_min_temp.substr(cargo_min_temp.find("=") + 1));
  }

  if (cargo_max_temp.find("=") == std::string::npos ||
      cargo_max_temp.substr(cargo_max_temp.find("=") + 1) == "") {
    max = 0;
  }
  else {
    max = to_number<signed>(cargo_max_temp.substr(cargo_max_temp.find("=") + 1));
  }

  if (cargo_min_temp == "" && cargo_max_temp == "") {
    return true;
  }
  else if (cargo_max_temp == "") {
    return max_temp >= min;
  }
  else if (cargo_min_temp == "") {
    return min_temp <= max;
  }
  else {
    return max_temp >= min && min_temp <= max;
  }

  return true;
}

/* Loads the cargo onto the Tanker ship */
void Tanker::load_cargo(const Cargo & cargo) {
  unsigned remaining_cargo = cargo.get_capacity();
  Ship::load_cargo(cargo);
  for (std::vector<std::pair<unsigned, std::string> >::iterator it = tanks.begin();
       it != tanks.end();
       ++it) {
    if (remaining_cargo > 0 && it->second == "") {
      it->second = cargo.get_name();
      update_tanks(it->first, remaining_cargo);
    }
    else if (remaining_cargo > 0 && (it->second == cargo.get_name() && it->first > 0)) {
      update_tanks(it->first, remaining_cargo);
    }
  }
}

/* Updates the capacity of each tank on the Tanker ship */
void Tanker::update_tanks(unsigned & tank_capacity, unsigned & cargo_size) {
  if (tank_capacity < cargo_size) {
    cargo_size = cargo_size - tank_capacity;
    tank_capacity = 0;
  }
  else {
    tank_capacity = tank_capacity - cargo_size;
    cargo_size = 0;
  }
}

/* Returns the amount of tanks used */
unsigned Tanker::get_tanks_used() const {
  unsigned tanks_used = 0;
  for (std::vector<std::pair<unsigned, std::string> >::const_iterator it = tanks.begin();
       it != tanks.end();
       ++it) {
    if (it->first < capacity_per_tank) {
      tanks_used++;
    }
  }

  return tanks_used;
}

/* Prints the amount of tanks used */
void Tanker::print_remaining_space() const {
  std::cout << "  " << get_tanks_used() << " / " << tanks.size() << " tanks used\n";
}

Animal::Animal() : Ship(), size() {
}

Animal::Animal(const std::string & name_,
               const std::string & ship_type_,
               const std::string & source_,
               const std::string & dest_,
               unsigned total_capacity_,
               unsigned used_capacity_,
               const std::vector<std::string> & capabilities_,
               const std::vector<Cargo> & cargos_carried_,
               unsigned size_) :
    Ship(name_,
         ship_type_,
         source_,
         dest_,
         total_capacity_,
         used_capacity_,
         capabilities_,
         cargos_carried_),
    size(size_) {
}

/* Checks if the current ship can load the cargo */
bool Animal::can_load(const Cargo & cargo) const {
  const std::vector<std::string> & properties = cargo.get_properties();

  bool same_route = cargo.get_source() == get_source() && cargo.get_dest() == get_dest();
  if (!same_route) {
    return false;
  }

  unsigned remaining_capacity = get_remaining_capacity();
  bool enough_space = cargo.get_capacity() <= remaining_capacity;
  if (!enough_space) {
    return false;
  }

  bool has_animal = contains_property(properties, "animal");
  if (has_animal) {
    bool has_roamer = contains_property(properties, "roamer");
    if (has_roamer) {
      return !check_roamer(get_cargos_carried());
    }
  }
  else {
    bool has_liquid_or_gas =
        contains_property(properties, "liquid") || contains_property(properties, "gas");
    if (has_liquid_or_gas) {
      return false;
    }

    bool small_enough = cargo.get_capacity() <= size;
    if (!small_enough) {
      return false;
    }

    // If any property contains the word hazardous, immediately return false
    for (std::vector<std::string>::const_iterator it = properties.begin();
         it != properties.end();
         ++it) {
      std::string word_to_find = "hazardous-";
      if (it->find(word_to_find) != std::string::npos) {
        return false;
      }
    }
  }

  return true;
}

/* Loads the cargo onto the Animal ship */
void Animal::load_cargo(const Cargo & cargo) {
  Ship::load_cargo(cargo);
}

/* Prints if the ship has a roamer or not */
void Animal::print_remaining_space() const {
  if (check_roamer(get_cargos_carried())) {
    std::cout << "  has a roamer\n";
  }
  else {
    std::cout << "  does not have a roamer\n";
  }
}

/* Checks if the ship has a roamer or not */
bool Animal::check_roamer(const std::vector<Cargo> & cargos_carried) const {
  for (std::vector<Cargo>::const_iterator it = cargos_carried.begin();
       it != cargos_carried.end();
       ++it) {
    std::vector<std::string> cargo_properties = it->get_properties();
    if (contains_property(cargo_properties, "roamer")) {
      return true;
    }
  }
  return false;
}
