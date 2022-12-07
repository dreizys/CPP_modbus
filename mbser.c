#include <stdio>
#include <modbus>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "./cursor.h"
#include <thread>

//#include <fcntl.h> //contains file controls like  O_RDWR
//#include <termios.h> //contains POSIX terminal control definitions
#include <unistd.h>  //write(), read(), close()
struct timespec tw = {5,12500000};
struct timespec tr;
modbus_t *ctx;
uint16_t tab_reg[32];
int rc;
int i;
time_t curtime;


int thread_func()

int main(void){
	
	//int esc_symb = sizeof("\n\r");

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
																							//send data to serial port setup;
																							/*int serial_port = open("/dev/ttyS15", O_RDWR);
																							struct termios tty;

																							  // Read in existing settings, and handle any error
																							  if(tcgetattr(serial_port, &tty) != 0) {
																							      printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
																							      return 1;
																							  }


																							  tty.c_cc[VTIME] = 10;    // Wait for up to 1s (10 deciseconds), returning as soon >
																							  tty.c_cc[VMIN] = 0;

																							  // Set in/out baud rate to be 9600
																							  cfsetispeed(&tty, B9600);
																							  cfsetospeed(&tty, B9600);

																							  // Save tty settings, also checking for error
																							  if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
																							      printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
																							      return 1;
																							  }

																							*/
    while(modbus_connect(ctx) == 0){
	rc = modbus_read_input_registers(ctx, 1, 2, tab_reg);
		if (rc == -1) {
		    fprintf(stderr, "%s\n", modbus_strerror(errno));
    		return -1;
		}

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

			
																						//write to serial:
																							/*		int coma_size = sizeof(",");
																									char str[4];
																									sprintf(str, "%d", tab_reg[i]);
																									write(serial_port, str, 4);
																									write(serial_port, ",", coma_size);
																									//write(serial_port, "\n\r", esc_symb);

																								}*/
																								//write(serial_port, "\n\r", esc_symb);
		nanosleep(&tw, &tr);

   }
	
}
	modbus_close(ctx);
	modbus_free(ctx);
	return 0;
}



