#include "CLOCK.h"
#include "SYS_INIT.h"
#include "GPIO.h"

int main(void){
	
	GPIO_PinState high 	= GPIO_PIN_SET;
	GPIO_PinState low 	= GPIO_PIN_RESET;
	
	
	initClock();
	sysInit();
	
	/* CLOCK ENABLE */
	RCC->AHB1ENR |= 1;
	
	GPIO_InitTypeDef PA5 = {5, GPIO_MODE_OUTPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW}; GPIO_Init(GPIOA, &PA5);
	GPIO_InitTypeDef PA6 = {6, GPIO_MODE_OUTPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW}; GPIO_Init(GPIOA, &PA6);
	GPIO_InitTypeDef PA7 = {7, GPIO_MODE_OUTPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW}; GPIO_Init(GPIOA, &PA7);
	
	while(1){
			
			GPIO_WritePin(GPIOA, PA5.Pin, high);
			GPIO_WritePin(GPIOA, PA6.Pin, high);
			GPIO_WritePin(GPIOA, PA7.Pin, high);
			ms_delay(500);
		
			GPIO_WritePin(GPIOA, 5, low);
			GPIO_WritePin(GPIOA, PA6.Pin, low);
			GPIO_WritePin(GPIOA, PA7.Pin, low);
			ms_delay(500);
		} 
}
