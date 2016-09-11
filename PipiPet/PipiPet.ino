#include "Arduino.h"
//The setup function is called once at startup of the sketch
void setup()
{
  //Setando a leitura da porta analogica A0
  //Jah liguei o fio do sensor na porta A0 e o GND e o VCC
  pinMode(A0, INPUT);

  //Setando para usar a porta serial no rate 9600 para ler println
  Serial.begin(9600);
}

// The loop function is called in an endless loop
void loop()
{
  //imprimindo medida do sensor de umidade
  Serial.println(analogRead(A0));
  delay(2000);
}
