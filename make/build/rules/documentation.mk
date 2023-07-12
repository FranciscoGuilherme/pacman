# ===================================================
# MAKE BUILD FOR DOCUMENTATION
# ===================================================

build.documentation: build.documentation.files build.documentation.final.configuration

build.documentation.files:
	@cd ./scripts/documentation/ && bash entrypoint.sh -d $$PROJECT_DIR --replace $(LANGUAGE)

build.documentation.final.configuration:
	@rm -fr $(DOXYGEN_DIR)/*
	@mv $(SOURCE_DIR)/html/ $(SOURCE_DIR)/latex/ $(SOURCE_DIR)/Doxyfile $(DOXYGEN_DIR)