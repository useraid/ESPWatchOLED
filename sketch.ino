#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
// Bitmaps for Menu
#include "menuAssets.h"
// Flappy Bird Assets
#include "flappyBirdGame.h"
// Pong Assets
#include "pongGame.h"

Adafruit_SSD1306 display(128, 64, &Wire, -1);

// Button Pin Declaration
#define BUTTON_UP_PIN 12
#define BUTTON_SELECT_PIN 8
#define BUTTON_DOWN_PIN 4
#define BUTTON_BACK_PIN 13

void setup() {
  // Debug Serial
  Serial.begin(115200);
  // Display init
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  // Buttons Init
  pinMode(BUTTON_UP_PIN, INPUT_PULLUP); // up button
  pinMode(BUTTON_SELECT_PIN, INPUT_PULLUP); // select button
  pinMode(BUTTON_DOWN_PIN, INPUT_PULLUP); // down button
  pinMode(BUTTON_BACK_PIN, INPUT_PULLUP); // back button

  display.clearDisplay();
  setupPong();
}

void loop() {

  // UP DOWN SELECT Handler for main menu
  menuButtonHandler();
  // Global BACK Button Handler
  globalBackHandler();  

  // set correct values for the previous and next items
  item_sel_previous = item_selected - 1;
  if (item_sel_previous < 0) {item_sel_previous = NUM_ITEMS - 1;} // previous item would be below first = make it the last
  item_sel_next = item_selected + 1;  
  if (item_sel_next >= NUM_ITEMS) {item_sel_next = 0;} // next item would be after last = make it the first

    if (current_screen == 0) { // MENU SCREEN
      renderMenu();
    } 
    else if (current_screen == 1) {
      
      if (item_selected == 0){
        inProgram = true;
        while (inProgram){
          display.clearDisplay();
          drawCourt();
          mainPong();
          globalBackHandler();
        }
      }
      else if (item_selected == 1) {
        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(12, 8+20+20+2+2);
        display.println("meow meow lol"); 
        display.display();
        
      }
      else if (item_selected == 2) {
        // current_screen = 2;
        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(12, 8+20+20+2+2);
        display.println("meow meow lol"); 
        display.display();
        
      }
      else if (item_selected == 4) {
        inProgram = true;
        while (inProgram){
          display.clearDisplay();
          mainFlappyBird();
          globalBackHandler();
        }
        
      }      
      else {
        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(12, 8+20+20+2+2);
        display.println("not implemented lol"); 
        display.display();
      }
    }
    // else if (current_screen == 2) { // QR SCREEN
    //     display.clearDisplay();
    //     display.setTextSize(1);
    //     display.setTextColor(WHITE);
    //     display.setCursor(12, 8+20+20+2+2);
    //     display.println("not implemented 2 lol"); 
    //     display.display();
    // }

}

void menuButtonHandler(){
  if (current_screen == 0) { // MENU SCREEN

    if ((digitalRead(BUTTON_UP_PIN) == LOW) && (button_up_clicked == 0)) { // up button clicked
      item_selected = item_selected - 1; // select previous item
      button_up_clicked = 1; 
      Serial.println("Up clicked");
      if (item_selected < 0) { // first item was selected
        item_selected = NUM_ITEMS-1;
      }
    }    
    else if ((digitalRead(BUTTON_DOWN_PIN) == LOW) && (button_down_clicked == 0)) { // down button clicked
      item_selected = item_selected + 1; // select next item
      button_down_clicked = 1;
      Serial.println("Down clicked");
      if (item_selected >= NUM_ITEMS) { // last item 
        item_selected = 0;
      }
    } 

    if ((digitalRead(BUTTON_UP_PIN) == HIGH) && (button_up_clicked == 1)) { // unclick 
      button_up_clicked = 0;
    }
    if ((digitalRead(BUTTON_DOWN_PIN) == HIGH) && (button_down_clicked == 1)) { // unclick
      button_down_clicked = 0;
    }
    if ((digitalRead(BUTTON_SELECT_PIN) == LOW) && (button_select_clicked == 0)) { 
      button_select_clicked = 1;
      Serial.println("Select clicked");
      if (current_screen == 0) {
        current_screen = 1;
      }
      else if (current_screen == 1) {current_screen = 2;} 
      else {current_screen = 0;} 
  
    }
    if ((digitalRead(BUTTON_SELECT_PIN) == HIGH) && (button_select_clicked == 1)) { // unclick 
      button_select_clicked = 0;
    }

  }
}

