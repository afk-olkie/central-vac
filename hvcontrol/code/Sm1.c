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

#include "Sm1.h"
#include <string.h>

#define COUNTOF(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))

typedef void(*Sm1_EventHandler)(Sm1* sm, Sm1_EventId event_id);

#define PARENT_HANDLER_BOOKMARK(parent_handler) //allows an IDE to jump to function. nothing else

static void exit_upto(Sm1* sm, Sm1_StateId stop_before_exiting);
static void exit_state(Sm1* sm, Sm1_StateId state_id);
static void enter_chain(Sm1* sm, Sm1_StateId *state_ids, uint16_t chain_length);
static void enter_state(Sm1* sm, Sm1_StateId state_id);
static Sm1_StateId get_parent_id(Sm1_StateId state_id);




/************************************************************************************************
* CUSTOM FUNCTIONS
************************************************************************************************/



/************************************************************************************************
* Handler Prototypes for Sm1
************************************************************************************************/
static void ROOT_event_handler               (Sm1 *sm, Sm1_EventId event_id);
static void DISABLED_event_handler           (Sm1 *sm, Sm1_EventId event_id);
static void ENABLED_event_handler            (Sm1 *sm, Sm1_EventId event_id);
static void TIMED_OFF_event_handler          (Sm1 *sm, Sm1_EventId event_id);
static void DEC_TIMEOUT_event_handler        (Sm1 *sm, Sm1_EventId event_id);
static void OFF_READY_event_handler          (Sm1 *sm, Sm1_EventId event_id);
static void ON_event_handler                 (Sm1 *sm, Sm1_EventId event_id);
static void DISABLED_BAD_SWITCH_event_handler(Sm1 *sm, Sm1_EventId event_id);


/************************************************************************************************
* Parent mapping for all Sm1 state IDs
************************************************************************************************/
static const Sm1_StateId parent_mapping[Sm1_StateCount] = {
  [Sm1_StateId__ROOT]                = Sm1_StateId__ROOT,
  [Sm1_StateId__DISABLED]            = Sm1_StateId__ROOT,
  [Sm1_StateId__ENABLED]             = Sm1_StateId__ROOT,
  [Sm1_StateId__TIMED_OFF]           = Sm1_StateId__ENABLED,
  [Sm1_StateId__DEC_TIMEOUT]         = Sm1_StateId__ENABLED,
  [Sm1_StateId__OFF_READY]           = Sm1_StateId__DEC_TIMEOUT,
  [Sm1_StateId__ON]                  = Sm1_StateId__DEC_TIMEOUT,
  [Sm1_StateId__DISABLED_BAD_SWITCH] = Sm1_StateId__ROOT,
};


/************************************************************************************************
* Parent mapping for all Sm1 state IDs
************************************************************************************************/
static const Sm1_EventHandler state_handlers[Sm1_StateCount] = {
  [Sm1_StateId__ROOT]                = ROOT_event_handler,
  [Sm1_StateId__DISABLED]            = DISABLED_event_handler,
  [Sm1_StateId__ENABLED]             = ENABLED_event_handler,
  [Sm1_StateId__TIMED_OFF]           = TIMED_OFF_event_handler,
  [Sm1_StateId__DEC_TIMEOUT]         = DEC_TIMEOUT_event_handler,
  [Sm1_StateId__OFF_READY]           = OFF_READY_event_handler,
  [Sm1_StateId__ON]                  = ON_event_handler,
  [Sm1_StateId__DISABLED_BAD_SWITCH] = DISABLED_BAD_SWITCH_event_handler,
};


static void ROOT_event_handler(Sm1 *sm, Sm1_EventId event_id)
{
  //TODO copy paste in entry and exit code in comments
    
  // if true
  if ((true)){ 
    if (event_id != Sm1_EventId__DO) {
        sm->event_handled = true;  //done before action code to allow action code to allow bubbling
    }
      
    sm->event_handled = true; //for loop efficiency; 
  }

}

static void DISABLED_event_handler(Sm1 *sm, Sm1_EventId event_id)
{
  //TODO copy paste in entry and exit code in comments
    
  // if enabled_req
  if (((params.requests.current.xable_request == XableRequest_ENABLE))){  
    //transitioning from DISABLED to TIMED_OFF
    exit_upto(sm, Sm1_StateId__ROOT);

    //enter states
    Sm1_StateId states_to_enter[] = {
      Sm1_StateId__ENABLED,
      Sm1_StateId__TIMED_OFF
    };
    enter_chain(sm, states_to_enter, COUNTOF(states_to_enter));

    sm->event_handled = true;
    return; //stop processing because it transitioned
  }

}

