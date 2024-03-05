void runEffect(int nr, int LEDNr) {
  int ledNr;

  ledNr = LEDNr;
  if ((LEDNr > 5) && (LEDNr<12)) ledNr = 17 - LEDNr; 
  if ((LEDNr > 17) && (LEDNr<24)) ledNr = 41 - LEDNr; 
  if ((LEDNr > 29) && (LEDNr<36)) ledNr = 65 - LEDNr; 
  
  switch (nr) {
    case 1: l1(ledNr); break;
    case 2: l2(ledNr); break;
    case 3: l3(ledNr); break;
    case 4: l4(ledNr); break;
    case 5: l5(ledNr); break;
    case 6: l6(ledNr); break;
    case 7: l7(ledNr); break;
    case 8: l8(ledNr); break;
    case 9: l9(ledNr); break;
    case 10: l10(ledNr); break;
    case 11: l11(ledNr); break;
    case 12: l12(ledNr); break;
    case 13: l13(ledNr); break;
    case 14: l14(ledNr); break;
    case 15: l15(ledNr); break;
    case 16: l16(ledNr); break;
    case 17: l17(ledNr); break;
    case 18: l18(ledNr); break;
    case 19: setPlayerLED(player, ledNr, 100); break;
    case 20: setPlayerLED(player, ledNr, 0); break;
    case 99: setLight(ledNr, 'g', 100);                 // for test
    }
}

//============ Purple fade-in ===============
void l1(int ledNr) {
   for (int i=0; i<100; i++) {
      setLight(ledNr, 'P', i);
      delay(10);
   }
      for (int i=100; i>0; i--) {
      setLight(ledNr, 'P', i);
      delay(10);
   }
   setLight(ledNr, '0', 0);
}

//=========== r-g-b-blink ==================
void l2(int ledNr) {
  for (int i=0; i<3; i++) {
    setLight(ledNr, 'R', 100);
    delay(200);
    setLight(ledNr, 'G', 100);
    delay(200);
    setLight(ledNr, 'B', 100);
    delay(200);
  }
   setLight(ledNr, '0', 0);
}

//================ white flash ============
void l3(int ledNr) {
  for (int i=0; i<10; i++) {
    setLight(ledNr, 'W', 100);
    delay(100);
    setLight(ledNr, '0', 100);
    delay(100);
  }
}

//============ red fade-in/out ===============
void l4(int ledNr) {
   for (int i=0; i<100; i++) {
      setLight(ledNr, 'R', i);
      delay(10);
   }
      for (int i=100; i>0; i--) {
      setLight(ledNr, 'R', i);
      delay(10);
   }
   setLight(ledNr, '0', 0);
}

//============ blue fade-in/out ===============
void l5(int ledNr) {
   for (int i=0; i<100; i++) {
      setLight(ledNr, 'B', i);
      delay(10);
   }
      for (int i=100; i>0; i--) {
      setLight(ledNr, 'B', i);
      delay(10);
   }
   setLight(ledNr, '0', 0);
}

//================ blue flash =================
void l6(int ledNr) {
  for (int i=0; i<5; i++) {
    setLight(ledNr, 'B', 100);
    delay(200);
    setLight(ledNr, '0', 100);
    delay(200);
  }
}

//================ blue/red flash ============
void l7(int ledNr) {
  for (int i=0; i<5; i++) {
    setLight(ledNr, 'B', 100);
    delay(200);
    setLight(ledNr, 'R', 100);
    delay(200);
  }
  setLight(ledNr, '0', 0);
}

//============= blue/yellow flash ============
void l8(int ledNr) {
  for (int i=0; i<5; i++) {
    setLight(ledNr, 'B', 100);
    delay(200);
    setLight(ledNr, 'Y', 100);
    delay(200);
  }
  setLight(ledNr, '0', 0);
}

//================ white/red flash ============
void l9(int ledNr) {
  for (int i=0; i<5; i++) {
    setLight(ledNr, 'W', 100);
    delay(200);
    setLight(ledNr, 'R', 100);
    delay(200);
  }
  setLight(ledNr, '0', 0);
}

//================ yellow/green flash ============
void l10(int ledNr) {
  for (int i=0; i<5; i++) {
    setLight(ledNr, 'Y', 100);
    delay(200);
    setLight(ledNr, 'G', 100);
    delay(200);
  }
  setLight(ledNr, '0', 0);
}

