#include "planet_util.h"

#include <stdio.h>
#include <string.h>

#include "provided.h"

point_t get_location_at(const planet_t * p, double time) {
  // Step 2: WRITE THIS
  point_t location;
  double angular_velocity = (2 * M_PI) / p->year_len;
  double raw_angle = p->init_pos + angular_velocity * time;
  double angle_at_time = fmod(raw_angle, 2 * M_PI);
  if (angle_at_time < 0) {
    angle_at_time += 2 * M_PI;
  }

  location.x = p->orbital_radius * cos(angle_at_time);
  location.y = p->orbital_radius * sin(angle_at_time);

  return location;
}
planet_t * find_planet(const planet_list_t * lst, const char * name) {
  //Step 2: WRITE THIS
  for (size_t i = 0; i < lst->num_planets; i++) {
    planet_t * planet = lst->planets[i];
    if (planet && strcmp(planet->name, name) == 0) {
      return planet;
    }
  }
  fprintf(stderr, "Planet not found\n");
  exit(EXIT_FAILURE);
}
