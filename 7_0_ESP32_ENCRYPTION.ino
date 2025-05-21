//============================
// Encryption Algorithm 6.0
// ESP32 w/ TFT
// Updates as of 4.13.2024:
//        1. Introducing the working Brute Force Calculator!
//        2. Uses all possible characters or a set of characters to determine all possible combinations, and guess your password you enter. 
//        2. Will return: your password (calculated), will print all combinations possible given a password length and set of characters, number of possible combinations,
//        3. It works now! Fixed the newline characters being added to the input of the user. This has been plaguing Serial input for a long time, but no more!
#include <SPI.h>
#include <Arduino.h>
// encryption variables
            // navigation through the program
            int menuSelector = 0; 
            int wipeIndex = 0; // used to loop through the arrays and delete the data. 
            //=========== encryption stuff
            int encryptionKey = 8; // used to multiply the data or divide it, which makes data encrypted or decrypted. 
            int dataSize = 10000; // keeps track of the size of data array to make. 
            // encrypted data stored in the array data[10,000]
            int data[10000];
            int decryptedData[10000];
            String EncryptedString = ""; // holds encrypted output
            String DecryptedString = ""; // holds decrypted output
            int x = 0; 
            int y = 0; 
            int height = data[x]; // used to draw pixels that represent the data. 
            int dataIndex = 0; // where the user is at in the data array. 
            int numInputs = 0; // this limits the amount of data the user can input. 
            // simple incrementor
            int i = 0; 
            //int z = 0; // loops through the data array to ensure it's not empty before you decrypt it. 
            // keep track of cursor
            int cursorIndex = 0; 
            // decryption
            int decryptPosition = 0; 
            // used to get input from the user, including navigation and encryption input. 
            char incomingByte; 
            int pageY = 40; // keeps track of the scrolling of the page, used for viewing. 
            // keeps track of the page. 
            int pageNumber = 0; // where the esp32 prints out from the data[] array. 
            int pageSize = 700; // number of characters the screen prints out per page.
            int arraySize = 10000; // IMPORTANT - keeps the loop from going outside bounds of array. 
            bool print = false; // controlls printing so the screen doesn't print the output many times
            bool firstBootup = true;// displays menu only if the device has just been turned on. 
            char input = 'x'; // used to select options from main menu of encryption algorithm. 
// Encryption Program Description:
        // The menu asks if the user wishes to decrypt or encrypt data. The menu is where the user loops back to. 
            // input 
                // a series of characters that the user provides.
            // processing 
                // take the ASCII value of each character and multiply it by the encryption key variable; store it in the data array. 
                // note: limited to 312 terms.  
                // decryption: divide each integer by the encryption key; store it in the data[] array. 
            // output
                // the encrypted data as integers, output char at a time. 
                // decryption: the decrypted data as chars, output 1 char at a time. 
                // a value showing where the computer is at decrypting in the array. 
// Brute Force Program Description
//        1. Uses all possible characters or a set of characters to determine all possible combinations, and guess your password you enter. 
//        2. Will return: your password (calculated), will print all combinations possible given a password length and set of characters, number of possible combinations
// HOW DOES IT WORK?
          // it uses a base 94 system as of 2.24.2024. This is because there are 94 possible characters on the keyboard. The computer starts with choosing entry  0 in every single slot of the password. 
          // it then increases the right most character of the password by 1 index entry, so it would go from 'a' to 'b' (Increase from entry [0] to Entry [1])
          // Each place in the password has one of these counters. 
          // when one of the counters is maxed out - it equals the library size. 
          // When a counter goes above 94, it is set to zero. The counter to its LEFT is increased by 1. 
          // in this way, the computer 'counts' in a base 94 system, which has 94 'numbers', each represented by a symbol aA - zZ, 0 - 9, and all special characters. 
          // Somehow, this generates every single possible combination without repeating. 
          // BENEFITS
                    // starts with a single character, and increases until it reaches the maximum size, that way, it guesses all combinations for a 1 character password and then a 2 character password and so on, until it reaches 8 
