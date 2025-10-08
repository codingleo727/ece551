#ifndef PLANET_ITER_TARGET_H
#define PLANET_ITER_TARGET_H
#include "provided.h"
#include "target.h"

launch_result_t solve_launch(const launch_input_t * this_launch,
                             const planet_list_t * planets);

double calculate_launch_travel_time(point_t src_position,
                                    point_t dest_position,
                                    double velocity);

double compute_launch_angle(point_t src_position, point_t dest_position);

double compute_dist_to_des(point_t ship_pos, point_t dest_planet_pos);

#endif
