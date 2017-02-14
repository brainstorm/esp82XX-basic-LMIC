//Copyright 2015 <>< Charles Lohr, see LICENSE file.

#include "mem.h"
#include "c_types.h"
#include "user_interface.h"
#include "ets_sys.h"
#include "uart.h"
#include "osapi.h"
#include "espconn.h"
#include "esp82xxutil.h"
#include "commonservices.h"

#include "lmic/lmic.h"
#include "lmic/hal.h"

void user_rf_pre_init(void) { /*nothing*/ }
void ICACHE_FLASH_ATTR charrx( uint8_t c ){ /*Called from UART*/}

//For SDK 2.0.0 only.
uint32 ICACHE_FLASH_ATTR
user_rf_cal_sector_set(void)
{
    enum flash_size_map size_map = system_get_flash_size_map();
    uint32 rf_cal_sec = 0;

    switch (size_map) {
        case FLASH_SIZE_4M_MAP_256_256:
            rf_cal_sec = 128 - 8;
            break;

        case FLASH_SIZE_8M_MAP_512_512:
            rf_cal_sec = 256 - 5;
            break;

        case FLASH_SIZE_16M_MAP_512_512:
        case FLASH_SIZE_16M_MAP_1024_1024:
            rf_cal_sec = 512 - 5;
            break;

        case FLASH_SIZE_32M_MAP_512_512:
        case FLASH_SIZE_32M_MAP_1024_1024:
            rf_cal_sec = 1024 - 5;
            break;

        default:
            rf_cal_sec = 0;
            break;
    }

    return rf_cal_sec;
}


// LMIC application callbacks not used in his example
void os_getArtEui (u1_t* buf) {
}

void os_getDevEui (u1_t* buf) {
}

void os_getDevKey (u1_t* buf) {
}

void onEvent (ev_t ev) {
}


// Main
void user_init(void)
{
	uart_init(BIT_RATE_115200, BIT_RATE_115200);

	uart0_sendStr("\r\nesp82XX Web-GUI\r\n" VERSSTR "\b");

	printf( "Boot Ok.\n" );

	//os_init(); XXX: gettimeofday linker error
	LMIC_init();
	// Disable data rate adaptation
	LMIC_setAdrMode(0);
	// Disable link check validation
	LMIC_setLinkCheckMode(0);
	// Disable beacon tracking
	LMIC_disableTracking ();
	// Stop listening for downstream data (periodical reception)
	//LMIC_stopPingable();
	// Set data rate and transmit power (note: txpow seems to be ignored by the library)
	//LMIC_setDrTxpow(DR_SF7,14);

	//LMIC_sendAlive();
	//LMIC_reset();
	//LMIC_shutdown();
}