// BELOW: BRUTE FORCE VARIABLES BRUTE FORCE VARIABLES BRUTE FORCE VARIABLES BRUTE FORCE VARIABLES BRUTE FORCE VARIABLES BRUTE FORCE VARIABLES BRUTE FORCE VARIABLES 
            float numPossibleCombinations = 0;
            // the library of characters from which the computer chooses. aA - bB, 0 - 9, all special characters, and space. 
            char possibleCharacters[] = { ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 
                                          'h', 'i', 'j', 'k', 'l', 'm', 'n', 
                                          'o', 'p', 'q', 'r', 's', 't', 'u', 
                                          'v', 'w', 'x', 'y', 'z', 'A', 'B', 
                                          'C', 'D', 'E', 'F', 'G', 'H', 'I', 
                                          'J', 'K', 'L', 'M', 'N', 'O', 'P', 
                                          'Q', 'R', 'S', 'T', 'U', 'V', 'W', 
                                          'X', 'Y', 'Z', '0', '1', '2', '3', 
                                          '4', '5', '6', '7', '8', '9', ',', 
                                          '`', '|', '"', '}', '{', '[', ']', 
                                          '(', ')', '!', '#', '.', ';', '?', 
                                          '$', '=', '*', '^', '+', '/', '-', 
                                          ':', '>', '<', '_', '&', '%', '@', 
                                          '~', '\\', '\''
                                        }; 

            // READ: these variables control the entry from 'possibleCharacters' the computer chooses. 
                  int onesPlace = 0; // placeholder for the rightmost character in the password. 
                  int twosPlace = 0; 
                  int threesPlace = 0;  
                  int foursPlace = 0; 
                  int fivesPlace = 0; 
                  int sixthsPlace = 0; 
                  int seventhsPlace = 0; 
                  int eighthsPlace = 0; // placeholder for the leftmost character in the password
            int passwordLength = 0; // the length of the password the computer tries to guess.  
            double librarySize = 95; // the size of the library. This also controlls the overflow from 1 place value to the next highest.
            String passwordToGuess = ""; // the password the computer is trying to guess. 
            String guessedPassword = ""; // the current guess the computer has generated. 
            int BruteMenuSelector = 0; 
            bool showOptions = false; // true = display brute mini menu, otherwise don't. 
            bool stopGuess = false; // controls guessing hte password loop. 
            double numCalculations = 0; 
            double possibleCombinations; 
            double percentComplete = numCalculations / possibleCombinations; 
            String inputString; // used for changing password to guess
            bool twosGuessed = false; 
            bool threesGuessed = false; 
            bool foursGuessed = false; 
            bool fivesGuessed = false; 
            bool sixthsGuessed = false; 
            bool seventhsGuessed = false; 
            bool eighthsGuessed = false; 
            double passwordsGuessed = 0; 
// ABOVE: BRUTE FORCE VARIABLES BRUTE FORCE VARIABLES BRUTE FORCE VARIABLES BRUTE FORCE VARIABLES BRUTE FORCE VARIABLES BRUTE FORCE VARIABLES BRUTE FORCE VARIABLES 

void setup() {
  // accept input through the keyboard
  Serial.begin(115200); 
}

