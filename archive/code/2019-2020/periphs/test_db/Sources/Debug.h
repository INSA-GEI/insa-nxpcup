/*
 * Debug.h
 *
 *  Created on: Nov 30, 2019
 *      Author: User
 */

#ifndef DEBUG_H_
#define DEBUG_H_

#include <MKL25Z4.h>

#define CORE_CLOCK 48000000UL

#ifndef BAUDRATE
	#define BAUDRATE 115200
#endif

#define UARTXBEE //uncomment this line to enable uart on xbee module. By default uart is on opensda debugger

#define DEBUG_RED_Pin		(1 << 18)
#define DEBUG_GREEN_Pin		(1 << 19)
#define DEBUG_BLUE_Pin		(1 << 1)
#define DEBUG_CAM_LED_Pin   (1 << 12)

#define DEBUG_RED_OFF		(GPIOB_PSOR = DEBUG_RED_Pin)
#define DEBUG_RED_ON		(GPIOB_PCOR = DEBUG_RED_Pin)
#define DEBUG_GREEN_OFF		(GPIOB_PSOR = DEBUG_GREEN_Pin)
#define DEBUG_GREEN_ON		(GPIOB_PCOR = DEBUG_GREEN_Pin)
#define DEBUG_BLUE_OFF		(GPIOD_PSOR = DEBUG_BLUE_Pin)
#define DEBUG_BLUE_ON		(GPIOD_PCOR = DEBUG_BLUE_Pin)
#define DEBUG_CAM_LED_ON    (GPIOC_PSOR = DEBUG_CAM_LED_Pin)
#define DEBUG_CAM_LED_OFF   (GPIOC_PCOR = DEBUG_CAM_LED_Pin)

#define DISP_CLK_PIN		(1<<5)
#define DISP_SIN_PIN 		(1<<6)
#define DISP_LATCH_PIN 		(1<<10)

#define DISP_CLK_OFF		(GPIOC_PCOR = DISP_CLK_PIN)
#define DISP_CLK_ON			(GPIOC_PSOR = DISP_CLK_PIN)
#define DISP_SIN_OFF		(GPIOC_PCOR = DISP_SIN_PIN)
#define DISP_SIN_ON			(GPIOC_PSOR = DISP_SIN_PIN)
#define DISP_LATCH_OFF		(GPIOC_PCOR = DISP_LATCH_PIN)
#define DISP_LATCH_ON		(GPIOC_PSOR = DISP_LATCH_PIN)

#define LPTMR_ARR 65535


void debug_init();

//input stuff
unsigned char debug_getRotarySW();
unsigned char debug_getUserSW1(void);
unsigned char debug_getUserSW2(void);

//7segment dsplay stuff
void debug_displaySendRaw(uint8_t data);
void debug_displaySendNb(int8_t nb);


static inline void enable_irq(int n) {
    NVIC_ICPR |= 1 << (n - 16);
    NVIC_ISER |= 1 << (n - 16);			
}
static inline void __enable_irq(void)	{ asm volatile ("cpsie i"); }
static inline void __disable_irq(void)  { asm volatile ("cpsid i"); }

//uart stuff
typedef struct {
    volatile uint16_t head;
    volatile uint16_t tail;
    volatile uint16_t size;
    volatile uint8_t data[];
} RingBuffer;


void buf_reset(RingBuffer *buf, int size);
int buf_len(const RingBuffer *buf);
int buf_isfull(const RingBuffer *buf);
int buf_isempty(const RingBuffer *buf);
uint8_t buf_get_byte(RingBuffer *buf);
void buf_put_byte(RingBuffer *buf, uint8_t val);

void UART0_IRQHandler() __attribute__((interrupt("IRQ")));
int uart_write(const char *p, int len);
void uart_writeNb(int n);
int uart_write_err(const char *p, int len);
int uart_read(char *p, int len);
void uart_init(int baudrate);


/************* Low Power Timer (LPTMR) **************/

#define f_timer 1 // 0.4Hz to 11.5kHz max setting
#define PSC_LPTMR 2048
#define PSC_POWER 10
#define ARR_LPTMR (int)(CORE_CLOCK/(f_timer*(PSC_LPTMR+1)))

void lptmr_conf(void);

/************* ADC0 **************/
#define ADC_SCALING (3.3*(2.2+4.7)*1000.0/2.2)
#define ADC_RESOLUTION 1023		//10 bits 
#define BATT_SEUIL VBATT * ADC_RESOLUTION *0.5	//50% of battery


void BatteryVoltage(void);
void ADC_init(void);
#endif /* DEBUG_H_ */
