const int REDpin = 13;
const int GREENpin = 12;
const int BLUEpin = 11;
 
const int flexpin = A1;

const int BUTTONpin = 2;


const int array_size = 100;
int flexread[array_size];

void setup()  
{
  Serial.begin(115200);  
  pinMode(REDpin, OUTPUT);
  pinMode(GREENpin, OUTPUT);
  pinMode(BLUEpin, OUTPUT);
  
  pinMode(BUTTONpin, INPUT);

  attachInterrupt(digitalPinToInterrupt(BUTTONpin), BUTTONpressed, RISING);

  for (byte i=0; i< array_size; i++){
    flexread[i] = -1;
  }
}

volatile bool start = false;
volatile bool configuracao = false;

int maxrange = 0;
int minrange = 1024;




void loop()
{
  
  int buttonState;
  int flexposition;  
  int flexpos;
  
  if(!start){
    setColor(255, 255, 0);  //amarelo enquando não inicia a configuração
    delay(100);
  }

  if(start){
    
    flexposition = analogRead(flexpin); 
    //flexread.push_back(flexposition);

    if(!configuracao){

      Serial.print("sensor:  ");
      Serial.println(flexposition);
      
      setColor(0, 255, 255);    //turquesa enquando está calibrando o sensor
      
      if(flexposition < minrange)
        minrange = flexposition;
      if(flexposition> maxrange)
        maxrange = flexposition;

      delay(1000);
        
    }else{

      //quando terminar de calibrar o sensor
      
       flexpos = map(flexposition, minrange, maxrange, 0, 3); 
       //flexpos = constrain(flexpos, 0, 2); 
        
      if(flexpos==0){
        setColor(255,0,0);
      }
      if(flexpos==1){
        setColor(0,255,0);
      }
      if(flexpos==2){
        setColor(0,0,255);
      }
    
      Serial.print("sensor: "); 
      Serial.print(flexposition); 
      Serial.print(" flex pos: "); 
      Serial.println(flexpos);  
    
      delay(1000); 
      
    }
  }

}

void setColor(int r, int g, int b){
  analogWrite(REDpin, r);
  analogWrite(GREENpin, g);
  analogWrite(BLUEpin, b);
}

void BUTTONpressed(){

  if(!start){
      Serial.println(" BOTÃO PRESSIONADO "); 
      start = true;
      Serial.println(" INICIE A CONFIGURAÇÂO ");

      //Serial.print("vector.max_size(): "); Serial.println(flexread.max_size());
  }else {
    if(!configuracao){
      configuracao = true;
      
        Serial.println(" CONFIGURAÇÃO FINALIZADA ");

        Serial.print("vector: ");
        for(int i =0; i<100; i++){
          Serial.print(flexread[i]); 
          Serial.print(" ");
        }
        Serial.println("   THE END    ");
        
        Serial.print("MAX: "); Serial.print(maxrange); Serial.print("   MIN: "); Serial.println(minrange);
        delay(5000);
    }
  }
}
