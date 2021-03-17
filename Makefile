PAPI = /site/local/papi_64-4.1.4
#PAPI = /site/local/papi_x86_64

PAPI_LIB_DIR        = $(PAPI)/lib
PAPI_INCLUDE_DIR    = $(PAPI)/include

EDITOR = vim
SHOW = less

#SimpleMMM Variables
M=30
N=30
P=30
OUTPUT=0
CACHE=1

#BLOCK Variables
NB=10

.PHONY: help simpleMMM show_simpleMMM

help:
	@cat Makefile | grep : | grep -v @ | grep -v PHONY | awk -F':' '{print $$1}'

clean:
	@rm *.exe

run_simpleMMM: 
	g++ -m64 -static -DSIMPLE_M=${M} -DSIMPLE_N=${N} -DSIMPLE_P=${P} -DMEASURE_CACHE=${CACHE}   -DOUTPUT_ALL=${OUTPUT} -o simpleMMM.exe -I${PAPI_INCLUDE_DIR} -L${PAPI_LIB_DIR} SimpleMMM.cpp -lpapi
	@./simpleMMM.exe

run_simpleMMM_OPT1:
	g++ -m64 -static -O1 -DSIMPLE_M=${M} -DSIMPLE_N=${N} -DSIMPLE_P=${P} -DMEASURE_CACHE=${CACHE}  -DOUTPUT_ALL=${OUTPUT} -o simpleMMM_OPT1.exe -I${PAPI_INCLUDE_DIR} -L${PAPI_LIB_DIR} SimpleMMM.cpp -lpapi
	@./simpleMMM_OPT1.exe

run_simpleMMM_OPT2:
	g++ -m64 -static -O2 -DSIMPLE_M=${M} -DSIMPLE_N=${N} -DSIMPLE_P=${P} -DMEASURE_CACHE=${CACHE}    -DOUTPUT_ALL=${OUTPUT} -o simpleMMM_OPT2.exe -I${PAPI_INCLUDE_DIR} -L${PAPI_LIB_DIR} SimpleMMM.cpp -lpapi
	@./simpleMMM_OPT2.exe

run_simpleMMM_OPT3:
	g++ -m64 -static -O3 -DSIMPLE_M=${M} -DSIMPLE_N=${N} -DSIMPLE_P=${P} -DMEASURE_CACHE=${CACHE}    -DOUTPUT_ALL=${OUTPUT} -o simpleMMM_OPT3.exe -I${PAPI_INCLUDE_DIR} -L${PAPI_LIB_DIR} SimpleMMM.cpp -lpapi
	@./simpleMMM_OPT3.exe 

run_simpleDynamicMMM: 
	g++ -m64 -static -DSIMPLE_M=${M} -DSIMPLE_N=${N} -DSIMPLE_P=${P}   -DMEASURE_CACHE=${CACHE}   -DOUTPUT_ALL=${OUTPUT} -o simpleDynamicMMM.exe -I${PAPI_INCLUDE_DIR} -L${PAPI_LIB_DIR} SimpleDynamicMMM.cpp -lpapi
	@./simpleDynamicMMM.exe

run_simpleDynamicMMM_OPT1: 
	g++ -m64 -static -O1 -DSIMPLE_M=${M} -DSIMPLE_N=${N} -DSIMPLE_P=${P}   -DMEASURE_CACHE=${CACHE}   -DOUTPUT_ALL=${OUTPUT} -o simpleDynamicMMM_OPT1.exe -I${PAPI_INCLUDE_DIR} -L${PAPI_LIB_DIR} SimpleDynamicMMM.cpp -lpapi
	@./simpleDynamicMMM_OPT1.exe

run_simpleDynamicMMM_OPT2: 
	g++ -m64 -static -O2 -DSIMPLE_M=${M} -DSIMPLE_N=${N} -DSIMPLE_P=${P}   -DMEASURE_CACHE=${CACHE}   -DOUTPUT_ALL=${OUTPUT} -o simpleDynamicMMM_OPT2.exe -I${PAPI_INCLUDE_DIR} -L${PAPI_LIB_DIR} SimpleDynamicMMM.cpp -lpapi
	@./simpleDynamicMMM_OPT2.exe

run_simpleDynamicMMM_OPT3: 
	g++ -m64 -static -O3 -DSIMPLE_M=${M} -DSIMPLE_N=${N} -DSIMPLE_P=${P}   -DMEASURE_CACHE=${CACHE}   -DOUTPUT_ALL=${OUTPUT} -o simpleDynamicMMM_OPT3.exe -I${PAPI_INCLUDE_DIR} -L${PAPI_LIB_DIR} SimpleDynamicMMM.cpp -lpapi
	@./simpleDynamicMMM_OPT3.exe


show_simpleMMM: SimpleMMM.cpp
	@${SHOW} SimpleMMM.cpp;

show_simpleDynamicMMM: SimpleDynamicMMM.cpp
	@${SHOW} SimpleDynamicMMM.cpp;

