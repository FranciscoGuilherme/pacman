# ===================================================
# MAKE BUILD FOR TESTS
# ===================================================

build.tests: build.tests.executable build.tests.final.configuration

build.tests.executable: $(TESTS_OBJECTS)
	$(CXX) -o $(TEST_BIN) $^ $(CPPUTEST_LDFLAGS)

build.tests.final.configuration:
	@mv $(filter %.o, $(TESTS_OBJECTS)) $(OBJECT_DIR)/tests