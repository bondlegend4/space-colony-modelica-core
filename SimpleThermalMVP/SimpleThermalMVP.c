/* Main Simulation File */

#if defined(__cplusplus)
extern "C" {
#endif

#include "SimpleThermalMVP_model.h"
#include "simulation/solver/events.h"

/* FIXME these defines are ugly and hard to read, why not use direct function pointers instead? */
#define prefixedName_performSimulation SimpleThermalMVP_performSimulation
#define prefixedName_updateContinuousSystem SimpleThermalMVP_updateContinuousSystem
#include <simulation/solver/perform_simulation.c.inc>

#define prefixedName_performQSSSimulation SimpleThermalMVP_performQSSSimulation
#include <simulation/solver/perform_qss_simulation.c.inc>


/* dummy VARINFO and FILEINFO */
const VAR_INFO dummyVAR_INFO = omc_dummyVarInfo;

int SimpleThermalMVP_input_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int SimpleThermalMVP_input_function_init(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int SimpleThermalMVP_input_function_updateStartValues(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int SimpleThermalMVP_inputNames(DATA *data, char ** names){
  TRACE_PUSH

  names[0] = (char *) data->modelData->booleanVarsData[0].info.name;
  
  TRACE_POP
  return 0;
}

int SimpleThermalMVP_data_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  TRACE_POP
  return 0;
}

int SimpleThermalMVP_dataReconciliationInputNames(DATA *data, char ** names){
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int SimpleThermalMVP_dataReconciliationUnmeasuredVariables(DATA *data, char ** names)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int SimpleThermalMVP_output_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->outputVars[0] = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* heaterStatus variable */);
  data->simulationInfo->outputVars[1] = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3]] /* temperature variable */);
  
  TRACE_POP
  return 0;
}

int SimpleThermalMVP_setc_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int SimpleThermalMVP_setb_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}


/*
equation index: 5
type: SIMPLE_ASSIGN
$DER.roomTemp = ((if heaterOn then heaterPower else 0.0) + lossCoefficient * (ambientTemp - roomTemp)) / roomCapacity
*/
void SimpleThermalMVP_eqFunction_5(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,5};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* der(roomTemp) STATE_DER */) = DIVISION_SIM(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[0]] /* heaterOn variable */)?(data->simulationInfo->realParameter[1] /* heaterPower PARAM */):0.0) + ((data->simulationInfo->realParameter[2] /* lossCoefficient PARAM */)) * ((data->simulationInfo->realParameter[0] /* ambientTemp PARAM */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* roomTemp STATE(1) */)),(data->simulationInfo->realParameter[3] /* roomCapacity PARAM */),"roomCapacity",equationIndexes);
  threadData->lastEquationSolved = 5;
  TRACE_POP
}

/*
equation index: 6
type: SIMPLE_ASSIGN
temperature = roomTemp
*/
void SimpleThermalMVP_eqFunction_6(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,6};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3]] /* temperature variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* roomTemp STATE(1) */);
  threadData->lastEquationSolved = 6;
  TRACE_POP
}

/*
equation index: 7
type: SIMPLE_ASSIGN
heaterStatus = if heaterOn then 1.0 else 0.0
*/
void SimpleThermalMVP_eqFunction_7(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,7};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* heaterStatus variable */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[0]] /* heaterOn variable */)?1.0:0.0);
  threadData->lastEquationSolved = 7;
  TRACE_POP
}

OMC_DISABLE_OPT
int SimpleThermalMVP_functionDAE(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  int equationIndexes[1] = {0};
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_DAE);
#endif

  data->simulationInfo->needToIterate = 0;
  data->simulationInfo->discreteCall = 1;
  SimpleThermalMVP_functionLocalKnownVars(data, threadData);
  static void (*const eqFunctions[3])(DATA*, threadData_t*) = {
    SimpleThermalMVP_eqFunction_5,
    SimpleThermalMVP_eqFunction_6,
    SimpleThermalMVP_eqFunction_7
  };
  
  for (int id = 0; id < 3; id++) {
    eqFunctions[id](data, threadData);
  }
  data->simulationInfo->discreteCall = 0;
  
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_DAE);
#endif
  TRACE_POP
  return 0;
}


