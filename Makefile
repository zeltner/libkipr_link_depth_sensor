
INC_DIRS = include

SRC_FILES = src/depth_c.cpp \
            src/DepthDriver.cpp \
            src/AsusXtionDepthDriver.cpp \
            src/DepthMap.cpp

LIB_NAME = libkipr_link_depth_sensor.a

CXX = g++
AR = ar

CXXFLAGS = -Wall -Werror

OBJ_FILES = ${SRC_FILES:.cpp=.o}


.PHONY : all

all : $(LIB_NAME)

$(LIB_NAME) : $(OBJ_FILES)
	$(AR) rcs $(LIB_NAME) $(OBJ_FILES)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
