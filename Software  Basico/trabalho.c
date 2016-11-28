#include "cMIPS.h"

#define EOF -1
#define TRUE 1
#define FALSE 0

typedef struct control { // control register fields (uses only ls byte)
  int ign   : 24+3,      // ignore uppermost bits
    intTX   : 1,         // interrupt on TX buffer empty (bit 4)
    intRX   : 1,         // interrupt on RX buffer full (bit 3)
    speed   : 3;         // 4,8,16..256 tx-rx clock data rates  (bits 0..2)
} Tcontrol;

typedef struct status { // status register fields (uses only ls byte)
  int s;
  // int ign   : 24,      // ignore uppermost bits
  //  ign7    : 1,        // ignored (bit 7)
  //  txEmpty : 1,        // TX register is empty (bit 6)
  //  rxFull  : 1,        // octet available from RX register (bit 5)
  //  int_TX_empt: 1,     // interrupt pending on TX empty (bit 4)
  //  int_RX_full: 1,     // interrupt pending on RX full (bit 3)
  //  ign2    : 1,        // ignored (bit 2)
  //  framing : 1,        // framing error (bit 1)
  //  overun  : 1;        // overun error (bit 0)
} Tstatus;

typedef union ctlStat { // control + status on same address
  Tcontrol  ctl;        // write-only
  Tstatus   stat;       // read-only
} TctlStat;

typedef union data {    // data registers on same address
  int tx;               // write-only
  int rx;               // read-only
} Tdata;

typedef struct serial {
  TctlStat cs;
  Tdata    d;
} Tserial;

extern int nrx;
extern char rx_queue[16];
extern int rx_hd;
extern int rx_tl;
extern int ntx;
extern char tx_queue[16];
extern int tx_hd;
extern int tx_tl;

extern int enableInterr ( void ); // habilita interrupcoes, retorna STATUS
extern int disableInterr ( void ); // desabilita interrupcoes, retorna STATUS

int proberx() {// retorna o valor de nrx
	volatile int x;
	x = nrx;
	return x;
}

int probetx(){ // retorna o valor de ntx
	volatile int x;	
	x = ntx;	
	return x;
}

int iostat() {// retorna o valor do registrados de status
	volatile Tserial *uart;  // tell GCC to not optimize away tests
	uart = (void *)IO_UART_BOT_ADDR; // bottom of UART address range
	
	return uart->cs.stat.s;
}

void ioctl(int x) {// permite escrever no seu registrador de controle
	volatile Tserial *uart;  // tell GCC to not optimize away tests
	uart = (void *)IO_UART_BOT_ADDR; // bottom of UART address range
	
	if (x == 1){ //enable inter. TX.
		uart->cs.ctl.intTX = 1;
    	uart->cs.ctl.intRX = 0;         
    	//uart->cs.clt.speed = 3;
	}

	if (x == 2){ //enable inter. RX.
		uart->cs.ctl.intTX = 0;
    	uart->cs.ctl.intRX = 1;         
    	uart->cs.ctl.speed = 4;
	}

	if (x == 3){ //show off bitch!
		uart->cs.ctl.intTX = 0;
    	uart->cs.ctl.intRX = 0;         
    	//uart->cs.clt.speed = 0;
	}
}

char getc(){ // retorna o caractere que está na ﬁla de recepção ou EOF se a ﬁla estiver vazia

	char c;
	if (proberx() > 0){
		disableInterr();
		c = rx_queue[rx_hd];
		rx_hd = (rx_hd + 1)%16;
		nrx--;
		enableInterr();
		return c;
	}
	
	return EOF;
}

int putc(char c){ // insere um caractere na ﬁla de transmissão

	if (probetx() > 0){
		disableInterr();
		tx_queue[rx_tl] = c;
		tx_tl = (tx_tl + 1 )%16;
		ntx--;
		to_stdout(c);
		enableInterr();
		return 1;
	}	
	else
		return FALSE;
}

int wrtc (char c){
	volatile Tserial *uart;  // tell GCC to not optimize away tests
	uart = (void *)IO_UART_BOT_ADDR; // bottom of UART address range
	
	uart->d.tx = c;
}

void insertion (int numbers[], int array_size){
	int i, j, index;
	for (i=1; i < array_size; i++){
		index = numbers[i];
		j = i;
    	while ((j > 0) && (numbers[j-1] > index)){
    	  	numbers[j] = numbers[j-1];
    	  	j = j - 1;
    	}
    	numbers[j] = index;
  	}
}

int string_hex_to_int(char* string){
	int tmp=0;
	int total=0;
	int i=0;
	int aux=0;
	int tam=0;
	int aux_temp=1;
	
	for(tam=0;string[i]!='\n';tam++){
		i++;
	}
		
	for(i=0;string[i]!='\n';i++){
		if((string[i]>=48)&&(string[i]<=57)){
			tmp=string[i]-48;
		}
		else if((string[i]>=65)&&(string[i]<=70)){
			tmp=string[i]-55;
		}
		else if((string[i]>=97)&&(string[i]<=102)){
			tmp=string[i]-87;
		}
		else{
			tmp=0;
		}
		
		for(aux=(tam-i-1);aux>0;aux--){
			aux_temp*=16;
		}

		tmp=tmp*aux_temp;

		aux_temp=1;
		
		total+=tmp;		
	}
	return total;
}

void string_int_to_hex(int decimal,char str[]){
	int resto;
	int i = 8;
	
	while((decimal)){ 
		i--;
		if (i == 7){
			str[i] = '\0';
			continue;
		}
		
		resto = decimal % 16;
		if ((resto >= 0) && (resto <=9))
			str[i] = resto + 48;
		else
			if ((resto >=10) && (resto <= 15))
				str[i] = resto + 55;
				
		decimal /= 16;
	}
	
	while(i>0){
		i--;
		str[i] = '0';
	}
	
}


int main (){
	int i, x, j;
	volatile Tserial *uart;  // tell GCC to not optimize away tests
	uart = (void *)IO_UART_BOT_ADDR; // bottom of UART address range
	Tcontrol ctrl;
	int numbers[16];
	char c, l;
	char fila[144];
	rx_hd = 0;
    rx_tl = 0;
    tx_hd = 0;
    tx_tl = 0;
    nrx = 0;
	ntx = 16;
	//ioctl(2); //Ativa transmissao
	ctrl.intTX = 0;
    ctrl.intRX = 1;         
    ctrl.speed = 4;
	uart->cs.ctl = ctrl;

	while (proberx() < 1)
	;
	c = getc();
	to_stdout(c);
	while (c != '\n'){
		while (proberx() < 1);
			c = getc();
		to_stdout(c);
	}


	ctrl.intTX = 1;
    ctrl.intRX = 0;
    ctrl.speed = 4;
	uart->cs.ctl = ctrl;
}