int SimpleThermalMVP_functionLocalKnownVars(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

/* forwarded equations */
extern void SimpleThermalMVP_eqFunction_5(DATA* data, threadData_t *threadData);

static void functionODE_system0(DATA *data, threadData_t *threadData)
{
  static void (*const eqFunctions[1])(DATA*, threadData_t*) = {
    SimpleThermalMVP_eqFunction_5
  };
  
  for (int id = 0; id < 1; id++) {
    eqFunctions[id](data, threadData);
  }
}

int SimpleThermalMVP_functionODE(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_FUNCTION_ODE);
#endif

  
  data->simulationInfo->callStatistics.functionODE++;
  
  SimpleThermalMVP_functionLocalKnownVars(data, threadData);
  functionODE_system0(data, threadData);

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_FUNCTION_ODE);
#endif

  TRACE_POP
  return 0;
}

void SimpleThermalMVP_computeVarIndices(DATA* data, size_t* realIndex, size_t* integerIndex, size_t* booleanIndex, size_t* stringIndex)
{
  TRACE_PUSH

  size_t i_real = 0;
  size_t i_integer = 0;
  size_t i_boolean = 0;
  size_t i_string = 0;

  realIndex[0] = 0;
  integerIndex[0] = 0;
  booleanIndex[0] = 0;
  stringIndex[0] = 0;

  /* temporary fix for https://github.com/OpenModelica/OpenModelica/issues/13999 */
  for (i_real = 0; i_real < data->modelData->nVariablesRealArray + 1; i_real++)
    realIndex[i_real] = i_real;
  for (i_integer = 0; i_integer < data->modelData->nVariablesIntegerArray + 1; i_integer++)
    integerIndex[i_integer] = i_integer;
  for (i_boolean = 0; i_boolean < data->modelData->nVariablesBooleanArray + 1; i_boolean++)
    booleanIndex[i_boolean] = i_boolean;
  for (i_string = 0; i_string < data->modelData->nVariablesStringArray + 1; i_string++)
    stringIndex[i_string] = i_string;

  /* stateVars */
  /* skip for #13999 */
  
  /* derivativeVars */
  /* skip for #13999 */
  
  /* algVars */
  /* skip for #13999 */
  
  /* discreteAlgVars */
  /* skip for #13999 */
  
  /* realOptimizeConstraintsVars */
  /* skip for #13999 */
  
  /* realOptimizeFinalConstraintsVars */
  /* skip for #13999 */
  
  
  /* intAlgVars */
  /* skip for #13999 */
  
  /* boolAlgVars */
  /* skip for #13999 */
  
  /* stringAlgVars */
  /* skip for #13999 */
  
  TRACE_POP
}

/* forward the main in the simulation runtime */
extern int _main_SimulationRuntime(int argc, char **argv, DATA *data, threadData_t *threadData);
extern int _main_OptimizationRuntime(int argc, char **argv, DATA *data, threadData_t *threadData);

#include "SimpleThermalMVP_12jac.h"
#include "SimpleThermalMVP_13opt.h"