void globalBackHandler(){

  if ((digitalRead(BUTTON_BACK_PIN) == LOW) && (button_back_clicked == 0)) {
    button_back_clicked = 1;
    Serial.println("Back clicked"); 
    if (current_screen == 1) {
      inProgram = false;
      if (item_selected == 0){ stopPong(); }      
      else if (item_selected == 4){ stopFlappyBird(); }
      current_screen = 0;
      }

    else if (current_screen == 2) {current_screen = 1;} 
    else {current_screen = 0;}
  }
  if ((digitalRead(BUTTON_BACK_PIN) == HIGH) && (button_back_clicked == 1)) { // unclick 
    button_back_clicked = 0;
  }
}

void renderMenu(){
  // selection box 
      display.clearDisplay();
      display.drawBitmap(0, 22, bitmap_item_sel_outline, 128, 21, WHITE);

      // previous item in menu
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(12, 8);
      display.println(menu_items[item_sel_previous]);

      // current item in menu
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(12, 8+20+2);
      display.println(menu_items[item_selected]);       

      // next item in menu
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(12, 8+20+20+2+2);
      display.println(menu_items[item_sel_next]);       
   
      // scrollbar background
      display.drawBitmap(128-8, 0, bitmap_scrollbar_background, 8, 64, WHITE);

      // scrollbar handle
      display.fillRect(125, 64/NUM_ITEMS * item_selected, 3, 64/NUM_ITEMS, WHITE);            
      display.display();
}

// Pong Functions
void drawCourt() 
{
    display.drawRect(0, 0, 128, 54, WHITE);
}

void mainPong() {
    bool update_needed = false;
    unsigned long time = millis();

    static bool up_state = false;
    static bool down_state = false;
    
    up_state |= (digitalRead(BUTTON_UP_PIN) == LOW);
    down_state |= (digitalRead(BUTTON_DOWN_PIN) == LOW);

    if(time > ball_update){
        uint8_t new_x = ball_x + ball_dir_x;
        uint8_t new_y = ball_y + ball_dir_y;

        // Check if we hit the vertical walls
        if(new_x == 0 || new_x == 127){
            ball_dir_x = -ball_dir_x;
            new_x += ball_dir_x + ball_dir_x;

            if (new_x < 64){
                player_score++;
            }
            else{
                mcu_score++;
            }

            if (player_score == SCORE_LIMIT || mcu_score == SCORE_LIMIT){
                win = player_score > mcu_score;
                game_over = true;
            }
        }

        // Check if we hit the horizontal walls.
        if(new_y == 0 || new_y == 53){
            ball_dir_y = -ball_dir_y;
            new_y += ball_dir_y + ball_dir_y;
        }

        // Check if we hit the CPU paddle
        if(new_x == MCU_X && new_y >= mcu_y && new_y <= mcu_y + PADDLE_HEIGHT){
            ball_dir_x = -ball_dir_x;
            new_x += ball_dir_x + ball_dir_x;
        }

        // Check if we hit the player paddle
        if(new_x == PLAYER_X && new_y >= player_y && new_y <= player_y + PADDLE_HEIGHT){
            ball_dir_x = -ball_dir_x;
            new_x += ball_dir_x + ball_dir_x;
        }

        display.drawPixel(ball_x, ball_y, BLACK);
        display.drawPixel(new_x, new_y, WHITE);
        ball_x = new_x;
        ball_y = new_y;

        ball_update += BALL_RATE;

        update_needed = true;
    }

    if(time > paddle_update){
        paddle_update += PADDLE_RATE;

        // CPU paddle
        display.drawFastVLine(MCU_X, mcu_y, PADDLE_HEIGHT, BLACK);
        const uint8_t half_paddle = PADDLE_HEIGHT >> 1;

        if(mcu_y + half_paddle > ball_y){
            int8_t dir = ball_x > MCU_X ? -1 : 1;
            mcu_y += dir;
        }

        if(mcu_y + half_paddle < ball_y){
            int8_t dir = ball_x > MCU_X ? 1 : -1;
            mcu_y += dir;
        }

        if(mcu_y < 1){
            mcu_y = 1;
        }

        if(mcu_y + PADDLE_HEIGHT > 53){
            mcu_y = 53 - PADDLE_HEIGHT;
        }

        // Player paddle
        display.drawFastVLine(MCU_X, mcu_y, PADDLE_HEIGHT, WHITE);
        display.drawFastVLine(PLAYER_X, player_y, PADDLE_HEIGHT, BLACK);

        if(up_state){
            player_y -= 1;
        }

        if(down_state){
            player_y += 1;
        }

        up_state = down_state = false;

        if(player_y < 1){
            player_y = 1;
        }

        if(player_y + PADDLE_HEIGHT > 53){
            player_y = 53 - PADDLE_HEIGHT;
        }

        display.drawFastVLine(PLAYER_X, player_y, PADDLE_HEIGHT, WHITE);
        update_needed = true;
    }

    if(update_needed){
        if (game_over){
            const char* text = win ? "YOU WIN!!" : "YOU LOSE!";
            display.clearDisplay();
            display.setCursor(40, 28);
            display.print(text);
            display.display();

            delay(5000);

            display.clearDisplay();
            ball_x = 53;
            ball_y = 26;
            ball_dir_x = 1;
            ball_dir_y = 1;
            mcu_y = 16;
            player_y = 16;
            mcu_score = 0;
            player_score = 0;
            game_over = false;
            drawCourt();
        }

        display.setTextColor(WHITE, BLACK);
        display.setCursor(0, 56);
        display.print(mcu_score);
        display.setCursor(122, 56);
        display.print(player_score);
        display.display();
    }
}