void loop() {
switch(menuSelector) {
  // the menu
  case 0:
    if(firstBootup == true) {
      firstBootup = false; 
      Serial.println("Menu:"); 
      Serial.println("a - Encrypt");       // 1
      Serial.println("b - Decrypt");       // 2
      Serial.println("c - Restart");       // 3
      Serial.println("d - Change Key");    // 4
      Serial.println("e - See Commands"); // 5
      Serial.println("f - Send Cipher to Serial Monitor");
      Serial.println("g - Graph CipherText");
      Serial.println("h - Brute Force");
      Serial.println("Your current key is: ");
      Serial.println(encryptionKey);  
    }
        if(Serial.available()) {
          input = Serial.read();
          switch(input) {
            case 'a':
                      // encryption instructions. 
                      Serial.println("Type characters into the Serial monitor.");
                      Serial.println("They will be ouput on the TFT as the ASCII value times the encryption key. The $, the #, the *, and the ^ will all be ignored and not placed into the ciphertext."); 
                      Serial.println("You have typed ");
                      Serial.println(numInputs);
                      Serial.println(" of ");
                      Serial.println(dataSize); 
                      Serial.println("Type a ^ to see number of remaining characters.");  
                      menuSelector = 1;
            break;

            case 'b':
                      // user can return home from here. 
                      if(Serial.available()) {
                            if(Serial.read() == '*') {
                              menuSelector = 0; 
                              Serial.println("Menu:"); 
                              Serial.println("a - Encrypt");      // 1
                              Serial.println("b - Decrypt");      // 2
                              Serial.println("c - Restart");      // 3
                              Serial.println("d - Change Key");   // 4
                              Serial.println("f - Send Cipher to Serial Monitor");
                              Serial.println("g - Graph CipherText");
                              Serial.println("Your current key is: ");
                              Serial.println(encryptionKey); 
                            }
                      }
                      // data appears to be empty
                      if(data[3] == 1 || data[3] == 0) {
                        Serial.println("NO DATA:"); 
                        int h; 
                        for(h = 0; h < 50; h++) {
                          Serial.println(data[h]); 
                          Serial.println(" ");
                        } 
                        // give user time to respond. 
                        delay(2000);
                        firstBootup = true;
                        menuSelector = 0;
                        
                      } 
                      // data appears to be in array. 
                      if(data[3] != 1 || data[3] != 0) {
                        for(decryptPosition = 0; decryptPosition < numInputs; decryptPosition++) {
                            // copy the encrypted data to where it will be decrypted
                            // this step also decrypts. 
                            decryptedData[decryptPosition] = data[decryptPosition] / encryptionKey;
                            DecryptedString += char(decryptedData[decryptPosition]);
                        }
                      menuSelector = 2;
                      Serial.println(DecryptedString); 
                      Serial.println("Use * to go home."); 
                      }
            break;

            case 'c':
                      menuSelector = 3; 
            break;

            case 'd': // user wishes to change the cipher key. 
                      Serial.println("Change Encryption Key"); 
                      Serial.println("The current key is: ");
                      Serial.println(encryptionKey); 
                      //Serial.println("Enter new key:"); 
                      Serial.println("Note: must be a number from 1 - 32768. High numbers are risky because the key multiplied by the text could be over this range. This will likely cause errors.");
                      //Serial.println("The first number will be ignored. To set the key to 100, you would have to type 1100."); 
                      Serial.println("Press 'aaa' to increase the key. Press 'bbb' to decrement the key.");
                      Serial.println("Typing something like 'aaaaaaaaaaaaaaaaaaaaaaaa' is allowed too.") ;
                      menuSelector = 4; 
            break;

            case 'e':
                      Serial.println("Use * at any time to go home.");  
                      Serial.println("$ = Scroll Up");
                      Serial.println("# = Scroll Down");
                      Serial.println("Encryption only: ^ = See remaining characters in the ciphertext");
                      menuSelector = 5; 
            break;

            case 'f': // user wants to send the cipher text into the Serial monitor
                      Serial.println("Printing CipherText . . "); 
                      for(i = 0; i < numInputs; i++) {
                        // print through the data, put it on the Serial monitor. 
                            Serial.println(data[i]); 
                            Serial.println(data[i]); 
                            Serial.println(" "); 
                      }
                      Serial.println("Done!"); 
                      menuSelector = 7;
            break;

            case 'g': // user wishes to print out a visual representation of the ciphertext.
              Serial.println("Deprecated.");                       
              Serial.println("Use '*' to go home.");
              menuSelector = 8; 
            break;
            
            // user chooses brute force algorithm
            case 'h':
                      Serial.println("Redirecting . . . "); 
                      Serial.println("-----BRUTE FORCE CALCULATOR MENU-----"); 
                      // display menu options for brute force calculator
                      Serial.println("a - Set Password"); 
                      Serial.println("b - Show Library"); 
                      Serial.println("c - Calculate Number Combinations"); 
                      Serial.println("d - Show Possible Combinations");
                      Serial.println("e - Guess my Password"); 
                      Serial.println("f - Main Menu"); 
                      Serial.println("g - Change Library Size");
                      menuSelector = 9; 
            break;
            default: // the catch all for user input error in the menu. 
            Serial.println("Invalid."); 
            break;
          }
        }
  break;

  case 1: // user wishes to encrypt
          if(Serial.available()) {
                incomingByte = Serial.read();
          } 
          // user cannot go over data size
          if(Serial.available() && incomingByte != 36 && incomingByte != 35 && incomingByte != 94) {
            // the user has started typing, so start encrypting:
            // The $, the #, the *, and the ^ will all be ignored and not placed into the ciphertext.
            if(numInputs < dataSize && dataIndex < dataSize && cursorIndex < dataSize) {   
              int theOutPut = incomingByte * encryptionKey;
              numInputs++; // the amount of types the user has given input, total. 
              dataIndex++; // the place in the array the user is modifying. 
              data[dataIndex] = theOutPut; // assign at the current index the data that has been encrypted. 
            }  else {
              // user has used up all data spots in array. 
              Serial.println("You have used up all your space. See below:");
              Serial.println("NumInputs:");
              Serial.println(numInputs);
              Serial.println("DataIndex:");
              Serial.println(dataIndex);
              Serial.println("CursorIndex:");
              Serial.println(cursorIndex); 
              Serial.println("Enter an '*' to go home.");
              Serial.println("Choose option 'c' in the menu. This flushes the encryption memory.");
              menuSelector = 6; 
            }
          }
          // user can see how many characters they have left
          if(incomingByte == 94) {
              Serial.println("You have typed ");
              Serial.println(numInputs);
              Serial.println(" of ");
              Serial.println(dataSize); 
            }
          // user has chosen to exit
          if(incomingByte == 42) {
            // the user has chosen to exit. 
            menuSelector = 0; 
            firstBootup = true; 
          }   
          if(incomingByte == 36) {
            if(pageNumber <= arraySize-pageSize) {
              pageNumber+=10;  
              Serial.println("Page #: "); 
              Serial.println(int(pageNumber)); 
              print = true;
            } else {
              Serial.println("End of file: ");
              Serial.println(pageNumber); 
            }
          } 
          if(incomingByte == 35) {
            if(pageNumber > 1 ) {
              pageNumber-=10;  
              Serial.println("Page #: "); 
              Serial.println(int(pageNumber)); 
              print = true;
            } else {
              Serial.println("End of file. Page #: ");
              Serial.println(pageNumber);
            }
          } 
          // print the enrypted data.
          if(print == true) {	
            for(i = 0; i <= pageSize; i++) {
              // don't print 0's or 1's:
              if(data[pageNumber+i] != 0 && data[pageNumber+i] != 1) {
                  Serial.println(data[pageNumber+i]);
                  Serial.println(" ");
              } 
            }
            Serial.println(""); 
            Serial.println("Page #: ");
            Serial.println(pageNumber/10); 
            print = false;
          }
  break;

  case 2: // user wishes to decrypt
      incomingByte = Serial.read(); 
      // print out the numbers, and change them using char() into letters. 
      for(i = 0; i < numInputs; i++) 
      {
        char character = char(decryptedData[i]);
        Serial.println(character);
        // "move" the cursor
        cursorIndex++;
      }
      // user can return home from here.  
        if(incomingByte == 42) {  
          menuSelector = 0;
          Serial.println("Menu:"); 
          Serial.println("a - Encrypt");      // 1
          Serial.println("b - Decrypt");      // 2
          Serial.println("c - Restart");      // 3
          Serial.println("d - Change Key");   // 4
          Serial.println("f - Send Cipher to Serial Monitor");
          Serial.println("g - Graph CipherText"); 
          Serial.println("Your current key is: ");
          Serial.println(encryptionKey); 
        }
  break;

  case 3: // user wishes to restart
    pageY = 40; 
    numInputs = 0; 
    dataIndex = 0; 
    cursorIndex = 0; 
    decryptPosition = 0; 
    // wipe the encryption array and decryption array, by assigning all values to be 1's. 
    wipeIndex = 0; // used to loop through the arrays and delete the data. 
      // wipe decrypted array
      for(wipeIndex = 0; wipeIndex < dataSize; wipeIndex++) {
        if(wipeIndex == 0) {
          Serial.println("Wiping the decrypted array:");
        }
        decryptedData[wipeIndex] = 1; 
      }
      Serial.println("Done!");
      // this x variable makes the loading bar move.
    // wipe encrypted array
      for(wipeIndex = 0; wipeIndex < dataSize; wipeIndex++) { 
        // wipe the data
        data[wipeIndex] = 1;
      }
      Serial.println("Done!"); 
    menuSelector = 0;
    firstBootup = true; 
  break;

  case 4: // user wishes to change the encryption key 
              // the user enters letter to increment or decrement the key. 
              if(Serial.available()) {
                  incomingByte = Serial.read();
                char input = char(Serial.read()); 
                // increment
                if(input == 'a') {
                  encryptionKey++;
                  Serial.println("   Increased to: "); 
                  Serial.println(encryptionKey); 
                }
                // decrement
                  if(input == 'b') {
                    encryptionKey--;
                    Serial.println("   Decreased to: "); 
                    Serial.println(encryptionKey); 
                }
                // user selects to go home by entering an *
                if(incomingByte == 42) {
                          menuSelector = 0; 
                          Serial.println("Menu:"); 
                          Serial.println("a - Encrypt");      // 1
                          Serial.println("b - Decrypt");      // 2
                          Serial.println("c - Restart");      // 3
                          Serial.println("d - Change Key");   // 4
                          Serial.println("e - See Commands");   
                          Serial.println("f - Send Cipher to Serial Monitor");
                          Serial.println("g - Graph CipherText");
                          Serial.println("Your current key is: ");
                          Serial.println(encryptionKey); 
                      }
              }
  break;

  case 5:// user is looking at the commands they can use. 
    if(Serial.available()) 
    {
      incomingByte = Serial.read(); 
    }
    if(incomingByte == 42) 
    {
      // the user has chosen to exit. 
      menuSelector = 0; 
      Serial.println("Menu:"); 
      Serial.println("a - Encrypt");      // 1
      Serial.println("b - Decrypt");      // 2
      Serial.println("c - Restart");      // 3
      Serial.println("d - Change Key");   // 4
      Serial.println("e - See Commands");
      Serial.println("f - Send Cipher to Serial Monitor");
      Serial.println("g - Graph CipherText");
      Serial.println("Your current key is: ");
      Serial.println(encryptionKey); 
    }
  break;

  case 6: // the user has run out of space. 
    if(Serial.available()) 
    {
      incomingByte = Serial.read(); 
        if(incomingByte == 42) 
        {
          firstBootup = true; 
          menuSelector = 0;
        }
    }
  break;

  case 7: // user wishes to send the ciphertext over the Serial monitor
      // user can go home by pressing asterisk. 
      if(Serial.available()) {
        incomingByte = Serial.read(); 
          if(incomingByte == 42) {
            menuSelector = 0; 
            firstBootup = true; 
          }
      }
  break; 

  case 8: // user wishes to map out the ciphertext visually. 
          // this screen will print out different lengths of lines which represent the numerical value of the ciphertext character. 
      // user can go home by pressing asterisk. 
      if(Serial.available()) {
        incomingByte = Serial.read(); 
          if(incomingByte == 42) {
            menuSelector = 0; 
            firstBootup = true; 
          }
      }
  break; 

  // brute force algorithm loop
  case 9: 
          // displays mini menu for Brute Force Algorithm each time the user comes back to it by using an asterisk 
          if(showOptions == true) {
            Serial.println("-----BRUTE FORCE CALCULATOR MENU-----"); 
            // display menu options for brute force calculator
            Serial.println("a - Set Password"); 
            Serial.println("b - Show Library"); 
            Serial.println("c - Calculate Number Combinations"); 
            Serial.println("d - Guess my Password");
            Serial.println("e - ?????"); 
            Serial.println("f - Main Menu"); 
            Serial.println("g - Change Library Size"); 
            showOptions = false;
          }            

        incomingByte = Serial.read();
        // listen for user's choice in the Brute force menu, display the text 1 time, or perform chosen action 1 time and go to another screen so it doesn't loop. 
        switch (incomingByte) {
            case 'a': // Set Password to Guess, 
                        Serial.println("Enter the password you wish to crack: "); 
                        Serial.println("* = Go Home"); 
                        Serial.println("Note: Password must be only 8 characters long. Asterisk Will send you home, so don't make a password with an asterisk."); 
                        BruteMenuSelector = 0; 
                        menuSelector = 10; 
            break;

            case 'b': // Print Library
                        Serial.println("Printing all characters in library:"); 
                        // print the entire  library for debugging.
                        for(i = 0; i < librarySize; i++) {
                            Serial.print(possibleCharacters[i]);
                            Serial.print(" ");   
                          }
                          Serial.println(); 
                          Serial.println("Done!"); 
                          Serial.println("* = Go Home"); 
                          BruteMenuSelector = 1;
                          menuSelector = 10;
                      // -----
            break;

            case 'c': // Calculate # of possible Combinations
                      Serial.println("* = Go Home"); 
                      Serial.println("Number of Possible calculations is "); 
                      Serial.println(librarySize);
                      Serial.println(" ^ 8"); 
                      Serial.println(); 
                      possibleCombinations = pow(librarySize, 8);
                      Serial.println(possibleCombinations);
                      BruteMenuSelector = 2; 
                      menuSelector = 10;
            break;

            case 'd': // Show Possible Combinations
                      Serial.println("* = Go Home"); 
                      onesPlace = 0; 
                      twosPlace = 0; 
                      threesPlace = 0; 
                      foursPlace = 0; 
                      fivesPlace = 0; 
                      sixthsPlace = 0; 
                      seventhsPlace = 0; 
                      eighthsPlace = 0; 
                      BruteMenuSelector = 3; 
                      menuSelector = 10;
                      possibleCombinations = pow(librarySize, 8.00); 
                      passwordsGuessed = 0; 
                      // guess the password as long as 'stopguess' is false. 
                      while (stopGuess == false) {
                        // increase counter by 1
                        onesPlace+=1; 
                        checkPassword(); 
                        passwordsGuessed ++; 
                        // keep track of the number of calculations
                        numCalculations+=1; 
                        // Show how close till done
                        //percentComplete =  (numCalculations / possibleCombinations)*10;
                        if(onesPlace > librarySize) {
                          twosPlace+=1; 
                          onesPlace = 0; 
                          twosGuessed = true;// bool set to true which allows "checkPassword()" to append it to the guessed password.
                          checkPassword(); 
                        }

                        if(twosPlace > librarySize) {  
                          twosPlace = 0; 
                          threesPlace += 1; 
                          threesGuessed = true; // bool set to true which allows "checkPassword()" to append it to the guessed password. 
                          checkPassword(); 
                        }

                        if(threesPlace > librarySize) {
                          threesPlace = 0; 
                          foursPlace +=1; 
                          foursGuessed = true; // bool set to true which allows "checkPassword()" to append it to the guessed password. 
                          checkPassword(); 
                        }

                        if (foursPlace > librarySize) {
                          fivesGuessed = true; // bool set to true which allows "checkPassword()" to append it to the guessed password. 
                          foursPlace = 0; 
                          fivesPlace +=1; 
                          checkPassword(); 
                        }

                        if(fivesPlace > librarySize) {
                          sixthsGuessed = true; // bool set to true which allows "checkPassword()" to append it to the guessed password. 
                          fivesPlace = 0; 
                          sixthsPlace +=1; 
                          checkPassword(); 
                        }

                        if(sixthsPlace > librarySize) {
                          seventhsGuessed = true; // bool set to true which allows "checkPassword()" to append it to the guessed password. 
                          sixthsPlace = 0; 
                          seventhsPlace += 1; 
                          checkPassword(); 
                        }

                        if (seventhsPlace > librarySize) {
                          eighthsGuessed = true; // bool set to true which allows "checkPassword()" to append it to the guessed password. 
                          seventhsPlace = 0; 
                          eighthsPlace +=1; 
                          checkPassword(); 
                        }

                        if(eighthsPlace > librarySize) {
                          stopGuess = true;
                          Serial.println("Stopping."); 
                        } 
                        checkPassword(); 
                      }
            break;

            case 'e': // Guess my password
                      Serial.println("* = Go Home"); 
                      BruteMenuSelector = 4;
                      menuSelector = 10;
            break;

            // user wants to return to main menu
            case 'f':
                    menuSelector = 0; 
                    firstBootup = true; 
            break;

            // user wants to change library size
            case 'g':
              Serial.println("* = Go Home"); 
              Serial.println("Enter a number into the Serial Monitor to change the library size"); 
              BruteMenuSelector = 5; 
              menuSelector = 10; 
            break;
        }
  break;

  // Where the user goes from the Brute Force Menu, using BruteMenuSelector. At this point the calculations should be done already and the user just can choose to go home from here. 
  // BUT this is usually where we loop to get info as well. 
  case 10: 
        switch (BruteMenuSelector) {
            // User comes here from 'Set Password to Guess' 
            case 0: 
                  Serial.flush();
                  if(Serial.available()) {
                    // read the first character
                    incomingByte = Serial.read(); 
                    // check if the first character is '*', indicating a request to go home
                    if(incomingByte == 42) {
                        menuSelector = 9;
                        showOptions = true; 
                    } else {
                      // include the first character in the password 
                      passwordToGuess = String(incomingByte);
                      // read the rest of the characters in the Serial buffer
                      while(Serial.available()) {
                          incomingByte = Serial.read();
                          passwordToGuess += String(incomingByte); // append each character to the string
                      } 
                      // trim newline characters and whitespace from the password:
                      passwordToGuess.trim(); 
                      // display the entered password
                      Serial.println("Password to Crack: "); 
                      Serial.println(passwordToGuess);
                      Serial.println("Length: "); 
                      Serial.println(String(passwordToGuess.length()));
                    }
                }
            break;

            // user comes here from 'print library'
            case 1:
                  // user can return to Brute Home from here.
                  if(Serial.available()) {
                  incomingByte = Serial.read(); // go home using asterisk
                  if(incomingByte == 42) {  
                    menuSelector = 9;
                    showOptions = true; 
                  }
          }
            break;
            
            // user comes here from 'calculate # of possible combinations'
            case 2:
                  // user can return to Brute Home from here.

                  if(Serial.available()) {
                  incomingByte = Serial.read(); // go home using asterisk
                  if(incomingByte == 42) {
                    menuSelector = 9;
                    showOptions = true;   
                  }
          }
            break;

            // user comes here from 'show possible combinations'
            case 3:
                  // user can return to Brute Home from here.

                  if(Serial.available()) {
                  incomingByte = Serial.read(); // go home using asterisk
                  if(incomingByte == 42) {
                    menuSelector = 9;
                    showOptions = true; 
                    stopGuess = false; 
                  }
          }
            break;

            // user comes here from 'guess my password'
            case 4:
                  // user can return to Brute Home from here.
                  if(Serial.available()) {
                    incomingByte = Serial.read(); // go home using asterisk
                    if(incomingByte == 42) {
                      menuSelector = 9;
                      showOptions = true;  
                    }
                  }
            break;
            
            // user comes here from "change library size"
            case 5:
                  // user can return to Brute home form here and change the library size. 
                  if(Serial.available()) {
                    incomingByte = Serial.read(); // go home using asterisk
                    if(incomingByte == 42) {
                      menuSelector = 9;
                      showOptions = true;  
                    }
                  // user can change library size:
                  if(incomingByte == 'a' && librarySize < 94) {
                    librarySize += 1; 
                    Serial.println("Library Size Changed: "); 
                    Serial.println(librarySize); 
                  }

                  if(incomingByte == 'b' && librarySize > 1) {
                    librarySize -=1; 
                    Serial.println("Library Size Changed: "); 
                    Serial.println(librarySize); 
                  }
                  }
            break;
        }
  break;
}
}

