void setup() {
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
}

int f1 = 0;
int f2 = 0;
int f3 = 0;

void loop() {
  analogWrite(3, func(f1));
  analogWrite(5, func(f2));
  analogWrite(6, func(f3));
  analogWrite(9, func(f1));
  analogWrite(10, func(f2));
  analogWrite(11, func(f3));
  
  f1 = (f1 + 1) % 512;
  f2 = (f2 + 3) % 512;
  f3 = (f3 + 5) % 512;

  delay(10);
}

int func(int x)
{
  if(x < 256)
  {
    return x;
  }
  else
  {
    return 511 - x;
  }
}
