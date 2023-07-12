# ===================================================
# MAKE THE BASIC STRUCTURE
# ===================================================

build.program.initial: build.program.sckeleton $(OBJECTS)

build.program.sckeleton:
	@mkdir $(BINARY_DIR)
	@mkdir $(REPORT_DIR)
	@mkdir -p $(OBJECT_DIR)/src
	@mkdir -p $(OBJECT_DIR)/tests
	@mkdir $(DOXYGEN_DIR)