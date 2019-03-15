/**
 * 5 semestre - Eng. da Computação - Insper
 * Rafael Corsi - rafael.corsi@insper.edu.br
 *
 * Projeto 0 para a placa SAME70-XPLD
 *
 * Objetivo :
 *  - Introduzir ASF e HAL
 *  - Configuracao de clock
 *  - Configuracao pino In/Out
 *
 * Material :
 *  - Kit: ATMEL SAME70-XPLD - ARM CORTEX M7
 */

/************************************************************************/
/* includes                                                             */
/************************************************************************/

#include "asf.h"

/************************************************************************/
/* defines                                                              */
/************************************************************************/

/************************************************************************/
/* constants                                                            */
/************************************************************************/

/************************************************************************/
/* variaveis globais                                                    */
/************************************************************************/

/************************************************************************/
/* prototypes                                                           */
/************************************************************************/
#define LED_PIO           PIOC                  // periferico que controla o LED
#define LED_PIO_ID        ID_PIOC                    // ID do periférico PIOC (controla LED)
#define LED_PIO_IDX       8u                    // ID do LED no PIO
#define LED_PIO_IDX_MASK  (1u << LED_PIO_IDX)   // Mascara para CONTROLARMOS o LED


#define BUZ_PIO           PIOA                  // periferico que controla o LED
#define BUZ_PIO_ID        ID_PIOA                    // ID do periférico PIOC (controla LED)
#define BUZ_PIO_IDX       0u                    // ID do LED no PIO
#define BUZ_PIO_IDX_MASK  (1u << BUZ_PIO_IDX)   // Mascara para CONTROLARMOS o LED

#define BUT1_PIO           PIOA                  // periferico que controla o LED
#define BUT1_PIO_ID        ID_PIOA                    // ID do periférico PIOC (controla LED)
#define BUT1_PIO_IDX       2u                    // ID do LED no PIO
#define BUT1_PIO_IDX_MASK  (1u << BUT1_PIO_IDX)   // Mascara para CONTROLARMOS o LED

#define BUT2_PIO           PIOD                 // periferico que controla o LED
#define BUT2_PIO_ID        ID_PIOD                    // ID do periférico PIOC (controla LED)
#define BUT2_PIO_IDX       30u                    // ID do LED no PIO
#define BUT2_PIO_IDX_MASK  (1u << BUT2_PIO_IDX)   // Mascara para CONTROLARMOS o LED

#define BUT3_PIO           PIOC                  // periferico que controla o LED
#define BUT3_PIO_ID        ID_PIOC                    // ID do periférico PIOC (controla LED)
#define BUT3_PIO_IDX       13u                    // ID do LED no PIO
#define BUT3_PIO_IDX_MASK  (1u << BUT3_PIO_IDX)   // Mascara para CONTROLARMOS o LED

// BOTAO DE PAUSA
#define BUT4_PIO           PIOB                  // periferico que controla o LED
#define BUT4_PIO_ID        ID_PIOB                   // ID do periférico PIOC (controla LED)
#define BUT4_PIO_IDX       3u                    // ID do LED no PIO
#define BUT4_PIO_IDX_MASK  (1u << BUT4_PIO_IDX)   // Mascara para CONTROLARMOS o LED




#define LED1_PIO           PIOC                  // periferico que controla o LED
#define LED1_PIO_ID        ID_PIOC                   // ID do periférico PIOC (controla LED)
#define LED1_PIO_IDX       19u                    // ID do LED no PIO
#define LED1_PIO_IDX_MASK  (1u << LED1_PIO_IDX)   // Mascara para CONTROLARMOS o LED

#define LED2_PIO           PIOD                  // periferico que controla o LED
#define LED2_PIO_ID        ID_PIOD                   // ID do periférico PIOC (controla LED)
#define LED2_PIO_IDX       26u                    // ID do LED no PIO
#define LED2_PIO_IDX_MASK  (1u << LED2_PIO_IDX)   // Mascara para CONTROLARMOS o LED


#define LED3_PIO           PIOD                  // periferico que controla o LED
#define LED3_PIO_ID        ID_PIOD                   // ID do periférico PIOC (controla LED)
#define LED3_PIO_IDX       11u                    // ID do LED no PIO
#define LED3_PIO_IDX_MASK  (1u << LED3_PIO_IDX)   // Mascara para CONTROLARMOS o LED



// Configuracoes do botao
#define BUT_PIO  PIOA
#define BUT_PIO_ID ID_PIOA
#define BUT_PIO_IDX 11u
#define BUT_PIO_IDX_MASK (1u << BUT_PIO_IDX)

