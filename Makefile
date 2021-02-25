PAPI = /site/local/papi_64-4.1.4

PAPI_LIB_DIR        = $(PAPI)/lib
PAPI_INCLUDE_DIR    = $(PAPI)/include

EDITOR = vim
SHOW = less

.PHONY: help simpleMMM show_simpleMMM

help:
	@echo "The following targets exist:";
	@echo "show_simpleMMM";
	@echo "run_simpleMMM";

clean:
	@rm *.exe

simpleMMM.exe : simpleMMM

simpleMMM:
	g++ -m64 -static  -o simpleMMM.exe -I${PAPI_INCLUDE_DIR} -L${PAPI_LIB_DIR} SimpleMMM.cpp -lpapi

run_simpleMMM: simpleMMM.exe
	@./simpleMMM.exe | less

show_simpleMMM: SimpleMMM.cpp
	@${SHOW} SimpleMMM.cpp;
