int gebruikerCode[4];// Array to store users 4 number code
int invoerCode[4];//array that checks if valid

int clearButton;//global array for clear button

const int rowPins[4] = {8, 12, 6, 4};   
const int colPins[3] = {9, 7, 5};       

//this is the 4x3 grid array for the numbpad
int keys[4][3] = {
  {1, 2, 3},
  {4, 5, 6},
  {7, 8, 9},
  {12, 0, 11} 
};//button 0 to 9 are normal keys, 12 is clear and 11 is enter




void setup() {
  Serial.begin(9600);
  Serial.println("jeff safe booting up");

  pinMode(8, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);

  //init the collum keys and sets it to high
  for (int j = 0; j < 3; j++) {
    pinMode(colPins[j], OUTPUT);
    digitalWrite(colPins[j], HIGH);
  }

  pinMode(A3, OUTPUT);//green led
  pinMode(A4, OUTPUT);//red led
  pinMode(A5, OUTPUT);//yellow led

  pinMode(A2, OUTPUT);//buzzer
  pinMode(A0, OUTPUT);//electro magnet

  pinMode(3, INPUT);//reset button
}



void loop() {
  //cals function
  gebruikerInvoerCode();
  delay(300);
  //cals function
  printGebruikerCode();

  
    
    
    Serial.println("safe is closed, enter your 4 digit pin to open the safe");

    for(int j=0; j<4;){
        int key = scanKeypad();
        int clearButton = 0;

        if (key > -1 && key <= 9) {
      invoerCode[j] = key;
      Serial.print("Key pressed: ");
      Serial.println(key);
      j++;
      geluidCijfer();
      delay(200);
      
      
    
      }
    // this is code for the clear button
    else if(key ==12){
      clearButton = 130;
      geluidClear();

      if(clearButton ==130){
     j =0;
     Serial.println("clear button pressed, please enter a 4 digit code");
     clearButton =0;
                     }
         }
    }
    Serial.println("Press enter button");
  // this is for the enter key to function
  for(int a=0; a<1;){
    int key = scanKeypad();

      if(key == 11){
      a++;
      geluidCijfer();
        }

      
      }
   // code check to compare if the users input == 4 digit pin   
  if(gebruikerCode[0] == invoerCode[0] && gebruikerCode[1] == invoerCode[1] && gebruikerCode[2] == invoerCode[2] && gebruikerCode[3] == invoerCode[3]){
     
     Serial.println("juiste code ingevoerd");
     tone(A2, 700);
     digitalWrite(A3, HIGH);
     
    
     digitalWrite(A0, HIGH);
     delay(2000);
     digitalWrite(A0, LOW);
     digitalWrite(A3, LOW);
     noTone(A2);
     }
  else{
    Serial.println("onjuiste code ingevoerd");
    tone(A2, 450);
    digitalWrite(A4, HIGH);
    delay(1000);
    noTone(A2);
    digitalWrite(A4, LOW);
                          }
  
  
  }


//scans the grid array
int scanKeypad() {
  for (int c = 0; c < 3; c++) {
    // Set the current column to LOW
    digitalWrite(colPins[c], LOW);

    // Loop through every row to check for key presses
    for (int r = 0; r < 4; r++) {
      // when a row pin == low that means that a key is being pressed
      if (digitalRead(rowPins[r]) == LOW) {
        delay(50);//debounce 

        
        if (digitalRead(rowPins[r]) == LOW) {
          // Wait until the key is released
          while (digitalRead(rowPins[r]) == LOW);

          // Set the column back to HIGH before returning the key
          digitalWrite(colPins[c], HIGH);

          // Return the value from the key map
          return keys[r][c];
        }
      }
    }

    // Set the columstatus back to high
    digitalWrite(colPins[c], HIGH);
  }


 
  return -1; //-1 is no key currently being pressed



  
}

//asks user for 4 digit code
int gebruikerInvoerCode(){

  Serial.println("Please enter your 4-digit code and press the E key after:");

  // this is code for user input 4 digit code
  
  int clearButton =0;
  
  for(int invoerGetallen = 0; invoerGetallen < 4;) {
    int key = scanKeypad();

    //ignores special keys and no key being pressed
    if (key > -1 && key <= 9) {
      gebruikerCode[invoerGetallen] = key;  // Store number in array
      Serial.print("the key  you have pressed is: ");
      Serial.println(key);
      invoerGetallen++;
      geluidCijfer();
      delay(200);
      
      
    
    }
    //code for the clear button
    else if(key ==12){
      clearButton = 130;
      geluidClear();

      if(clearButton ==130){
     invoerGetallen =0;
     Serial.println("clear button pressed, please enter a 4 digit code");
     clearButton =0;
     
     
    }
      
    
    
    }
    

  }
  Serial.println("Press enter button");
  //code for the enter button
  for(int a=0; a<1;){
    int key = scanKeypad();

    if(key == 11){
      a++;
      geluidCijfer();
    }

    else{
      
    }

    delay(100);
    
    
  }
  
  
}


int printGebruikerCode(){
  
  Serial.print("The code you have entered: ");
  
  if(gebruikerCode[0] == 0 && gebruikerCode[1] == 0 && gebruikerCode[2] == 0 && gebruikerCode[3] == 0){
    Serial.println("Clear button pressed, input a new code 4 digit code");
  }
  else{
  for (int i = 0; i < 4; i++) {
    Serial.print(gebruikerCode[i]);
  }
  }
  Serial.println();
}

int geluidCijfer(){
   digitalWrite(A5, HIGH);
  delay(200);
  digitalWrite(A5, LOW);
  tone(A2, 800);
  delay(200);
  noTone(A2);
  
}

int geluidClear(){
  tone(A2, 1000);
  delay(200);
  noTone(A2);
}


//code written by Jeffrey, 1st year electrical engineering student
