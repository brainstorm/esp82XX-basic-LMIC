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
#include "time.h"

#include "lmic/lmic.h"
#include "lmic/hal.h"

void ICACHE_FLASH_ATTR charrx( uint8_t c )
{
	//Called from UART.
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