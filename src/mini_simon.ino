//Sequences
int sequence[100];
int stage = 1;
int guessed = 0;
int level = 1;
int soundPin = 13;
bool started = false;
bool intro = false;
bool pressed = false;

void setup() {
  // Initialize pins
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  random_seq(100);
}

void loop() {
  pressed = false;
  if (digitalRead(6) == HIGH)
  {
    play_note(2, 250);
    check_button(6);
  }

  if (digitalRead(7) == HIGH)
  {
    play_note(3, 250);
    check_button(7);
  }

  if (digitalRead(8) == HIGH)
  {
    play_note(4, 250);
    check_button(8);
  }

  if (digitalRead(9) == HIGH)
  {
    play_note(5, 250);
    check_button(9);
  }
}

void check_button(int button) {
  if (started) {
    //check if guess is right

    if (sequence[guessed] == (button - 4)) {
      flash_single(button, 50);
      guessed++;
      if (guessed == stage) {
        if (stage >= level * 5) {
          level++;
          if (level < 10) {
            level_up();
          } else {
            triumph();
          }
        } else {
          delay(1000);
          guessed = 0;
          stage++;
          play_sequence(sequence, stage, 500);
        }

      }

    } else {
      reset_game();
    }

  } else {
    start();
  }
}

void reset_game() {
  stage = 1;
  level = 1;
  guessed = 0;
  random_seq(100);
  game_over();
  start();
}

void triumph() {
  win();
  win();
  reset_game();
}

void level_up() {
  win();
  stage = 1;
  guessed = 0;
  random_seq(100);
  play_sequence(sequence, stage, 500);
}


void start() {
  started = true;
  play_start();
  intro = true;
  delay(1000);
  play_sequence(sequence, stage, 500);
}

void random_seq(int len) {
  for (int i = 0; i < len; i++) {
    sequence[i] = random(2, 6);
  }
}

void play_sound(int pin, int button, int duration) {
  int pitch = 0;
  if (button == 6) {
    pitch = 220;
  }
  if (button == 7) {
    pitch = 329.63;
  }
  if (button == 8) {
    pitch = 440;
  }
  if (button == 9) {
    pitch = 554.37;
  }

  tone (pin, pitch, duration);


}

void play_note(int pin, int spd) {
  digitalWrite(pin, HIGH);
  play_sound(13, pin + 4, spd);
  delay(spd);
  digitalWrite(pin, LOW);
  delay(spd / 2);
}

void play_sequence(int seq[], int len, int spd) {
  for (int i = 0; i < len; i++) {
    play_note(seq[i], spd);
  }
}

void win() {
  play_note(3, 75);
  delay(75);
  play_note(3, 75);
  play_note(3, 75);
  play_note(3, 75);
  delay(75);
  play_note(3, 75);
  play_note(3, 75);
  play_note(3, 75);
  delay(75);
  play_note(3, 75);
  play_note(3, 75);
  play_note(3, 75);
  delay(75);
  play_note(3, 75);
  delay(75);
  play_note(4, 150);
  delay(150);
  play_note(5, 500);
  delay(1000);
}

void play_start() {
  play_note(3, 150);
  play_note(3, 150);
  play_note(3, 150);
  play_note(4, 150);
  delay(300);
  play_note(5, 150);
  delay(300);
  play_note(3, 150);
  play_note(3, 150);
  play_note(3, 150);
  play_note(4, 150);
  delay(300);
  play_note(5, 150);
  delay(1000);
}

void game_over() {
  play_note(3, 125);
  play_note(3, 125);
  play_note(4, 500);
  play_note(3, 125);
  play_note(4, 125);
  play_note(5, 500);
  play_note(3, 125);
  play_note(4, 125);
  play_note(5, 500);
  play_note(4, 250);
  play_note(5, 250);
  play_note(4, 125);
  play_note(3, 500);
  delay(1000);
}


void flash_all(int spd) {
  for (int i = 0; i < 10; i++) {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    delay(spd);
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    delay(spd);
  }
}

void flash_single(int pin, int spd) {
  for (int i = 0; i < 10; i++) {
    digitalWrite(pin, HIGH);
    delay(spd);
    digitalWrite(pin, LOW);
    delay(spd);
  }
}
