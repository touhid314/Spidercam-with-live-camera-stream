#include <Stepper.h>

//Setting up the stepper
Stepper stepper1 = Stepper(2048, 8, 10, 9, 11);
Stepper stepper2 = Stepper(2048, 2, 3, 4, 5);

//int step_count = 0;
int flag = 1;
int e = 1; //error threshold for pot inputs 
int step_size = 5;

int potx; //pot1
int poty; //pot2
int potz; //pot3

int potx_prev = 0; int poty_prev = 0; int potz_prev = 0;

int del_potx, del_poty, del_potz; //////////////// may be needed in future

bool potx_changed = 0;
bool poty_changed = 0;
bool potz_changed = 0;

// field parameters
float r = 1.5 ; // r = radius of stepper head in cm
float a = 40; // cm
float b = 30.4; // cm
float h = 34; //cm

float l1_prev = 0; 
float l2_prev = a;
float l3_prev = sqrt(a*a + b*b);
float l4_prev = b;

float x_prev = 0; float y_prev = 0; float z_prev = h;
float x_curr, y_curr, z_curr;
float del_x, del_y, del_z;
float l1_curr, l2_curr, l3_curr, l4_curr;
float del_l1, del_l2, del_l3, del_l4;
int st1_steps, st2_steps, st3_steps, st4_steps; // only stepper 1 and 2 in this arduino

void setup() {

  //Set the RPM of the stepper motor
  stepper1.setSpeed(5);
  stepper2.setSpeed(5);

  Serial.begin(9600);
}

void loop() {    
    potx = analogRead(0);
    poty = analogRead(1);
    potz = analogRead(2);
 
    potx = map(potx, 0, 1023, 0, a);
    poty = map(poty, 0, 1023, 0, b);
    potz = map(potz, 0, 1023, 0, h);
    
    
    if ((potx <= potx_prev + e) && (potx >= potx_prev - e)) potx_changed = 0;
    else potx_changed = 1;

    if ((poty <= poty_prev + e) && (poty >= poty_prev - e)) poty_changed = 0;
    else poty_changed = 1;

    if ((potz <= potz_prev + e) && (potz >= potz_prev - e)) potz_changed = 0;
    else potz_changed = 1;

    
    if ((potx_changed == 0) && (poty_changed == 0) && (potz_changed == 0) ){
      flag = 0;
    }else{
      flag = 1;
    }

    x_curr = potx;
    y_curr = poty;
    z_curr = potz;

    l1_curr = sqrt(x_curr*x_curr + y_curr*y_curr + (h - z_curr)*(h - z_curr));
    l2_curr = sqrt( (a - x_curr)*(a - x_curr) + y_curr*y_curr + (h - z_curr)*(h - z_curr));
    l3_curr = sqrt( (a - x_curr)*(a - x_curr) + (b - y_curr)*(b - y_curr) + (h - z_curr)*(h - z_curr) );
    l4_curr = sqrt( x_curr*x_curr + (b - y_curr)*(b - y_curr) + (h - z_curr)*(h - z_curr) );

    del_l1 = l1_curr - l1_prev;
    del_l2 = l2_curr - l2_prev;
    del_l3 = l3_curr - l3_prev;
    del_l4 = l4_curr - l4_prev;

    Serial.print("pot val\n");
    
    Serial.print(potx); Serial.print('\n');
    Serial.print(poty); Serial.print('\n');
    Serial.print(potz); Serial.print('\n');
    Serial.print('\n');
    
    Serial.print(del_l1); Serial.print('\n');
    Serial.print(del_l2); Serial.print('\n');
    Serial.print(del_l3); Serial.print('\n');
    Serial.print(del_l4); Serial.print('\n');
     Serial.print('\n');

    st1_steps = (1024*del_l1)/(3.1416*r);
    st2_steps = (1024*del_l2)/(3.1416*r);
    st3_steps = (1024*del_l3)/(3.1416*r);
    st4_steps = (1024*del_l4)/(3.1416*r);

    Serial.println("steps \n");
    Serial.print(st1_steps); Serial.print('\n');
    Serial.print(st2_steps); Serial.print('\n');
    Serial.print(st3_steps); Serial.print('\n');
    Serial.print(st4_steps); Serial.print('\n');
    Serial.print('\n');
        
    if(flag == 1){

      //moving stepper1, stepper2 concurrently
      int st1_rotdir = abs(st1_steps)/st1_steps;
      int st2_rotdir = abs(st2_steps)/st2_steps;

      st1_steps = abs(st1_steps);
      st2_steps = abs(st2_steps);

      int st1_rem = st1_steps % step_size; // steps that cannot be included using the specified step size
      int st2_rem = st2_steps % step_size; 

      for(int i=step_size; i<max(st1_steps, st2_steps); i = i+step_size){
        if(st1_steps >= step_size){
          stepper1.step(st1_rotdir*step_size);
          st1_steps = st1_steps - step_size;
        }

        if(st2_steps >= step_size){
          stepper2.step(st2_rotdir*step_size);
          st2_steps = st2_steps - step_size;
        }
      }//for end

      //performing the remaining steps
      stepper1.step(st1_rotdir*st1_rem);
      stepper2.step(st2_rotdir*st2_rem);

      
    } // if end

    delay(3000);

    potx_prev = potx;
    poty_prev = poty;
    potz_prev = potz;

    l1_prev = l1_curr;
    l2_prev = l2_curr;
    l3_prev = l3_curr;
    l4_prev = l4_curr;
    

}
