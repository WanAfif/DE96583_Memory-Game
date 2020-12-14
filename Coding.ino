/*
  Title		: Arduino Memory Test Game
  Programmed by	: Wan Afif Hilmi
  Created on   	: 22 November 2020
*/

//the LiquidCrystal library included
#include<LiquidCrystal.h>
LiquidCrystal lcd(A5,A4,5,4,3,2);	//(RS,EN,DB4,DB5,DB6,DB7)

/*----------------------------------------setup function--------------------------------*/
void setup()
{
   //LED pins set to output
   pinMode(13, OUTPUT);
   pinMode(12, OUTPUT);
   pinMode(11, OUTPUT);
   pinMode(10, OUTPUT); 
  
   //button pins set to input
   //enable internal pullup; buttons start in high position; logic reversed
   pinMode(9, INPUT_PULLUP);
   pinMode(8, INPUT_PULLUP);
   pinMode(7, INPUT_PULLUP);
   pinMode(6, INPUT_PULLUP);
 
  
  Serial.begin(9600);
  randomSeed(42);	//To generate "more randomness" with the randomNumber for the output function
  
  //lcd
  lcd.begin(16,2);	//configure type of LCD
  lcd.setCursor(0,0);
  lcd.print("Welcome to the");
  lcd.setCursor(1,1);
  lcd.print("Game System ^_^");
  delay(2000);
  lcd.clear();
  
  //count down
  lcd.setCursor(4,0);
  lcd.print("Start In");
  for(int d=5; d>=1; d--)
  {
  lcd.setCursor(7,1);
  lcd.print(d);
  lcd.print("s");
  delay(1000);
  }
  delay(1000);
  lcd.clear();
  successed();
}
/*----------------------------------------end of setup function--------------------------------*/

byte randomNumber,size=1,Highscore=0,life=16;
byte arr[250];
bool S = true,button1,button2,button3,button4;

/*----------------------------------------loop function---------------------------------------*/
void loop()
{
  Serial.println(size);
  for(byte i=0 ; i<size ;i++)	//to randomize once
  {
    randomNumber = random(1,5);	//to assigning a random number (1-4) to the randomNumber
    arr[i]=randomNumber;
    digitalWrite(randomNumber+9,HIGH);
    delay(400);
    digitalWrite(randomNumber+9,LOW);
    delay(200);
    
    //the stored values in the array will be display 
    if(randomNumber==1)
     Serial.println("Green");
    
	else if(randomNumber==2)
     Serial.println("Yellow");
      
	else if(randomNumber==3)
     Serial.println("Blue");
      
	else if(randomNumber==4)
     Serial.println("Red");
   
  }
  for(byte i=0 ; i<size;)	//Size count control the statement 
  {
    button1=digitalRead(9);
    button2=digitalRead(8);
    button3=digitalRead(7);
    button4=digitalRead(6);
    
    //Checking for button push
    if(arr[i]==1&&!button1&&button2&&button3&&button4)	//check for the Green LED's button
      i++;
    else if(arr[i]==2&&button1&&!button2&&button3&&button4)	//check for the Yellow LED's button
      i++;
    else if(arr[i]==3&&button1&&button2&&!button3&&button4)	//check for the Blue LED's button
      i++;
    else if(arr[i]==4&&button1&&button2&&button3&&!button4)	//check for the Red LED's button
      i++;
    else if(button1&&button2&&button3&&button4)	//ignore if no button is push
    {
      continue;
    }
    else
    {
        life--;	//decrease player's life by 1 when wrongly press
		if(life)
        {
          extra();
        }
        else
        {
          S=false;
        }
      
      break;
    }
    delay(100);
  }
  if(S)
  {
    Serial.println("Sucessed");
    size++;		//increace the number of output for the LED to be display
    successed();
  }
  else
  {
    
    Serial.println("Game over !");
    size=1;
    life=16;
    S=true;
    finish();
  }

  
}
/*----------------------------------------end of loop function--------------------------------*/

/*-------------------------------------------other functions----------------------------------*/
void successed()	
{//Function used to display the player's score
  	lcd.clear();
    lcd.print("Your Score: ");
    lcd.print(size-1);
    lcd.setCursor(0,1);
    lcd.print("High Score: ");
    if(size-1>Highscore)
      Highscore=size-1;
    lcd.print(Highscore);
}
void finish()	
{//Function used to display when player's life is zero or none
    lcd.clear();
    lcd.setCursor(3,0);
    lcd.print("Game Over!");
     lcd.setCursor(4,1);
    lcd.print("You Lose");
    delay(1000);
    successed();
}
void extra()	
{//Function used to display the remaining life of the player
	lcd.clear();
  	for(byte i=0 ; i<life ;i++)
      lcd.print("*");
 	
  lcd.setCursor(1,1);
  lcd.print("U 've a ");
  lcd.print(life);
  lcd.print(" life");
  delay(1000);
  size--;
  successed();
}
/*-------------------------------------------end of other functions----------------------------------*/ 
