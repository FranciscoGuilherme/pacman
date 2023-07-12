# ===================================================
# CONFIGURING GTK DEPENDENCES
# ===================================================

# ---------------------------------------------------
# GTK DEPENDENCES
# ---------------------------------------------------

GTK_INCLUDES  := $(shell pkg-config gtk+-3.0 --cflags)
GTK_LIBRARIES := $(shell pkg-config gtk+-3.0 --libs)

# ---------------------------------------------------
# GNUCC PARAMETERS
# ---------------------------------------------------

GTK_CFLAGS  := $(GTK_INCLUDES)
GTK_LDFLAGS := $(GTK_LIBRARIES)