static void ENABLED_event_handler(Sm1 *sm, Sm1_EventId event_id)
{
  //TODO copy paste in entry and exit code in comments
    
  // if pop_xable_if_req_enable()
  if ((pop_xable_if_req(XableRequest_ENABLE))){ 
    if (event_id != Sm1_EventId__DO) {
        sm->event_handled = true;  //done before action code to allow action code to allow bubbling
    }
      
    (sm->vars.enable_time_left = params.requests.current.xable_request_duration); 
  }

  //ON DO
  if (event_id == Sm1_EventId__DO){ 
    if (event_id != Sm1_EventId__DO) {
        sm->event_handled = true;  //done before action code to allow action code to allow bubbling
    }
      
    (dec_duration_by(&sm->vars.onoff_time_left, sm->vars.step_duration)); (dec_duration_by(&sm->vars.enable_time_left, sm->vars.step_duration)); 
  }

  // if pop_xable_if_req_disable() OR enabled_timed_out
  if ((pop_xable_if_req(XableRequest_DISABLE) ||
(sm->vars.enable_time_left <= 0))){  
    //transitioning from ENABLED to DISABLED
    exit_upto(sm, Sm1_StateId__ROOT);

    //enter states
    Sm1_StateId states_to_enter[] = {
      Sm1_StateId__DISABLED
    };
    enter_chain(sm, states_to_enter, COUNTOF(states_to_enter));

    sm->event_handled = true;
    return; //stop processing because it transitioned
  }

  // if cool_down_duration > secs(15)
  if ((sm->vars.cool_down_duration > (15*1000))){  
    //transitioning from ENABLED to DISABLED_BAD_SWITCH
    exit_upto(sm, Sm1_StateId__ROOT);

    //enter states
    Sm1_StateId states_to_enter[] = {
      Sm1_StateId__DISABLED_BAD_SWITCH
    };
    enter_chain(sm, states_to_enter, COUNTOF(states_to_enter));

    sm->event_handled = true;
    return; //stop processing because it transitioned
  }

}

static void TIMED_OFF_event_handler(Sm1 *sm, Sm1_EventId event_id)
{
  //TODO copy paste in entry and exit code in comments
    
  // if onoff_timed_out
  if (((sm->vars.onoff_time_left <= 0))){  
    //transitioning from TIMED_OFF to OFF_READY
    exit_upto(sm, Sm1_StateId__ENABLED);

    //enter states
    Sm1_StateId states_to_enter[] = {
      Sm1_StateId__DEC_TIMEOUT,
      Sm1_StateId__OFF_READY
    };
    enter_chain(sm, states_to_enter, COUNTOF(states_to_enter));

    sm->event_handled = true;
    return; //stop processing because it transitioned
  }

}

static void DEC_TIMEOUT_event_handler(Sm1 *sm, Sm1_EventId event_id)
{
  //TODO copy paste in entry and exit code in comments
    
  //ON DO if time_in_state() > secs(30)
  if (event_id == Sm1_EventId__DO && ((sm->vars.current_time - sm->vars.state_entered_at) > (30*1000))){ 
    if (event_id != Sm1_EventId__DO) {
        sm->event_handled = true;  //done before action code to allow action code to allow bubbling
    }
      
    {
      (dec_duration_by(&sm->vars.cool_down_duration, sm->vars.step_duration));
    }; 
  }

}

static void OFF_READY_event_handler(Sm1 *sm, Sm1_EventId event_id)
{
  //TODO copy paste in entry and exit code in comments
    
  // if on_req
  if (((params.requests.current.on_off_request == OnOffRequest_ON))){  
    //transitioning from OFF_READY to ON
    exit_upto(sm, Sm1_StateId__DEC_TIMEOUT);

    //enter states
    Sm1_StateId states_to_enter[] = {
      Sm1_StateId__ON
    };
    enter_chain(sm, states_to_enter, COUNTOF(states_to_enter));

    sm->event_handled = true;
    return; //stop processing because it transitioned
  }

}

static void ON_event_handler(Sm1 *sm, Sm1_EventId event_id)
{
  //TODO copy paste in entry and exit code in comments
    
  // if pop_onoff_if_req_on()
  if ((pop_onoff_if_req(OnOffRequest_ON))){ 
    if (event_id != Sm1_EventId__DO) {
        sm->event_handled = true;  //done before action code to allow action code to allow bubbling
    }
      
    (sm->vars.onoff_time_left = params.requests.current.on_off_request_duration); 
  }

  // if pop_onoff_if_req_off() OR onoff_timed_out
  if ((pop_onoff_if_req(OnOffRequest_OFF) ||
(sm->vars.onoff_time_left <= 0))){  
    //transitioning from ON to TIMED_OFF
    exit_upto(sm, Sm1_StateId__ENABLED);

    //enter states
    Sm1_StateId states_to_enter[] = {
      Sm1_StateId__TIMED_OFF
    };
    enter_chain(sm, states_to_enter, COUNTOF(states_to_enter));

    sm->event_handled = true;
    return; //stop processing because it transitioned
  }

}

