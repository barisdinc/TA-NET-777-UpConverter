// FUSES
// low: 79
// high: FF

#define F_CPU 8000000L 
//4800000L

#include <avr/io.h>
#include <util/delay.h>


#define FREQ_STEP 25		// kHz
#define FREQ_REF 25000		// kHz

#define FREQ1 1967000  //433 MHz
#define FREQ2 2256000  //144 MHz
#define FREQ3 2349000  //51 MHz
#define FREQ4 2371000  //29 MHz
#define FREQ5 1150000  //1250 MHz

#define ADF4351_PORT PORTB
#define ADF4351_DDR  DDRB
#define ADF4351_LE   PINB0
#define ADF4351_DATA PINB1
#define ADF4351_CLK  PINB2

#define KEY1 PINB3
#define KEY2 PINB4
#define KEY_PORT PORTB
#define KEY_DDR DDRB
#define KEY_PIN PINB

#if (FREQ1 >= 550000 && FREQ1 < 1100000)
	#define ADF4351_RF_DIVIDER_SELECT_F1 2
	#define ADF4351_RF_DIVIDER_F1 1
	#define ADF4351_MUL_F1 4
#elif (FREQ1 >= 1100000 && FREQ1 < 2200000)
	#define ADF4351_RF_DIVIDER_SELECT_F1 1
	#define ADF4351_RF_DIVIDER_F1 2
	#define ADF4351_MUL_F1 2
#elif (FREQ1 >= 2200000 && FREQ1 <= 4400000)
	#define ADF4351_RF_DIVIDER_SELECT_F1 0
	#define ADF4351_RF_DIVIDER_F1 4
	#define ADF4351_MUL_F1 1
#endif
#define ADF4351_MODULUS_F1 FREQ_REF/(FREQ_STEP*ADF4351_RF_DIVIDER_F1)
#define ADF4351_INT_F1 (FREQ1*ADF4351_MUL_F1/FREQ_REF)
#define ADF4351_FRAC_F1 (FREQ1*ADF4351_MUL_F1-ADF4351_INT_F1*FREQ_REF)/(FREQ_STEP*ADF4351_RF_DIVIDER_F1)


#if (FREQ2 >= 550000 && FREQ2 < 1100000)
	#define ADF4351_RF_DIVIDER_SELECT_F2 2
	#define ADF4351_RF_DIVIDER_F2 1
	#define ADF4351_MUL_F2 4
#elif (FREQ2 >= 1100000 && FREQ2 < 2200000)
	#define ADF4351_RF_DIVIDER_SELECT_F2 1
	#define ADF4351_RF_DIVIDER_F2 2
	#define ADF4351_MUL_F2 2
#elif (FREQ2 >= 2200000 && FREQ2 <= 4400000)
	#define ADF4351_RF_DIVIDER_SELECT_F2 0
	#define ADF4351_RF_DIVIDER_F2 4
	#define ADF4351_MUL_F2 1
#endif
#define ADF4351_MODULUS_F2 FREQ_REF/(FREQ_STEP*ADF4351_RF_DIVIDER_F2)
#define ADF4351_INT_F2 (FREQ2*ADF4351_MUL_F2/FREQ_REF)
#define ADF4351_FRAC_F2 (FREQ2*ADF4351_MUL_F2-ADF4351_INT_F2*FREQ_REF)/(FREQ_STEP*ADF4351_RF_DIVIDER_F2)

#if (FREQ3 >= 550000 && FREQ3 < 1100000)
	#define ADF4351_RF_DIVIDER_SELECT_F3 2
	#define ADF4351_RF_DIVIDER_F3 1
	#define ADF4351_MUL_F3 4
#elif (FREQ3 >= 1100000 && FREQ3 < 2200000)
	#define ADF4351_RF_DIVIDER_SELECT_F3 1
	#define ADF4351_RF_DIVIDER_F3 2
	#define ADF4351_MUL_F3 2
#elif (FREQ3 >= 2200000 && FREQ3 <= 4400000)
	#define ADF4351_RF_DIVIDER_SELECT_F3 0
	#define ADF4351_RF_DIVIDER_F3 4
	#define ADF4351_MUL_F3 1
