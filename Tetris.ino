#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

#define TFT_MISO 12 
#define TFT_LED A0 
#define TFT_SCK 13 
#define TFT_MOSI 11 
#define TFT_DC 9
#define TFT_RESET 8 
#define TFT_CS 10
#define GAME_ROW 12
#define GAME_COLUMN 16

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC,TFT_MOSI,TFT_SCK,TFT_RESET,TFT_MISO);
// 0 empty
// 1 placed block
int game[GAME_ROW][GAME_COLUMN] = {
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};

int leftButton = 2;
int downButton = 3;
int rotateButton = 4;
int rightButton = 5;

// Array that holds the blocks
// Every row has a square of block and the column has its cordinate
int tetromino[4][2];
// Location of center point of block
int point[2] = {0,0};
// What is the current block
int block;
// What is the state of current location (every tetromino is generated in state 0)
int state = 0;


void setup() {

  pinMode(rightButton, INPUT);
  pinMode(leftButton, INPUT);
  pinMode(rotateButton, INPUT);
  pinMode(downButton, INPUT);

  // put your setup code here, to run once:
  pinMode(TFT_LED, OUTPUT);
  digitalWrite(TFT_LED, HIGH);
  tft.begin();
  tft.setRotation(2);
  tft.fillScreen(ILI9341_WHITE);
  for (int i = 0; i < GAME_ROW; i++ ){
    for (int j = 0; j < GAME_COLUMN; j++){
      if (game[i][j] == 1){
        tft.fillRect(i*20, j*20, 20, 20, ILI9341_BLACK);
      }
    }
  }
  randomSeed(analogRead(A3));
  generateRandomBlock();
}

void loop() {
  int leftButtonValue = digitalRead(leftButton);
  int rightButtonValue = digitalRead(rightButton);
  int rotateButtonValue = digitalRead(rotateButton);
  int downButtonValue = digitalRead(downButton);
  int fullColumn = checkFullColumn(); 
  if(fullColumn != -1){
    clearColumn(fullColumn);
    allBlockDown(fullColumn);
  }
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 4; i++){
    tft.drawRect(tetromino[i][0]* 20, tetromino[i][1]*20, 20, 20, ILI9341_BLACK);
  }
  delay(100);


  // Make blocks dissapear and update the values
  if(canGoDown()){
    makeBlockGoDown();
  } else{
    makeBlockPlaced();
    generateRandomBlock();
  }


  if (leftButtonValue == 1){
    if(canGoLeft()){
      makeBlockGoLeft();
    }
  }
  if (rightButtonValue == 1){
    if(canGoRight()){
      makeBlockGoRight();
    }
  }
  if (rotateButtonValue == 1) {
    if(canRotate()){
      rotateBlock();
    }
  }
  if(downButtonValue != 1){
    delay(100);

  }


}


// These functions generate the tetromino in the middle of the screen

void generateIBlock()
{
  tetromino[0][0] = 4;
  tetromino[0][1] = 0;

  tetromino[1][0] = 5;
  tetromino[1][1] = 0;

  tetromino[2][0] = 6;
  tetromino[2][1] = 0;

  tetromino[3][0] = 7;
  tetromino[3][1] = 0;
}

void generateJBlock()
{
  tetromino[0][0] = 4;
  tetromino[0][1] = 0;

  tetromino[1][0] = 4;
  tetromino[1][1] = 1;

  tetromino[2][0] = 5;
  tetromino[2][1] = 1;

  tetromino[3][0] = 6;
  tetromino[3][1] = 1;

}

void generateLBlock()
{

  tetromino[0][0] = 6;
  tetromino[0][1] = 0;

  tetromino[1][0] = 4;
  tetromino[1][1] = 1;

  tetromino[2][0] = 5;
  tetromino[2][1] = 1;

  tetromino[3][0] = 6;
  tetromino[3][1] = 1;


}

void generateOBlock()
{
  tetromino[0][0] = 5;
  tetromino[0][1] = 0;

  tetromino[1][0] = 6;
  tetromino[1][1] = 0;

  tetromino[2][0] = 5;
  tetromino[2][1] = 1;

  tetromino[3][0] = 6;
  tetromino[3][1] = 1;


}

void generateSBlock()
{
  tetromino[0][0] = 5;
  tetromino[0][1] = 0;

  tetromino[1][0] = 6;
  tetromino[1][1] = 0;

  tetromino[2][0] = 4;
  tetromino[2][1] = 1;

  tetromino[3][0] = 5;
  tetromino[3][1] = 1;

}
void generateTBlock()
{
  tetromino[0][0] = 5;
  tetromino[0][1] = 0;

  tetromino[1][0] = 4;
  tetromino[1][1] = 1;

  tetromino[2][0] = 5;
  tetromino[2][1] = 1;

  tetromino[3][0] = 6;
  tetromino[3][1] = 1;
}
void generateZBlock()
{
  tetromino[0][0] = 4;
  tetromino[0][1] = 0;

  tetromino[1][0] = 5;
  tetromino[1][1] = 0;

  tetromino[2][0] = 5;
  tetromino[2][1] = 1;

  tetromino[3][0] = 6;
  tetromino[3][1] = 1;

}
void generateRandomBlock()
{
  int blockSelect = random(7);
  point[0] = 5;
  point[1] = 1;
  switch(blockSelect){
    case 0:
      generateIBlock();
      point[1] = 0;
      break;
    case 1:
      generateJBlock();
      break;
    case 2:
      generateLBlock();
      break;
    case 3:
      generateOBlock();
      break;
    case 4:
      generateSBlock();
      break;
    case 5:
      generateTBlock();
      break;
    case 6:
      generateZBlock();
      break;
  }
  block = blockSelect;

  return;
}

