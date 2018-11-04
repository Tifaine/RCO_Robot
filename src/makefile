
ROOT_DIR=../bin
EXEC=eave

CXX=g++
CROSS_COMPILE=
CROSS_LIBS=

VERSION=0.1.2
TIMESTAMP:=$(shell date "+%F %T")

LIBSFLAGS=

IDIRS=-I. \
-I./lib/roboclaw \
-I./struct \

FLAGS+=$(CROSS_LIBS) $(IDIRS) $(LIBSFLAGS) -DVERSION="\"${VERSION}\"" -DTIMESTAMP="\"${TIMESTAMP}\"" -Wall

LDFLAGS=$(CROSS_LIBS) $(LIBSFLAGS)

CPP_SRC=$(shell find . -name "*.cpp")
CPP_OBJ=$(CPP_SRC:.cpp=.o)

C_SRC=$(shell find . -name "*.c")
C_OBJ=$(C_SRC:.c=.o)

OBJ=$(C_OBJ) $(CPP_OBJ)

all: $(ROOT_DIR) $(DEPEND) $(ROOT_DIR)/$(EXEC) $(ROOT_DIR)/$(OUTFOLDER)
	@echo "+=======================================+"
	@echo "|	\033[1;92mBuid $(EXEC) done\033[0m			|"
	@echo "| for hard_arch : \033[1;92m$(shell file $(ROOT_DIR)/$(EXEC) | cut -d ',' -f2)\033[0m   		|"
	@echo "+=======================================+"

$(ROOT_DIR):
	@$(shell [ -d "$(ROOT_DIR)" ] || mkdir -p "$(ROOT_DIR)" )

$(ROOT_DIR)/$(EXEC): $(OBJ)
	$(CROSS_COMPILE)$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CROSS_COMPILE)$(CXX) $(FLAGS) -c -o $@ $<
%.o: %.cpp
	$(CROSS_COMPILE)$(CXX) $(FLAGS) -c -o $@ $<

clean:
	rm -f $(shell find . -name "*.o") $(shell find . -name *.so) $(shell find . -name "*.d") $(shell find ./$(SOURCE_DIR)/ -name "*.gch")
	rm -f $(ROOT_DIR)/$(EXEC)

cleanAll:
	rm -f $(shell find . -name "*.o") $(shell find . -name *.so) $(shell find . -name "*.d") $(shell find ./$(SOURCE_DIR)/ -name "*.gch")
	rm -rf $(ROOT_DIR)

makedeps:
	@makedepend -Y $(C_SRC) $(CPP_SRC) 2> /dev/null

# DO NOT DELETE
