# ===================================================
# MAKE A DETAIL REPORT (MEMORY & PROGRAM STATUS)
# ===================================================

build.program.report: build.program.executable build.program.final.configuration
	valgrind $(MEMORY_LEAKS) $(BINARY)

performance.analysis:
	valgrind $(CALLGRIND) $(BINARY)
	valgrind $(CACHEGRIND) $(BINARY)