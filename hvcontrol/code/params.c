#include "params.h"

//global vars
struct params params;




//noInterrupts()
//interrupts();

bool pop_xable_if_req(enum XableRequest matching_req)
{
  if (params.requests.current.xable_request)
  {
    params.requests.current.xable_request = XableRequest_NONE;
    return true;
  }

  return false;
}

bool pop_onoff_if_req(enum OnOffRequest matching_req)
{
  if (params.requests.current.on_off_request == matching_req)
  {
    params.requests.current.on_off_request = OnOffRequest_NONE;
    return true;
  }

  return false;
}

void dec_duration_by(int32_t * const time_ms, int32_t amount_ms)
{
  *time_ms -= amount_ms;
  if (*time_ms < 0)
  {
    *time_ms = 0;
  }
}
