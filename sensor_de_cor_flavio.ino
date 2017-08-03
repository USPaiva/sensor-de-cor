/*
#
# 03/08/2017 - v0.1.0
#
*/

// Pinos de conexao do sensor de cor TCS230 da direita
const byte r_s0 = 8;
const byte r_s1 = 9;
const byte r_s2 = 12;
const byte r_s3 = 11;
const byte r_out = 10;

// Pinos de conexao do sensor de cor TCS230 da esquerda
const byte l_s0 = 3;
const byte l_s1 = 7;
const byte l_s2 = 5;
const byte l_s3 = 4;
const byte l_out = 6;

// Valores adquiridos a cada loop
int l_red = 0;
int l_green = 0;
int l_blue = 0;
int r_red = 0;
int r_green = 0;
int r_blue = 0;

// Contagem
int count = 0;

void setup() {
  // Configurar pinos do sensor de cor TCS230 da direita
  pinMode(r_s0, OUTPUT);
  pinMode(r_s1, OUTPUT);
  pinMode(r_s2, OUTPUT);
  pinMode(r_s3, OUTPUT);
  pinMode(r_out, INPUT);

  // Configurar pinos do sensor de cor TCS230 da esquerda
  pinMode(l_s0, OUTPUT);
  pinMode(l_s1, OUTPUT);
  pinMode(l_s2, OUTPUT);
  pinMode(l_s3, OUTPUT);
  pinMode(l_out, INPUT);

  // Configurar a comunicaçao Serial
  Serial.begin(9600);
  Serial.println("uriel2469 v0.1.3");

  // (?!) ja estava aqui
  digitalWrite(l_s0, HIGH);
  digitalWrite(l_s1, LOW);
  digitalWrite(r_s0, HIGH);
  digitalWrite(r_s1, LOW);
}


void loop() {
  count++;

  getColorsFromLeftSensor();
  getColorsFromRightSensor();

  printColorsOfLeftSensor();
  printColorsOfRightSensor();

  delay(4e3);
}

void getColorsFromLeftSensor() {
  // (?!) Nao faço a minima ideia de como isso funciona
  digitalWrite(l_s2, LOW);
  digitalWrite(l_s3, LOW);
  l_red = pulseIn(l_out, digitalRead(l_out) == HIGH ? LOW : HIGH);
  digitalWrite(l_s3, HIGH);
  l_blue = pulseIn(l_out, digitalRead(l_out) == HIGH ? LOW : HIGH);
  digitalWrite(l_s2, HIGH);
  l_green = pulseIn(l_out, digitalRead(l_out) == HIGH ? LOW : HIGH);
}

void getColorsFromRightSensor() {
  // (?!) Nao faço a minima ideia de como isso funciona
  digitalWrite(r_s2, LOW);
  digitalWrite(r_s3, LOW);
  r_red = pulseIn(r_out, digitalRead(r_out) == HIGH ? LOW : HIGH);
  digitalWrite(r_s3, HIGH);
  r_blue = pulseIn(r_out, digitalRead(r_out) == HIGH ? LOW : HIGH);
  digitalWrite(r_s2, HIGH);
  r_green = pulseIn(r_out, digitalRead(r_out) == HIGH ? LOW : HIGH);
}

void printColorsOfLeftSensor() {
  Serial.println(String(count) + String("- SENSOR ESQUERDO"));
  Serial.println(String("RED:   ") + String(l_red));
  Serial.println(String("GREEN: ") + String(l_green));
  Serial.println(String("BLUE:  ") + String(l_blue));

  if (l_blue > 100 && l_green > 300 && l_red > 400) {
    Serial.println("preto");
  } else if (l_blue < 80 && l_red < 400 && l_green < 300) {
    Serial.println("branco");
  } else if (l_blue > 60) {
    Serial.println("Verde");
  }

  Serial.println("-----");
}

void printColorsOfRightSensor() {
  Serial.println(String(count) + String("- SENSOR DIREITO"));
  Serial.println(String("RED: ") + String(r_red));
  Serial.println(String("GREEN: ") + String(r_green));
  Serial.println(String("BLUE: ") + String(r_blue));

  if (r_blue > 100 && r_green > 300 && r_red > 400) {
    Serial.println("preto");
  } else if (r_blue < 80 && r_red < 400 && r_green < 300) {
    Serial.println("branco");
  } else if (r_blue > 400) {
    Serial.println("Verde");
  }

  Serial.println("-----");
}