#endif
#define ADF4351_MODULUS_F3 FREQ_REF/(FREQ_STEP*ADF4351_RF_DIVIDER_F3)
#define ADF4351_INT_F3 (FREQ3*ADF4351_MUL_F3/FREQ_REF)
#define ADF4351_FRAC_F3 (FREQ3*ADF4351_MUL_F3-ADF4351_INT_F3*FREQ_REF)/(FREQ_STEP*ADF4351_RF_DIVIDER_F3)

#if (FREQ4 >= 550000 && FREQ4 < 1100000)
	#define ADF4351_RF_DIVIDER_SELECT_F4 2
	#define ADF4351_RF_DIVIDER_F4 1
	#define ADF4351_MUL_F4 4
#elif (FREQ4 >= 1100000 && FREQ4 < 2200000)
	#define ADF4351_RF_DIVIDER_SELECT_F4 1
	#define ADF4351_RF_DIVIDER_F4 2
	#define ADF4351_MUL_F4 2
#elif (FREQ4 >= 2200000 && FREQ4 <= 4400000)
	#define ADF4351_RF_DIVIDER_SELECT_F4 0
	#define ADF4351_RF_DIVIDER_F4 4
	#define ADF4351_MUL_F4 1
#endif
#define ADF4351_MODULUS_F4 FREQ_REF/(FREQ_STEP*ADF4351_RF_DIVIDER_F4)
#define ADF4351_INT_F4 (FREQ4*ADF4351_MUL_F4/FREQ_REF)
#define ADF4351_FRAC_F4 (FREQ4*ADF4351_MUL_F4-ADF4351_INT_F4*FREQ_REF)/(FREQ_STEP*ADF4351_RF_DIVIDER_F4)

#if (FREQ5 >= 550000 && FREQ5 < 1100000)
	#define ADF4351_RF_DIVIDER_SELECT_F5 2
	#define ADF4351_RF_DIVIDER_F5 1
	#define ADF4351_MUL_F5 4
#elif (FREQ5 >= 1100000 && FREQ5 < 2200000)
	#define ADF4351_RF_DIVIDER_SELECT_F5 1
	#define ADF4351_RF_DIVIDER_F5 2
	#define ADF4351_MUL_F5 2
#elif (FREQ5 >= 2200000 && FREQ5 <= 4400000)
	#define ADF4351_RF_DIVIDER_SELECT_F5 0
	#define ADF4351_RF_DIVIDER_F5 4
	#define ADF4351_MUL_F5 1
#endif
#define ADF4351_MODULUS_F5 FREQ_REF/(FREQ_STEP*ADF4351_RF_DIVIDER_F5)
#define ADF4351_INT_F5 (FREQ5*ADF4351_MUL_F5/FREQ_REF)
#define ADF4351_FRAC_F5 (FREQ5*ADF4351_MUL_F5-ADF4351_INT_F5*FREQ_REF)/(FREQ_STEP*ADF4351_RF_DIVIDER_F5)


// Register 1
#define ADF4351_PHASE_ADJUST 0
#define ADF4351_PRESCALER 1 
#define ADF4351_PHASE 1 
#define ADF4351_MODULUS 25 

// Register 2
#define ADF4351_LOW_NOISE_AND_SPUR 0 
#define ADF4351_MIXOUT 0b110
#define ADF4351_REFERENCE_DOUBLER 0
#define ADF4351_R_DIV2 0
#define ADF4351_R_COUNTER 1
#define ADF4351_DOUBLE_BUFFER 0
#define ADF4351_CHARGE_PUMP_CURRENT_SETTING 0b0111
#define ADF4351_LDF 0
#define ADF4351_LDP 0
#define ADF4351_PD_POLARITY 1
#define ADF4351_POWERDOWN 0
#define ADF4351_CP_THREESTATE 0
#define ADF4351_COUNER_RESET 0

// Register 3
#define ADF4351_BAND_SELECT_CLOCK_MODE 0
#define ADF4351_ABP 0
#define ADF4351_CHARGE_CANCEL 0
#define ADF4351_CSR 0
#define ADF4351_CLK_DIV_MODE 0
#define ADF4351_CLOCK_DIVIDER 150

