/* Initialization */
#include "SimpleThermalMVP_model.h"
#include "SimpleThermalMVP_11mix.h"
#include "SimpleThermalMVP_12jac.h"
#if defined(__cplusplus)
extern "C" {
#endif

void SimpleThermalMVP_functionInitialEquations_0(DATA *data, threadData_t *threadData);
extern void SimpleThermalMVP_eqFunction_7(DATA *data, threadData_t *threadData);


/*
equation index: 2
type: SIMPLE_ASSIGN
roomTemp = $START.roomTemp
*/
void SimpleThermalMVP_eqFunction_2(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* roomTemp STATE(1) */) = (data->modelData->realVarsData[0] /* roomTemp STATE(1) */).attribute .start;
  threadData->lastEquationSolved = 2;
  TRACE_POP
}
extern void SimpleThermalMVP_eqFunction_6(DATA *data, threadData_t *threadData);

extern void SimpleThermalMVP_eqFunction_5(DATA *data, threadData_t *threadData);

OMC_DISABLE_OPT
void SimpleThermalMVP_functionInitialEquations_0(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  static void (*const eqFunctions[4])(DATA*, threadData_t*) = {
    SimpleThermalMVP_eqFunction_7,
    SimpleThermalMVP_eqFunction_2,
    SimpleThermalMVP_eqFunction_6,
    SimpleThermalMVP_eqFunction_5
  };
  
  for (int id = 0; id < 4; id++) {
    eqFunctions[id](data, threadData);
  }
  TRACE_POP
}

int SimpleThermalMVP_functionInitialEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->discreteCall = 1;
  SimpleThermalMVP_functionInitialEquations_0(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
  TRACE_POP
  return 0;
}

/* No SimpleThermalMVP_functionInitialEquations_lambda0 function */

int SimpleThermalMVP_functionRemovedInitialEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int *equationIndexes = NULL;
  double res = 0.0;

  
  TRACE_POP
  return 0;
}


#if defined(__cplusplus)
}
#endif
