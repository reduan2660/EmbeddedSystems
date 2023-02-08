#include "CLOCK.h"
#include "SYS_INIT.h"
#include "GPIO.h"
#include <stdlib.h>

static GPIO_PinState high 	= GPIO_PIN_SET;
static GPIO_PinState low 	= GPIO_PIN_RESET;


int random(){
	int upper = 3, lower = 1;
	return (rand() % (upper - lower + 1)) + lower;
	
}


int max(int a, int b){
	if(a>b) return a;
	else return b;
}


int main(void){
	
	
	
	initClock();
	sysInit();
	
	/* CLOCK ENABLE */
	RCC->AHB1ENR |= 1; /* PORT A */
	RCC->AHB1ENR |= 1 << 1; /* PORT B */
	RCC->AHB1ENR |= 1 << 2; /* PORT C */
	
	uint32_t frame_period = 50; /* ANIMATION FRAME TIME */
	
	/* CAR RIGHT */
	GPIO_InitTypeDef PA5 = {5, GPIO_MODE_OUTPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIOA}; GPIO_Init(GPIOA, &PA5);
	GPIO_InitTypeDef PA6 = {6, GPIO_MODE_OUTPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIOA}; GPIO_Init(GPIOA, &PA6);
	GPIO_InitTypeDef PA7 = {7, GPIO_MODE_OUTPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIOA}; GPIO_Init(GPIOA, &PA7);
	
	// GPIO_InitTypeDef carR[] = {PA7, PA6, PA5};
	GPIO_InitTypeDef carR[] = {PA5, PA6, PA7};
	
	/* CAR RIGHT */
	GPIO_InitTypeDef PB13 = {13, GPIO_MODE_OUTPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIOB}; GPIO_Init(GPIOB, &PB13);
	GPIO_InitTypeDef PB14 = {14, GPIO_MODE_OUTPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIOB}; GPIO_Init(GPIOB, &PB14);
	GPIO_InitTypeDef PB15 = {15, GPIO_MODE_OUTPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIOB}; GPIO_Init(GPIOB, &PB15);
	
	// GPIO_InitTypeDef carL[] = {PB13, PB14, PB15};
	GPIO_InitTypeDef carL[] = {PB15, PB14, PB13};
	
	/* CAR DOWN */
	GPIO_InitTypeDef PA12 = {12, GPIO_MODE_OUTPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIOA}; GPIO_Init(GPIOA, &PA12);
	GPIO_InitTypeDef PA11 = {11, GPIO_MODE_OUTPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIOA}; GPIO_Init(GPIOA, &PA11);
	GPIO_InitTypeDef PA9  = { 9, GPIO_MODE_OUTPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIOA}; GPIO_Init(GPIOA, &PA9);
	
	// GPIO_InitTypeDef carD[] = {PA12, PA11, PA9};
	GPIO_InitTypeDef carD[] = {PA9, PA12, PA11};
	
	/* CAR UP */
	GPIO_InitTypeDef PA10 = {10, GPIO_MODE_OUTPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIOA}; GPIO_Init(GPIOA, &PA10);
	GPIO_InitTypeDef PB5 =  { 5, GPIO_MODE_OUTPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIOB}; GPIO_Init(GPIOB, &PB5);
	GPIO_InitTypeDef PA8 =  { 8, GPIO_MODE_OUTPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIOA}; GPIO_Init(GPIOA, &PA8);
	
	GPIO_InitTypeDef carU[] = {PA10, PB5, PA8};
	// GPIO_InitTypeDef carU[] = {PA13, PA14, PA15};
	
	
	/* LEFT RIGHT SIGNAL LED */
	GPIO_InitTypeDef RedLR 		=  {6, GPIO_MODE_OUTPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIOC}; GPIO_Init(GPIOC, &RedLR);
	GPIO_InitTypeDef YellowLR   =  {5, GPIO_MODE_OUTPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIOC}; GPIO_Init(GPIOC, &YellowLR);	
	GPIO_InitTypeDef GreenLR  	=  {8, GPIO_MODE_OUTPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIOC}; GPIO_Init(GPIOC, &GreenLR );
	
	/* UP DOWN SIGNAL LED */
	GPIO_InitTypeDef RedUD    =  { 0, GPIO_MODE_OUTPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIOA}; GPIO_Init(GPIOA, &RedUD);
	GPIO_InitTypeDef YellowUD =  { 1, GPIO_MODE_OUTPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIOA}; GPIO_Init(GPIOA, &YellowUD);	
	GPIO_InitTypeDef GreenUD  =  { 4, GPIO_MODE_OUTPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIOA}; GPIO_Init(GPIOA, &GreenUD );
	

	int loadL = random();
	int loadR = random();
	int loadU = random();
	int loadD = random();
	int loadi, loadLR, loadUD;
	
	int GreenUDflag = 1;
  int GreenLRflag = 0;

	
	GPIO_WritePin(RedLR,	high);
	GPIO_WritePin(YellowLR, high);
	GPIO_WritePin(GreenLR,  high);
	
	GPIO_WritePin(RedUD,	high);
	GPIO_WritePin(YellowUD, low);
	GPIO_WritePin(GreenUD,  high);
	
	GPIO_WritePin(carR[0],	high);
	GPIO_WritePin(carR[1],	high);
	GPIO_WritePin(carR[2],	high);
	
	GPIO_WritePin(carL[0],	high);
	GPIO_WritePin(carL[1],	high);
	GPIO_WritePin(carL[2],	high);
	
	GPIO_WritePin(carU[0],	high);
	GPIO_WritePin(carU[1],	high);
	GPIO_WritePin(carU[2],	high);
	
	GPIO_WritePin(carD[0],	high);
	GPIO_WritePin(carD[1],	high);
	GPIO_WritePin(carD[2],	high);
	
	
}
