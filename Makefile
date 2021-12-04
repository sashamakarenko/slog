PRJ_NAME    := slog
PRJ_BRANCH  := 1.0
PRJ_VERSION := $(PRJ_BRANCH).0
PRJ_TYPE    := lib

SRCSUBDIRS = impl
LINK_EXTRA_LIBS = -lpthread
TEST_EXTRA_LINK_LIBS = -lpthread

-include ../makefile/Makefile

../makefile/Makefile:
	@echo "cloning makefile..."
	@cd ..; git clone https://github.com/sashamakarenko/makefile.git makefile
