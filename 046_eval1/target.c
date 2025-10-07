#include "target.h"

launch_result_t compute_launch_by_info(const launch_input_t * this_launch,
                                       const planet_list_t * planets) {
  //STEP 3: Write this
  launch_result_t result;
  planet_t * src_planet = find_planet(planets, this_launch->src);
  planet_t * dest_planet = find_planet(planets, this_launch->dest);

  point_t src_pos = get_location_at(src_planet, this_launch->time);
  point_t dest_pos = get_location_at(dest_planet, this_launch->time);
  double dis_to_travel =
      sqrt(pow(dest_pos.x - src_pos.x, 2) + pow(dest_pos.y - src_pos.y, 2));
  double travel_time = dis_to_travel / this_launch->speed;

  double dx = dest_pos.x - src_pos.x;
  double dy = dest_pos.y - src_pos.y;
  double launch_angle = atan(dy / dx);
  if (dx < 0) {
    launch_angle += M_PI;
  }
  launch_angle = fmod(launch_angle, 2 * M_PI);
  if (launch_angle < 0) {
    launch_angle += 2 * M_PI;
  }

  result.theta = launch_angle;
  result.duration = travel_time;

  return result;
}

double when_does_planet_return_to(const planet_t * planet,
                                  point_t pos,
                                  double start_time) {
  //STEP 3: Write this
  point_t planet_pos_at_t0 = get_location_at(planet, start_time);
  double planet_angle_t0 = atan(planet_pos_at_t0.y / planet_pos_at_t0.x);
  if (planet_pos_at_t0.x < 0) {
    planet_angle_t0 += M_PI;
  }
  double current_rocket_angle = atan(pos.y / pos.x);
  if (pos.x < 0) {
    current_rocket_angle += M_PI;
  }
  double angle_diff = current_rocket_angle - planet_angle_t0;
  angle_diff = fmod(angle_diff, 2 * M_PI);
  if (angle_diff < 0) {
    angle_diff += 2 * M_PI;
  }
  double planet_velocity = (2 * M_PI) / planet->year_len;

  return start_time + (angle_diff / planet_velocity);
}
