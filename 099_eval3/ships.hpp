#ifndef SHIPS_HPP
#define SHIPS_HPP

#include <ostream>
#include <string>
#include <vector>

#include "cargo.hpp"

class Ship {
 private:
  std::string name;
  std::string ship_type;
  std::string source;
  std::string dest;
  unsigned long total_capacity;
  unsigned used_capacity;
  std::vector<std::string> capabilities;
  std::vector<Cargo> cargos_carried;

 public:
  Ship();
  Ship(const std::string & name_,
       const std::string & ship_type_,
       const std::string & source_,
       const std::string & dest_,
       unsigned long total_capacity_,
       unsigned used_capacity_,
       const std::vector<std::string> & capabilities_,
       const std::vector<Cargo> & cargos_carried_);
  const std::string & get_name() const;
  const std::string & get_ship_type() const;
  const std::string & get_source() const;
  const std::string & get_dest() const;
  unsigned long get_total_capacity() const;
  unsigned get_used_capacity() const;
  unsigned get_remaining_capacity() const;
  const std::vector<std::string> & get_capabilities() const;
  const std::vector<Cargo> & get_cargos_carried() const;
  virtual bool can_load(const Cargo & cargo) const = 0;
  virtual void load_cargo(const Cargo & cargo);
  virtual void print_remaining_space() const = 0;
  virtual ~Ship(){};
};

/* Used in stable_sort and CompareV */
struct ShipPtrLess {
  bool operator()(Ship * lhs, Ship * rhs) const {
    if (lhs->get_name() != rhs->get_name()) {
      return lhs->get_name() < rhs->get_name();
    }
    return lhs < rhs;
  }
};

class Container : public Ship {
 private:
  unsigned num_slots;

 public:
  Container();
  Container(const std::string & name_,
            const std::string & ship_type_,
            const std::string & source_,
            const std::string & dest_,
            unsigned long total_capacity_,
            unsigned used_capacity_,
            const std::vector<std::string> & capabilities_,
            const std::vector<Cargo> & cargos_carried_,
            unsigned num_slots_);
  virtual bool can_load(const Cargo & cargo) const;
  virtual void load_cargo(const Cargo & cargo);
  virtual void print_remaining_space() const;
  virtual ~Container(){};
};

class Tanker : public Ship {
 private:
  signed min_temp;
  signed max_temp;
  unsigned capacity_per_tank;
  std::vector<std::pair<unsigned, std::string> > tanks;

 public:
  Tanker();
  Tanker(const std::string & name_,
         const std::string & ship_type_,
         const std::string & source_,
         const std::string & dest_,
         unsigned long total_capacity_,
         unsigned used_capacity_,
         const std::vector<std::string> & capabilities_,
         const std::vector<Cargo> & cargos_carried_,
         signed min_temp_,
         signed max_temp_,
         unsigned num_tanks_);
  bool check_tank_capacity(const Cargo & cargo) const;
  bool check_temps(const std::vector<std::string> & properties) const;
  void update_tanks(unsigned & tank_capacity, unsigned & cargo_size);
  unsigned get_tanks_used() const;
  virtual bool can_load(const Cargo & cargo) const;
  virtual void load_cargo(const Cargo & cargo);
  virtual void print_remaining_space() const;
  virtual ~Tanker(){};
};

class Animal : public Ship {
 private:
  unsigned size;

 public:
  Animal();
  Animal(const std::string & name_,
         const std::string & ship_type_,
         const std::string & source_,
         const std::string & dest_,
         unsigned long total_capacity_,
         unsigned used_capacity_,
         const std::vector<std::string> & capabilities_,
         const std::vector<Cargo> & cargos_carried_,
         unsigned size_);
  bool check_roamer(const std::vector<Cargo> & cargos_carried) const;
  virtual bool can_load(const Cargo & cargo) const;
  virtual void load_cargo(const Cargo & cargo);
  virtual void print_remaining_space() const;
  virtual ~Animal(){};
};

#endif
