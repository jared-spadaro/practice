//CPE - 123 Fall 2012
//Final Recieving Code
//Karthik Jayakumar, Gerik Kubiak, Isaias Diaz, and Jared Spadaro
//
//Revieve codes and move the robot

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void initialize_timer(void) {
  TCCR1B = 2;                                           //Increment timer at 2MHz

  TIMSK1 |= (1 << OCIE1A);                              //Enable output compare match

  sei();                                                //Enable global interrupts
}

int period = 40000;                                     //The total length of time for one complete pulse
int servo_period = 4000;                                //The maximum amount of time for each servo pulse
int s0_time_on = 3000;                                  //Amount of time that servo 0 is high (initialized to make the servo stand still)
int s0_state = 0;                                       //State of servo 0
int g0 = 10000;                                         //Length of time between servo 0 and servo 1's control pulse
int s1_time_on = 3000;                                  //Amount of time that servo 0 is high (initialized to make the servo stand still)
int s1_state = 0;                                       //State of servo 1
int g1 = 10000;                                         //Length of time between servo 1 and servo 2's control pulse
int s2_time_on = 3000;                                  //Amount of time that servo 0 is high (initialized to make the servo stand still)
int s2_state = 0;                                       //State of servo 2
int g2 = 8000;                                          //Length of time between servo 2 and servo 0's control pulse
int servo = 0;                                          //The servo that the ISR is currently working on
volatile int timershutdown;

ISR(TIMER1_COMPA_vect) {                                //Interrupt Service Routine using TIMER1, comparing against OCR1A

  if(servo == 0) {                                      //If the servo to be worked on is servo 0:
    if(s0_state == 0) {                                 //If the servo is not being pulsed high:
      PORTD |= (1 << PD0);                              //Set Servo 0 to high
      OCR1A += s0_time_on;                              //Add servo 0 pulse length to interrupt comparison register
	  timershutdown++;
      s0_state = 1;                                     //Change the recorded state of servo 0 to 1
    } else {                                            //If the servo is being pulsed high:
      PORTD &= ~(1 << PD0);                             //Set servo 0 to low
      OCR1A += servo_period - s0_time_on;               //Add servo 1 off gap to interrupt comparison register
      s0_state = 0;                                     //Change the recorded state of servo 0 to 0
    }
    
    if(s0_state == 0) {                                 //If the servo is not being pulsed (runs after every servo 0 pulse cycle):
      OCR1A += g0;                                      //Set the next interrupt to occur after gap 0 amount of time
      servo = 1;                                        //Set the servo to be pulsed to servo 1
    }
  } else if (servo == 1) {                              //If the servo to be worked on is servo 1:
    if(s1_state == 0) {                                 //If the servo is not being pulsed high:
      PORTD |= (1 << PD1);                              //Set Servo 1 to high
      OCR1A += s1_time_on;                              //Add Servo 1 pulse length to interrupt comparison register
      s1_state = 1;                                     //Change the recorded state of servo 1 to 1
    } else {                                            //If the servo is being pulsed high:
      PORTD &= ~(1 << PD1);                             //Set servo 1 to low
      OCR1A += servo_period - s1_time_on;               //Add servo 1 off gap to interrupt comparison register
      s1_state = 0;                                     //Change the recorded state of servo 1 to 0
    }
    
    if(s1_state == 0) {                                 //If the servo is not being pulsed (runs after every servo 1 pulse cycle):
      OCR1A += g1;                                      //Set the next interrupt to occur after gap 1 amount of time
      servo = 2;                                        //Set the servo to be pulsed to servo 2
    }
  } else {                                              //If the servo to be worked on is servo 2:
    if(s2_state == 0) {                                 //If the servo is not being pulsed high:
      PORTD |= (1 << PD2);                              //Set Servo 2 to high
      OCR1A += s2_time_on;                              //Add Servo 2 pulse length to interrupt comparison register
      s2_state = 1;                                     //Change the recorded state of servo 2 to 1
    } else {                                            //If the servo is being pulsed high:
      PORTD &= ~(1 << PD2);                             //Set servo 2 to low
      OCR1A += servo_period - s2_time_on;               //Add servo 2 off gap to interrupt comparison register
      s2_state = 0;                                     //Change the recorded state of servo 2 to 0
    }
    
    if(s2_state == 0) {                                 //If the servo is not being pulsed (runs after every servo 2 pulse cycle):
      OCR1A += g2;                                      //Set the next interrupt to occur after gap 2 amount of time
      servo = 0;                                        //Set the servo to be pulsed to servo 0
    }
  }

} 