/*  Default pin configuration (no attribute). */
#define _PIO_DEFAULT             (0u << 0)
/*  The internal pin pull-up is active. */
#define _PIO_PULLUP              (1u << 0)
/*  The internal glitch filter is active. */
#define _PIO_DEGLITCH            (1u << 1)
/*  The pin is open-drain. */
#define _PIO_OPENDRAIN           (1u << 2)
/*  The internal debouncing filter is active. */
#define _PIO_DEBOUNCE            (1u << 3)

void init(void);

/************************************************************************/
/* interrupcoes                                                         */
/************************************************************************/

/************************************************************************/
/* funcoes                                                              */
/************************************************************************/


// Função de inicialização do uC
void init(void)
{
	sysclk_init();
	
	WDT->WDT_MR=WDT_MR_WDDIS;
	
	// Ativa o PIO na qual o LED foi conectado
	// para que possamos controlar o LED.
	pmc_enable_periph_clk(LED_PIO_ID);
	
	// Ativa o PIO na qual o BUZZER foi conectado
	// para que possamos controlar o BUZZER.
	pmc_enable_periph_clk(BUZ_PIO_ID);
	
	//Inicializa PC8 como saída
	pio_set_output(LED_PIO, LED_PIO_IDX_MASK, 0, 0, 0);
	
	pio_set_output(BUZ_PIO, BUZ_PIO_IDX_MASK, 0, 0, 0);

	pmc_enable_periph_clk(BUT_PIO_ID);
	pmc_enable_periph_clk(BUT1_PIO_ID);
	pmc_enable_periph_clk(BUT4_PIO_ID);



	pio_set_input(BUT1_PIO, BUT1_PIO_IDX_MASK,PIO_DEFAULT);
	pio_set_input(BUT4_PIO, BUT1_PIO_IDX_MASK,PIO_DEFAULT);


	
	//Inicializa Led 1 
	pmc_enable_periph_clk(LED1_PIO_ID);
	pio_set_output(LED1_PIO, LED1_PIO_IDX_MASK, 0, 0, PIO_DEFAULT | PIO_PULLUP);
	//Inicializa Led 2
	pmc_enable_periph_clk(LED2_PIO_ID);
	pio_set_output(LED2_PIO, LED2_PIO_IDX_MASK, 0, 0, PIO_DEFAULT | PIO_PULLUP);
		
	//Inicializa Led 3
	pmc_enable_periph_clk(LED3_PIO_ID);
	pio_set_output(LED3_PIO, LED3_PIO_IDX_MASK, 0, 0, PIO_DEFAULT | PIO_PULLUP);

	
	// configura pino ligado ao botão como entrada com um pull-up.
	//pio_set_input(BUT_PIO, BUT_PIO_IDX_MASK, _PIO_PULLUP | _PIO_DEBOUNCE  | _PIO_OPENDRAIN);


}

const int songspeed = 1.5; //Change to 2 for a slower version of the song, the bigger the number the slower the song
//*****************************************
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