show_cache_info:
	@getconf -a | grep CACHE

show_blockingMMM: BlockingMMM.cpp
	@${SHOW} BlockingMMM.cpp;

show_blockingDynamicMMM: BlockingDynamicMMM.cpp
	@${SHOW} BlockingDynamicMMM.cpp;

run_blockingMMM:
	g++ -m64 -static -DBLOCK_M=${M} -DBLOCK_N=${N} -DBLOCK_P=${P} -DMEASURE_CACHE=${CACHE}    -DBLOCK_NB=${NB} -DOUTPUT_ALL=${OUTPUT} -o blockingMMM.exe -I${PAPI_INCLUDE_DIR} -L${PAPI_LIB_DIR} BlockingMMM.cpp -lpapi
	@./blockingMMM.exe

run_blockingMMM_OPT1:
	g++ -m64 -static -O1 -DBLOCK_M=${M} -DBLOCK_N=${N} -DBLOCK_P=${P} -DMEASURE_CACHE=${CACHE}    -DBLOCK_NB=${NB} -DOUTPUT_ALL=${OUTPUT} -o blockingMMM_OPT1.exe -I${PAPI_INCLUDE_DIR} -L${PAPI_LIB_DIR} BlockingMMM.cpp -lpapi
	@./blockingMMM_OPT1.exe

run_blockingMMM_OPT2:
	g++ -m64 -static -O2 -DBLOCK_M=${M} -DBLOCK_N=${N} -DBLOCK_P=${P} -DMEASURE_CACHE=${CACHE}    -DBLOCK_NB=${NB} -DOUTPUT_ALL=${OUTPUT} -o blockingMMM_OPT2.exe -I${PAPI_INCLUDE_DIR} -L${PAPI_LIB_DIR} BlockingMMM.cpp -lpapi
	@./blockingMMM_OPT2.exe

run_blockingMMM_OPT3:
	g++ -m64 -static -O3 -DBLOCK_M=${M} -DBLOCK_N=${N} -DBLOCK_P=${P} -DMEASURE_CACHE=${CACHE}    -DBLOCK_NB=${NB} -DOUTPUT_ALL=${OUTPUT} -o blockingMMM_OPT3.exe -I${PAPI_INCLUDE_DIR} -L${PAPI_LIB_DIR} BlockingMMM.cpp -lpapi
	@./blockingMMM_OPT3.exe

run_blockingDynamicMMM:
	g++ -m64 -static -DBLOCK_M=${M} -DBLOCK_N=${N} -DBLOCK_P=${P} -DMEASURE_CACHE=${CACHE}    -DBLOCK_NB=${NB} -DOUTPUT_ALL=${OUTPUT} -o blockingDynamicMMM.exe -I${PAPI_INCLUDE_DIR} -L${PAPI_LIB_DIR} BlockingDynamicMMM.cpp -lpapi
	@./blockingDynamicMMM.exe

run_blockingDynamicMMM_OPT1:
	g++ -m64 -static -O1 -DBLOCK_M=${M} -DBLOCK_N=${N} -DBLOCK_P=${P} -DMEASURE_CACHE=${CACHE}    -DBLOCK_NB=${NB} -DOUTPUT_ALL=${OUTPUT} -o blockingDynamicMMM_OPT1.exe -I${PAPI_INCLUDE_DIR} -L${PAPI_LIB_DIR} BlockingDynamicMMM.cpp -lpapi
	@./blockingDynamicMMM_OPT1.exe

run_blockingDynamicMMM_OPT2:
	g++ -m64 -static -O2 -DBLOCK_M=${M} -DBLOCK_N=${N} -DBLOCK_P=${P} -DMEASURE_CACHE=${CACHE}    -DBLOCK_NB=${NB} -DOUTPUT_ALL=${OUTPUT} -o blockingDynamicMMM_OPT2.exe -I${PAPI_INCLUDE_DIR} -L${PAPI_LIB_DIR} BlockingDynamicMMM.cpp -lpapi
	@./blockingDynamicMMM_OPT2.exe

run_blockingDynamicMMM_OPT3:
	g++ -m64 -static -O3 -DBLOCK_M=${M} -DBLOCK_N=${N} -DBLOCK_P=${P} -DMEASURE_CACHE=${CACHE}    -DBLOCK_NB=${NB} -DOUTPUT_ALL=${OUTPUT} -o blockingDynamicMMM_OPT3.exe -I${PAPI_INCLUDE_DIR} -L${PAPI_LIB_DIR} BlockingDynamicMMM.cpp -lpapi
	@./blockingDynamicMMM_OPT3.exe

isRightServer:
	$(eval SERVER_NAME= $(shell uname -n))
	$(if $(filter-out sandbox,$(SERVER_NAME)), $(info Error - server is "${SERVER_NAME}", ssh to sandbox),$(info On correct server))
	@echo 

