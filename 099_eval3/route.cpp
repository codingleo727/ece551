#include "route.hpp"

Route::Route() : source(), dest(), capacity(0) {
}

Route::Route(std::string source_, std::string dest_, unsigned capacity_) :
    source(source_), dest(dest_), capacity(capacity_) {
}

/* Returns source */
const std::string & Route::get_source() const {
  return source;
}

/* Returns destination */
const std::string & Route::get_dest() const {
  return dest;
}

/* Returns current route capacity */
unsigned Route::get_capacity() const {
  return capacity;
}

/* Updates the route's capacity */
void Route::update_capacity(unsigned int extra_capacity) {
  capacity = capacity + extra_capacity;
}

/* Checks if other route is the same as current route */
bool Route::operator==(const Route & rhs) const {
  return source == rhs.source && dest == rhs.dest;
}

/* Used for sorting the route in alphabetical order, starting with source, then destination */
bool Route::operator<(const Route & rhs) const {
  if (source < rhs.source) {
    return true;
  }
  if (source > rhs.source) {
    return false;
  }
  return dest < rhs.dest;
}

/* Used for printing */
std::ostream & operator<<(std::ostream & os, const Route & route) {
  os << "(" << route.source << " -> " << route.dest << ") has total capacity "
     << route.capacity << "\n";
  return os;
}
