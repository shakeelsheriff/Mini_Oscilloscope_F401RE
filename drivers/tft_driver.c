#include "tft_driver.h"

void ili941_init(){

	TFT_HW_Reset();
	TFT_SW_reset();


}

void TFT_HW_Reset(void){
	parallel_reset(1); //Reset Low
	parallel_reset(0); //Reset High
}

void TFT_WriteCommand(uint8_t command){
	parallel_chip_select(1);
	parallel_register_select(COMMAND);
	parallel_write(command);
	parallel_write_strobe();
	parallel_chip_select(0);
}

void TFT_WriteData(uint8_t data){
	parallel_chip_select(1);
	parallel_register_select(DATA);
	parallel_write(data);
	parallel_write_strobe();
	parallel_chip_select(0);
}

void No_operation_mode(void){
	TFT_WriteCommand(NOP);
}

void TFT_SW_reset(void){
	TFT_WriteCommand(SFT_RST);
	HAL_Delay(5); //It will be necessary to wait 5msec before sending new command following software reset
}