//*****************************************
int notes1[] = {       //Note of the song, 0 is a rest/pulse
   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
   NOTE_A4, NOTE_G4, NOTE_A4, 0,
   
   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
   NOTE_A4, NOTE_G4, NOTE_A4, 0,
   
   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0, 
   NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
   NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,
   
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_D5, NOTE_E5, NOTE_A4, 0, 
   NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
   NOTE_C5, NOTE_A4, NOTE_B4, 0,

   NOTE_A4, NOTE_A4, 
   //Repeat of first part
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
   NOTE_A4, NOTE_G4, NOTE_A4, 0,

   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
   NOTE_A4, NOTE_G4, NOTE_A4, 0,
   
   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0, 
   NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
   NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,
   
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_D5, NOTE_E5, NOTE_A4, 0, 
   NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
   NOTE_C5, NOTE_A4, NOTE_B4, 0,
   //End of Repeat

   NOTE_E5, 0, 0, NOTE_F5, 0, 0,
   NOTE_E5, NOTE_E5, 0, NOTE_G5, 0, NOTE_E5, NOTE_D5, 0, 0,
   NOTE_D5, 0, 0, NOTE_C5, 0, 0,
   NOTE_B4, NOTE_C5, 0, NOTE_B4, 0, NOTE_A4,

   NOTE_E5, 0, 0, NOTE_F5, 0, 0,
   NOTE_E5, NOTE_E5, 0, NOTE_G5, 0, NOTE_E5, NOTE_D5, 0, 0,
   NOTE_D5, 0, 0, NOTE_C5, 0, 0,
   NOTE_B4, NOTE_C5, 0, NOTE_B4, 0, NOTE_A4
};
int notes2[] = {       //Note of the song, 0 is a rest/pulse
	0,0,NOTE_E6,NOTE_A6,NOTE_B6,
	NOTE_C7,NOTE_B6,NOTE_A6,
	NOTE_A6,0,NOTE_E6,NOTE_A6,NOTE_B6,
	NOTE_C7,NOTE_D7,NOTE_C7,NOTE_D7,
	NOTE_D7,NOTE_E7,0,NOTE_E6,NOTE_A6,NOTE_B6,

	NOTE_C7,NOTE_B6,NOTE_A6,
	NOTE_A6,0,NOTE_A6,NOTE_E7,NOTE_D7,
	0,NOTE_A6,NOTE_E7,NOTE_D7,0,NOTE_G6,NOTE_G6,
	0,NOTE_A6,NOTE_A6,

	0,0,NOTE_E6,NOTE_A6,NOTE_B6,
	NOTE_C7,0,NOTE_C7,
	NOTE_B6,NOTE_C7,NOTE_B6,0,NOTE_E6,NOTE_B6,NOTE_C7,
	NOTE_D7,0,NOTE_E7,

	NOTE_C7,NOTE_B6,NOTE_A6,0,NOTE_A6,NOTE_C7,NOTE_D7,
	NOTE_E7,NOTE_A6,NOTE_C6,NOTE_C6,NOTE_D7,NOTE_E7,
	NOTE_E7,NOTE_E7,NOTE_G5,NOTE_F5,NOTE_E7,
	NOTE_E7,0,

	0,0,NOTE_E6,NOTE_A6,NOTE_B6,
	NOTE_C7,NOTE_B6,NOTE_A6,
	NOTE_A6,0,NOTE_E6,NOTE_A6,NOTE_B6,
	NOTE_C7,NOTE_D7,NOTE_C7,NOTE_D7,

	NOTE_D7,NOTE_E7,0,NOTE_E6,NOTE_A6,NOTE_B6,
	NOTE_C7,NOTE_B6,NOTE_A6,
	NOTE_A6,NOTE_A6,NOTE_E7,NOTE_D7,

	0,NOTE_A6,NOTE_E7,NOTE_D7,0,NOTE_G6,NOTE_G6,
	0,NOTE_A6,NOTE_A6,
	0,0,NOTE_A6,NOTE_E7,NOTE_D7,
	0,NOTE_A6,NOTE_E7,NOTE_D7,0,NOTE_G6,NOTE_G6,

	0,NOTE_A6,NOTE_A6,0,NOTE_A6,NOTE_E7,NOTE_D7,
	0,NOTE_A6,NOTE_E7,NOTE_D7,0,NOTE_G6,NOTE_G6,
	NOTE_A6,NOTE_A6,0
};

int notes3[] = {       //Note of the song, 0 is a rest/pulse
  NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_G5, NOTE_C5, NOTE_D5,
  NOTE_E5,
  NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5,
  NOTE_F5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_D5, NOTE_D5, NOTE_E5,
  NOTE_D5, NOTE_G5
};



//int songs[][] ={notes1,notes2,notes3};
//*****************************************
int duration1[] = {         //duration of each note (in ms) Quarter Note is set to 250 ms
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125, 
  
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125, 
  
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 125, 250, 125,

  125, 125, 250, 125, 125, 
  250, 125, 250, 125, 
  125, 125, 250, 125, 125,
  125, 125, 375, 375,

  250, 125,
  //Rpeat of First Part
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125, 
  
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125, 
  
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 125, 250, 125,

  125, 125, 250, 125, 125, 
  250, 125, 250, 125, 
  125, 125, 250, 125, 125,
  125, 125, 375, 375,
  //End of Repeat
  
  250, 125, 375, 250, 125, 375,
  125, 125, 125, 125, 125, 125, 125, 125, 375,
  250, 125, 375, 250, 125, 375,
  125, 125, 125, 125, 125, 500,

  250, 125, 375, 250, 125, 375,
  125, 125, 125, 125, 125, 125, 125, 125, 375,
  250, 125, 375, 250, 125, 375,
  125, 125, 125, 125, 125, 500
};
int duration2[] = {         //duration of each note (in ms) Quarter Note is set to 250 ms
	500,125,125,125,125,
	500,375,125,
	500,125,125,125,125,
	500,250,125,125,
	125,375,125,125,125,125,

	500,375,125,
	500,125,125,125,125,
	125,125,125,125,125,250,125,
	125,125,750,

	500,125,125,125,125,
	500,250,250,
	250,250,250,125,125,125,125,
	500,250,250,

	250,250,250,125,125,125,125,
	250,125,125,125,250,125,
	375,125,250,125,125,
	500,500,

	500,125,125,125,125,
	500,375,125,
	500,125,125,125,125,
	500,125,125,125,

	125,375,125,125,125,125,
	500,375,125,
	500,125,125,125,125,
	125,125,125,125,125,250,125,
	125,125,750,
	500,125,125,125,125,
	125,125,125,125,125,250,125,

	125,125,250,125,125,125,125,
	125,125,125,125,125,250,125,
	125,375,500
};

