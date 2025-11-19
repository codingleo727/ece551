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
  unsigned total_capacity;
  unsigned used_capacity;
  std::vector<std::string> capabilities;
  std::vector<Cargo> cargos_carried;

 public:
  Ship();
  Ship(std::string name_,
       std::string ship_type_,
       std::string source_,
       std::string dest_,
       unsigned total_capacity_,
       unsigned used_capacity_,
       std::vector<std::string> capabilities_,
       std::vector<Cargo> cargos_carried_);
  const std::string & get_name() const;
  const std::string & get_ship_type() const;
  const std::string & get_source() const;
  const std::string & get_dest() const;
  unsigned get_total_capacity() const;
  unsigned get_used_capacity() const;
  const std::vector<std::string> & get_capabilities() const;
  const std::vector<Cargo> & get_cargos_carried() const;
  bool operator<(const Ship & rhs) const;
  virtual bool can_load(const Cargo & cargo) const = 0;
  virtual void load_cargo(const Cargo & cargo);
  virtual void print_remaining_space() const = 0;
  virtual ~Ship(){};
};

bool ship_ptr_less(Ship * lhs, Ship * rhs);

class Container : public Ship {
 private:
  unsigned num_slots;

 public:
  Container();
  Container(std::string name_,
            std::string ship_type_,
            std::string source_,
            std::string dest_,
            unsigned total_capacity_,
            unsigned used_capacity_,
            std::vector<std::string> capabilities_,
            std::vector<Cargo> cargos_carried_,
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
  unsigned num_tanks;

 public:
  Tanker();
  Tanker(std::string name_,
         std::string ship_type_,
         std::string source_,
         std::string dest_,
         unsigned total_capacity_,
         unsigned used_capacity_,
         std::vector<std::string> capabilities_,
         std::vector<Cargo> cargos_carried_,
         signed min_temp_,
         signed max_temp_,
         unsigned num_tanks_);
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
  Animal(std::string name_,
         std::string ship_type_,
         std::string source_,
         std::string dest_,
         unsigned total_capacity_,
         unsigned used_capacity_,
         std::vector<std::string> capabilities_,
         std::vector<Cargo> cargos_carried_,
         unsigned size_);
  virtual bool can_load(const Cargo & cargo) const;
  virtual void load_cargo(const Cargo & cargo);
  virtual void print_remaining_space() const;
  virtual ~Animal(){};
};

#endif
