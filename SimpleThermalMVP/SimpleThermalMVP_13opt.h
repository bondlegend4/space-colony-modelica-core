#if defined(__cplusplus)
  extern "C" {
#endif
  int SimpleThermalMVP_mayer(DATA* data, modelica_real** res, short*);
  int SimpleThermalMVP_lagrange(DATA* data, modelica_real** res, short *, short *);
  int SimpleThermalMVP_getInputVarIndicesInOptimization(DATA* data, int* input_var_indices);
  int SimpleThermalMVP_pickUpBoundsForInputsInOptimization(DATA* data, modelica_real* min, modelica_real* max, modelica_real*nominal, modelica_boolean *useNominal, char ** name, modelica_real * start, modelica_real * startTimeOpt);
  int SimpleThermalMVP_setInputData(DATA *data, const modelica_boolean file);
  int SimpleThermalMVP_getTimeGrid(DATA *data, modelica_integer * nsi, modelica_real**t);
#if defined(__cplusplus)
}
#endif
