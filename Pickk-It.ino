int state = 0;
#include"pitches.h"
#define PIN_SLIDE_POT_A A0
#define PIN_FLEX_POT_A A1
#define SNAP_BUTTON 0
#define GAME_BUTTON 9

#include <LiquidCrystal_I2C.h> 
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); 

int slideSong[] = {NOTE_D4, NOTE_G4, END};
int noteDurationSlide[] = {4,8};
int flickSong[] = {NOTE_G4, NOTE_D4, END};
int noteDurationFlick[] = {4,8};
int snapSong[] = {NOTE_A4, END};
int noteDurationSnap[] = {8};
int speed = 100;
int game_call = 0; 

//Read the initial state values for this turn for slide
int org_pot_value = analogRead(PIN_SLIDE_POT_A);
//Read the initial state values for this turn for sensor 
int org_flex_value = analogRead(PIN_FLEX_POT_A);

void setup() {
  randomSeed(analogRead(3));
  Serial.begin(9600);
  pinMode(PIN_SLIDE_POT_A, INPUT);
  pinMode(PIN_FLEX_POT_A, INPUT);
  pinMode(SNAP_BUTTON, INPUT);
  pinMode(GAME_BUTTON, INPUT);
  lcd.begin();
  lcd.backlight();

}

void loop() {

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Press Start");

  state = digitalRead(GAME_BUTTON);

  if (state == HIGH) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Game Started");
    game();

  }  
}

void game() {

  bool end = 0;
  int score = 0;

  countdown(); //3 second countdown to start game

  int time_increment = 50; //0.05 seconds decrease for every point
  unsigned long time_allowed = 4000; //Allow user four seconds to start
  unsigned long start_time = 0;
  unsigned long end_time = 0;

    
  while (end != 1){ //Repeat Until End is Signaled

    //Every time a new input is needed reset time
    if (time_allowed > 700){ //Decrease the time for user each time
      time_allowed = time_allowed-time_increment;
    }

    //Randomly call a Variable to choose Input
    randomSeed(analogRead(3));
    game_call = random(1,4); //1-slide; 2-flex; 3-snap

    //Read the initial state values for this turn for slide
    org_pot_value = analogRead(PIN_SLIDE_POT_A);
    //Read the initial state values for this turn for sensor 
    org_flex_value = analogRead(PIN_FLEX_POT_A);  

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Score: "+String(score));
    
     
    switch (game_call) {

      case 1: {//Case 1: Slide

        lcd.setCursor(0,1);
        lcd.print("Slide-It!");
        speaker_out(game_call); //Have speaker indicate input choice 
        int scored_pot = 0;

        start_time = millis();
        end_time = start_time;

        while((abs(end_time - start_time) <= time_allowed) && (scored_pot < 1)){
        //Run loop for amount of time allowed to user or until action successful

          int slide_pot_value = analogRead(PIN_SLIDE_POT_A); //Read Potentiometer

          if (abs(slide_pot_value - org_pot_value) > 500) {
          //If potentiometer is significantly moved then score
            scored_pot = 1; //Set mode to scored
            score = increaseScore(score); //Increase score

          } else if ((abs(analogRead(PIN_FLEX_POT_A) - org_flex_value) > 500) || (digitalRead(SNAP_BUTTON)==HIGH)){            
          //Check for incorrect inputs
          
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Wrong Input!");
            delay(1000);
            end = gameover(score);    
            break;        
          }
          end_time = millis();             
        }

        if (scored_pot != 1){ //If input is not within time alloted end game
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Out of Time!");
          delay(1000);
          end = gameover(score);        
        }

        break;
      }      
      case 2: {//Case 2: Flick

        lcd.setCursor(0,1);
        lcd.print("Flick-It!");
        speaker_out(game_call); //Have speaker indicate input choice 

        int scored_flex = 0;

        start_time = millis();
        end_time = start_time;

        while((abs(end_time - start_time) <= time_allowed) && (scored_flex < 1)){
        //Run loop for amount of time allowed to user or until action successful

          int flex_pot_value = analogRead(PIN_FLEX_POT_A); //Read Sensor      

          if (abs(flex_pot_value - org_flex_value) > 250) {
          //If sensor is significantly moved then score
            scored_flex = 1; //Set mode to scored
            score = increaseScore(score); //Increase score
            
          } else if ((abs(analogRead(PIN_SLIDE_POT_A) - org_pot_value) > 500) || (digitalRead(SNAP_BUTTON)==HIGH)){
          //Check for incorrect inputs
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Wrong Input!");
            delay(1000);
            end = gameover(score);            
          }
          end_time = millis();        
        }

        if (scored_flex != 1){ //If input is not within time alloted end game
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Out of Time!");
          delay(1000);
          end = gameover(score);           
        }
        delay(1000); //Delay because flex sensor is finicky
        break;
      }
      case 3: {//Case 3: Snap

        lcd.setCursor(0,1);
        lcd.print("Snap-It!");
        speaker_out(game_call); //Have speaker indicate input choice 

        start_time = millis();
        end_time = start_time;

        int scored_snap = 0;

        while((abs(end_time - start_time) <= time_allowed) && (scored_snap != 1)){
          //Run loop for amount of time allowed to user or until action successful

            int button_value = digitalRead(SNAP_BUTTON); //Read Button State

            if (button_value == HIGH) {
            //If button is pressed then score
              scored_snap = 1; //Set mode to scored
              score = increaseScore(score); //Increase score

            } else if ((abs(analogRead(PIN_FLEX_POT_A) - org_flex_value) > 500) || (abs(analogRead(PIN_SLIDE_POT_A) - org_pot_value) > 500)){
            //Check for incorrect inputs
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("Wrong Input!");
              delay(1000);
              end = gameover(score);            
            }
            end_time = millis();     
        }

        if (scored_snap != 1){ //If input is not within time alloted end game
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Out of Time!");
          delay(1000);
          end = gameover(score);           
        }

        break;
      }
    }
    
    if(score==99){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(String("Score: ")+String(score));
      lcd.setCursor(0,1);  
      lcd.print("You Win!");               
      end = 1;      
    }
  }

delay(6000);  
  
}

