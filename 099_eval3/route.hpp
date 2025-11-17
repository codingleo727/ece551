#ifndef ROUTE_HPP
#define ROUTE_HPP

#include <ostream>
#include <string>

class Route {
 private:
  std::string source;
  std::string dest;
  unsigned capacity;

 public:
  Route();
  Route(std::string source_, std::string dest_, unsigned capacity_);
  const std::string & get_source() const;
  const std::string & get_dest() const;
  unsigned get_capacity() const;
  void update_capacity(unsigned extra_capacity);
  bool operator==(const Route & rhs) const;
  bool operator<(const Route & rhs) const;
  friend std::ostream & operator<<(std::ostream & os, const Route & route);
};

#endif
