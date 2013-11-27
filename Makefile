

OpenNI2_INC_DIR = /usr/include/OpenNI2

INC_DIRS = -Iinclude \
           -I${OpenNI2_INC_DIR}

SRC_FILES = src/depth_c.cpp \
            src/DepthDriver.cpp \
            src/OpenNI2DepthDriver.cpp \
            src/OpenNI2DepthImage.cpp \
            src/PointCloud.cpp

LIB_NAME = libkipr_link_depth_sensor.so

INSTALL_INCLUDE_FILES = include/libkipr_link_depth_sensor/depth.h \
                        include/libkipr_link_depth_sensor/DepthImageResolution.h

CXX = g++
RM = -@rm -f
INSTALL = install

CXXFLAGS = ${INC_DIRS} -Wall -Werror -std=c++0x
LDFLAGS = #-Wl,--no-undefined

OBJ_FILES = ${SRC_FILES:.cpp=.o}
DEB_FILES = ${SRC_FILES:.cpp=.d}

.PHONY : all clean install

all : $(LIB_NAME)

$(LIB_NAME) : $(OBJ_FILES)
	$(CXX) -o $(LIB_NAME) $(OBJ_FILES) $(LDFLAGS) -shared

%.o : %.cpp %.d
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.d : %.cpp
	$(CXX) $(CXXFLAGS) -MF"$@" -MG -MM -MP -MT"$@" -MT"$(<:.cpp=.o)" "$<"

clean:
	$(RM) $(OBJ_FILES) $(LIB_NAME) $(DEB_FILES)

install: $(LIB_NAME)
	$(INSTALL) -d /usr/include/libkipr_link_depth_sensor
	$(INSTALL) $(INSTALL_INCLUDE_FILES) -t /usr/include/libkipr_link_depth_sensor
	$(INSTALL) $(LIB_NAME) -D /usr/lib/

-include $(DEB_FILES)
