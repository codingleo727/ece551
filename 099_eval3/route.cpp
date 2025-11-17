#include "route.hpp"

Route::Route() : source(), dest(), capacity(0) {
}

Route::Route(std::string source_, std::string dest_, unsigned capacity_) :
    source(source_), dest(dest_), capacity(capacity_) {
}

const std::string & Route::get_source() const {
  return source;
}

const std::string & Route::get_dest() const {
  return dest;
}

unsigned Route::get_capacity() const {
  return capacity;
}

void Route::update_capacity(unsigned int extra_capacity) {
  capacity = capacity + extra_capacity;
}

bool Route::operator==(const Route & rhs) const {
  return get_source() == rhs.get_source() && get_dest() == rhs.get_dest();
}

bool Route::operator<(const Route & rhs) const {
  if (get_source() < rhs.get_source()) {
    return true;
  }
  if (get_source() > rhs.get_source()) {
    return false;
  }
  return get_dest() < rhs.get_dest();
}

std::ostream & operator<<(std::ostream & os, const Route & route) {
  os << "(" << route.source << " -> " << route.dest << ") has total capacity "
     << route.capacity << "\n";
  return os;
}