// Register 4
#define ADF4351_FEEDBACK_SELECT 1
#define ADF4351_RF_DIVIDER_SELECT 0b1
#define ADF4351_BAND_SELECT_CLOCK_DIVIDER 0b11001000
#define ADF4351_VCO_POWERDOWN 0
#define ADF4351_MTLD 0
#define ADF4351_AUX_OUTPUT_SELECT 0
#define ADF4351_AUX_OUTPUT_EN 0
#define ADF4351_AUX_OUTPUT_PWR 0
#define ADF4351_RF_OUTPUT_EN 1
#define ADF4351_OUTPUT_PWR 0b11

// Register 5
#define ADF4351_LD_PIN_MODE 1


char rf_out = 1;
unsigned adf4351_int;
unsigned adf4351_frac;
unsigned adf4351_modulus;
char adf4351_rf_divider_select;



void adf4351_init(void) {
	ADF4351_DDR = 0xFF;
	ADF4351_PORT = 0x00;
//	ADF4351_PORT &= ~(1<<ADF4351_CLK) & ~(1<<ADF4351_DATA);	// ADF4351_CLK = 0; ADF4351_DATA =0;
//	ADF4351_PORT |= (1<<ADF4351_LE);			// ADF4351_EN = 1;
//	ADF4351_DDR  |= (1<<ADF4351_DATA) | (1<<ADF4351_CLK) | (1<<ADF4351_LE);
	}

// |DB31|DB30|...|DB2 (ADDR2)|DB1 (ADDR1)|DB0 (ADDR0)| - 32 
void adf4351_send_raw (long unsigned data) {
	char i;
	
	_delay_ms(1);
	for (i=0;i<32;i++) {
		if (data & 0x80000000)
		{
			ADF4351_PORT |= (1<<ADF4351_DATA);
			} else {
			ADF4351_PORT &= ~(1<<ADF4351_DATA);
		}	
		_delay_us(1000);
		ADF4351_PORT |= (1<<ADF4351_CLK);
		_delay_ms(1);
		ADF4351_PORT &= ~(1<<ADF4351_CLK);
		_delay_ms(1);
		data = data << 1;
	}
	ADF4351_PORT |= (1<<ADF4351_LE);
	_delay_ms(1);
	ADF4351_PORT &= ~(1<<ADF4351_LE);
	_delay_ms(1);
}

long unsigned adf4351_reg_data(char addr) {
	long unsigned data;
	
	data = 0;
	switch (addr) {
		case 0 :
			data |=  adf4351_int & 0xffff;
			data = data << 12;
			data |= adf4351_frac & 0b111111111111;
			data = 0x4E8008;
			break;
		case 1 :
			data |=  ADF4351_PHASE_ADJUST & 1 ;
			data = data << 1;
			data |=  ADF4351_PRESCALER & 1 ;
			data = data << 12;
			data |=  ADF4351_PHASE & 0b111111111111;
			data = data << 12;
			data |=  adf4351_modulus & 0b111111111111;
			data =0x8008029;
			break;
		case 2 :
			data |=  ADF4351_LOW_NOISE_AND_SPUR & 0b11;
			data = data << 3;
			data |=  ADF4351_MIXOUT & 0b111;
			data = data << 1;
			data |=  ADF4351_REFERENCE_DOUBLER & 1;
			data = data << 1;
			data |=  ADF4351_R_DIV2 & 1;
			data = data << 10;
			data |=  ADF4351_R_COUNTER & 0b1111111111;
			data = data << 1;
			data |=  ADF4351_DOUBLE_BUFFER & 1;
			data = data << 4;
			data |=  ADF4351_CHARGE_PUMP_CURRENT_SETTING & 0b1111;
			data = data << 1;
			data |=  ADF4351_LDF & 1;
			data = data << 1;
			data |=  ADF4351_LDP & 1;
			data = data << 1;
			data |=  ADF4351_PD_POLARITY & 1;
			data = data << 1;
			data |=  ADF4351_POWERDOWN & 1;
			data = data << 1;
			data |=  ADF4351_CP_THREESTATE & 1;
			data = data << 1;
			data |=  ADF4351_COUNER_RESET & 1;
			data = 0x18004E42;
			break;
		case 3 :
			data |= ADF4351_BAND_SELECT_CLOCK_MODE & 1;
			data = data << 1;
			data |= ADF4351_ABP & 1;
			data = data << 1;
			data |= ADF4351_CHARGE_CANCEL & 1;
			data = data << 3;
			data |= ADF4351_CSR & 1;
			data = data << 3;
			data |= ADF4351_CLK_DIV_MODE & 0b11;
			data = data << 12;
			data |= ADF4351_CLOCK_DIVIDER & 0b111111111111;			
			data = 0x4B3;
			break;
		case 4 :
			data |= ADF4351_FEEDBACK_SELECT & 1;
			data = data << 3;
			//data |= ADF4351_RF_DIVIDER_SELECT & 0b111;
			data |= adf4351_rf_divider_select & 0b111;
			data = data << 8;			
			data |= ADF4351_BAND_SELECT_CLOCK_DIVIDER & 0b11111111;
			data = data << 1;
			data |= ADF4351_VCO_POWERDOWN & 1;
			data = data << 1;
			data |= ADF4351_MTLD & 1;
			data = data << 1;
			data |= ADF4351_AUX_OUTPUT_SELECT & 1;
			data = data << 1;
			data |= ADF4351_AUX_OUTPUT_EN & 1;
			data = data << 2;
			data |= ADF4351_AUX_OUTPUT_PWR & 0b11;
			data = data << 1;
			//data |= ADF4351_RF_OUTPUT_EN & 1;
			data |= rf_out & 1;
			data = data << 2;
			data |= ADF4351_OUTPUT_PWR & 0b11;
			data = 0x9C81FC;
			break;
		case 5 :
			data |= ADF4351_LD_PIN_MODE & 0b11;
			data = data << 3;
			data |= 0b11;
			data = data << 16;			
			data = 0x580005;
			break;
		default:
			break;
	}
	return data;
}


