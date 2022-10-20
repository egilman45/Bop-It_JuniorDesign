int state = 0;

#define PIN_SLIDE_POT_A A0
#define PIN_FLEX_POT_A A1
#define PIN_BUTTON_A A2
#include <LiquidCrystal_I2C.h> 
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); 


void setup() {
  Serial.begin(9600);
  pinMode(PIN_SLIDE_POT_A, INPUT);
  pinMode(PIN_FLEX_POT_A, INPUT);
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  lcd.print("Press Button to Start Game");
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(9, OUTPUT);

}

void loop() {

  state = digitalRead(13);

  if (state == HIGH) {
    lcd.clear();
    LEDbutton_blink();
    lcd.print("Game Started");
    game();

  }  
}

void game() {

  bool end = FALSE;
  int score = 0;
  int initial[] = {0,0,0,0};
  int initial_input_states = read_inputs(initial);
  int input_states = initial_input_states;

  time_increment = 3000;

    
  while (end != TRUE){
    //Randomly call
    game_call = random(1,4);


    input_states = read_inputs(input_states);

    if(time_increment > 599){
      time_increment = time_increment - 100;
    }

  }

  new_score = increaseScore(score);

  delay(500);
}

int input_states = read_inputs(){
  int button_value = analogRead(PIN_BUTTON_A);
  int flex_pot_value = analogRead(PIN_FLEX_POT_A);
  int slide_pot_value = analogRead(PIN_SLIDE_POT_A);
}

bool snap_bool = snap_reader(button_value) {
  
  if (button_value == 0) {
    LEDbutton_blink();
  }
}

bool flick_bool = flex_reader(flex_pot_value){

  if (flex_pot_value > 512) {
    LEDflex_blink();
    pot_bool = TRUE;
  }
}

bool slide_bool = pot_reader(slide_pot_value){

  if (slide_pot_value > 512) {
    LEDslide_blink();
    pot_bool = TRUE;
  }
}

int score = increaseScore(int s) {
  score = s + 1;
  lcd.setCursor(0, 0);
  lcd.print(String("Score: ")+String(score));
}

void LEDslide_blink() {
  digitalWrite(8,HIGH);
  delay(1);
  digitalWrite(8, LOW);
}

void LEDflex_blink() {
  digitalWrite(7,HIGH);
  delay(1);
  digitalWrite(7, LOW);
}

void LEDbutton_blink() {
  digitalWrite(9,HIGH);
  delay(500);
  digitalWrite(9, LOW);
}
 