int duration3[] = {         //duration of each note (in ms) Quarter Note is set to 250 ms
125, 125, 250, 125, 125, 250, 125, 125, 125, 125, 500, 125, 125, 125, 125, 125, 125, 125, 62, 62, 125, 125, 125, 125, 250, 250
};

//int durations[][] = {duration1, duration2, duration3};
volatile Bool para_musica = false;
void tone(long noteFreq,long duration){
	const int t = 1000000.0/(noteFreq*2.0);

	for (int i = 0;i<(noteFreq*duration)/1000;i++)
	{
		if (!pio_get(BUT4_PIO,PIO_INPUT,BUT4_PIO_IDX_MASK)) {
			para_musica = true;
		}
		
		
		pio_set(PIOA,BUZ_PIO_IDX_MASK);
		delay_us(t);
		pio_clear(PIOA, BUZ_PIO_IDX_MASK);
		delay_us(t);
	}

}

void playMusic(int notes[], int duration[],int songLen,float songspeed){

	for(int i =0; i<songLen; i++){
		if(para_musica) {
			para_musica = false;
			break;
		}
		
		int wait = duration[i]*songspeed;
			pio_clear(LED_PIO,LED_PIO_IDX_MASK);

		tone(notes[i],duration[i]);
			pio_set(LED_PIO,LED_PIO_IDX_MASK);

		delay_ms(wait);
	}
}


/********************************f****************************************/
/* Main                                                                 */
/************************************************************************/
void blink(){
	for(int i=0;i<5;i++){
		
	 pio_clear(PIOC, LED_PIO_IDX_MASK);
	 delay_ms(200); 
	}
}

// Funcao principal chamada na inicalizacao do uC.
int main(void)
{
  // inicializa sistema e IOs
  init();
  

  // super loop
  // aplicacoes embarcadas não devem sair do while(1).
	int flag1 = 0;
	int flag2 = 0;
	int flag3 = 0;
	
	while(1){
	const int but1 = !pio_get(BUT1_PIO,PIO_INPUT,BUT1_PIO_IDX_MASK);
	const int but2 = !pio_get(BUT2_PIO,PIO_INPUT,BUT2_PIO_IDX_MASK);
	const int but3 = !pio_get(BUT3_PIO,PIO_INPUT,BUT3_PIO_IDX_MASK);
	const int but4 = !pio_get(BUT4_PIO,PIO_INPUT,BUT4_PIO_IDX_MASK);

	const int but0 = !pio_get(BUT_PIO,PIO_INPUT,BUT_PIO_IDX_MASK);

	

	if(but1){
		flag1=1;
		flag2=0;
		flag3=0;
//		playMusic(notes1, duration1,203,songspeed);

	}else if(but2){
		flag2=1;
		flag1=0;
		flag3=0;
//		playMusic(notes2, duration2,149,songspeed);

	}else if(but3){
		flag3=1;
		flag1=0;
		flag2=0;
//		playMusic(notes1, duration1,203,songspeed);

	}
	if(flag1){
		pio_clear(LED1_PIO,LED1_PIO_IDX_MASK);
		pio_set(LED2_PIO,LED2_PIO_IDX_MASK);
		pio_set(LED3_PIO,LED3_PIO_IDX_MASK);
	}else if(flag2){
		pio_clear(LED2_PIO,LED2_PIO_IDX_MASK);
		pio_set(LED1_PIO,LED1_PIO_IDX_MASK);
		pio_set(LED3_PIO,LED3_PIO_IDX_MASK);
	}else if(flag3){
		pio_clear(LED3_PIO,LED3_PIO_IDX_MASK);
		pio_set(LED1_PIO,LED1_PIO_IDX_MASK);
		pio_set(LED2_PIO,LED2_PIO_IDX_MASK);
	}
	
	pio_clear(PIOA, BUZ_PIO_IDX_MASK);
	
	
		if (but0 && flag1) {
			playMusic(notes1, duration1,203,songspeed);
			
		}
		if (but0 && flag2) {
			playMusic(notes2, duration2,149,songspeed);
			
		}
		if (but0 && flag3) {
			playMusic(notes3, duration3,26,songspeed);
			
		}
	}
	

		
  return 0;
}