void adf4351_set_reg(char addr) {
	long unsigned data;
	
	data = adf4351_reg_data(addr);
	//data = data << 3;
	//data |= addr;		
	adf4351_send_raw(data);
	_delay_ms(5);
}



void adf4351_set(void) {
	short i;
	
	for (i=5;i>=0;i--)
	{
		adf4351_set_reg(i);
	}
}


int main(void)
{
	uint8_t freq, freq_new;
	
//	KEY_DDR &= ~(1<<KEY1)&~(1<<KEY2);
//	KEY_PORT |= (1<<KEY1)|(1<<KEY2);		// pull-up

adf4351_set();
while(1){};
	freq = 0;
	while (1)
	{
		freq_new = 1;
		if (~KEY_PIN & (1<<KEY1)) 
		{
			// KEY1
			freq_new = 2;
			if (~KEY_PIN & (1<<KEY2)) 
			{
				// KEY1 KEY2
				freq_new = 4;
			}
		} 
		else 
		{
			if (~KEY_PIN & (1<<KEY2)) 
			{
				// KEY2
				freq_new = 3;
			}
		}
		if (freq != freq_new)
		{
			freq = freq_new;
			switch (freq)
			{
				case 1:
					adf4351_int = ADF4351_INT_F1;
					adf4351_frac = ADF4351_FRAC_F1;
					adf4351_modulus = ADF4351_MODULUS_F1;
					adf4351_rf_divider_select = ADF4351_RF_DIVIDER_SELECT_F1;
					break;
				case 2:
					adf4351_int = ADF4351_INT_F2;
					adf4351_frac = ADF4351_FRAC_F2;
					adf4351_modulus = ADF4351_MODULUS_F2;
					adf4351_rf_divider_select = ADF4351_RF_DIVIDER_SELECT_F2;
					break;
				case 3:
					adf4351_int = ADF4351_INT_F3;
					adf4351_frac = ADF4351_FRAC_F3;
					adf4351_modulus = ADF4351_MODULUS_F3;
					adf4351_rf_divider_select = ADF4351_RF_DIVIDER_SELECT_F3;
					break;
				case 4:
					adf4351_int = ADF4351_INT_F4;
					adf4351_frac = ADF4351_FRAC_F4;
					adf4351_modulus = ADF4351_MODULUS_F4;
					adf4351_rf_divider_select = ADF4351_RF_DIVIDER_SELECT_F4;
					break;	
			}
			adf4351_set();
		}
		
	}	
	
}