struct OpenModelicaGeneratedFunctionCallbacks SimpleThermalMVP_callback = {
  (int (*)(DATA *, threadData_t *, void *)) SimpleThermalMVP_performSimulation,    /* performSimulation */
  (int (*)(DATA *, threadData_t *, void *)) SimpleThermalMVP_performQSSSimulation,    /* performQSSSimulation */
  SimpleThermalMVP_updateContinuousSystem,    /* updateContinuousSystem */
  SimpleThermalMVP_callExternalObjectDestructors,    /* callExternalObjectDestructors */
  NULL,    /* initialNonLinearSystem */
  NULL,    /* initialLinearSystem */
  NULL,    /* initialMixedSystem */
  #if !defined(OMC_NO_STATESELECTION)
  SimpleThermalMVP_initializeStateSets,
  #else
  NULL,
  #endif    /* initializeStateSets */
  SimpleThermalMVP_initializeDAEmodeData,
  SimpleThermalMVP_computeVarIndices,
  SimpleThermalMVP_functionODE,
  SimpleThermalMVP_functionAlgebraics,
  SimpleThermalMVP_functionDAE,
  SimpleThermalMVP_functionLocalKnownVars,
  SimpleThermalMVP_input_function,
  SimpleThermalMVP_input_function_init,
  SimpleThermalMVP_input_function_updateStartValues,
  SimpleThermalMVP_data_function,
  SimpleThermalMVP_output_function,
  SimpleThermalMVP_setc_function,
  SimpleThermalMVP_setb_function,
  SimpleThermalMVP_function_storeDelayed,
  SimpleThermalMVP_function_storeSpatialDistribution,
  SimpleThermalMVP_function_initSpatialDistribution,
  SimpleThermalMVP_updateBoundVariableAttributes,
  SimpleThermalMVP_functionInitialEquations,
  GLOBAL_EQUIDISTANT_HOMOTOPY,
  NULL,
  SimpleThermalMVP_functionRemovedInitialEquations,
  SimpleThermalMVP_updateBoundParameters,
  SimpleThermalMVP_checkForAsserts,
  SimpleThermalMVP_function_ZeroCrossingsEquations,
  SimpleThermalMVP_function_ZeroCrossings,
  SimpleThermalMVP_function_updateRelations,
  SimpleThermalMVP_zeroCrossingDescription,
  SimpleThermalMVP_relationDescription,
  SimpleThermalMVP_function_initSample,
  SimpleThermalMVP_INDEX_JAC_A,
  SimpleThermalMVP_INDEX_JAC_B,
  SimpleThermalMVP_INDEX_JAC_C,
  SimpleThermalMVP_INDEX_JAC_D,
  SimpleThermalMVP_INDEX_JAC_F,
  SimpleThermalMVP_INDEX_JAC_H,
  SimpleThermalMVP_initialAnalyticJacobianA,
  SimpleThermalMVP_initialAnalyticJacobianB,
  SimpleThermalMVP_initialAnalyticJacobianC,
  SimpleThermalMVP_initialAnalyticJacobianD,
  SimpleThermalMVP_initialAnalyticJacobianF,
  SimpleThermalMVP_initialAnalyticJacobianH,
  SimpleThermalMVP_functionJacA_column,
  SimpleThermalMVP_functionJacB_column,
  SimpleThermalMVP_functionJacC_column,
  SimpleThermalMVP_functionJacD_column,
  SimpleThermalMVP_functionJacF_column,
  SimpleThermalMVP_functionJacH_column,
  SimpleThermalMVP_linear_model_frame,
  SimpleThermalMVP_linear_model_datarecovery_frame,
  SimpleThermalMVP_mayer,
  SimpleThermalMVP_lagrange,
  SimpleThermalMVP_getInputVarIndicesInOptimization,
  SimpleThermalMVP_pickUpBoundsForInputsInOptimization,
  SimpleThermalMVP_setInputData,
  SimpleThermalMVP_getTimeGrid,
  SimpleThermalMVP_symbolicInlineSystem,
  SimpleThermalMVP_function_initSynchronous,
  SimpleThermalMVP_function_updateSynchronous,
  SimpleThermalMVP_function_equationsSynchronous,
  SimpleThermalMVP_inputNames,
  SimpleThermalMVP_dataReconciliationInputNames,
  SimpleThermalMVP_dataReconciliationUnmeasuredVariables,
  NULL,
  NULL,
  NULL,
  NULL,
  -1,
  NULL,
  NULL,
  -1

};

#define _OMC_LIT_RESOURCE_0_name_data "SimpleThermalMVP"
#define _OMC_LIT_RESOURCE_0_dir_data "/Users/jose_d_sandoval/Desktop/Brown/School/Other/InfoSec/ICS/Game/v-ics.le/V-ICS/modelica-rust-modbus-server/modelica-rust-ffi/space-colony-modelica-core/SimpleThermalMVP"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_0_name,16,_OMC_LIT_RESOURCE_0_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_0_dir,171,_OMC_LIT_RESOURCE_0_dir_data);

