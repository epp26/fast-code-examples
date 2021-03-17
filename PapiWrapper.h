#include <stdio.h>
#include <stdlib.h>
#include <papi.h>
#include <math.h>

#ifndef MEASURE_CACHE
#define MEASURE_CACHE 1
#endif

static const size_t EVENT_COUNT = 2;
#if MEASURE_CACHE
static int events[] = { PAPI_L1_TCM, PAPI_L2_TCM};
#else
static int events[] = { PAPI_TOT_INS, PAPI_FP_OPS };
#endif
static long long values[EVENT_COUNT];

__attribute__((always_inline))
static inline void papiSetup()
{

  if (PAPI_VER_CURRENT != PAPI_library_init(PAPI_VER_CURRENT))
  {
     std::cerr << "PAPI_library_init error." << std::endl;
     exit(1);
  }

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

  if (PAPI_OK != PAPI_query_event(PAPI_L1_TCM))
  {
     std::cerr << "Cannot count PAPI_L1_TCM." << std::endl;
     exit(1);
  }

  if (PAPI_OK != PAPI_query_event(PAPI_L2_TCM))
  {
     std::cerr << "Cannot count PAPI_L2_TCM." << std::endl;
     exit(1);
  }

}

__attribute__((always_inline))
static inline void papiStart()
{

  PAPI_start_counters(events, EVENT_COUNT);
  if(PAPI_OK != PAPI_read_counters(values, EVENT_COUNT))
  {
     std::cerr << "Problem reading counters." << std::endl;
//   exit(1);
  }
}

__attribute__((always_inline))
static inline void papiFinish()
{
  if(PAPI_OK != PAPI_read_counters(values, EVENT_COUNT))
  {
     std::cerr << "Problem reading counters." << std::endl;
//   exit(1);
  }
}

__attribute__((always_inline))
static inline void papiPrintResults()
{
  const size_t EVENT_MAX = PAPI_num_counters();
  printf("# Max counters = %zd\n", EVENT_MAX);

#if MEASURE_CACHE
  printf("Number of L1 total cache misses = %lld\n",values[0]);
  printf("Number of L2 total cache misses = %lld\n",values[1]);
#else
  printf("Number of instructions = %lld\n",values[0]);
  printf("Number of fp operations = %lld\n",values[1]);
#endif
}

