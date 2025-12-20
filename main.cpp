int red=10;
int yellow=11;
int green=12;

int pushButton=7;
int readPushbutton=0;

void setup()
{
  pinMode(red,OUTPUT);
  pinMode(yellow,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(pushButton,INPUT);
  
  digitalWrite(red,LOW);
  digitalWrite(yellow,LOW);
  digitalWrite(green,LOW);
  
  Serial.begin(9600);
}

void loop()
{
  int readPushbutton=digitalRead(pushButton);
  if(readPushbutton==0)
  {
    digitalWrite(green,HIGH);
    digitalWrite(yellow,LOW);
    digitalWrite(red,LOW);
  }
  else if(readPushbutton==1)
  {
    digitalWrite(green,LOW);
    digitalWrite(yellow,HIGH);
    digitalWrite(red,LOW);
    Serial.print("Pedistrain are waiting !");
    delay(5000);
    
    digitalWrite(green,LOW);
    digitalWrite(yellow,LOW);
    digitalWrite(red,HIGH);
    Serial.print("Pedistrain crossing !");
    delay(10000);
    
  }
}
