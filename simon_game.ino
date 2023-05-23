int botoes[5] = {18, 16, 25, 14};
int leds[4] = {19, 17, 26, 21};

int reset = 2;

int estado = 0;
int level = 1;
int verifica = 0;
int sequencia[100];
int* ptr = &sequencia[0];


void setup() {
  Serial.begin(115200);
  for (byte i = 0; i < 4; i++) {
    pinMode(leds[i], OUTPUT);
    pinMode(botoes[i], INPUT_PULLUP);
  }

  pinMode(reset, INPUT_PULLUP);

  randomSeed(analogRead(0));
}

void loop() {
  if (digitalRead(reset) == HIGH) {
    estado = 0;
    level = 1;
    verifica = 0;
  }

  switch(estado) {
    case 0:
      init();
      gerarSequencia();
      estado++;
      break;

    case 1:
      mostrarSequencia();
      estado++;
      break;
    
    case 2:
      verificarSequencia();
      break;
  }
}

void init() {
  for (int j = 0; j<4; j++){
    for(int i = 0; i<4; i++) {
      digitalWrite(leds[i], HIGH);
      delay(100);
      digitalWrite(leds[i], LOW);
      delay(100);
    }
  }
  for (int j = 0; j<2; j++){
    for(int i = 0; i<4; i++) {
      digitalWrite(leds[i], HIGH);
    }
    delay(200);
    for(int i = 0; i<4; i++) {
      digitalWrite(leds[i], LOW);
    }
    delay(200);
  }
}

void gerarSequencia() {
  for (int i = 0; i < 100; i++) {
    sequencia[i] = random(0, 4);
  }

  ptr = &sequencia[0];
}

void mostrarSequencia() {
  for (int i = 0; i < level; i++) {
    digitalWrite(leds[sequencia[i]], HIGH);
    delay(500);
    digitalWrite(leds[sequencia[i]], LOW);
    delay(500);
  }
}

void verificarSequencia() {
  for(int i = 0; i<4; i++) {
    if (digitalRead(botoes[i]) == HIGH) {
      digitalWrite(leds[i], HIGH);

      if (leds[i] == leds[*ptr]) {
        delay(500);
        digitalWrite(leds[i], LOW);
        delay(500);
        ptr++;
        verifica++;

        if (verifica == level) {
          level++;
          estado = 1;
          verifica = 0;
          ptr = &sequencia[0];
        }

      } else {
        delay(500);
        digitalWrite(leds[i], LOW);
        estado = 0;
        level = 1;
        verifica = 0;
      }
    }
  }
}