void stopPong(){
  display.clearDisplay();
  ball_x = 53;
  ball_y = 26;
  ball_dir_x = 1;
  ball_dir_y = 1;
  mcu_y = 16;
  player_y = 16;
  mcu_score = 0;
  player_score = 0;
}

void setupPong(){
    ball_update = millis();
    paddle_update = ball_update;
}

// Flappy Bird Functions
void textAtCenter(int y, String txt) {
  display.setCursor(128 / 2 - txt.length() * 3, y);
  display.print(txt);
}

void mainFlappyBird(){ 
  if (game_state == 0) {    
    display.clearDisplay();
    if (digitalRead(BUTTON_UP_PIN) == LOW) {
      momentum = -4;
    }
    momentum += 1;
    bird_y += momentum;
    if (bird_y < 0 ) {
      bird_y = 0;
    }
    if (bird_y > 64 - 16) {
      bird_y = 64 - 16;
      momentum = -2;
    }
    if (momentum < 0) {
      if (random(2) == 0) {
        display.drawBitmap(bird_x, bird_y, wing_down_bmp, 16, 16, WHITE);
      }
      else {
        display.drawBitmap(bird_x, bird_y, wing_up_bmp, 16, 16, WHITE);
      }
    }
    else {
      display.drawBitmap(bird_x, bird_y, wing_up_bmp, 16, 16, WHITE);
    }
    for (int i = 0 ; i < 2; i++) {
      display.fillRect(wall_x[i], 0, wall_width, wall_y[i], WHITE);
      display.fillRect(wall_x[i], wall_y[i] + wall_gap, wall_width, 64 - wall_y[i] + wall_gap, WHITE);
      if (wall_x[i] < 0) {
        wall_y[i] = random(0, 64 - wall_gap);
        wall_x[i] = 128;
      }
      if (wall_x[i] == bird_x) {
        birdScore++;
        high_score = max(birdScore, high_score);
      }
      if (
        (bird_x + 16 > wall_x[i] && bird_x < wall_x[i] + wall_width) // level with wall
        &&
        (bird_y < wall_y[i] || bird_y + 16 > wall_y[i] + wall_gap) // not level with the gap
      ) {        
        display.display();
        delay(500);
        game_state = 1;
      }
      wall_x[i] -= 4;
    }
    textAtCenter(0, (String)birdScore);
    display.display();
    delay(50);
  }
  else {
    display.clearDisplay();
    textAtCenter(1, "Flappy Bird");    
    textAtCenter(64 / 2 - 8, "GAME OVER");
    textAtCenter(64 / 2, String(birdScore));    
    textAtCenter(64 - 16, "HIGH SCORE");
    textAtCenter(64  - 8, String(high_score));
    display.display();
    while (digitalRead(BUTTON_UP_PIN) == LOW);
    bird_y = 64 / 2;
    momentum = -4;
    wall_x[0] = 128 ;
    wall_y[0] = 64 / 2 - wall_gap / 2;
    wall_x[1] = 128 + 128 / 2;
    wall_y[1] = 64 / 2 - wall_gap / 1;
    birdScore = 0;
    while (digitalRead(BUTTON_UP_PIN) == HIGH);
    display.clearDisplay();
    game_state = 0;        
  }
}

void stopFlappyBird(){
  display.clearDisplay();
  game_state = 1;
}