// Check if there is a placed block (or the ground below) current tetromino

bool canGoDown(){
  for(int i = 0; i < 4; i++){
    int x = tetromino[i][0];
    int y = tetromino[i][1];
    if(game[x][y+1] == 1 || y == 15){
      return false;
    }
  }
  return true;
}

// Moves tetromino a space down

void makeBlockGoDown(){
  for(int i = 0; i < 4; i++){
    tft.drawRect(tetromino[i][0] * 20, tetromino[i][1] * 20, 20, 20, ILI9341_WHITE);
    tetromino[i][1]++;


  }  
  point[1]++;

}

// Turns current tetromino into a placed block

void makeBlockPlaced(){
    for(int i = 0; i < 4; i++){
    int x = tetromino[i][0];
    int y = tetromino[i][1];
    game[x][y] = 1;
    tft.fillRect(x * 20, y * 20, 20, 20, ILI9341_BLACK);

  }
}

// Check if there is a placed block (the borders are blocks too) on the left of current tetromino

bool canGoLeft(){
  for(int i = 0; i < 4; i++){
    int x = tetromino[i][0];
    int y = tetromino[i][1];
    if(game[x - 1][y] == 1 ){
      return false;
    }
  }
  return true;
}

// Moves tetromino a space left

void makeBlockGoLeft(){
  for(int i = 0; i < 4; i++){
    tft.drawRect(tetromino[i][0] * 20, tetromino[i][1] * 20, 20, 20, ILI9341_WHITE);
    tetromino[i][0]--;
  }  
  point[0]--;

}

// Check if there is a placed block (the borders are blocks too) on the right current tetromino


bool canGoRight(){
  for(int i = 0; i < 4; i++){
    int x = tetromino[i][0];
    int y = tetromino[i][1];
    if(game[x + 1][y] == 1 ){
      return false;
    }
  }
  return true;
}

// Moves tetromino a space right

void makeBlockGoRight(){
  for(int i = 0; i < 4; i++){
    tft.drawRect(tetromino[i][0] * 20, tetromino[i][1] * 20, 20, 20, ILI9341_WHITE);
    tetromino[i][0]++;
  }  
  point[0]++;

}

// This function makes sure there is nothing on the location the tetromino will be rotated

bool canRotate(){
  for (int i = 0; i < 4; i++){
    int x = tetromino[i][0];
    int y = tetromino[i][1];
    int relativeX =  x - point[0];
    int relativeY =  point[1] - y;
    int rotatedCordinateX = relativeY + point[0];
    int rotatedCordinateY = relativeX + point[1];
    if (rotatedCordinateX <= 0 || rotatedCordinateX >= 11){
      return false;
    }
    if ( rotatedCordinateY > 15 || rotatedCordinateY < 0){
      return false;
    }
    if ( game[rotatedCordinateX][rotatedCordinateY] == 1){
      return false;
    }
  }
  return true;
}

// Rotates current tetromino

void rotateBlock(){
  if (block == 3){
    return;
  }
  for (int i = 0; i < 4; i++){
    int x = tetromino[i][0];
    int y = tetromino[i][1];
    int relativeX =  x - point[0];
    int relativeY =  point[1] - y;
    int rotatedCordinateX = relativeY + point[0];
    int rotatedCordinateY = relativeX + point[1];

    tetromino[i][0] = rotatedCordinateX;
    tetromino[i][1] = rotatedCordinateY;
  }
  if (block == 0){
    switch (state)
    {
      case 0:
        point[1]++;
        break;
      case 1:
        point[0]++;
        break;
      case 2:
        point[1]--;
        break;
      case 3:
        point[0]--;
        break;
      
      default:
        break;
    }
  }
  if (state == 3){
    state = 0;
  } else{
    state++;
  }


}

// The functions bellow check if there is a full column, if there is they clear it and move everything one block down

int checkFullColumn()
{
  for (int j = 0; j < 16; j++){
    for (int i = 1; i < 11; i++ ){

      if(game[i][j] == 0){
        break;
      }

      if (i == 10){
        return j;

      }
    }
  }
return -1;



}
void clearColumn(int column){
  for (int i = 1; i < 11; i++ ){
    game[i][column] = 0;
    tft.fillRect( i * 20, column * 20, 20, 20, ILI9341_WHITE);

  }

}

void allBlockDown(int column){
  for(int j = column -1 ; j >= 0; j--){
    for (int i = 1; i < 11; i++ ){
      if(game[i][j] == 1){
        game[i][j] = 0;
        tft.fillRect( i * 20, j * 20, 20, 20, ILI9341_WHITE);
        game[i][j+1] = 1;
        tft.fillRect( i * 20, (j+1) * 20, 20, 20, ILI9341_BLACK);   
      }


    }
  }
}
