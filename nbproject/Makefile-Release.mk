#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/src/Crypto/base64.o \
	${OBJECTDIR}/src/Errors.o \
	${OBJECTDIR}/src/HTTP/HTTP.o \
	${OBJECTDIR}/src/Request.o \
	${OBJECTDIR}/src/Response.o \
	${OBJECTDIR}/src/client.o \
	${OBJECTDIR}/src/pugixml/pugixml.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1

# Test Object Files
TESTOBJECTFILES= \
	${TESTDIR}/tests/Base64Test.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-Llib

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libwsdl.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libwsdl.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libwsdl.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libwsdl.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libwsdl.a

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Iinclude -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/src/Crypto/base64.o: src/Crypto/base64.cpp
	${MKDIR} -p ${OBJECTDIR}/src/Crypto
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Iinclude -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Crypto/base64.o src/Crypto/base64.cpp

${OBJECTDIR}/src/Errors.o: src/Errors.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Iinclude -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Errors.o src/Errors.cpp

${OBJECTDIR}/src/HTTP/HTTP.o: src/HTTP/HTTP.cpp
	${MKDIR} -p ${OBJECTDIR}/src/HTTP
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Iinclude -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/HTTP/HTTP.o src/HTTP/HTTP.cpp

${OBJECTDIR}/src/Request.o: src/Request.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Iinclude -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Request.o src/Request.cpp

${OBJECTDIR}/src/Response.o: src/Response.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Iinclude -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Response.o src/Response.cpp

${OBJECTDIR}/src/client.o: src/client.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Iinclude -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/client.o src/client.cpp

${OBJECTDIR}/src/pugixml/pugixml.o: src/pugixml/pugixml.cpp
	${MKDIR} -p ${OBJECTDIR}/src/pugixml
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Iinclude -std=c++98 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/pugixml/pugixml.o src/pugixml/pugixml.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-tests-subprojects .build-conf ${TESTFILES}
.build-tests-subprojects:

${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/Base64Test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS}  -lcrypto -lssl -Llib 


${TESTDIR}/tests/Base64Test.o: tests/Base64Test.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Iinclude -Iinclude -std=c++98 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/Base64Test.o tests/Base64Test.cpp


${OBJECTDIR}/main_nomain.o: ${OBJECTDIR}/main.o main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/main.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Iinclude -std=c++98 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main_nomain.o main.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/main.o ${OBJECTDIR}/main_nomain.o;\
	fi

${OBJECTDIR}/src/Crypto/base64_nomain.o: ${OBJECTDIR}/src/Crypto/base64.o src/Crypto/base64.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Crypto
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/Crypto/base64.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Iinclude -std=c++98 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Crypto/base64_nomain.o src/Crypto/base64.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/Crypto/base64.o ${OBJECTDIR}/src/Crypto/base64_nomain.o;\
	fi

${OBJECTDIR}/src/Errors_nomain.o: ${OBJECTDIR}/src/Errors.o src/Errors.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/Errors.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Iinclude -std=c++98 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Errors_nomain.o src/Errors.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/Errors.o ${OBJECTDIR}/src/Errors_nomain.o;\
	fi

${OBJECTDIR}/src/HTTP/HTTP_nomain.o: ${OBJECTDIR}/src/HTTP/HTTP.o src/HTTP/HTTP.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/HTTP
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/HTTP/HTTP.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Iinclude -std=c++98 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/HTTP/HTTP_nomain.o src/HTTP/HTTP.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/HTTP/HTTP.o ${OBJECTDIR}/src/HTTP/HTTP_nomain.o;\
	fi

${OBJECTDIR}/src/Request_nomain.o: ${OBJECTDIR}/src/Request.o src/Request.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/Request.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Iinclude -std=c++98 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Request_nomain.o src/Request.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/Request.o ${OBJECTDIR}/src/Request_nomain.o;\
	fi

${OBJECTDIR}/src/Response_nomain.o: ${OBJECTDIR}/src/Response.o src/Response.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/Response.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Iinclude -std=c++98 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Response_nomain.o src/Response.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/Response.o ${OBJECTDIR}/src/Response_nomain.o;\
	fi

${OBJECTDIR}/src/client_nomain.o: ${OBJECTDIR}/src/client.o src/client.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/client.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Iinclude -std=c++98 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/client_nomain.o src/client.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/client.o ${OBJECTDIR}/src/client_nomain.o;\
	fi

${OBJECTDIR}/src/pugixml/pugixml_nomain.o: ${OBJECTDIR}/src/pugixml/pugixml.o src/pugixml/pugixml.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/pugixml
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/pugixml/pugixml.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Iinclude -std=c++98 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/pugixml/pugixml_nomain.o src/pugixml/pugixml.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/pugixml/pugixml.o ${OBJECTDIR}/src/pugixml/pugixml_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f1 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
