#Example:   export set NAC_LIB_DIR=~/binCLib
ifeq ($(NAC_LIB_DIR),)
  $(error NAC_LIB_DIR is not set)
endif

STATIC_LIB = 1

CC = g++

LIB_NAME = nstring

ifdef STATIC_LIB
OUTPUT = lib$(LIB_NAME).a
else
OUTPUT = lib$(LIB_NAME).so
endif

C_FILES = nstring.cpp 

L_FLAGS = 

# g3 compiles with debugging information
C_FLAGS = -g3

O_FILES := $(patsubst %.cpp,o/%.o,$(C_FILES))

all:
	mkdir -p o
	make $(OUTPUT)

$(OUTPUT): $(O_FILES)
ifdef STATIC_LIB
	ar rc $(OUTPUT) $(O_FILES) $(L_FILES)
	ranlib $(OUTPUT)
else
	$(CC) $(L_FLAGS) -shared $(O_FILES) -o $(OUTPUT)
endif
	mv ./$(OUTPUT) $(NAC_LIB_DIR)/$(OUTPUT)
	make clean

o/%.o: %.cpp
	echo "  Compiling $@....";
	$(CC) $(C_FLAGS) -c $< -o $@

clean:
	rm -f $(OUTPUT) $(O_FILES)
