# ===================================================
# MAKE THE EXECUTABLE FILE
# ===================================================

# ---------------------------------------------------
# SIMPLE EXECUTABLE FILE
# ---------------------------------------------------

build.program.executable: clean build.program.initial
	$(CC) $(CFLAGS) $(OBJECTS) -o $(BINARY) -lm

# ---------------------------------------------------
# EXECUTABLE FILE WITH GTK LIBRARIE
# ---------------------------------------------------

build.gtk.executable: clean build.program.initial gtk.compile

gtk.compile: $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $(BINARY) $(GTK_LDFLAGS)

# ===================================================
# FINAL EXTRA CONFIGURATION FOR THE PROJECT
# ===================================================

build.program.final.configuration:
	@mv $(filter %.o, $(OBJECTS)) $(OBJECT_DIR)/src