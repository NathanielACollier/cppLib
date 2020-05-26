

STATIC_LIB = 1

CC = g++

LIB_NAME = ncalc

ifdef STATIC_LIB
OUTPUT = lib$(LIB_NAME).a
else
OUTPUT = lib$(LIB_NAME).so
endif

C_FILES = math.cpp math_build.cpp math_conv.cpp math_function.cpp math_run.cpp \
          math_string.cpp

L_FLAGS = 

C_FLAGS = -g3

O_FILES := $(patsubst %.cpp,o/%.o,$(C_FILES))

all:
	make $(OUTPUT)

$(OUTPUT): $(O_FILES)
ifdef STATIC_LIB
	ar rc $(OUTPUT) $(O_FILES)
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

