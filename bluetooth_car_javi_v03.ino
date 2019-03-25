//www.elegoo.com
// https://informatica.javiteran.com
// https://www.youtube.com/javiteran
// @javiteran
// https://github.com/javiteran/Arduino

// Permite controlar el ELEGOO UNO Proyecto Kit de Coche Robot Inteligente V3.0
// Permite ir hacia adelante y atrás rápido. Girar sin parar y aumentar o disminuir la velocidad
#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11
#define LED 13

unsigned char carSpeed = 150;
bool state = LOW;
char getstr;
char AnteriorLetra ='w';
int retraso = 500;

void forward(){ 
  digitalWrite(ENA,HIGH);
  digitalWrite(ENB,HIGH);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  Serial.print("Adelante: ");
  Serial.println(carSpeed);
}

void back(){
  digitalWrite(ENA,HIGH);
  digitalWrite(ENB,HIGH);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  Serial.print("Atras: ");
  Serial.println(carSpeed);
}

void left(){
  analogWrite(ENA,carSpeed+50);
  analogWrite(ENB,carSpeed+50);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH); 
  Serial.print("Izquierda: ");
  Serial.println(carSpeed);
}

void right(){
  analogWrite(ENA,carSpeed+50);
  analogWrite(ENB,carSpeed+50);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  Serial.print("Derecha: ");
  Serial.println(carSpeed);
}

void AdelanteLento(){
  analogWrite(ENA,carSpeed);
  analogWrite(ENB,carSpeed);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
 // delay(retraso);
  Serial.print("Adelante Lento: ");
  Serial.println(carSpeed);
}

void AtrasLento(){
  analogWrite(ENA,carSpeed);
  analogWrite(ENB,carSpeed);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
//  delay(retraso);
  Serial.print("Atras Lento: ");
  Serial.println(carSpeed);
}

void stop(){
  digitalWrite(ENA,LOW);
  digitalWrite(ENB,LOW);
  Serial.println("Parar");
}

void stateChange(){
  state = !state;
  digitalWrite(LED, state);
  Serial.println("Luz");  
}

void setup() { 
  Serial.begin(9600);
  pinMode(LED, OUTPUT); 
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  stop();
}

void QueVelocidad (bool miVelocidad) {
  if (miVelocidad) {
    if (carSpeed < 300) { carSpeed = carSpeed + 15; }
  } else {
    if (carSpeed > 80)  {carSpeed = carSpeed - 15; }
  }
  Serial.println("Velocidad: " );  
  Serial.println(carSpeed);    
}

void loop() { 
  getstr = Serial.read();
  //Hacer que la velocidad suba o baje sin parar el robot
  if (getstr == '+') {
    QueVelocidad(true);
    getstr = AnteriorLetra;
    Serial.print ("Letra anterior: "); 
    Serial.println(getstr);
  }
  if (getstr == '-') {
    QueVelocidad(false);
    getstr = AnteriorLetra;
    Serial.print("Letra anterior: "); 
    Serial.println(getstr);
  }
  //Hacer que el giro sea suave y el coche siga hacia adelante.
  if (AnteriorLetra == 'l') { AdelanteLento(); delay(20);  left();  delay(20); }
  if (AnteriorLetra == 'r') { AdelanteLento(); delay(20);  right(); delay(20);}
  
  switch(getstr){
    case 'f': forward();        AnteriorLetra= 'f';       break;
    case 'b': back();           AnteriorLetra= 'b';       break;
    case 'l': left();           AnteriorLetra= 'l';       break;
    case 'r': right();          AnteriorLetra= 'r';       break;
    case 's': stop();           AnteriorLetra= 's';       break;
    case 'a': stateChange();    AnteriorLetra= 'a';       break;
    case 'w': AdelanteLento();  AnteriorLetra= 'w';       break;
    case 'z': AtrasLento();     AnteriorLetra= 'z';       break;
    default:  break;
  }
}
