# fast-code-examples
Implemented examples from the fast code paper

All examples can be executed from the Makefile

make help - list outs all available options

make show_cache_info - outputs cache info from getconf

make isRightServer - tests that on node sandbox

make show_simpleMMM - displays the code SimpleMMM.cpp

make show_blockingMMM - displays the code BlockingMMM.cpp

options for targets run_simpleMMM*:
 M=300    - Matrix A is MxN
 N=300    - Matrix B is NxP
 P=300    - Resulting Matrix is MxP
 OUTPUT=0 - toggle on outputting matrix operations
 CACHE=1  - Display Cache info from papi
 CACHE=0  - Display instructions and fp operations from papi

options for targets run_blockingMMM*:
 M=300    - Matrix A is MxN
 N=300    - Matrix B is NxP
 P=300    - Resulting Matrix is MxP
 NB=100   - Block/tile size is NBxNB
 OUTPUT=0 - toggle on outputting matrix operations
 CACHE=1  - Display Cache info from papi
 CACHE=0  - Display instructions and fp operations from papi