void set_motor_speed(int motor_number, int speed) {     //Sets the speed of a particular servo: (0 <= servo <= 2), (-100 <= speed <= 100)
  if(motor_number == 0) {                               //If the 0th servo is the servo to modify:
    s0_time_on = 3000 + 10 * speed;                     //Set the amount of time that servo 0 is high to (stand still value) + (given speed value adjusted to span the motor's full range of speeds)
  } else if(motor_number == 1) {                        //If the 0th servo is not the servo to modify and the 1st servo is the servo to modify:
    s1_time_on = 3000 + 10 * speed;                     //Set the amount of time that servo 1 is high to (stand still value) + (given speed value adjusted to span the motor's full range of speeds)
  } else {                                              //If the servo to modify is not the 0th or 1st servo (2nd servo):
    s2_time_on = 3000 + 10 * speed;                     //Set the amount of time that servo 2 is high to (stand still value) + (given speed value adjusted to span the motor's full range of speeds)
  }
}

void blink(int a){
  int i;
  for(i = 0; i<a; i++){
    PORTD |= (1 << PD6);
    _delay_ms(200);
    PORTD &= ~(1 << PD6);
    _delay_ms(200);
  }
}

void lab4_initialize_timer0(void) {
  TCCR0B |= (1 << CS02);   //set timer 0 to increment at 62.5KHz
}

int main(void){
  int i;                         //start of main
  char previous;
  char falling_start_edge;
  unsigned char current;
  char timeout;
  int timeout_delay = 157;		// starting edge timeout
  int timeout_delay2 = 57;		// find first data bit timeout
  int timeout_delay3 = 75;		// find remaining data bits
  int answer;
  int Port;
  initialize_timer();
  lab4_initialize_timer0();  //set the timeout delay to 10 timer ticks
  DDRD |= (1 << PD6);
  DDRD |= (1 << PD0);                                   //Set Port D, Pins 3-5 to outputs
  DDRD |= (1 << PD1);
  PORTD |= (1 << PD7);
  if(PIND&(1 << PD7)){
	  blink(1);
	  Port = 4;
  }
  else{
	  blink(2);
	  Port = 5;
  }
  TCNT0 = 0;     //reset the timer
  while(1){
    falling_start_edge = 0;
    previous = 0;
    while(falling_start_edge == 0){  //find a starting edge
      current = (PIND & (1 << Port));
	  if(timershutdown == 6000){
		  set_motor_speed (0,0);
		  set_motor_speed (1,0);
		  blink(3);
		  while(1){
		  }
	  }
      if(current == 0 && previous != 0){
        falling_start_edge = 1;
      }
      previous = current;
    }

    timeout_delay = 157;
    timeout = 1;
    TCNT0 = 0;
    previous = 0;
    while(TCNT0 < timeout_delay){   //start the find for a starting bit
      current = (PIND & (1 << Port));
      if(current == 0 && previous != 0){   //find another falling edge
        timeout = 0;        //if it is high, set to no timeout
        timeout_delay = 0;  //break out of this loop
      }
      previous = current;
    }
    if(timeout == 1){   //if it times out, go past start bit and start the 7 data bit
		answer = 0;
      for(i = 0; i < 7; i++){  //loops 7 times
        TCNT0 = 0;
        timeout = 1;
        previous = 0;
        timeout_delay3 = 75;
        while(TCNT0 < timeout_delay3){     //runs for 1.2ms
          current = (PIND & (1 << Port));
          if(current == 0 && previous != 0){  //checks for falling edge
            timeout = 0;                      //
            timeout_delay3 = 0;
          }
          previous = current;
        }

        if(timeout == 1){   //times out, doesn't find a falling edge
          i = 8;
        }

        if(timeout == 0){   //finds a falling edge during 1.2ms
          TCNT0 = 0;
          previous = 0;
          timeout = 1;
          timeout_delay2 = 57;
          while(TCNT0 < timeout_delay2){   //look for the 0.9ms delay
            current = (PIND & (1 << Port));
            if(current == 0 && previous != 0){
              timeout = 0;        //set to no timeout
              timeout_delay2 = 0;  //break out of this loop
            }
            previous = current;
          }

          if(timeout == 1){    //times out, doesn't find a falling edge during 0.9ms 
            current = (PIND & (1 << Port));
            if(current == 0){
              answer |= (1 << i);  //store  bit value
            }  //end of if current
          }    //end of last if time out == 1
        }      //end of timeout == 0
      }        //end of for loop
    }          //end of first time out == 1
  

    if(answer == 31){
		set_motor_speed(0, -30);
		set_motor_speed(1, 30);
		blink(1);
    } else if(answer == 32){
		set_motor_speed(0, 30);
		set_motor_speed(1, -30);
		blink(2);
    } else if(answer == 33){
		set_motor_speed(0, 30);
		set_motor_speed(1, 0);
		blink(3);
    } else if(answer == 34){
		set_motor_speed(0, 0);
		set_motor_speed(1, -30);
		blink(4);
	} else if(answer == 35){
		set_motor_speed(0, 0);
		set_motor_speed(1, 0);
		blink(5);
	}
  }    //end of infinite while loop
  return 0;
}      //end of main