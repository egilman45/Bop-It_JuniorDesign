int state = 0;
#include <SimpleSDAudio.h>
#define Speaker 4
#define PIN_SLIDE_POT_A A0
#define PIN_FLEX_POT_A A1
#define SNAP_BUTTON 1
#define GAME_BUTTON 2



#include <LiquidCrystal_I2C.h> 
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); 


void setup() {
  Serial.begin(9600);
  pinMode(PIN_SLIDE_POT_A, INPUT);
  pinMode(PIN_FLEX_POT_A, INPUT);
  pinMode(SNAP_BUTTON, INPUT);
  pinMode(GAME_BUTTON, INPUT);
  lcd.init();
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(2,0);
  lcd.print("Press Button to Start Game");
 //speaker setup
  SdPlay.setSDCSPin(Speaker); // sd card cs pin
  if (!SdPlay.init(SSDA_MODE_FULLRATE | SSDA_MODE_MONO | SSDA_MODE_AUTOWORKER)) // setting mode 
  { 
    while(1); 
  }  

}

void loop() {

  state = digitalRead(GAME_BUTTON);

  if (state == HIGH) {
    lcd.clear();
    lcd.setCursor(2,0);
    lcd.print("Game Started");
    game();

  }  
}

void game() {

  bool end = FALSE;
  int score = 0;

  time_increment = 100000; //100 seconds

    
  while (end != TRUE){
    //Randomly call
    game_call = random(1,4); //1-slide; 2-flex; 3-snap
    speaker_out(game_call);
    countdown(5000); //5 second countdown  
    
     
      switch (game_call) {
        case 1:
        int slide_pot_value = analogRead(PIN_SLIDE_POT_A);
        if(slide_pot_value>512){
          increaseScore(score);
          time_increment = time_increment-1000; //reduce time by 1 second          
        }
        else{
          lcd.clear();
          lcd.setCursor(2,0);
          lcd.print("Wrong input, Game Over!!"); 
          end = FALSE;
        }
        break;
       case 2:
        int flex_pot_value = analogRead(PIN_FLEX_POT_A);
        if(flex_pot_value>512){
          increaseScore(score);
          time_increment = time_increment-1000; //reduce time by 1 second          
        }
        else{
          lcd.clear();
          lcd.setCursor(2,0);
          lcd.print("Wrong input, Game Over!!"); 
          end = FALSE;
        }
        break;
        case 3:
        int button_value = digitalRead(SNAP_BUTTON);
        f(button_value==1){
          increaseScore(score);
          time_increment = time_increment-1000; //reduce time by 1 second          
        }
        else{
          lcd.clear();
          lcd.setCursor(2,0);
          lcd.print("Wrong input, Game Over!!"); 
          end = FALSE;
        }
        break;
      }
    
    if(score==99){
      lcd.clear();
        lcd.setCursor(2,0);
        lcd.print(String("Score: ")+String(score));
        lcd.setCursor(2,1);  
        lcd.print("You Win!!");               
        end = FALSE;      
    }

  }
  
}


void countdown(time){
    lcd.clear();
    j=0;
    for (int i=(time/1000); i>0 ;i--){
        lcd.setCursor(j,0);      
        lcd.print(i + "...");
        delay(1000);//1 second delay
        j=j+4;
              
    }
      
}

void speaker_out(int command)
{
  
  switch (command) {
      case 1:
        if(!SdPlay.setFile("music1.wav")) // music name file
          { 
            while(1);          
          }
          command = 2;
        break;
      case 2:
        if(!SdPlay.setFile("music2.wav")) // music name file
          { 
            while(1);
          }
          command = 3;
        break;
      case 3:
        if(!SdPlay.setFile("music3.wav")) // music name file
          { 
            while(1);
          }
          command = 1;
        break;
    }
    
  SdPlay.play(); // play music
  
  while(!SdPlay.isStopped())
    { 
      ;
    }

}


void increaseScore(int score) {
  score = score + 1;
  lcd.clear();  
  lcd.setCursor(2, 0);
  lcd.print(String("Score: ")+String(score));
}

