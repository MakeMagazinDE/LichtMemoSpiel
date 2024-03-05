/***********************************************************************************
 * LED-Memory mit Kugeln aus Deo-Rollern             (C) Ralf Stoffels 2023
 * 
 ***********************************************************************************/
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#define PIN 10 // Data in on Pin 10


Adafruit_NeoPixel strip = Adafruit_NeoPixel(64, PIN, NEO_GRB + NEO_KHZ800);

//================================ Global Variables ================================
#define PITS 36           // Size of the board
#define XMAX 6            // Number of Columns of the board
#define YMAX 6            // Number or Rows of the board
#define THRESHOLD 20      // Minimum Sensor-Value-Change for Ball Detection

#define DEBUG 2           // Debug-Level: 1 = All Sensor Values, 2 = Decisions
#define PL9823            // This define swaps the colors red and green for the PL9823
                          // in order to make it compatible with WS2812 

int senseArray[PITS];     // The up-to-date representation of the board as analog sensor values
int lastSenseArray[PITS]; // Stores the previous values of the sense Array
int calArray[PITS];       // This Matrix contains the reflection values without balls
int effectArray[PITS];    // Contains the refernces to the light effects (random)
int playerArray[PITS];    // Holds the correctly placed balls for the two players
int player;               // Stores, which player is active (1|2)
int ballNr;               // first or second ball
int lastEffectNr;         // remembers the previous effect
int lastNr;               // previous pit;
int playerScore[3];       // Counts the successully found pairs per player (playerScore[0] is wasted)


/*****************************************************************************************************
* Setup is run only after power up
* Each new game is initialized by the function resetGame()
******************************************************************************************************/ 
void setup() {
  pinMode(2, OUTPUT);    // Drivers for the LED of the refection switches
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

  pinMode(A0, INPUT);    // Receivers of the phototransistors of the reflecetion sensors
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);

  for (int i=2; i<8; i++) {
    digitalWrite(i,HIGH);      // Disable all reflection sensors
  }

  Serial.begin(9600);          // For debug
  strip.begin();
  strip.show();                // All Pixels off
  delay(500);

  for (int i=0; i<PITS; i++) {
    #ifdef PL9823
      strip.setPixelColor(i, (strip.Color(50, 200, 50))); // All Pixels RED for PL9823
    #else
      strip.setPixelColor(i, (strip.Color(200, 50, 50))); // All Pixels RED for WS2812
    #endif
  }
  strip.show();

  resetGame();
}

/****************************************************************************************************************
*                                    resetGame is executed to start a new Game
****************************************************************************************************************/
void resetGame() {  
  shuffle();                   // Distribute the effects randomly over the board#
  Serial.println("================ Effects =================");
  printAsMatrix(effectArray);  // Debug and Cheating ;-)

  for (int i=0; i<PITS; i++) playerArray[i]=0;   
  playerScore[1] = 0;
  playerScore[2] = 0;

  delay(200);
  for (int i=0; i<PITS; i++) {
     runEffect(99,i);
     delay(60);
  }
  strip.show();
  delay(500);
    for (int i=0; i<PITS; i++) {
     strip.setPixelColor(i, (strip.Color(0, 0, 0))); // All Pixels OFF
  }
  strip.show();

  readSensors();
  for (int i=0; i<PITS; i++) lastSenseArray[i] = senseArray[i];
  
  player = 1;                     // Start with Player 1 (red)
  ballNr = 1;
  lastEffectNr = -1;
  lastNr = -1;
}


/***************************************************************************************************************
 *                                                   Game Loop 
 ***************************************************************************************************************/
void loop() {
  int nr=0, effectNr;

  #if(DEBUG == 1)  
    readSensors();
    printAsMatrix(senseArray);
  #endif
  
  nr = getChange();    // Check if a ball has been added (return -1 if no change)
  
  #if(DEBUG == 2) 
    if (nr>=0) {
      Serial.print("Changed: ");
      Serial.println(nr);
    }
  #endif
  
  if ((nr>=0) && (nr!=lastNr) && isEmpty(nr)) {
     effectNr = effectArray[nr];
     runEffect(effectNr, nr);
     
     if (ballNr==2) {
       if (effectNr == lastEffectNr) {    // right pair 
         runEffect(19, nr);
         runEffect(19, lastNr);
         playerArray[lastNr] = player;   // Mark the positions in the Matrix
         playerArray[nr] = player;
         playerScore[player]++;          // increment the score of the active player
         
         if (playerScore[1]+playerScore[2]>=18) gameEnd();  // Game ends when all balls are placed

         #if(DEBUG == 1) 
           Serial.println("============= Player Array ================");
           printAsMatrix(playerArray);  
         #endif
         Serial.print("Player: "); Serial.println(player);

         lastEffectNr = -1;
         lastNr = -1;
         ballNr = 1;
       }
       else {                              // wrong pair
         if (player == 1) player = 2; else player = 1;
         ballNr = 1;
         lastNr = nr;
         lastEffectNr = -1;
       }
     }  
     else {              // first of the two balls
       ballNr = 2;
       lastNr = nr;
       lastEffectNr = effectNr;
     }
  }
  delay(10);
}


