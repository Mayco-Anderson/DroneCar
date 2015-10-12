#include <SoftwareSerial.h>  
#include <Stepper.h>
#include <Servo.h>

Servo servoMotor;              
int angulo = 50;
int bluetoothTx = 0;                          // configura a porta 0 do arduino para enviar dados ao adaptador bluetooth
int bluetoothRx = 1;                          // configura a porta 1 do arduino para receber dados do adaptador bluetooth
int select;                                   // variavel de controle recebida do adaptador
int power;                                    // intensidade dos motores
float aux;

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

void setup()
{
  
    bluetooth.begin(9600);                    // Começa a comunicação Serial com adaptador bluetooth
    pinMode(11, OUTPUT);                      // configura o pino 11 como saida, esta porta é usada para o controle dos motores através de um PWM
    digitalWrite(11,LOW);                     // Inicia com o motor desligado!
    servoMotor.attach(3);                      // conecta o motor ao pino de controle
    servoMotor.write(angulo); 
  
 
}

void loop()
{
  if(bluetooth.available())                  // Se receber algum dado do adaptador , atualize os valores dos motores e do servomotor
  {
    select=(int)bluetooth.read();
    if (select==192)                          // codigo para parar o carrinho
    {
 
      power=0;
      frente();
      
    }
    else if(select>192)
    {
      power=select-162;                     // codigo para o carrinho dar ré (não foi implementado neste projeto inicialmente)
    }
       else if(select<100)                  // valores menores do que 100 representao comando para o servomotor
    {
    angulo=select;
    virar();                                // atualiza o angulo do servo motor
    }
    else{
      aux=(float)(3.5*select-416);         // calculo para ajustar a potencia do motor
      power=(int)aux;
      frente();                           // atualiza a potencia do motor
    }
  }
}


void frente()                             // subrotina para atualizar o a potencia dos motores
{  
     analogWrite (11,power);
}  
  
  void virar()
  {
   servoMotor.write(angulo);               //subrotina para atualizar o angulo do motor
  }
