# ===================================================
# INCLUDE MAKEFILE DEPENDENCES
# ===================================================

# ---------------------------------------------------
# INCLUDE VARIABLES
# ---------------------------------------------------

include compiler/environment.mk
include compiler/compiler.mk
include compiler/libs/gtk.mk
include compiler/libs/mysql.mk

# ---------------------------------------------------
# INCLUDE RULES
# ---------------------------------------------------

include rules/structure.mk
include rules/executable.mk
include rules/report.mk
include rules/tests.mk
include rules/documentation.mk
include rules/clean.mk

# ===================================================
# BUILDING A DEFAULT PROJECT
# ===================================================
#
# 1. Rules list by categories
#      C.1: Build basic structure
#      C.2: Build executable file
#      C.3: Build program report
#      C.4: Build tests
#      C.5: Build bocumentation
#      C.6: Clean project
#
# ===================================================

build.program: build.program.report

build.program.full: build.program.report performance.analysis build.documentation








