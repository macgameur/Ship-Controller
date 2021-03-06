//initialisation librairie pour le LCD
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#include <SoftwareSerial.h>
#include <SerialCommand.h>
SerialCommand sCmd;

//pin photorésistance rouge
#define redSensorPin A0
void pingHandler (const char *command);

//sa variable
int redSensorValue = 0;
int newRedSensorValue = 0;

void setup() {
  pinMode(redSensorPin, INPUT);
  Serial.begin(9600);
  //inscription du nombre de colomnes et de lignes du lcd
  lcd.begin(16, 2);
  //------> lcd démarage
  // clean up the screen before printing a new reply
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("   J workshop   ");
  //écrir la seconde ligne
  lcd.setCursor(0, 1);
  lcd.print("================");
  while (!Serial);
  //------> lcd connection série établie avec l'ordinateur
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("   J workshop   ");
  lcd.setCursor(0, 1);
  lcd.print("connect serie /");
  //------> lcd connection avec application établie
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("   J workshop   ");
  lcd.setCursor(0, 1);
  lcd.print("connect app ~");
  sCmd.addCommand("PING", pingHandler);
  lcd.clear(); //------> vide le lcd pour se préparer  au reste
  sCmd.addCommand("/", commandHandler);

  ////////////////test
  //envoie données capteur photo rouge
  redSensorValue = analogRead(redSensorPin);
  Serial.println(redSensorValue);
  lcd.setCursor(0, 0);
  lcd.print("Rouge : ");
  lcd.print(redSensorValue);
}

void loop () {
  if (Serial.available() > 0)
    sCmd.readSerial();
  newRedSensorValue = analogRead(redSensorPin);
  if (redSensorValue != newRedSensorValue) {
    redSensorValue = newRedSensorValue;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Rouge : ");
    lcd.print(redSensorValue);
  }
}

void pingHandler (const char *command) {
  Serial.println("PONG");
  //------> lcd connection avec application établie
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("   J workshop   ");
  lcd.setCursor(0, 1);
  lcd.print("connect app /");
}

void echoHandler () {
  char *arg;
  arg = sCmd.next();
  if (arg != NULL)
    Serial.println(arg);
  else
    Serial.println("nothing to echo");
}
void commandHandler () {
  char *arg;
  arg = sCmd.next();
  if (arg != NULL)
    commande(arg);
  else
    Serial.println("ERREUR : argument manquant.");
}

void commande (char arg) {
  if (arg = "rouge") {
    redSensorValue = analogRead(redSensorPin);
    Serial.println(redSensorValue);
  }
  else {
    Serial.println("ERREUR : mauvais argument.");
  }
}