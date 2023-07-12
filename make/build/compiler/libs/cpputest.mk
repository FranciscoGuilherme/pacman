# ===================================================
# CONFIGURING CPPUTEST DEPENDENCES
# ===================================================

# ---------------------------------------------------
# CPPUTEST DEPENDENCES
# ---------------------------------------------------

CPPUTEST_INCLUDES  := -pthread -I/usr/include/CppUTest/* -I/usr/include/CppUTestExt/*
CPPUTEST_LIBRARIES := $(shell pkg-config --libs cpputest)

# ---------------------------------------------------
# GNUCC PARAMETERS
# ---------------------------------------------------

CPPUTEST_CFLAGS  := -Wall -g $(CPPUTEST_INCLUDES)
CPPUTEST_LDFLAGS := $(CPPUTEST_LIBRARIES)