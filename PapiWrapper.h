#include <stdio.h>
#include <stdlib.h>
#include <papi.h>
#include <math.h>

static const size_t EVENT_COUNT = 2;
static int events[] = { PAPI_TOT_INS, PAPI_FP_OPS };
static long long values[EVENT_COUNT];

static inline void papiSetup()
{

  if (PAPI_VER_CURRENT != PAPI_library_init(PAPI_VER_CURRENT))
  {
     std::cerr << "PAPI_library_init error." << std::endl;
     exit(1);
  }

//const size_t EVENT_MAX = PAPI_num_counters();
//printf("# Max counters = %zd\n", EVENT_MAX);

  if (PAPI_OK != PAPI_query_event(PAPI_TOT_INS))
  {
     std::cerr << "Cannot count PAPI_TOT_INS." << std::endl;
     exit(1);
  }

  if (PAPI_OK != PAPI_query_event(PAPI_FP_OPS))
  {
     std::cerr << "Cannot count PAPI_FP_OPS." << std::endl;
     exit(1);
  }

}

static inline void papiStart()
{

  PAPI_start_counters(events, EVENT_COUNT);
  if(PAPI_OK != PAPI_read_counters(values, EVENT_COUNT))
  {
     std::cerr << "Problem reading counters." << std::endl;
     exit(1);
  }
}

static inline void papiFinish()
{
  if(PAPI_OK != PAPI_read_counters(values, EVENT_COUNT))
  {
     std::cerr << "Problem reading counters." << std::endl;
     exit(1);
  }
}

static inline void papiPrintResults()
{
  const size_t EVENT_MAX = PAPI_num_counters();
  printf("# Max counters = %zd\n", EVENT_MAX);

  printf("Number of instructions = %lld\n",values[0]);
  printf("Number of fp operations = %lld\n",values[1]);
}

