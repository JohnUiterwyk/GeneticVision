.SUFFIXES: .cpp $(SUFFIXES)

CC = g++ 
#CC = /usr/local/pkg/gcc-3-1/bin/g++
#CC = cxx                               #FOR VPAC
CFLAGS = -g -ansi -pedantic -Wall
#CFLAGS = -g -std gnu                   #FOR VPAC
DEFINES = -DUNIX
RM = rm
DIR = `pwd`
AR = ar
OUTPUT = librmitgp.a

OBJS = Function.o Terminal.o Node.o ReturnData.o GeneticProgram.o Random.o \
       Mutation.o Crossover.o NodeSet.o ProgramGenerator.o \
       Selection.o Population.o Util.o GPConfig.o Fitness.o \
       GridPopulation.o CoEvolutionPopulation.o CoEvolutionFitness.o \
       TournamentSelection.o ADFunction.o ADFRoot.o ADFProgramGenerator.o \
       EMOTournamentSelection.o EMOPopulation.o NSGA2.o list.o \
       Parsimony.o CovariantTarpeian.o DynamicDepthLimit.o
SRCS=$(OBJS:.o=.cpp)

LIB =
INCLUDE = -I. 




all: $(OBJS)
	$(AR) -rv $(OUTPUT) $?

.cpp.o:
	$(CC) -c $(CFLAGS) $(DEFINES) $(CXXINCLUDE) $(INCLUDE) $*.cpp

clean:
	$(RM) -f $(OBJS) $(OUTPUT)

objects:
	@for f in $(OBJS); do echo $(DIR)/$$f; done

#depend: $(SRCS)
#	@(sed <Makefile '/^#--DEPENDENCIES--$$/,$$d'; \
#	echo '#--DEPENDENCIES--'; \
#	$(CC) -c -M $(CFLAGS) $(CXXINCLUDE) $(INCLUDE) $(SRCS) \
#	) > Makefile.new
#	mv Makefile.new Makefile


#all:
#	g++ -g -ansi -Wall -pedantic -c *.cpp
#clean:
#	rm *.o

