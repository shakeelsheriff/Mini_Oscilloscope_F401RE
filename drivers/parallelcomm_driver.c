#include "parallelcomm_driver.h"


void parallel_init(){
	//PB0 - PB7 as output
	  configure_GPIO(GPIOB,PIN_0,OUTPUT_STATE);
	  configure_GPIO(GPIOB,PIN_1,OUTPUT_STATE);
	  configure_GPIO(GPIOB,PIN_2,OUTPUT_STATE);
	  configure_GPIO(GPIOB,PIN_3,OUTPUT_STATE);
	  configure_GPIO(GPIOB,PIN_4,OUTPUT_STATE);
	  configure_GPIO(GPIOB,PIN_5,OUTPUT_STATE);
	  configure_GPIO(GPIOB,PIN_6,OUTPUT_STATE);
	  configure_GPIO(GPIOB,PIN_7,OUTPUT_STATE);

	  //PC0 - PC4 as output
	  configure_GPIO(GPIOC,PIN_0,OUTPUT_STATE);
	  configure_GPIO(GPIOC,PIN_1,OUTPUT_STATE);
	  configure_GPIO(GPIOC,PIN_2,OUTPUT_STATE);
	  configure_GPIO(GPIOC,PIN_3,OUTPUT_STATE);
	  configure_GPIO(GPIOC,PIN_4,OUTPUT_STATE);

	  Write_GPIO(GPIOC, PIN_1, HIGH); // CS inactive
	  Write_GPIO(GPIOC, PIN_3, HIGH); // WR inactive
	  Write_GPIO(GPIOC, PIN_4, HIGH); // RD inactive
}


void parallel_write(uint8_t data){
	GPIOB->ODR = (GPIOB->ODR & ~0x00FF) | (uint32_t)data;
}

void parallel_reset(uint8_t state){
	if(state){
		Write_GPIO(GPIOC, PIN_0, LOW);
	}else{
		Write_GPIO(GPIOC, PIN_0, HIGH);
	}
}

void parallel_chip_select(uint8_t enable){
	if(enable){
		Write_GPIO(GPIOC, PIN_1, LOW);
	}
	else{
		Write_GPIO(GPIOC, PIN_1, HIGH);
	}
}

void parallel_register_select(Register_Select RS_){
	if(RS_ == DATA){
		Write_GPIO(GPIOC, PIN_2, HIGH);
	}
	else{
		Write_GPIO(GPIOC, PIN_2, LOW);
	}
}

void parallel_write_strobe(void){
		Write_GPIO(GPIOC, PIN_3, LOW);
		Write_GPIO(GPIOC, PIN_3, HIGH);
}

void parallel_read_strobe(void){
		Write_GPIO(GPIOC, PIN_4, LOW);
		Write_GPIO(GPIOC, PIN_4, HIGH);
}
