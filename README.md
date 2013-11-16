libkipr_link_depth_sensor
=========================

libkipr_link_depth_sensor is a depth sensor library for the [KIPR Link Robot Controller](http://www.kipr.org/products/link). It is designed in such a way that it can be easily used by applications build with the KISS IDE.

**DISCLAIMER:**
libkipr_link_depth_sensor is currently under development and not part of the KIPR Link firmware. Installing libkipr_link_depth_sensor and its prerequisites requires modifying the KIPR Link firmware which, even following carefully this README, may result in a non-working system. So you should be aware that if you follow these instructions, you do it at your own risk.

## 1 Installing Prerequisites
### 1.1 Update the KIPR Link Firmware
**This step is optional.** However you might face some issues if you have another firmware running than 1.9.5 or if you run a modified version of 1.9.5.

To update the firmware to version 1.9.5 follow these [instructions](http://www.kipr.org/kiss-platform-link-firmware) 

*Note:* If you previously called

```
opkg update
```
on your firmware, you might have to add *--force-downgrade* to all *opkg* calls to be able to download packages from *http://netv.bunnie-bar.com/build/kovan-debug/LATEST/armv5te*.

### 1.2 Setup the WIFI and connect to the Link
Enable WIFI in [Settings] > [Network] and connect to a wireless network.
Then log in to the Link via SSH. An example for IP 192.168.0.1:
```
ssh root@192.168.0.1
```

### 1.3 Set Date and Time
Set */etc/localtime* to the correct time zome. An example for *PST*:
```
root@kovan:~# ln -sf /usr/share/zoneinfo/America/Los_Angeles /etc/localtime
```

Set the date and time using the *date* command. An example for 10/31/2013 2:00 pm

```
root@kovan:~# date 103114002013
Thu Oct 31 14:00:00 PDT 2013
```

### 1.4 Get wget and git with SSL support
*Note:* This step is not required to install libkipr_link_depth_sensor but it allows us to retrieve the source directly via *git*. Alternatively you can download the source using a PC and transfer it to the Link via SFTP.

#### 1.4.1 Install wget
```
root@kovan:~# opkg install http://netv.bunnie-bar.com/build/kovan-debug/LATEST/armv5te/wget_1.13.4-r13.1_armv5te.ipk
```

#### 1.4.2 Install curl
```
root@kovan:~# opkg install http://netv.bunnie-bar.com/build/kovan-debug/LATEST/armv5te/libcurl5_7.23.1-r0_armv5te.ipk
root@kovan:~# opkg install http://netv.bunnie-bar.com/build/kovan-debug/LATEST/armv5te/curl_7.23.1-r0_armv5te.ipk
```

#### 1.4.3 Install CA certificates
```
root@kovan:~# mkdir -p /etc/ssl/certs
```

Add the following to the end of file */etc/profile*
```
export SSL_CERT_DIR=/etc/ssl/certs
```

```
root@kovan:~# source /etc/profile
root@kovan:~# opkg install http://netv.bunnie-bar.com/build/kovan-debug/LATEST/armv5te/openssl-misc_1.0.0g-r15.0_armv5te.ipk
root@kovan:~# cd /etc/ssl/certs
root@kovan:/etc/ssl/certs# curl http://curl.haxx.se/ca/cacert.pem -o cacert.pem
root@kovan:/etc/ssl/certs# awk 'split_after==1{n++;split_after=0} /-----END CERTIFICATE-----/ {split_after=1} {print > "cert" n ".pem"}' cacert.pem 
root@kovan:/etc/ssl/certs# for file in *.pem; do ln -s $file `openssl x509 -hash -noout -in $file`.0; done
root@kovan:/etc/ssl/certs# cd ~
```

#### 1.4.4 Install git
```
root@kovan:~# opkg install http://netv.bunnie-bar.com/build/kovan-debug/LATEST/armv5te/git_1.7.7-r2_armv5te.ipk
root@kovan:~# git config --global http.sslcainfo /etc/ssl/certs/cacert.pem
```

### 1.5 Install libusb-dev
```
root@kovan:~# opkg install http://netv.bunnie-bar.com/build/kovan-debug/LATEST/armv5te/libusb-1.0-dev_1.0.8-r3_armv5te.ipk
```

### 1.6 Install libudev
```
root@kovan:~/OpenNI2# opkg install http://netv.bunnie-bar.com/build/kovan-debug/LATEST/armv5te/udev-dev_180-r0_armv5te.ipk
```

### 1.7 Create a Swap File
Creating a swap file will speed up the OpenNI2 and libkipr_link_depth_sensor compilation time.
```
root@kovan:~# dd if=/dev/zero of=/swapfile bs=1024 count=262144
root@kovan:~# mkswap /swapfile
root@kovan:~# swapon /swapfile
```

### 1.8 Install OpenNI2
#### 1.8.1 Clone the Source Files

```
root@kovan:~# git clone https://github.com/OpenNI/OpenNI2.git
root@kovan:~# cd OpenNI2/
root@kovan:~/OpenNI2# git checkout 2.2-beta
```

#### 1.8.2 Prepare the Source Files
Comment the Hardware specifying flags and the *XN_NEON* define in *ThirdParty/PSCommon/BuildSystem/Platform.Arm*:
```
ifeq "$(CFG)" "Release"

    # Hardware specifying flags
#    CFLAGS += -march=armv7-a -mtune=cortex-a9 -mfpu=neon -mfloat-abi=softfp #-m

    # Optimization level, minus currently buggy optimizing methods (which break
    CFLAGS += -O3 -fno-tree-pre -fno-strict-aliasing

    # More optimization flags
    CFLAGS += -ftree-vectorize -ffast-math -funsafe-math-optimizations #-fsingle

#    DEFINES += XN_NEON
    CFLAGS += -flax-vector-conversions
endif
```

Comment *#pragma GCC diagnostic push* and *#pragma GCC diagnostic pop* in *Include/OpenNI.h* as this pragmas are not supported by GCC 4.5:
```
/** This special URI can be passed to @ref Device::open() when the application h
#if ONI_PLATFORM != ONI_PLATFORM_WIN32
#pragma GCC diagnostic ignored "-Wunused-variable"
/* #pragma GCC diagnostic push */
#endif
static const char* ANY_DEVICE = NULL;
#if ONI_PLATFORM != ONI_PLATFORM_WIN32
/* #pragma GCC diagnostic pop */
#endif
```

Comment all \*.java targets in *Makefile*:
```
  # list all wrappers
  ALL_WRAPPERS = \
      Wrappers/java/OpenNI.jni \
  #       Wrappers/java/OpenNI.java

  # list all tools
  ALL_TOOLS = \
      Source/Drivers/PS1080/PS1080Console \
      Source/Drivers/PSLink/PSLinkConsole

  # list all core projects
  ALL_CORE_PROJS = \
      $(XNLIB)  \
      $(OPENNI) \
      $(DEPTH_UTILS) \
      $(ALL_DRIVERS) \
      $(ALL_WRAPPERS) \
      $(ALL_TOOLS)

  # list all samples
  CORE_SAMPLES = \
      Samples/SimpleRead \
      Samples/EventBasedRead \
      Samples/MultipleStreamRead \
      Samples/MWClosestPoint \
      Samples/MWClosestPointApp

  # list all java samples
  JAVA_SAMPLES = \
  #       Samples/SimpleViewer.java
```

#### 1.8.3 Compile OpenNI2
```
root@kovan:~/OpenNI2# make
```

#### 1.8.4 Test OpenNI2
Connect a depth sensor with the Link, then

```
root@kovan:~/OpenNI2# cd Bin/Arm-Release/
root@kovan:~/OpenNI2/Bin/Arm-Release# ./SimpleRead
[00000000]        0
[00033369]     5933
[00066738]        0
[00100107]        0

. . .

<< press any key to stop the example >>

root@kovan:~/OpenNI2/Bin/Arm-Release# cd ~/OpenNI2/
```

#### 1.8.5 Install OpenNI2
```
root@kovan:~/OpenNI2# mkdir -p /usr/include/OpenNI2
root@kovan:~/OpenNI2# cp -r Include/* /usr/include/OpenNI2/
root@kovan:~/OpenNI2# cp Bin/Arm-Release/lib* /usr/lib/
root@kovan:~/OpenNI2# cp -r Bin/Arm-Release/OpenNI2 /usr/lib/
root@kovan:~/OpenNI2# cd ~
```

#### 1.8.6 Delete Source Files
```
root@kovan:~# rm -r OpenNI2
```

## 2. Install libkipr_link_depth_sensor
### 2.1 Clone the Source Files
```
root@kovan:~# git clone https://github.com/zeltner/libkipr_link_depth_sensor.git
```

### 2.2 Build libkipr_link_depth_sensor
```
root@kovan:~# cd libkipr_link_depth_sensor/
root@kovan:~/libkipr_link_depth_sensor# make
```

### 2.3 Install libkipr_link_depth_sensor
```
root@kovan:~/libkipr_link_depth_sensor# make install
```

### 2.4 Update platform.hints

Update */etc/kovan/platform.hints* :
```
[General]
LD_FLAGS=-lkovan -lm -lpthread -lkipr_link_depth_sensor -lOpenNI2
C_FLAGS=-include kovan/kovan.h -include stdio.h -include target.h -include math.h -include libkipr_link_depth_sensor/depth.h
CPP_FLAGS=-include kovan/kovan.hpp -include stdio.h -include target.h -include math.h
```

## 3 Clean-up
### 3.1 Delete the Swap File
```
root@kovan:~# swapoff /swapfile
root@kovan:~# rm /swapfile
```

## 4 Examples
The libkipr_link_depth_sensor repository comes with a few examples located in *./kiss_ide_examples*.
You can clone libkipr_link_depth_sensor to your PC and open them with your KISS IDE.
