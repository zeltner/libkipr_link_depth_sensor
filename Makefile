

OpenNI2_INC_DIR = /usr/include/OpenNI2

INC_DIRS = -Iinclude \
           -I${OpenNI2_INC_DIR}

SRC_FILES = src/depth_c.cpp \
            src/DepthDriver.cpp \
            src/AsusXtionDepthDriver.cpp \
            src/DepthMap.cpp

LIB_NAME = libkipr_link_depth_sensor.a

CXX = g++
AR = ar
RM = -@rm -f

CXXFLAGS = ${INC_DIRS} -Wall -Werror

OBJ_FILES = ${SRC_FILES:.cpp=.o}
DEB_FILES = ${SRC_FILES:.cpp=.d}

.PHONY : all clean

all : $(LIB_NAME)

$(LIB_NAME) : $(OBJ_FILES)
	$(AR) rcs $(LIB_NAME) $(OBJ_FILES)

%.o : %.cpp %.d
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.d : %.cpp
	$(CXX) $(CXXFLAGS) -MF"$@" -MG -MM -MP -MT"$@" -MT"$(<:.cpp=.o)" "$<"

clean:
	$(RM) $(OBJ_FILES) $(LIB_NAME) $(DEB_FILES)

-include $(DEB_FILES)