static const MMC_DEFSTRUCTLIT(_OMC_LIT_RESOURCES,2,MMC_ARRAY_TAG) {MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_0_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_0_dir)}};
void SimpleThermalMVP_setupDataStruc(DATA *data, threadData_t *threadData)
{
  assertStreamPrint(threadData,0!=data, "Error while initialize Data");
  threadData->localRoots[LOCAL_ROOT_SIMULATION_DATA] = data;
  data->callback = &SimpleThermalMVP_callback;
  OpenModelica_updateUriMapping(threadData, MMC_REFSTRUCTLIT(_OMC_LIT_RESOURCES));
  data->modelData->modelName = "SimpleThermalMVP";
  data->modelData->modelFilePrefix = "SimpleThermalMVP";
  data->modelData->modelFileName = "SimpleThermalMVP.mo";
  data->modelData->resultFileName = NULL;
  data->modelData->modelDir = "/Users/jose_d_sandoval/Desktop/Brown/School/Other/InfoSec/ICS/Game/v-ics.le/V-ICS/modelica-rust-modbus-server/modelica-rust-ffi/space-colony-modelica-core/SimpleThermalMVP";
  data->modelData->modelGUID = "{9f225c1f-0381-4a36-a0cd-08c23ee0f946}";
  #if defined(OPENMODELICA_XML_FROM_FILE_AT_RUNTIME)
  data->modelData->initXMLData = NULL;
  data->modelData->modelDataXml.infoXMLData = NULL;
  #else
  #if defined(_MSC_VER) /* handle joke compilers */
  {
  /* for MSVC we encode a string like char x[] = {'a', 'b', 'c', '\0'} */
  /* because the string constant limit is 65535 bytes */
  static const char contents_init[] =
    #include "SimpleThermalMVP_init.c"
    ;
  static const char contents_info[] =
    #include "SimpleThermalMVP_info.c"
    ;
    data->modelData->initXMLData = contents_init;
    data->modelData->modelDataXml.infoXMLData = contents_info;
  }
  #else /* handle real compilers */
  data->modelData->initXMLData =
  #include "SimpleThermalMVP_init.c"
    ;
  data->modelData->modelDataXml.infoXMLData =
  #include "SimpleThermalMVP_info.c"
    ;
  #endif /* defined(_MSC_VER) */
  #endif /* defined(OPENMODELICA_XML_FROM_FILE_AT_RUNTIME) */
  data->modelData->modelDataXml.fileName = "SimpleThermalMVP_info.json";
  data->modelData->resourcesDir = NULL;
  data->modelData->runTestsuite = 0;
  data->modelData->nStates = 1;
  data->modelData->nVariablesRealArray = 4;
  data->modelData->nDiscreteReal = 0;
  data->modelData->nVariablesIntegerArray = 0;
  data->modelData->nVariablesBooleanArray = 1;
  data->modelData->nVariablesStringArray = 0;
  data->modelData->nParametersReal = 4;
  data->modelData->nParametersInteger = 0;
  data->modelData->nParametersBoolean = 0;
  data->modelData->nParametersString = 0;
  data->modelData->nInputVars = 1;
  data->modelData->nOutputVars = 2;
  data->modelData->nAliasReal = 0;
  data->modelData->nAliasInteger = 0;
  data->modelData->nAliasBoolean = 0;
  data->modelData->nAliasString = 0;
  data->modelData->nZeroCrossings = 0;
  data->modelData->nSamples = 0;
  data->modelData->nRelations = 0;
  data->modelData->nMathEvents = 0;
  data->modelData->nExtObjs = 0;
  data->modelData->modelDataXml.modelInfoXmlLength = 0;
  data->modelData->modelDataXml.nFunctions = 0;
  data->modelData->modelDataXml.nProfileBlocks = 0;
  data->modelData->modelDataXml.nEquations = 9;
  data->modelData->nMixedSystems = 0;
  data->modelData->nLinearSystems = 0;
  data->modelData->nNonLinearSystems = 0;
  data->modelData->nStateSets = 0;
  data->modelData->nJacobians = 6;
  data->modelData->nOptimizeConstraints = 0;
  data->modelData->nOptimizeFinalConstraints = 0;
  data->modelData->nDelayExpressions = 0;
  data->modelData->nBaseClocks = 0;
  data->modelData->nSpatialDistributions = 0;
  data->modelData->nSensitivityVars = 0;
  data->modelData->nSensitivityParamVars = 0;
  data->modelData->nSetcVars = 0;
  data->modelData->ndataReconVars = 0;
  data->modelData->nSetbVars = 0;
  data->modelData->nRelatedBoundaryConditions = 0;
  data->modelData->linearizationDumpLanguage = OMC_LINEARIZE_DUMP_LANGUAGE_MODELICA;
}

