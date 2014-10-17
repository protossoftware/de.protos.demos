/*
 * Main.c
 *
 *  Created on: 12.10.2014
 *      Author: TJung
 */

#include <DAVE3.h>			//Declarations from DAVE3 Code Generation (includes SFR declaration)
#include "GUI.h"
#include "stdio.h"

#define I2C_ADDR 0x9A //0x98
/*******************************************************************************
 ** EXTERN Declarations                                                       **
 ******************************************************************************/
extern const GUI_BITMAP bmIFX_LOGO;
extern const GUI_BITMAP bmXMC_test;
extern const GUI_BITMAP bmeTriceLogo;
extern const GUI_BITMAP bmprotosLogo;

void delay(unsigned int count);

/* To store the conversion result */
ADC001_ResultHandleType Result;
#define DELAY	20000000


int main(void) {
// Configure message data length
	I2C001_DataType data1, data2, data3, data4, data5, data6; // Data type to compose USIC I2C TDF code and I2C data in one 16 bit word to be written to the USIC FIFO
	unsigned char i2c_counter = 0;
	char strBuf[50];
	unsigned long i;
//	status_t status;		// Declaration of return variable for DAVE3 APIs (toggle comment if required)

	DAVE_Init(); // Initialization of DAVE Apps

	/* Initialize GUI Library */
	GUI_Init();

	/* Generate Load Event*/
	ADC001_GenerateLoadEvent(&ADC001_Handle0);

	/* Set background colour */
	GUI_SetBkColor(GUI_WHITE);

	/* Clear screen */
	GUI_Clear();

	/*  I2C sequence to set all 8 GPIO of the PC 9502 as output */
	// Transmission by the master with start condition,I2C WRITE condition and slave address
	data1.Data1.TDF_Type = I2C_TDF_MStart;
	data1.Data1.Data = (I2C_ADDR | I2C_WRITE); // address of  the GPI expander PCA 9502
	while (!I2C001_WriteData(&I2C001_Handle0, &data1))
		;

	// Write data to address the Direction register
	data2.Data1.TDF_Type = I2C_TDF_MTxData;
	data2.Data1.Data = 0x50; // address of  direction register in the GPI expander
	while (!I2C001_WriteData(&I2C001_Handle0, &data2))
		;

	// Write data to the Direction register
	data3.Data1.TDF_Type = I2C_TDF_MTxData;
	data3.Data1.Data = 0xFF; //  all GPIOs are set as output
	while (!I2C001_WriteData(&I2C001_Handle0, &data3))
		;

	/*  I2C sequence to the turn on every other LED:  write into the State register 0xAA */
	// Transmit repeated start condition and slave address
	data4.Data1.TDF_Type = I2C_TDF_MRStart;
	data4.Data1.Data = I2C_ADDR | I2C_WRITE; // address of the GPI expander PCA 9502
	while (!I2C001_WriteData(&I2C001_Handle0, &data4))
		;

	// Write data to address the State register
	data2.Data1.TDF_Type = I2C_TDF_MTxData;
	data2.Data1.Data = 0x58; // address of  state register in the GPI expander
	while (!I2C001_WriteData(&I2C001_Handle0, &data2))
		;

	// Write data to the sate register to turn some other LED on
	data3.Data1.TDF_Type = I2C_TDF_MTxData;
	data3.Data1.Data = 0x3C; //  turn any other LED on, LED is on when writing 0
	while (!I2C001_WriteData(&I2C001_Handle0, &data3))
		;

	// Write data to the sate register to turn some other LED on
	data3.Data1.TDF_Type = I2C_TDF_MTxData;
	data3.Data1.Data = 0x41; //  turn any other LED on, LED is on when writing 0
	while (!I2C001_WriteData(&I2C001_Handle0, &data3))
		;

	//----------------------

	while (1) {
		/* Display IFX image */
		GUI_DrawBitmap(&bmIFX_LOGO, 5, 32);
		delay(DELAY);
		GUI_Clear();

		/* Display text */
		GUI_SetFont(&GUI_Font24B_1);
		GUI_SetColor(GUI_BLUE);
		GUI_DispStringHCenterAt("and", 70, 60);
		delay(DELAY);
		GUI_Clear();

		GUI_DrawBitmap(&bmprotosLogo, 5, 20);
		delay(DELAY);
		GUI_Clear();

		/* Display text */
		GUI_SetFont(&GUI_Font24B_1);
		GUI_SetColor(GUI_BLUE);
		GUI_DispStringHCenterAt("proudly", 80, 30);
		GUI_DispStringHCenterAt("presents...", 80, 60);
		delay(DELAY);
		GUI_Clear();

		GUI_DrawBitmap(&bmeTriceLogo, 25, 10);
		delay(DELAY);
		GUI_Clear();

		/* Display text */
		GUI_SetFont(&GUI_Font24B_1);
		GUI_SetColor(GUI_BLUE);
		GUI_DispStringHCenterAt("on", 80, 60);
		delay(DELAY);
		GUI_Clear();

		/* Display XMC image */
		GUI_DrawBitmap(&bmXMC_test, 0, 0);
		delay(DELAY);
		GUI_Clear();

		IO004_TogglePin(IO004_Handle1);
		UART001_WriteDataBytes(&UART001_Handle0, "Test \n", 6);

		data3.Data1.TDF_Type = I2C_TDF_MTxData;
		data3.Data1.Data = i2c_counter++; //  turn any other LED on, LED is on when writing 0
		while (!I2C001_WriteData(&I2C001_Handle0, &data3))
			;

		for (i = 0; i < 2000; i++) {
//		ADC001_GetResult(&ADC001_Handle0,&Result);
			ADC001_GetResult(&ADC001_Handle0, &Result);
			sprintf(strBuf, "%04i", Result.Result / 10);
			GUI_DispStringHCenterAt(strBuf, 70, 60);
			//delay(30000000);
			//GUI_Clear();
		}

	}
	return 0;
}

/**
 * @brief Delay function:This routine is used for creating delay
 * @param[in] count (value = n sec X 12 X 1000000)
 * @return None
 */
void delay(unsigned int count) {
	while (count != 0) {
		count--;
	}
}

/* Global Result Register ISR*/
void GlobalResultEvent(void) {
	/* Read the Result Register*/
	ADC001_GetResult(&ADC001_Handle0, &Result);
}
