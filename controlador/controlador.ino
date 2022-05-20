#include <Servo.h>

Servo DedaoServo;
Servo ApontadorServo;
Servo MeioServo;
Servo AnelarServo;
//Servo DedinhoServo;

const int REDpin = 13;
const int GREENpin = 12;
const int BLUEpin = 11;

const int BUTTONpin = 2;

const int DEDAO = 0;
const int APONTADOR = 1;
const int DEDOMEIO = 2;
const int ANELAR = 3;
const int MINDINHO = 4;

const int flexpin[] = {DEDAO, APONTADOR, DEDOMEIO, ANELAR, MINDINHO};

void setup()  
{
  Serial.begin(115200);  

  DedaoServo.attach(3);
  ApontadorServo.attach(5);
  MeioServo.attach(6);
  AnelarServo.attach(9);

  //led RGB foi adicionado ao projeto para melhor visualizar o andamento do codigo
  pinMode(REDpin, OUTPUT); 
  pinMode(GREENpin, OUTPUT);
  pinMode(BLUEpin, OUTPUT);
  
  pinMode(BUTTONpin, INPUT);

  attachInterrupt(digitalPinToInterrupt(BUTTONpin), BUTTONpressed, RISING);
}

volatile bool start_config = false;
volatile bool end_config = false;

bool processed_data_received = false;
bool ler_dados = false;
String val;

int maxrange[] = {0,0,0,0,0};
int minrange[] = {1024,1024,1024,1024,1024};
int processing_maxrange[] = {0,0,0,0,0};
int processing_minrange[] = {1024,1024,1024,1024,1024};
int data[] = {-1,-1,-1,-1,-1};
int posicao_sensor[] = {-1,-1,-1,-1,-1};

void loop()
{

  //enquando a configuracao nao for iniciada
  if(!start_config){
    //o led fica amarelo
    setColor(255, 255, 0);    //Amarelo
    delay(100);
  }

  //se a configuracao for iniciada
  if(start_config){

    //fazer leitura dos sensores
    for (int i=0; i<5; i++){
      data[i]= analogRead(flexpin[i]);
    }

    //se a confiuracao nao for finalizada
    if(!end_config){

       //o led fica branco
       setColor(255,255,255);  //Branco

      //o valor lido nos sensores e imprimido no monitor serial
       for (int i=0; i<5; i++){
        Serial.print(data[i]); 

        //para facilitar a litura dos dados como um arquivo .csv
        if(i!=4)
          Serial.print(",");
      }
      //para facilitar a litura dos dados como um arquivo .csv
      Serial.println("");

      //para achar a variação do valor máximo e minimo coletado pelos sensores:
      for(int i=0; i<5; i++){
        if(data[i] < minrange[i])
          minrange[i] = data[i];
        if(data[i] > maxrange[i])
          maxrange[i] = data[i];
      }

      delay(100);
    }
  }

  //se a configuracao for finalizada
  if(end_config){

    //o led fica vermelho
    setColor(255,0,0);     //Vermelho
    delay(100);

    //se os dados ainda nao froam processados pelo computador
    if(!processed_data_received){
      //verificar se o computador já terminou de processar os dados
      //se tiver algo disponível para leitura na comunicacao Serial
      if(Serial.available()){

          //ler e guardar em val
          val = Serial.readStringUntil('\n');
          //retirar possíveis caracteres indesejados da String
          val.trim();
          Serial.println("String recebida = " + val);

           processing_minrange[0] = val.substring(0,4).toInt();
           processing_minrange[1] = val.substring(5,9).toInt();
           processing_minrange[2] = val.substring(10,14).toInt();
           processing_minrange[3] = val.substring(15,19).toInt();
           processing_minrange[4] = val.substring(20,24).toInt();

           processing_maxrange[0] = val.substring(25,29).toInt();
           processing_maxrange[1] = val.substring(30,34).toInt();
           processing_maxrange[2] = val.substring(35,39).toInt();
           processing_maxrange[3] = val.substring(40,44).toInt();
           processing_maxrange[4] = val.substring(45,49).toInt();

            for(int i = 0; i<5; i++){
              Serial.print("[ "); Serial.print(i); 
              Serial.print(" ] -> min: "); Serial.print(processing_minrange[i]); 
              Serial.print(" max: "); Serial.println(processing_maxrange[i]);
            }
           processed_data_received = true;
      }
    }
    
    if(processed_data_received){
      for (int i=0; i<5; i++){
        //leitura da posicao atual do sensor
        data[i]= analogRead(flexpin[i]);
  
        //encontrar a regiao de valores que identifica se o sensor esta flexionado
        posicao_sensor[i] 
        = map(data[i], processing_minrange[i], processing_maxrange[i],-10,10);
  
        //Dessa maneira, 
        //Caso prosicao_sensor[i] = 0 -> sensor nao flexionado;
        //Caso prosicao_sensor[i] = 1 -> sensor flexionado;
      } 

            //para visualizar a caraga dos motores
             for(int i = 0; i<5 ; i++){
              Serial.print("[ "); Serial.print(i); Serial.print(" ] -> "); 
              Serial.print(posicao_sensor[i]); Serial.print("  ");
            }
              Serial.println("");
              
      //movimentar os motores
      if(posicao_sensor[0]<-1000){
        DedaoServo.write(180);
      }else{
        DedaoServo.write(0);
      }
      //movimentar os motores
      if(posicao_sensor[1]<-5){
        ApontadorServo.write(180);
      }else{
        ApontadorServo.write(0);
      }
      //movimentar os motores
      if(posicao_sensor[2]<-1000){
        MeioServo.write(180);
      }else{
        MeioServo.write(0);
      }
      //movimentar os motores
      if(posicao_sensor[4]<-5){
        AnelarServo.write(180);
      }else{
        AnelarServo.write(0);
      }
      
    }
  }
}



void setColor(int r, int g, int b){
  analogWrite(REDpin, r);
  analogWrite(GREENpin, g);
  analogWrite(BLUEpin, b);
}


//o botao e utilizado para iniciar e finalizar a configuração dos sensores
void BUTTONpressed(){

  if(!start_config){
      //Serial.println(" BOTAO PRESSIONADO "); 
      start_config = true;
      //Serial.println(" INICIE A CONFIGURACAO ");

      //delayMicroseconds(3000);
  }else {
    if(!end_config){
      end_config = true;

      //avisar ao processing que o arduino parou de mandar dados
      Serial.println("F");
      
      // delayMicroseconds(1000);
    }
  }
}
