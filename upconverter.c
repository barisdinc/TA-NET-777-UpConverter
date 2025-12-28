/*
  yeniden ATOLYE 2025 (CopyLeft)
  QO-100 Upconverter
  
  ISTEK: PB3 ve PB4 girislerini oku, PB0 ve PB1 cikislarina yansit.
  NOT: Bu kod, PB0/PB1'i hem PLL (LE/DATA) hem de durum gostergesi
       olarak kullanir. PLL yazmasi bittikten sonra pinler
       PB3/PB4'un durumunu yansitir.

  derleme :
  avr-gcc -g -Os -mmcu=attiny45 atolye_uc.c -o a.out
  avr-objcopy -O ihex -j.text -j.data a.out atolye_uc.hex
  yazma:
  avrdude -p attiny45 -c avrispmkII -P usb -U flash:w:atolye_uc.hex:i
*/


#define F_CPU 8000000L 

#include <avr/io.h>
#include <util/delay.h>



long int r0, r1, r2, r3, r4, r5;

void write2PLL(uint32_t PLLword) {         // clocks 32 bits word  directly to the ADF4351
                                          // msb (b31) first, lsb (b0) last 
   for (char i=32; i>0; i--) {   // PLL word 32 bits 

     if (PLLword & 0x80000000)
     {
        PORTB |= 0b00000010 ; // PB1 (DATA) = 1
     }
     else
     {
        PORTB &= 0b11111101 ; // PB1 (DATA) = 0
     }
     PORTB |= 0b00000100;                 // clock in bit on rising edge of CLK (PB2 = 1)
     PORTB &= 0b11111011;                // CLK (PB2 = 0) 
     PLLword <<= 1; 
     } 
     PORTB |= 0b00000001;                 // latch in PLL word on rising edge of LE (PB0 = 1)
     PORTB &= 0b11111110;  // LE (PB0 = 0)   
     _delay_ms(1);
} 


int main()
{

     DDRB = 0b11100111; // 3 ve 4. portlar INPUT (select switch) digerleri OUTPUT
     PORTB = 0b00011000; // PB3 ve PB4 icin dahili PULL-UP'lari aktif et

     _delay_ms(100);

     // Switch'ler pull-up'li ve active-low varsayiliyor (basinca 0 olurlar)
     // Ilk durum okumasi (Terslenmis)
     uint8_t sw1 = ((~PINB) & 0b00010000) >> 4; // PB4
     uint8_t sw2 = ((~PINB) & 0b00001000) >> 3; // PB3
     uint8_t sw = sw1 * 2 + sw2;
     uint8_t sw_old = 255; // Ilk dongude guncellemeyi zorla

     while(1)
     {
        //NOT: Kart arkasindaki duruma gore hazirla
        // Switch'leri oku (Terslenmis, 0b00011000 -> 0b00000000)
        
        sw1 = ((~PINB) & 0b00010000) >> 4; // PB4 okuma (active-low)
        sw2 = ((~PINB) & 0b00001000) >> 3; // PB3 okuma (active-low)
        
        sw = sw1 * 2 + sw2; // sw1=MSB, sw2=LSB

        if (sw_old != sw)
        {
           switch (sw)
           {
               case 0:
                   // Fout= 1965 MHz +5dBm LO= 2400 MHz - 435 MHz
                   r0 = 0x4E8008;
                   r1 = 0x8008029;
                   r2 = 0x18004E42;
                   r3 = 0x4B3;
                   r4 = 0x9C81FC;
                   r5 = 0x580005;
                   break;
               case 1:
                   // Fout= 2256 MHz +5dBm LO= 2400 MHz - 144 MHz
                   r0 = 0x2D0030;  
                   r1 = 0x80080C9;
                   r2 = 0x18004E42;
                   r3 = 0x4B3;
                   r4 = 0x8C81FC;
                   r5 = 0x580005;
                   break;
               case 2:
                   // Fout= 2350 MHz +5dBm LO= 2400 MHz - 50 MHz
                   r0 = 0x2F0000;  
                   r1 = 0x8008011;
                   r2 = 0x18004E42;
                   r3 = 0x4B3;
                   r4 = 0x8C81FC;
                   r5 = 0x580005;
                   break;
               case 3:
                   // Fout= 1160 MHz +5dBm LO= 2400 MHz - 1240 MHz
                   r0 = 0x2E0020;  
                   r1 = 0x8008029;
                   r2 = 0x18004E42;
                   r3 = 0x4B3;
                   r4 = 0x9C81FC;
                   r5 = 0x580005;
                   break;
               //case 3: //28 MHz icin olan bolumdur
               //    // Fout= 2371 MHz +5dBm LO= 2400 MHz - 29 MHz
               //    r0 = 0x2F00A8;  
               //    r1 = 0x80080C9;
               //    r2 = 0x18004E42;
               //    r3 = 0x4B3;
               //    r4 = 0x8C81FC;
               //    r5 = 0x580005;
               //    break;

               default:
                   // Fout= 1965 MHz +5dBm LO= 2400 MHz - 435 MHz
                   r0 = 0x4E8008;  
                   r1 = 0x8008029;
                   r2 = 0x18004E42;
                   r3 = 0x4B3;
                   r4 = 0x9C81FC;
                   r5 = 0x580005;
                   break;
           }//case
           
           PORTB &= 0b11111000; 

           write2PLL(r5); 
           write2PLL(r4);
           write2PLL(r3);
           write2PLL(r2);
           write2PLL(r1);
           write2PLL(r0);

           sw_old = sw;
        }//if

        
        
        _delay_ms(10); 
        
     }//while

}

