#include "gtest/gtest.h"

static uint32_t mock_time_ms;

extern "C"
{
  #include "Sm1.h"

  uint32_t get_time_ms(void)
  {
    return mock_time_ms;
  }
}


class TestFixture : public ::testing::Test
{
protected:
  Sm1 sm = {};

  TestFixture()
  {
    Sm1_instance_init(&sm);
  }

  void setup_time()
  {

  }
};


TEST_F(TestFixture, basic) {

  uint32_t current_time = mock_time_ms;
  uint32_t last_run_time = sm.vars.current_time;

  sm.vars.step_duration = current_time - last_run_time;
  sm.vars.current_time = current_time;

  ASSERT_EQ(Sm1_StateId__DISABLED, sm.state_id);


  Sm1_dispatch_event(&sm, Sm1_EventId__DO);

  ASSERT_EQ(Sm1_StateId__DISABLED, sm.state_id);
}
