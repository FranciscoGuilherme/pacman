# ===================================================
# CONFIGURING MYSQL DEPENDENCES
# ===================================================

# ---------------------------------------------------
# MYSQL DEPENDENCES
# ---------------------------------------------------

MYSQL_INCLUDES  := $(shell pkg-config mysqlclient --cflags)
MYSQL_LIBRARIES := $(shell pkg-config mysqlclient --libs)

# ---------------------------------------------------
# GNUCC PARAMETERS
# ---------------------------------------------------

MYSQL_CFLAGS  := $(MYSQL_INCLUDES)
MYSQL_LDFLAGS := $(MYSQL_LIBRARIES)