//================ red/green flash ============
void l11(int ledNr) {
  for (int i=0; i<5; i++) {
    setLight(ledNr, 'R', 100);
    delay(200);
    setLight(ledNr, 'G', 100);
    delay(200);
  }
  setLight(ledNr, '0', 0);
}

//=========== fade blue out - white in ==========
void l12(int ledNr) {
      for (int i=100; i>0; i--) {
      setLight(ledNr, 'B', i);
      delay(10);
   }
   for (int i=0; i<100; i++) {
      setLight(ledNr, 'W', i);
      delay(10);
   }
   setLight(ledNr, '0', 0);
}


//=========== fade blue in - purple out ==========
void l13(int ledNr) {
   for (int i=0; i<100; i++) {
      setLight(ledNr, 'B', i);
      delay(10);
   }
   for (int i=100; i>0; i--) {
      setLight(ledNr, 'P', i);
      delay(10);
   }
   setLight(ledNr, '0', 0);
}

//========= r-0-w-0-b-0 ======================
void l14(int ledNr) {
  setLight(ledNr, 'R', 100);
  delay(200);
  setLight(ledNr, '0', 100);
  delay(200);
  setLight(ledNr, 'W', 100);
  delay(200);
  setLight(ledNr, '0', 100);
  delay(200);
  setLight(ledNr, 'B', 100);
  delay(200);  
  setLight(ledNr, '0', 100);
}

//========= y-w-p-w-b-w ======================
void l15(int ledNr) {
  setLight(ledNr, 'Y', 100);
  delay(200);
  setLight(ledNr, 'W', 100);
  delay(200);
  setLight(ledNr, 'P', 100);
  delay(200);
  setLight(ledNr, 'W', 100);
  delay(200);
  setLight(ledNr, 'B', 100);
  delay(200);  
  setLight(ledNr, 'W', 100);
  delay(200);  
  setLight(ledNr, '0', 100);
}

//======================= y-b-r-g-p fade in =======================
void l16(int ledNr) {
   for (int i=0; i<100; i++) {
      setLight(ledNr, 'Y', i);
      delay(4);
   }
   setLight(ledNr, '0', 0);
   for (int i=0; i<100; i++) {
      setLight(ledNr, 'B', i);
      delay(4);
   }
   setLight(ledNr, '0', 0);
   for (int i=0; i<100; i++) {
      setLight(ledNr, 'R', i);
      delay(4);
   }
   setLight(ledNr, '0', 0);
   for (int i=0; i<100; i++) {
      setLight(ledNr, 'G', i);
      delay(4);
   }
   setLight(ledNr, '0', 0);
   for (int i=0; i<100; i++) {
      setLight(ledNr, 'P', i);
      delay(4);
   }
   setLight(ledNr, '0', 0);
}

void l17(int ledNr) {
    setLight(ledNr, 'R', 100);
    delay(700);
    setLight(ledNr, 'G', 100);
    delay(700);
    setLight(ledNr, 'B', 100);
    delay(700);
    setLight(ledNr, '0', 0);
}

void l18(int ledNr) {
    setLight(ledNr, 'R', 100);
    delay(300);
    setLight(ledNr, 'G', 100);
    delay(300);
    setLight(ledNr, 'B', 100);
    delay(300);
    setLight(ledNr, 'Y', 100);
    delay(300);
    setLight(ledNr, 'W', 100);
    delay(300);
    setLight(ledNr, '0', 0);  
}

//========== Set LEDs permanently to player color ==========
void setPlayerLED(int player, int ledNr, int brightness) {
  if(player == 1) setLight(ledNr, 'r', brightness);
  else setLight(ledNr, 'g', brightness);
}


void setLight(int nr, char code, int percent) {
  int r,g,b;
  int R,G,B; 

  r = 0; g = 0; b = 0;
  switch (code) {
    case 'R': r = 255; break;
    case 'G': g = 255; break;
    case 'B': b = 255; break;
    case 'Y': r=255; g=255; break;
    case 'P': r=255; b=255; break;
    case 'W': r=255; b=255, g=255; break; 
    case '0': r=0; b=0, g=0; break; 
    case 'r': r=200; b=50, g=50; break; 
    case 'g': r=50; b=50, g=200; break; 
  }

  R = r * percent;
  G = g * percent;
  B = b * percent;
  
  #ifdef PL9823
    strip.setPixelColor(nr, (strip.Color(G/100, R/100, B/100)));    //for PL9823
  #else
    strip.setPixelColor(nr, (strip.Color(R/100, G/100, B/100)));    //for WS2812
  #endif
  strip.show();
}
