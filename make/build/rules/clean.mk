SUPPRESS_WARN = 2> /dev/null

# ===================================================
# CLEANING THE PROJECT
# ===================================================

clean:
	@rm -R $(BINARY_DIR) $(REPORT_DIR) $(OBJECT_DIR) $(DOXYGEN_DIR) $(SUPPRESS_WARN) || true