static void DISABLED_BAD_SWITCH_event_handler(Sm1 *sm, Sm1_EventId event_id)
{
  //TODO copy paste in entry and exit code in comments
    
}


/************************************************************************************************
* Public constructor function for Sm1 state machine
************************************************************************************************/
void Sm1_instance_init(Sm1* sm)
{
  enter_state(sm, Sm1_StateId__ROOT);
  Sm1_StateId states_to_enter[] = {
    Sm1_StateId__DISABLED
  };
  enter_chain(sm, states_to_enter, COUNTOF(states_to_enter));
}


/************************************************************************************************
* TODO Sm1 
************************************************************************************************/
static void enter_state(Sm1* sm, Sm1_StateId state_id)
{
  switch(state_id)
  {
    case Sm1_StateId__ROOT:
      break;

    case Sm1_StateId__DISABLED:
      //rec_entry_time();
      (sm->vars.state_entered_at = sm->vars.current_time);
      //clear_requests();
      params.requests.current.on_off_request = OnOffRequest_NONE; params.requests.current.xable_request = XableRequest_NONE;
      break;

    case Sm1_StateId__ENABLED:
      break;

    case Sm1_StateId__TIMED_OFF:
      //{ 
      //  rec_entry_time();
      //  cool_down_duration += secs(2);
      //  //clamp(cool_down_duration, secs(4), secs(30));
      //  set_onoff_timeout_dur(cool_down_duration);
      //}
      { 
        (sm->vars.state_entered_at = sm->vars.current_time);
        sm->vars.cool_down_duration += (2*1000);
        //clamp(cool_down_duration, secs(4), secs(30));
        (sm->vars.onoff_time_left = sm->vars.cool_down_duration);
      };
      break;

    case Sm1_StateId__DEC_TIMEOUT:
      break;

    case Sm1_StateId__OFF_READY:
      //rec_entry_time();
      (sm->vars.state_entered_at = sm->vars.current_time);
      break;

    case Sm1_StateId__ON:
      //rec_entry_time();
      (sm->vars.state_entered_at = sm->vars.current_time);
      //turn_on_output()
      sm->vars.relay_output = true;
      break;

    case Sm1_StateId__DISABLED_BAD_SWITCH:
      //rec_entry_time();
      (sm->vars.state_entered_at = sm->vars.current_time);
      break;
  }
};


/************************************************************************************************
* TODO Sm1 
************************************************************************************************/
static void exit_state(Sm1* sm, Sm1_StateId state_id)
{
  switch(state_id)
  {
    case Sm1_StateId__ROOT:
      break;

    case Sm1_StateId__DISABLED:
      break;

    case Sm1_StateId__ENABLED:
      break;

    case Sm1_StateId__TIMED_OFF:
      break;

    case Sm1_StateId__DEC_TIMEOUT:
      break;

    case Sm1_StateId__OFF_READY:
      break;

    case Sm1_StateId__ON:
      //turn_off_output()
      sm->vars.relay_output = false;
      break;

    case Sm1_StateId__DISABLED_BAD_SWITCH:
      break;
  }
};



/************************************************************************************************
* Function that translates a custom input event ID to a string
* NOTE: actual passed in enum values should be from 'Sm1_EventId'
************************************************************************************************/
const char* Sm1_InputEvent_to_string(Sm1_EventId event_id)
{
  const char * str;
  switch(event_id)
  {
    //no custom input events defined for this state machine
    default: str = "??CUSTOM"; break;
  }

  return str;
}


void Sm1_dispatch_event(Sm1* sm, Sm1_EventId event_id)
{
    Sm1_StateId state_id_to_rx_event = sm->state_id;
    sm->event_handled = false;

    do
    {
        Sm1_EventHandler event_handler = state_handlers[state_id_to_rx_event];
        event_handler(sm, event_id);
        state_id_to_rx_event = get_parent_id(state_id_to_rx_event);
    }
    while(!sm->event_handled);
}


static void enter_chain(Sm1* sm, Sm1_StateId *state_ids, uint16_t chain_length)
{
    for(uint16_t i = 0; i < chain_length; i++)
    {
        Sm1_StateId to_enter = state_ids[i];
        enter_state(sm, to_enter);
        sm->state_id = to_enter;
    }
}


static Sm1_StateId get_parent_id(Sm1_StateId state_id)
{
    Sm1_StateId parent = parent_mapping[state_id];
    return parent;
}


static void exit_upto(Sm1* sm, Sm1_StateId stop_before_exiting)
{
    while(sm->state_id != Sm1_StateId__ROOT && sm->state_id != stop_before_exiting)
    {
        exit_state(sm, sm->state_id);
        sm->state_id = get_parent_id(sm->state_id);
    }
}
