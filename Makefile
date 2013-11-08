

OpenNI2_INC_DIR = /usr/include/OpenNI2

INC_DIRS = -Iinclude \
           -I${OpenNI2_INC_DIR}

SRC_FILES = src/depth_c.cpp \
            src/DepthDriver.cpp \
            src/AsusXtionDepthDriver.cpp \
            src/DepthMap.cpp

LIB_NAME = libkipr_link_depth_sensor.so

CXX = g++
RM = -@rm -f

CXXFLAGS = ${INC_DIRS} -Wall -Werror
LDFLAGS = #-Wl,--no-undefined

OBJ_FILES = ${SRC_FILES:.cpp=.o}
DEB_FILES = ${SRC_FILES:.cpp=.d}

.PHONY : all clean

all : $(LIB_NAME)

$(LIB_NAME) : $(OBJ_FILES)
	$(CXX) -o $(LIB_NAME) $(OBJ_FILES) $(LDFLAGS) -shared

%.o : %.cpp %.d
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.d : %.cpp
	$(CXX) $(CXXFLAGS) -MF"$@" -MG -MM -MP -MT"$@" -MT"$(<:.cpp=.o)" "$<"

clean:
	$(RM) $(OBJ_FILES) $(LIB_NAME) $(DEB_FILES)

-include $(DEB_FILES)
