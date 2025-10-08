#include "iter_target.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

double calculate_launch_travel_time(point_t src_position,
                                    point_t dest_position,
                                    double velocity) {
  double dis_to_travel = sqrt(pow(dest_position.x - src_position.x, 2) +
                              pow(dest_position.y - src_position.y, 2));
  return dis_to_travel / velocity;
}

double compute_launch_angle(point_t src_position, point_t dest_position) {
  double dx = dest_position.x - src_position.x;
  double dy = dest_position.y - src_position.y;
  double launch_angle = atan(dy / dx);
  if (dx < 0) {
    launch_angle += M_PI;
  }
  launch_angle = fmod(launch_angle, 2 * M_PI);
  if (launch_angle < 0) {
    launch_angle += 2 * M_PI;
  }

  return launch_angle;
}

double compute_dist_to_des(point_t ship_pos, point_t dest_planet_pos) {
  return sqrt(pow(dest_planet_pos.x - ship_pos.x, 2) +
              pow(dest_planet_pos.y - ship_pos.y, 2));
}

launch_result_t solve_launch(const launch_input_t * this_launch,
                             const planet_list_t * planets) {
  //STEP 4: write this function
  launch_result_t result;
  planet_t * src_planet = find_planet(planets, this_launch->src);
  planet_t * dest_planet = find_planet(planets, this_launch->dest);

  point_t src_pos = get_location_at(src_planet, this_launch->time);
  double travel_time = 0;
  double wait_time = INFINITY;

  for (uint64_t i = 0; i < this_launch->max_iterations; i++) {
    point_t altered_dest_pos =
        get_location_at(dest_planet, this_launch->time + travel_time);
    double launch_angle = compute_launch_angle(src_pos, altered_dest_pos);
    travel_time =
        calculate_launch_travel_time(src_pos, altered_dest_pos, this_launch->speed);

    point_t dest_planet_pos_after_time =
        get_location_at(dest_planet, this_launch->time + travel_time);
    double dist_from_ship =
        compute_dist_to_des(altered_dest_pos, dest_planet_pos_after_time);

    if (dist_from_ship <= this_launch->close_enough) {
      result.theta = launch_angle;
      result.duration = travel_time;
      return result;
    }

    double new_wait_time =
        when_does_planet_return_to(
            dest_planet, altered_dest_pos, this_launch->time + travel_time) -
        (this_launch->time + travel_time);

    if (new_wait_time < wait_time) {
      wait_time = new_wait_time;
      result.theta = launch_angle;
      result.duration = travel_time;
    }
  }

  return result;
}