/****************************************************************************************************************
 *                                        High Level Game Functions
 ****************************************************************************************************************/

//================= Fills the effectArray with random pairs ==================
void shuffle() {     
  int nr;
  
  for (int i=0; i<PITS; i++) effectArray[i]=0;   
  
  pinMode(A6,INPUT);
  randomSeed(analogRead(A6));  // random Seed by using the input noise of an analog pin
  
  for (int effectNr = 1; effectNr<=PITS/2; effectNr++) {      // assign half of the number of pits effects
    do {
       nr = random(0, PITS);
    } while (effectArray[nr]!=0);
    effectArray[nr] = effectNr;
    do {
       nr = random(0, PITS);
    } while (effectArray[nr]!=0);
    effectArray[nr] = effectNr;
  }
} 


//============ Returns the first pit that has changed ========================
int getChange() {
  int firstChange=-1;
  
  readSensors();
  for (int i=PITS-1; i>=0; i--) {
    if (senseArray[i] < lastSenseArray[i]-THRESHOLD) {
      firstChange = i;                      
    } else {
      lastSenseArray[i] = senseArray[i];    // Update the lastSenseArray with the recent Values
    }
  }
  if (firstChange >= 0) lastSenseArray[firstChange] = senseArray[firstChange];  // only update the first field
  return(firstChange);
}


//========== Checks if the change took place on an empty field ===============
boolean isEmpty(int nr) {
  if (playerArray[nr] == 0) return true; else return false;
}


//================ Animation and restart =====================================
void gameEnd() {
  int winner, loser;

  delay(1000);   

  if (playerScore[1] != playerScore[2]) {     // We have a winner
    if (playerScore[1] > playerScore[2]) {
      winner = 1; 
      loser = 2; 
    }
    if (playerScore[1] < playerScore[2]) {
      winner = 2;
      loser = 1;
    }
    setAllPlayerLED(loser, false);
    for (int i=0; i<10; i++) {
      setAllPlayerLED(winner, false);
      delay(200);   
      setAllPlayerLED(winner, true);
      delay(200);
    }
    setAllPlayerLED(loser, true);
  } else {     // tie
    Serial.println("Tie!");
    for (int i=0; i<10; i++) {
      setAllPlayerLED(1, false);
      delay(200);
      setAllPlayerLED(1, true);
      setAllPlayerLED(2, false);
      delay(200);
      setAllPlayerLED(2, true);
    }
    setAllPlayerLED(1, true);
  }
  delay(1000);
  resetGame();
}

//================= Sets all LEDs of a player to on or off =================================
void setAllPlayerLED(int playerFinal, boolean on) {    // LED on or off   
  int nr;

  for (nr = 0; nr < PITS; nr++) {
    if (playerArray[nr] == playerFinal) {
       player = playerFinal;
       if (on) runEffect(19,nr); else runEffect(20,nr); 
    }
  }
}  


/****************************************************************************************************************
 *                                  Hardware access to read board status
 ****************************************************************************************************************/
void readSensors() {
  int row, col;
  int val;

  for (row = 0; row < YMAX; row++) {
    for (col = 0; col < XMAX; col++) {
       digitalWrite(row+2,LOW);
       delay(10);
       val = analogRead(col+A0);
       digitalWrite(row+2,HIGH);
       delay(10);
       senseArray[col*YMAX + row] = val;
    }
  } 
}


/**********************************************************************************************************
*                                       Debug Functions
***********************************************************************************************************/

//========= Switch light on under all balls on the board =========================
void indicateBalls() {
  readSensors();
  for (int i=0; i<PITS; i++) {
     if (senseArray[i] < calArray[i]-THRESHOLD) runEffect(99, i);
  }
}

//======== Print all detected boards in the Terminal Window ======================
void printAsArray(int a[]) {
  for (int i=0; i<PITS; i++) {
    Serial.print(a[i]);
    Serial.print(", ");
  }
  Serial.println(" ");
  Serial.println("==========================================");
}

//=========== Prints the Array with XMAX x YMAX Matrix for easier debug ===========
void printAsMatrix(int m[]) {
  int row, col;
  
  for (row = 0; row < YMAX; row++) {
    for (col = 0; col < XMAX; col++) {
       Serial.print(m[col + XMAX * row]); Serial.print("  ");
    }
    Serial.println(" ");
  }
  Serial.println("==========================================");
}
