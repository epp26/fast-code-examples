# fast-code-examples
This repository houses implementations of optimization examples from the paper:

```
“How To Write Fast Numerical Code: - A Small Introduction” By Srinivas Chellappa, Franz Franchetti, and Markus Püschel
```

All examples can be executed from the Makefile

## Make Targets
```
$ make help                    # list outs all available options
$ make isRightServer           # tests that on node sandbox
$ make show_cache_info         # outputs cache info from getconf
$ make show_simpleMMM          # displays the code SimpleMMM.cpp
$ make show_simpleDynamicMMM   # displays the code SimpleDynamicMMM.cpp
$ make show_blockingMMM        # displays the code BlockingMMM.cpp
$ make show_blockingDynamicMMM # displays the code BlockingDynamicMMM.cpp
```

## `make run_simpleMMM M=300 N=300 P=300 OUTPUT=0 CACHE=1`

Compiles and executes a simple matrix-matrix multiplication example.
The example will create an `MxN` matrix and an `NxP` matrix, and multiply them to create an `MxP` matrix.

The `OUTPUT` option specifies whether the three matrics should be included in the output.

The `CACHE` option specifies the type of PAPI information to display.
`CACHE=1` displays cache information from PAPI, while `CACHE=0` displays instruction count and FP operations.

## `make run_blockingMMM M=300 N=300 P=300 NB=100 OUTPUT=0 CACHE=1`

Compiles and executes a blocking matrix-matrix multiplication example.
The example will create an `MxN` matrix and an `NxP` matrix, and multiply them to create an `MxP` matrix.
The program will do block multiplication with block sizes `NB`.
The block size must divide evenly into the matrices.

The `OUTPUT` option specifies whether the three matrics should be included in the output.

The `CACHE` option specifies the type of PAPI information to display.
`CACHE=1` displays cache information from PAPI, while `CACHE=0` displays instruction count and FP operations.
