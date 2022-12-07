#include <stdio.h>
#include <modbus.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "./cursor.h"
#include <iostream>
#include <thread>

#include <unistd.h>  //write(), read(), close()
struct timespec tw = {5,12500000};
struct timespec tr;
modbus_t *ctx;
uint16_t tab_reg[32];
int rc;
int i;
int number = 0;
int data = 0;
time_t curtime;
using namespace std;

int thread_fun(){
	CURSOR(7,0);
	printf("Choose action: \n");
	cin >> number;
	data = number;
	
	return 0;

}

int main(void){
	
		

	ctx = modbus_new_rtu("/dev/ttyUSB0", 9600, 'N', 8, 1);
		if (ctx == NULL) {
    		fprintf(stderr, "Unable to create the libmodbus context\n");
    		return -1;
		}
		else {
			printf("new rtu set \n");
		}

		modbus_set_slave(ctx, 2);  //set  address of the slave device

		if (modbus_connect(ctx) == -1) {
  		  fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
  		  modbus_free(ctx);
  		  return -1;
		}
		else{
			printf("rtu connected \n");
			CLEAR;
			HOME;
			CURSOR(2,0);
			//COLOR_A(7,-1,5);
			printf(" Receiving data from the XY-MDO2 sensor\n");
			printf("****************************************\n");
			RESET_COLOR;
			printf(" Temperature           Humidity         Timestamp");
		}

    while(modbus_connect(ctx) == 0){
	rc = modbus_read_input_registers(ctx, 1, 2, tab_reg);
		if (rc == -1) {
		    fprintf(stderr, "%s\n", modbus_strerror(errno));
    		return -1;
		}
		
		thread thr(thread_fun);                                                                 
        thr.detach(); 
		
		for (i=0; i < rc; i++) {
 		   //printf("reg[%d]=%d \n", i, tab_reg[i]);
 		  float  temperature = tab_reg[0]/10;
 		  float  humidity = tab_reg[1]/10;
			time(&curtime);
 		   CURSOR(5,0);
 		   printf("  %.1f\n", temperature);
 		   CURSOR(5,22);
 		   printf("	 %.1f\n", humidity);
 		   CURSOR(5,36);
 		   printf(" %s", ctime(&curtime));
		   CURSOR(7,0)	;
		   printf("Choose  an option : 1, 2, or 3 ");
	  	   printf(" %i", number );
			
		nanosleep(&tw, &tr);

   }
	
}
	modbus_close(ctx);
	modbus_free(ctx);
	return 0;
}
