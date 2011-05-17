/* Programme Arduino pour tester le protocol de communication
PC <-> Carte moteur
Recoit et renvoie la trame correspondante

Olivier Wenger @ CVRA
26/04/2011
*/

int inByte = 0;
int Status = 0;
int cmd = 0;

void setup()
{
  Serial.begin(115200);
  establishContact();
}

void loop()
{
  if(Serial.available()>0){
    inByte = Serial.read();
  }
  switch(Status){
   case 0:
     if(inByte=='A'){
       Status = 1;
     }
     break;
  case 1:
    if(inByte == 'B'){
      Status = 2;
    }
    break;
  case 2:
    if(inByte == 'C'){
      Status = 3;
    }
    break;
  case 3:
    cmd = inByte;
    Status = 4;
    break;
  case 4:
    if(inByte == '\n'){
      Serial.print('ABC'+cmd+'\n');
      Status = 0;
    }
    break;   
  }
}

void establishContact() {
  while(Serial.available()<=0){
    Serial.println('ABC0');
  }
}