static int rml_execution_failed()
{
  fflush(NULL);
  fprintf(stderr, "Execution failed!\n");
  fflush(NULL);
  return 1;
}


#if defined(__MINGW32__) || defined(_MSC_VER)

#if !defined(_UNICODE)
#define _UNICODE
#endif
#if !defined(UNICODE)
#define UNICODE
#endif

#include <windows.h>
char** omc_fixWindowsArgv(int argc, wchar_t **wargv)
{
  char** newargv;
  /* Support for non-ASCII characters
  * Read the unicode command line arguments and translate it to char*
  */
  newargv = (char**)malloc(argc*sizeof(char*));
  for (int i = 0; i < argc; i++) {
    newargv[i] = omc_wchar_to_multibyte_str(wargv[i]);
  }
  return newargv;
}

#define OMC_MAIN wmain
#define OMC_CHAR wchar_t
#define OMC_EXPORT __declspec(dllexport) extern

#else
#define omc_fixWindowsArgv(N, A) (A)
#define OMC_MAIN main
#define OMC_CHAR char
#define OMC_EXPORT extern
#endif

#if defined(threadData)
#undef threadData
#endif
/* call the simulation runtime main from our main! */
#if defined(OMC_DLL_MAIN_DEFINE)
OMC_EXPORT int omcDllMain(int argc, OMC_CHAR **argv)
#else
int OMC_MAIN(int argc, OMC_CHAR** argv)
#endif
{
  char** newargv = omc_fixWindowsArgv(argc, argv);
  /*
    Set the error functions to be used for simulation.
    The default value for them is 'functions' version. Change it here to 'simulation' versions
  */
  omc_assert = omc_assert_simulation;
  omc_assert_withEquationIndexes = omc_assert_simulation_withEquationIndexes;

  omc_assert_warning_withEquationIndexes = omc_assert_warning_simulation_withEquationIndexes;
  omc_assert_warning = omc_assert_warning_simulation;
  omc_terminate = omc_terminate_simulation;
  omc_throw = omc_throw_simulation;

  int res;
  DATA data;
  MODEL_DATA modelData;
  SIMULATION_INFO simInfo;
  data.modelData = &modelData;
  data.simulationInfo = &simInfo;
  measure_time_flag = 0;
  compiledInDAEMode = 0;
  compiledWithSymSolver = 0;
  MMC_INIT(0);
  omc_alloc_interface.init();
  {
    MMC_TRY_TOP()
  
    MMC_TRY_STACK()
  
    SimpleThermalMVP_setupDataStruc(&data, threadData);
    res = _main_initRuntimeAndSimulation(argc, newargv, &data, threadData);
    if(res == 0) {
      if (omc_flag[FLAG_MOO_OPTIMIZATION]) {
        res = _main_OptimizationRuntime(argc, newargv, &data, threadData);
      } else {
        res = _main_SimulationRuntime(argc, newargv, &data, threadData);
      }
    }
    
    MMC_ELSE()
    rml_execution_failed();
    fprintf(stderr, "Stack overflow detected and was not caught.\nSend us a bug report at https://trac.openmodelica.org/OpenModelica/newticket\n    Include the following trace:\n");
    printStacktraceMessages();
    fflush(NULL);
    return 1;
    MMC_CATCH_STACK()
    
    MMC_CATCH_TOP(return rml_execution_failed());
  }

  fflush(NULL);
  return res;
}

#ifdef __cplusplus
}
#endif


