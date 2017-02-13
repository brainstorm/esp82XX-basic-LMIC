# Experiment on porting LMIC (LoRa) to a bare ESP82XX 

***WARNING:*** Not working yet, too big footprint for now:

```
~/dev/espressif/esp-open-sdk/xtensa-lx106-elf/lib/gcc/xtensa-lx106-elf/4.8.5/../../../../xtensa-lx106-elf/bin/ld: image.elf section `.text' will not fit in region `iram1_0_seg'
~/dev/espressif/esp-open-sdk/xtensa-lx106-elf/lib/gcc/xtensa-lx106-elf/4.8.5/../../../../xtensa-lx106-elf/bin/ld: region `iram1_0_seg' overflowed by 5988 bytes
collect2: error: ld returned 1 exit status
```

ESP82XX-basic-LMIC is a stripped down version of @cnlohr's and @con-fu-se's [esp82XX-basic](https://github.com/con-f-use/esp82XX-basic) **plus** the LoRa ["LMIC" stack from IBM](https://www.research.ibm.com/labs/zurich/ics/lrsc/lmic.html), inspired on the [LMIC Arduino+ESP8266 port](https://github.com/things4u/LoRa-LMIC-1.51) from @things4u but
with a focus on just using bare ESP82xx's SDKs, without involving Arduino's ecosystem.
