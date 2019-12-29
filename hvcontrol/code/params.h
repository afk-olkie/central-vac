#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

enum XableRequest {
  XableRequest_NONE,
  XableRequest_ENABLE,
  XableRequest_DISABLE,
};

enum OnOffRequest {
  OnOffRequest_NONE,
  OnOffRequest_ON,
  OnOffRequest_OFF,
};

struct Requests {
  enum XableRequest xable_request;
  int32_t xable_request_duration;

  enum OnOffRequest on_off_request;
  int32_t on_off_request_duration;
};

struct params {
  struct 
  {
    /**
     * must access atomic! set by receive handler, cleared by state machine.
     */
    struct Requests next;

    /**
     * values used by state machine.
     */
    struct Requests current;
  } requests;

};

extern struct params params;

bool pop_xable_if_req(enum XableRequest matching_req);
bool pop_onoff_if_req(enum OnOffRequest matching_req);
void dec_duration_by(int32_t * const time_ms, int32_t amount_ms);



