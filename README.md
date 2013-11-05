libkipr_link_depth_sensor
=========================

libkipr_link_depth_sensor is a depth sensor library for the [KIPR Link Robot Controller](http://www.kipr.org/products/link). It is designed in such a way that it can be easily integrated and used by the KISS IDE.

**DISCLAIMER:**
libkipr_link_depth_sensor is currently under development and not part of the KIPR Link firmware. Installing libkipr_link_depth_sensor and its prerequisites requires modifying the KIPR Link firmware which, even following carefully this README, may result in a non-working system. So you should be aware that if you follow this instruction, you do it at your own risk.

## 1 Installing Prerequisites

### 1.1 Update the KIPR Link Firmware

Update the firmware to version 1.9.6 following the [instructions](http://www.kipr.org/kiss-platform-link-firmware) 

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

### 1.4 Install wget with HTPS support

*wget* with HTPS support is required for downloading source from gitHub directly from the Link. An alternative way is to download the source by a PC and copy it to the KIPR Link.

```
root@kovan:~# opkg install http://netv.bunnie-bar.com/build/kovan-debug/LATEST/armv5te/wget_1.13.4-r13.1_armv5te.ipk
root@kovan:~# mkdir -p /etc/ssl/certs
```

Add *export SSL_CERT_DIR=/etc/ssl/certs* to the file */etc/profile*

```
root@kovan:~# source /etc/profile
root@kovan:~# opkg install http://netv.bunnie-bar.com/build/kovan-debug/LATEST/armv5te/openssl-misc_1.0.0g-r15.0_armv5te.ipk
root@kovan:~# cd /etc/ssl/certs
root@kovan:/etc/ssl/certs# wget --no-check-certificate https://www.digicert.com/CACerts/DigiCertHighAssuranceEVRootCA.crt
root@kovan:/etc/ssl/certs# openssl x509 -inform der -in DigiCertHighAssuranceEVRootCA.crt -out DigiCertHighAssuranceEVRootCA.pem 
root@kovan:/etc/ssl/certs# ln -s DigiCertHighAssuranceEVRootCA.pem `openssl x509 -hash -noout -in DigiCertHighAssuranceEVRootCA.pem`.0
root@kovan:/etc/ssl/certs# wget https://www.digicert.com/CACerts/DigiCertHighAssuranceEVCA-1.crt
root@kovan:/etc/ssl/certs# openssl x509 -inform der -in DigiCertHighAssuranceEVCA-1.crt -out DigiCertHighAssuranceEVCA-1.pem
root@kovan:/etc/ssl/certs# ln -s DigiCertHighAssuranceEVCA-1.pem `openssl x509 -hash -noout -in DigiCertHighAssuranceEVCA-1.pem`.0
```
