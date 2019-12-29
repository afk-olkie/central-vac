/************************************************************************************************
* @file
* 
* @brief     State machine "Sm1"
*            Auto generated from file: ./Sm1.graphml
* 
* @copyright Copyright (c) 2019 JCA Electronics, Winnipeg, MB.
*            All rights reserved.
* 
************************************************************************************************/

#pragma once
#include <stdint.h>
#include <stdbool.h>

#include "params.h"


/************************************************************************************************
* Enumeration for all Sm1 state IDs
************************************************************************************************/
typedef enum Sm1_StateId
{
  Sm1_StateId__ROOT,
  Sm1_StateId__DISABLED,
  Sm1_StateId__ENABLED,
  Sm1_StateId__TIMED_OFF,
  Sm1_StateId__DEC_TIMEOUT,
  Sm1_StateId__OFF_READY,
  Sm1_StateId__ON,
  Sm1_StateId__DISABLED_BAD_SWITCH,
  //--------------------------
  Sm1_StateCount,
} Sm1_StateId;



/************************************************************************************************
* Enumeration for all Sm1 input event IDs
************************************************************************************************/
typedef enum Sm1_EventId
{
  Sm1_EventId__DO,
} Sm1_EventId;




/************************************************************************************************
* STRUCT for Sm1 variables 
************************************************************************************************/
typedef struct Sm1_Vars
{

  uint32_t state_entered_at;      //ms
  int32_t cool_down_duration;     //ms
  int32_t onoff_time_left;        //ms
  int32_t enable_time_left;       //ms
  bool relay_output;              //active high
  uint32_t step_duration;         //ms
  uint32_t current_time;         //ms

} Sm1_Vars;



/************************************************************************************************
* STRUCT for Sm1 
************************************************************************************************/
typedef struct Sm1
{
  bool event_handled;
  Sm1_StateId state_id;

  Sm1_Vars vars;
} Sm1;


/************************************************************************************************
* public functions
************************************************************************************************/
void Sm1_instance_init(Sm1* sm);
const char* Sm1_InputEvent_to_string(Sm1_EventId event_id);
void Sm1_dispatch_event(Sm1* sm, Sm1_EventId event_id);
