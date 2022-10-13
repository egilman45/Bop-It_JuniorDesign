#include <SimpleSDAudio.h>
#define Speaker 4
#define StartButton 0

void setup() {
  // put your setup code here, to run once:
  //speaker setup
  SdPlay.setSDCSPin(Speaker); // sd card cs pin
  if (!SdPlay.init(SSDA_MODE_FULLRATE | SSDA_MODE_MONO | SSDA_MODE_AUTOWORKER)) // setting mode 
  { 
    while(1); 
  }
  //
}

void loop() {
  // put your main code here, to run repeatedly:

}

/*
 *  First we need to convert mp3 file to wav file with below setting
 *  bit resolution : 8 Bit
 *  sampling rate  : 32000 Hz
 *  audio channel  : stereo
 *  
 *  to convert mp3 visit link: https://audio.online-convert.com/convert-to-wav
 */


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
