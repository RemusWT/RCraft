#ifndef rcf_basic_h

/*
  remus config file, in case you were wondering.
  In rcf_basic we are going to only provide functions that retrieve certain values from certain variables.
  rcf_fetch_xvalue(variable_name)
  Strongly recommend error checking these functions.
  rcf_fetch_ivalue returns 0 in case of errors.
  rcf_fetch_fvalue returns 0.0f in case of errors.
  rcf_fetch_svalue returns NULL in case of errors.
  
 */

#define rcf_basic_h

#include "basic_types.h"



// We might want to add rcf_fetch_boolean function.
int         rcf_fetch_ivalue(std::string data, const char* variable_name);
float       rcf_fetch_fvalue(std::string data, const char* variable_name);
std::string rcf_fetch_svalue(std::string data, const char* variable_name);
bool        rcf_fetch_bvalue(std::string data, const char* variable_name);







#endif
