# Detect OS
ifeq ($(OS),Windows_NT)
    EXE = ash.exe
    RUN = .\$(EXE)
else
    EXE = ash
    RUN = ./$(EXE)
endif

build:
	@gcc -o $(EXE) src/main.c

run: build
	@$(RUN)
