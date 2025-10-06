#include "myinput.h"

#include <stdio.h>

void parse_planet_info(planet_t * planet, char * line) {
  //STEP 1: Write this
  char * p = line;
  int name_len = 0;

  if (*p == ':' || *p == '\0') {
    fprintf(stderr, "Missing field for planet name\n");
    exit(EXIT_FAILURE);
  }

  // For name
  while (*p != ':' && *p != '\n') {
    planet->name[name_len] = *p;
    name_len++;
    p++;
  }

  if (name_len > 31) {
    fprintf(stderr, "Name length exceeds maximum length allowed\n");
    exit(EXIT_FAILURE);
  }
  else {
    if ((*p == ':' && *(p + 1) == '\n') || *(p + 1) == '\0') {
      fprintf(stderr,
              "Missing fields for orbital radius, year length, and initial position\n");
      exit(EXIT_FAILURE);
    }
    p++;
    planet->name[name_len] = '\0';
  }

  // For orbital radius
  int j = 0;
  char orbital[132];
  int decimal_orbital = 0;

  if (*p == ':') {
    fprintf(stderr, "Missing field for orbital radius\n");
    exit(EXIT_FAILURE);
  }

  while (*p != ':' && *p != '\n') {
    if (!((*p >= '0' && *p <= '9') || *p == '.')) {
      fprintf(stderr, "Please only enter a valid number for the orbital radius\n");
      exit(EXIT_FAILURE);
    }
    if (*p == '.') {
      decimal_orbital++;
    }
    if (decimal_orbital > 1) {
      fprintf(stderr, "Please only use one decimal for the orbital radius\n");
      exit(EXIT_FAILURE);
    }
    orbital[j] = *p;
    j++;
    p++;
  }
  if ((*p == ':' && *(p + 1) == '\n') || *(p + 1) == '\0') {
    fprintf(stderr, "Missing fields for year length and initial position\n");
    exit(EXIT_FAILURE);
  }
  p++;
  orbital[j] = '\0';
  double orbital_num = atof(orbital);
  planet->orbital_radius = orbital_num;

  // For year length
  int k = 0;
  char year_length[132];
  int decimal_year = 0;

  if (*p == ':') {
    fprintf(stderr, "Missing field for year length\n");
    exit(EXIT_FAILURE);
  }

  while (*p != ':' && *p != '\n') {
    if (!((*p >= '0' && *p <= '9') || *p == '.')) {
      fprintf(stderr, "Please only enter a valid number for the year length\n");
      exit(EXIT_FAILURE);
    }
    if (*p == '.') {
      decimal_year++;
    }
    if (decimal_year > 1) {
      fprintf(stderr, "Please only use one decimal for the year length\n");
      exit(EXIT_FAILURE);
    }
    year_length[k] = *p;
    k++;
    p++;
  }
  if ((*p == ':' && *(p + 1) == '\n') || *(p + 1) == '\0') {
    fprintf(stderr, "Missing field for initial position\n");
    exit(EXIT_FAILURE);
  }
  p++;
  year_length[k] = '\0';
  double year_num = atof(year_length);
  planet->year_len = year_num;

  // For initial position
  int l = 0;
  char pos[132];
  int decimal_pos = 0;
  while (*p != '\0' && *p != '\n') {
    if (!((*p >= '0' && *p <= '9') || *p == '.')) {
      fprintf(stderr, "Please only enter a valid number for the initial position\n");
      exit(EXIT_FAILURE);
    }
    if (*p == '.') {
      decimal_pos++;
    }
    if (decimal_pos > 1) {
      fprintf(stderr, "Please only use one decimal for the initial position\n");
      exit(EXIT_FAILURE);
    }
    pos[l] = *p;
    l++;
    p++;
  }
  pos[l] = '\0';
  double initial_pos = atof(pos);
  double init_pos_converted = initial_pos * (M_PI / 180);
  planet->init_pos = init_pos_converted;
}
