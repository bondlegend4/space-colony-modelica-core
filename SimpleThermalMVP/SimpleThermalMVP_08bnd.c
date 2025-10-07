/* update bound parameters and variable attributes (start, nominal, min, max) */
#include "SimpleThermalMVP_model.h"
#if defined(__cplusplus)
extern "C" {
#endif


/*
equation index: 8
type: SIMPLE_ASSIGN
$START.roomTemp = ambientTemp
*/
static void SimpleThermalMVP_eqFunction_8(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,8};
  (data->modelData->realVarsData[0] /* roomTemp STATE(1) */).attribute .start = (data->simulationInfo->realParameter[0] /* ambientTemp PARAM */);
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* roomTemp STATE(1) */) = (data->modelData->realVarsData[0] /* roomTemp STATE(1) */).attribute .start;
    infoStreamPrint(OMC_LOG_INIT_V, 0, "updated start value: %s(start=%g)", data->modelData->realVarsData[0].info /* roomTemp */.name, (modelica_real) (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* roomTemp STATE(1) */));
  threadData->lastEquationSolved = 8;
  TRACE_POP
}
OMC_DISABLE_OPT
int SimpleThermalMVP_updateBoundVariableAttributes(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  /* min ******************************************************** */
  infoStreamPrint(OMC_LOG_INIT, 1, "updating min-values");
  if (OMC_ACTIVE_STREAM(OMC_LOG_INIT)) messageClose(OMC_LOG_INIT);
  
  /* max ******************************************************** */
  infoStreamPrint(OMC_LOG_INIT, 1, "updating max-values");
  if (OMC_ACTIVE_STREAM(OMC_LOG_INIT)) messageClose(OMC_LOG_INIT);
  
  /* nominal **************************************************** */
  infoStreamPrint(OMC_LOG_INIT, 1, "updating nominal-values");
  if (OMC_ACTIVE_STREAM(OMC_LOG_INIT)) messageClose(OMC_LOG_INIT);
  
  /* start ****************************************************** */
  infoStreamPrint(OMC_LOG_INIT, 1, "updating primary start-values");
  SimpleThermalMVP_eqFunction_8(data, threadData);
  if (OMC_ACTIVE_STREAM(OMC_LOG_INIT)) messageClose(OMC_LOG_INIT);
  
  TRACE_POP
  return 0;
}

OMC_DISABLE_OPT
int SimpleThermalMVP_updateBoundParameters(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  TRACE_POP
  return 0;
}

#if defined(__cplusplus)
}
#endif
