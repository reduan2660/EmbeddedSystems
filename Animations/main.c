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



void animate(int loadL, int loadR, int loadU, int loadD, GPIO_InitTypeDef *carL, GPIO_InitTypeDef *carR, GPIO_InitTypeDef *carU, GPIO_InitTypeDef *carD, uint32_t frame_period, int GreenLRflag, int GreenUDflag) {
	
				/* TURNING ON LOAD LEDs*/
				int loadi = 0;
				while(loadi < 3){
					if((loadL <= loadi + 1)) GPIO_WritePin(GPIOB, carL[loadi].Pin, high); /*  CAR LEFT   */
					if((loadR <= loadi + 1)) GPIO_WritePin(GPIOA, carR[loadi].Pin, high); /*  CAR RIGHT  */
					if((loadD <= loadi + 1)) GPIO_WritePin(GPIOA, carD[loadi].Pin, high); /*  CAR DOWN     */
					loadi = loadi + 1;
					
					ms_delay(frame_period);
				}
				
				ms_delay(frame_period*30);
			
				/* TURNING OFF LOAD LEDs*/
				loadi = 0;
				while(loadi < 3){
					if((loadL <= loadi + 1) && GreenLRflag == 1) GPIO_WritePin(GPIOB, carL[loadi].Pin, low); /*  CAR LEFT   */
					if((loadR <= loadi + 1) && GreenLRflag == 1) GPIO_WritePin(GPIOA, carR[loadi].Pin, low); /*  CAR RIGHT  */
					if((loadD <= loadi + 1) && GreenUDflag == 1) GPIO_WritePin(GPIOA, carD[loadi].Pin, low); /*  CAR DOWN     */
					loadi = loadi + 1;
					
					ms_delay(frame_period);
				}
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
	GPIO_InitTypeDef PA5 = {5, GPIO_MODE_OUTPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW}; GPIO_Init(GPIOA, &PA5);
	GPIO_InitTypeDef PA6 = {6, GPIO_MODE_OUTPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW}; GPIO_Init(GPIOA, &PA6);
	GPIO_InitTypeDef PA7 = {7, GPIO_MODE_OUTPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW}; GPIO_Init(GPIOA, &PA7);
	
	// GPIO_InitTypeDef carR[] = {PA7, PA6, PA5};
	GPIO_InitTypeDef carR[] = {PA5, PA6, PA7};
	
	/* CAR RIGHT */
	GPIO_InitTypeDef PB13 = {13, GPIO_MODE_OUTPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW}; GPIO_Init(GPIOB, &PB13);
	GPIO_InitTypeDef PB14 = {14, GPIO_MODE_OUTPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW}; GPIO_Init(GPIOB, &PB14);
	GPIO_InitTypeDef PB15 = {15, GPIO_MODE_OUTPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW}; GPIO_Init(GPIOB, &PB15);
	
	// GPIO_InitTypeDef carL[] = {PB13, PB14, PB15};
	GPIO_InitTypeDef carL[] = {PB15, PB14, PB13};
	
	/* CAR DOWN */
	GPIO_InitTypeDef PA12 = {12, GPIO_MODE_OUTPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW}; GPIO_Init(GPIOA, &PA12);
	GPIO_InitTypeDef PA11 = {11, GPIO_MODE_OUTPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW}; GPIO_Init(GPIOA, &PA11);
	GPIO_InitTypeDef PA9  = { 9, GPIO_MODE_OUTPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW}; GPIO_Init(GPIOA, &PA9);
	
	// GPIO_InitTypeDef carD[] = {PA12, PA11, PA9};
	GPIO_InitTypeDef carD[] = {PA9, PA11, PA12};
	
	/* CAR UP */
	GPIO_InitTypeDef PC13 = {13, GPIO_MODE_OUTPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW}; GPIO_Init(GPIOC, &PC13);
	GPIO_InitTypeDef PC14 = {14, GPIO_MODE_OUTPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW}; GPIO_Init(GPIOC, &PC14);
	GPIO_InitTypeDef PC15 = {15, GPIO_MODE_OUTPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW}; GPIO_Init(GPIOC, &PC15);
	
	GPIO_InitTypeDef carU[] = {PC13, PC14, PC15};
	// GPIO_InitTypeDef carU[] = {PA13, PA14, PA15};
	
	
	/* LEFT RIGHT SIGNAL LED */
	GPIO_InitTypeDef RedLR    =  {5, GPIO_MODE_OUTPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW}; GPIO_Init(GPIOC, &RedLR   );
	GPIO_InitTypeDef YellowLR =  {6, GPIO_MODE_OUTPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW}; GPIO_Init(GPIOC, &YellowLR);	
	GPIO_InitTypeDef GreenLR  =  {8, GPIO_MODE_OUTPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW}; GPIO_Init(GPIOC, &GreenLR );
	
	/* UP DOWN SIGNAL LED */
	GPIO_InitTypeDef RedUD    =  { 0, GPIO_MODE_OUTPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW}; GPIO_Init(GPIOA, &RedUD   );
	GPIO_InitTypeDef YellowUD =  { 1, GPIO_MODE_OUTPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW}; GPIO_Init(GPIOA, &YellowUD);	
	GPIO_InitTypeDef GreenUD  =  { 4, GPIO_MODE_OUTPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW}; GPIO_Init(GPIOA, &GreenUD );
	

	int loadL = random();
	int loadR = random();
	int loadU = random();
	int loadD = random();
	int loadi, loadLR, loadUD;
	
	int GreenUDflag = 1;
  int GreenLRflag = 0;
	
	GPIO_WritePin(GPIOC, RedLR.Pin,		 low);
	GPIO_WritePin(GPIOC, YellowLR.Pin, low);
	GPIO_WritePin(GPIOC, GreenLR.Pin,  low);
	
	GPIO_WritePin(GPIOA, RedUD.Pin,		 low);
	GPIO_WritePin(GPIOA, YellowUD.Pin, low);
	GPIO_WritePin(GPIOA, GreenUD.Pin,  low);
	
	int loadIncWhileGreen = 0; /* May be set to random(0,1) */
	
	
	while(1){
		    
				loadLR = loadL + loadR;
				loadUD = loadD + loadU;
		
				if(loadLR >= loadUD){ /* Load is heavier in left-right */
					GreenLRflag = 0; /* So, open left-right green */
					GreenUDflag = 1;
				}
				else{
					GreenUDflag = 0;
					GreenLRflag = 1;
				}
				
				/* GREEN LEFT RIGHT, RED UP DOWN */
				if( GreenUDflag == 1){
					
					GPIO_WritePin(GPIOC, GreenLR.Pin,  high);
					GPIO_WritePin(GPIOA, GreenUD.Pin,	 low );
					
					GPIO_WritePin(GPIOC, RedLR.Pin,    low );
					GPIO_WritePin(GPIOA, RedUD.Pin,		 high);
					
					
					/* UPDATE LOAD */
					loadL = loadL - 1 + loadIncWhileGreen;
					loadR = loadR - 1 + loadIncWhileGreen;
					loadU = max( loadU - 0 + random() , 3) ;
					loadD = max( loadD - 0 + random() , 3) ;
					
				}
				
				/* RED LEFT RIGHT, GREEN UP DOWN */
				else if(GreenLRflag == 1){
				
					GPIO_WritePin(GPIOC, GreenLR.Pin,  low);
					GPIO_WritePin(GPIOA, GreenUD.Pin,	 high );
					
					GPIO_WritePin(GPIOC, RedLR.Pin,    high );
					GPIO_WritePin(GPIOA, RedUD.Pin,		 low);
					
					
					/* UPDATE LOAD */
					loadL = max( loadL - 0 + random() , 3) ;
					loadR = max( loadR - 0 + random() , 3) ;
					loadU = loadU - 1 + loadIncWhileGreen;
					loadD = loadD - 1 + loadIncWhileGreen;
		
				}
				
				animate(loadL, loadR, loadU, loadD, carL, carR, carU, carD, frame_period, GreenLRflag, GreenUDflag);
				
				/* LOAD UPDATE */
				
				/* GREEN LEFT RIGHT, RED UP DOWN */
				if(GreenLRflag == 1){
				
				}
				
				/* RED LEFT RIGHT, GREEN UP DOWN */
				else if(GreenUDflag == 1){
					
					
				}
				
		  
				ms_delay(frame_period*3); 
				
		  
	}
}