void countdown(){
//Display countdown until game started

    for (int i=3; i>0;i--){
        lcd.clear();
        lcd.setCursor(0,1);      
        lcd.print("..."+String(i));
        delay(1000);//1 second delay              
    }

    lcd.clear();
    lcd.setCursor(0,1);      
    lcd.print("Kickoff!");
    delay(1000);
      
}

int gameover(int score) {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Game Over!"); 
  lcd.setCursor(0,1);
  lcd.print("Score: "+String(score));
  return 1;
}

void speaker_out(int command)
{
  
  switch (command) {
      case 1:
        for (int thisNote = 0; slideSong[thisNote]!=-1; thisNote++) {

          int noteDuration = speed*noteDurationSlide[thisNote];
          tone(3, slideSong[thisNote],noteDuration*.95);
          delay(noteDuration);
          //noTone(3);
        }
        break;
      case 2:
        for (int thisNote = 0; flickSong[thisNote]!=-1; thisNote++) {

          int noteDuration = speed*noteDurationFlick[thisNote];
          tone(3, flickSong[thisNote],noteDuration*.95);
          delay(noteDuration);
          noTone(3);
        }
        break;
      case 3:
        for (int thisNote = 0; snapSong[thisNote]!=-1; thisNote++) {

          int noteDuration = speed*noteDurationSnap[thisNote];
          tone(3, snapSong[thisNote],noteDuration*.95);
          delay(noteDuration);
          noTone(3);
        }
      break;
    }
    
}


int increaseScore(int score) {
  int s = score + 1;
  lcd.clear();  
  lcd.setCursor(2, 0);
  lcd.print(String("Score: ")+String(score));
  return s;
}

