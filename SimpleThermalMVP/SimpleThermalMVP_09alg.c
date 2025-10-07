/* Algebraic */
#include "SimpleThermalMVP_model.h"

#ifdef __cplusplus
extern "C" {
#endif

/* forwarded equations */
extern void SimpleThermalMVP_eqFunction_6(DATA* data, threadData_t *threadData);
extern void SimpleThermalMVP_eqFunction_7(DATA* data, threadData_t *threadData);

static void functionAlg_system0(DATA *data, threadData_t *threadData)
{
  static void (*const eqFunctions[2])(DATA*, threadData_t*) = {
    SimpleThermalMVP_eqFunction_6,
    SimpleThermalMVP_eqFunction_7
  };
  
  for (int id = 0; id < 2; id++) {
    eqFunctions[id](data, threadData);
  }
}
/* for continuous time variables */
int SimpleThermalMVP_functionAlgebraics(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_ALGEBRAICS);
#endif
  data->simulationInfo->callStatistics.functionAlgebraics++;

  SimpleThermalMVP_function_savePreSynchronous(data, threadData);
  
  functionAlg_system0(data, threadData);

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_ALGEBRAICS);
#endif

  TRACE_POP
  return 0;
}

#ifdef __cplusplus
}
#endif
