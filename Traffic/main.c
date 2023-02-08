#include "CLOCK.h"
#include "SYS_INIT.h"
#include "GPIO.h"
#include <stdlib.h>

static GPIO_PinState on 	= GPIO_PIN_SET;
static GPIO_PinState off 	= GPIO_PIN_RESET;


uint32_t random(){
	uint32_t upper = 3, lower = 0;
	return (rand() % (upper - lower + 1)) + lower;
	
}

uint32_t rrandom(uint32_t upper, uint32_t lower){
	return (rand() % (upper - lower + 1)) + lower;
}




uint32_t max(uint32_t a, uint32_t b){
	if(a>b) return a;
	else return b;
}


void noanimate(uint32_t loadL, uint32_t loadR, uint32_t loadU, uint32_t loadD, GPIO_InitTypeDef *carL, GPIO_InitTypeDef *carR, GPIO_InitTypeDef *carU, GPIO_InitTypeDef *carD, uint32_t frame_period, uint32_t GreenLRflag, uint32_t GreenUDflag) {
	uint32_t cari = 0;

	/* TURNING OFF ALL LOAD LEDs*/
	cari = 0;
	while(cari < 3){
		GPIO_WritePin(carL[cari], off); /*  CAR LEFT   */
		GPIO_WritePin(carR[cari], off); /*  CAR RIGHT  */
		
		GPIO_WritePin(carD[cari], off); /*  CAR DOWN     */
		GPIO_WritePin(carU[cari], off); /*  CAR UP     */

		cari = cari + 1;
	}
	
	
	cari = 3;
	while(cari > 0){
		if(loadD>= (cari)) GPIO_WritePin(carD[cari-1], on);
		if(loadU>= (cari)) GPIO_WritePin(carU[cari-1], on);
		
		if(loadL>= (cari)) GPIO_WritePin(carL[cari-1], on); 
		if(loadR>= (cari)) GPIO_WritePin(carR[cari-1], on); 
		
		cari = cari - 1;
	}
			
}




int main(void){
	
	
	
	initClock();
	sysInit();
	
	/* CLOCK ENABLE */
	RCC->AHB1ENR |= 1; /* PORT A */
	RCC->AHB1ENR |= 1 << 1; /* PORT B */
	RCC->AHB1ENR |= 1 << 2; /* PORT C */
	
	uint32_t frame_period = 1000; /* ANIMATION FRAME TIME */
	
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
	
	GPIO_InitTypeDef carL[] = {PB13, PB14, PB15};
	// GPIO_InitTypeDef carL[] = {PB15, PB14, PB13};
	
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
	

	uint32_t loadL = random();
	uint32_t loadR = 1;
	uint32_t loadU = random();
	uint32_t loadD = random();
	
//	uint32_t loadL = 3;
//	uint32_t loadR = 3;
//	uint32_t loadU = 2;
//	uint32_t loadD = 2;
//	
	uint32_t loadi, loadLR, loadUD;
	
	uint32_t GreenUDflag = 1;
  uint32_t GreenLRflag = 0;
	
	GPIO_WritePin(RedLR,		off);
	GPIO_WritePin(YellowLR, off);
	GPIO_WritePin(GreenLR,  off);
	
	GPIO_WritePin(RedUD,		off);
	GPIO_WritePin(YellowUD, off);
	GPIO_WritePin(GreenUD,  off);
	
	uint32_t loadIncWhileGreen = 0; /* May be set to random(0,1) */
	
	
	while(1){
					
				noanimate(loadL, loadR, loadU, loadD, carL, carR, carU, carD, frame_period, GreenLRflag, GreenUDflag);  ms_delay(frame_period/10U); 
		
				loadLR = loadL + loadR;
				loadUD = loadD + loadU;
		
				if((loadLR - loadUD) > 1){
			
					if(loadLR >= (loadUD + 1)){ /* Load is heavier in left-right */
						GreenLRflag = 1; /* So, open left-right green */
						GreenUDflag = 0;
					}
					else{ /* Load is heavier in up-down */
						GreenUDflag = 1; /* So, open up-down green */
						GreenLRflag = 0;
					}
				
				
				/* GREEN LEFT RIGHT, RED UP DOWN */
				if( GreenLRflag == 1  && GreenUDflag == 0){
					
					
					GPIO_WritePin(RedLR,  off );
					GPIO_WritePin(GreenUD,	off );
					
					/* Yellow UD */
					GPIO_WritePin(YellowUD,  on);
					GPIO_WritePin(YellowLR,  off);
					ms_delay(frame_period*2);
					GPIO_WritePin(YellowUD,  off);
					
					GPIO_WritePin(GreenLR,  on);
					GPIO_WritePin(RedUD,	on);
					GPIO_WritePin(YellowUD,  off);
					
				}
				
				/* RED LEFT RIGHT, GREEN UP DOWN */
				else if(GreenUDflag == 1 && GreenLRflag == 0){
				
					GPIO_WritePin(GreenLR,  off );
					GPIO_WritePin(RedUD,	off );
					
					/* Yellow LR */
					GPIO_WritePin(YellowLR,  on);
					GPIO_WritePin(YellowUD,  off);
					ms_delay(frame_period*2);
					GPIO_WritePin(YellowLR,  off);
					
					GPIO_WritePin(RedLR,  on);
					GPIO_WritePin(GreenUD,	on);
					GPIO_WritePin(YellowLR,  off);
					
				}
				}
				
				noanimate(loadL, loadR, loadU, loadD, carL, carR, carU, carD, frame_period, GreenLRflag, GreenUDflag);  ms_delay(frame_period/10U); 
				noanimate(loadL, loadR, loadU, loadD, carL, carR, carU, carD, frame_period, GreenLRflag, GreenUDflag);  ms_delay(frame_period/10U); 
				
				
				
				
				/* LOAD UPDATE */
				
				/* GREEN LEFT RIGHT, RED UP DOWN */
				if(GreenLRflag == 1){
					
					loadL = loadL - 1;
					loadR = loadR - 1;

					// loadU = max( loadU - 0 + random() , 3) ;
					// loadD = max( loadD - 0 + random() , 3) ;
					loadU = loadU + 1;
					loadD = loadD + 1 ;
				}
				
				/* RED LEFT RIGHT, GREEN UP DOWN */
				else if(GreenUDflag == 1){
					
					// loadL = max( loadL - 0 + random() , 3) ;
					// loadR = max( loadR - 0 + random() , 3) ;
					loadL = loadL + 1;
					loadR = loadR + 1;

					loadU = loadU - 1;
					loadD = loadD - 1;
				}
				
				noanimate(loadL, loadR, loadU, loadD, carL, carR, carU, carD, frame_period, GreenLRflag, GreenUDflag); ms_delay(frame_period/10U); 
				
		  
			//	ms_delay(frame_period*20); 
				
		  
	}
}
