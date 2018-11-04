ROOT_DIR=bin

#modules/telecommande
#modules/roboclawTester
EAVE=src

all: eave

eave:
ifeq ("$(wildcard $(src/eave.o))","")
	rm -f src/eave.o
endif
	$(MAKE) -C $(EAVE)

clean:
	$(MAKE) -C $(EAVE) clean

cleanAll:
	$(MAKE) -C $(EAVE) cleanAll