void checkPassword() {
  guessedPassword="";                 
  // only add the letters to the guessed password if they haven't been changed yet. 
  guessedPassword+=possibleCharacters[onesPlace];
  if(twosGuessed == true) { guessedPassword+=possibleCharacters[twosPlace];}
  if(threesGuessed == true) {guessedPassword+=possibleCharacters[threesPlace];}
  if(foursGuessed == true) {guessedPassword+=possibleCharacters[foursPlace];}
  if(fivesGuessed == true) {guessedPassword+=possibleCharacters[fivesPlace];}
  if(sixthsGuessed == true) {guessedPassword+=possibleCharacters[sixthsPlace];}
  if(seventhsGuessed == true) {guessedPassword+=possibleCharacters[seventhsPlace];}
  if(eighthsGuessed == true) {guessedPassword+=possibleCharacters[eighthsPlace];} 
  // update the user on the number of guesses
  if(passwordsGuessed > 1000000) {
    passwordsGuessed = 0; 
    Serial.print("Guessed ");
    Serial.print(numCalculations);
    Serial.print(" times: Current Password: "); 
    Serial.print(guessedPassword); 
    Serial.println(); 
  }
  if(guessedPassword.equals(passwordToGuess)) {
    stopGuess = true; 
    Serial.println("Is your password "); 
    Serial.println(guessedPassword); 
  }
}