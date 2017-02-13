#include "lmic.h"
#include "hal.h"
#include "user_interface.h"
#include "osapi.h"
#include "c_types.h"
#include "uart.h"

#define US_PER_OSTICK 20

// -----------------------------------------------------------------------------
// I/O

struct {
    uint32_t nss;
    uint32_t rxtx;
    uint32_t rst;
    uint32_t miso;
    uint32_t mosi;
} pins;

static void hal_io_init () {
    gpio_init();
    uart_init(BIT_RATE_115200, BIT_RATE_115200);

	uart0_sendStr("\r\nLMIC for esp82xx initializing\r\n");

    pins.nss = PERIPHS_IO_MUX_SD_CLK_U;
    pins.rxtx = PERIPHS_IO_MUX_GPIO0_U;
    pins.rst = PERIPHS_IO_MUX_SD_DATA2_U;
    pins.miso = PERIPHS_IO_MUX_MTDI_U;
    pins.mosi = PERIPHS_IO_MUX_GPIO2_U;
    
    //PIN_FUNC_SELECT(pins.mosi, FUNC_GPIO2);
    PIN_FUNC_SELECT(pins.rst, FUNC_GPIO9);
    while(1) {
        gpio_output_set(0, BIT2, BIT2, 0);
        os_delay_us(500000);
        gpio_output_set(1, BIT2, BIT2, 1);
    }
    

}

// val == 1  => tx 1
void hal_pin_rxtx (u1_t val) {
    return;
}

// set radio RST pin to given value (or keep floating!)
void hal_pin_rst (u1_t val) {
    return;
}

//XXX: NUM_DIO
//int NUM_DIO = 0;
//static int dio_states[NUM_DIO] = {0};

static void hal_io_check() {
    return;
}

// -----------------------------------------------------------------------------
// SPI

//static const SPISettings settings(10E6, MSBFIRST, SPI_MODE0);

static void hal_spi_init () {
    return;
}

void hal_pin_nss (u1_t val) {
    return;
}

// perform SPI transaction with radio
u1_t hal_spi (u1_t out) {
    u1_t res = 0;
    return res;
}

// -----------------------------------------------------------------------------
// TIME

// Keep track of overflow of micros()
u4_t lastmicros=0;
u8_t addticks=0;

static void hal_time_init () {
    lastmicros=0;
    addticks=0;
}

u4_t hal_ticks () {
    // LMIC requires ticks to be 15.5μs - 100 μs long
    // Check for overflow of micros()
    
    /* XXX: does micros() cause gettimeofday errors?
    
    if ( micros()  < lastmicros ) {
        addticks += (u8_t)4294967296 / US_PER_OSTICK;
    }
    lastmicros = micros();
    return ((u8_t)micros() / US_PER_OSTICK) + addticks;
    */
    
    //return micros(); XXX: yes, it does!
    return 10;
}

// Returns the number of ticks until time. 
static u4_t delta_time(u8_t time) {
      u8_t t = hal_ticks( );
      s4_t d = time - t;
      if (d<=1) { return 0; }
      else {
        return (u4_t)(time - hal_ticks());
      }
}

void hal_waitUntil (u4_t time) {
    u4_t delta = delta_time(time);
    os_delay_us(delta * US_PER_OSTICK);
}

// check and rewind for target time
u1_t hal_checkTimer (u4_t time) {
    // No need to schedule wakeup, since we're not sleeping
    return delta_time(time) <= 0;
}

static u8_t irqlevel = 0;

void hal_disableIRQs () {
    //cli();
    return;
}

void hal_enableIRQs () {
    return;
}

void hal_sleep () {
    // Not implemented
}

// -----------------------------------------------------------------------------
// For ESP8266: If the radio is not connected well, we will probably get a
// wdt (watchdog) problem in this routine.
//
void hal_init () {
    // configure radio I/O and interrupt handler
    hal_io_init();
    // configure radio SPI
    hal_spi_init();
    // configure timer and interrupt handler
    hal_time_init();
}

void hal_failed () {
    return;
}

void debug(u4_t n) {return;}
void debug_str(const char *s) {return;}