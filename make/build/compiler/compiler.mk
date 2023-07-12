# ===================================================
# HIDING THE GCC COMPILATION
# ===================================================

MAKEFLAGS += --quiet

# ===================================================
# OTHER PARAMETERS
# ===================================================

BINARY   := $(BINARY_DIR)/program
TEST_BIN := $(BINARY_DIR)/tests

# ===================================================
# GNUCC PARAMETERS
# ===================================================

CFLAGS := -Wall -g -O2 -rdynamic

# ===================================================
# SOURCE FILES (*.c, *.o)
# ===================================================

SOURCES := $(wildcard $(SOURCE_DIR)/**/*.c $(SOURCE_DIR)/*.c)
OBJECTS := $(patsubst %.c, %.o, $(SOURCES))

# ===================================================
# TESTS FILES (*.c, *.o)
# ===================================================

TESTS_METHODS := $(filter-out ../src/main.c, $(SOURCES))
TESTS_SOURCES := $(wildcard $(TESTS_DIR)/**/*.cpp $(TESTS_DIR)/*.cpp $(TESTS_METHODS))
TESTS_OBJECTS := $(patsubst %.cpp, %.o, $(TESTS_SOURCES))