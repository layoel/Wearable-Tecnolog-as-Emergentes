/**
  * @file werable.ino
  * @brief Fichero del wearable que mide el ritmo cardiaco con el sensor AD8232 y lilypad
  *        y dibuja en una matriz de leds de 10x10 en la camiseta, un corazón latiendo 
  *        mientras mide y cuando tiene la medida enciende los leds con los números
  *        que representan las pulsaciones medidas.
  *        
  * @autor Elvira Castillo Fernández
  */
#define NUM_PINS 11

/* 
 * @brief Estructura que contiene el par PIN A HIGH y pin a LOW de un led determinado
 * 
 * @pinhigh es el pin con valor High en un led
 * @pinlow es el pin con valor Low en un led
 */
struct parpin{
    byte pinhigh;
    byte pinlow;
    /**
     * @brief Constructor por defecto
     * 
     */
    parpin(){
        pinhigh; 
        pinlow;
    }
    /**
     * @brief Constructor con parámetros
     * @param p1 pin del led a high
     * "param p2 pin del led a low
     */
    parpin(byte p1, byte p2){
        pinhigh = p1; 
        pinlow = p2;
    }
    /**
     * @brief acceder al primer campo del pair
     * 
     * ret pinhigh es el pin que esta a high en este momento
     * 
     */
    byte first() {
      return pinhigh; 
    }
    /**
     * @brief acceder al segundo campo del pair
     * 
     * ret pinlow es el pin que esta a low en este momento
     * 
     */
    byte second() {
      return pinlow; 
    }
    /**
     * @brief Asigna un par de pines high-low a otro par high-low
     * @param original pines a los que vamos a asignar el par de pines actual
     * @return devuelve una referencia al objeto asignado
     */ 
    parpin& operator= (const parpin& original) {
      if(this!=&original){
        this->pinhigh = original.pinhigh;
        this->pinlow = original.pinlow;
      }
      return *this;
    }
  };
  
/* 
 * @brief Estructura que contiene el valor de los pines necesario para encender un led. representa un pair <estado, pin_a_high>
 * 
 * @estadoPines es el estado (input, output) de los pines de arduino para encender un led de la matriz
 * @pinhigh si vale 0 significa que el primer pin que encontramos de forma descendente de 11 a 0 
 *          en estado OUTPUT es el pin que está a high para que ese led se encienda. Si por el contrario
 *          vale 1 significa que el segundo pin que encontramos de forma descendente de 11 a 0 
 *          en estado OUTPUT es el pin que está a high para que ese led se encienda.
 */ 
struct L{
      word estadoPines;
      bool pinHigh; //1 es el primer pin a 1 es high, 0 el segundo pin a1 es high
    /**
     * @brief Constructor por defecto
     * 
     */
    L(){
        estadoPines; 
        pinHigh;
    }
    /**
     * @brief Constructor con parámetros
     * @param e es el estado de los pines (input-output)
     * @param p indica si el primer pin es high o low si vale 0 o 1
     */
    L(word e, bool p){
        estadoPines = e; 
        pinHigh = p;
    }
    /**
     * @brief acceder al primer campo del pair
     * 
     * ret estadoPines el estado de los pines (input-output)
     * 
     */
    word first() {
      return estadoPines; 
    }
    /**
     * @brief acceder al segundo campo del pair
     * 
     * ret pinHigh indica si el primer pin es high o low si vale 0 o 1
     * 
     */
    bool second() {
      return pinHigh; 
    }
    /**
     * @brief Asigna un estado de un led a otro led
     * @param original estado de los pines de un led a los que vamos a asignar el estado de los pines del led actual
     * @return devuelve una referencia al objeto asignado
     */ 
    L& operator= (const L& original) {
      if(this!=&original){
        this->estadoPines = original.estadoPines;
        this->pinHigh = original.pinHigh;
      }
      return *this;
    }
};




void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  //estado por defecto de los pines a Input, LEDS desconectados
  for (int i=1; i<12;i++)
    pinMode(i, INPUT);


}

void loop() {
  //inicializo los led con su estado y que pin va a high o low 
  L    led0(0x0600, 1) , led1(0x0600, 0) , led2(0x0300, 1) ,  led3(0x0300, 0) , led4(0x0180  ,1), led5(0x0180 ,0) , led6(0x00C0 ,1) , led7(0x00C0  ,0), led8(0x0060  ,1), led9(0x0060  ,0), 
       led10(0x0030 ,1), led11(0x0030 ,0), led12(0x0018 ,1),  led13(0x0018 ,0), led14(0x000C ,1), led15(0x000C ,0), led16(0x0006 ,1), led17(0x0006 ,0), led18(0x0003 ,1), led19(0x0003 ,0),
       led20(0x0500 ,1), led21(0x0500 ,0), led22(0x0280 ,1),  led23(0x0280 ,0), led24(0x0140 ,1), led25(0x0140 ,0), led26(0x00A0 ,1), led27(0x00A0 ,0), led28(0x0050 ,1), led29(0x0050 ,0), 
       led30(0x0028 ,1), led31(0x0028 ,0), led32(0x0014 ,1),  led33(0x0014 ,0), led34(0x000A ,1), led35(0x000A ,0), led36(0x0005 ,1), led37(0x0005 ,0), led38(0x0480 ,1), led39(0x0480 ,0),
       led40(0x0240 ,1), led41(0x0240 ,0), led42(0x0120 ,1),  led43(0x0120 ,0), led44(0x0090 ,1), led45(0x0090 ,0), led46(0x0048 ,1), led47(0x0048 ,0), led48(0x0024 ,1), led49(0x0024 ,0), 
       led50(0x0012 ,1), led51(0x0012 ,0), led52(0x0009 ,1),  led53(0x0009 ,0), led54(0x0440 ,1), led55(0x0440 ,0), led56(0x0220 ,1), led57(0x0220 ,0), led58(0x0110 ,1), led59(0x0110 ,0), 
       led60(0x0088 ,1), led61(0x0088 ,0), led62(0x0044 ,1),  led63(0x0044 ,0), led64(0x0022 ,1), led65(0x0022 ,0), led66(0x0011 ,1), led67(0x0011 ,0), led68(0x0420 ,1), led69(0x0420 ,0), 
       led70(0x0210 ,1), led71(0x0210 ,0), led72(0x0108 ,1),  led73(0x0108 ,0), led74(0x0084 ,1), led75(0x0084 ,0), led76(0x0042 ,1), led77(0x0042 ,0), led78(0x0021 ,1), led79(0x0021 ,0), 
       led80(0x0410 ,1), led81(0x0410 ,0), led82(0x0208 ,1),  led83(0x0208 ,0), led84(0x0104 ,1), led85(0x0104 ,0), led86(0x0082 ,1), led87(0x0082 ,0), led88(0x0041 ,1), led89(0x0041 ,0), 
       led90(0x0408 ,1), led91(0x0408 ,0), led92(0x0204 ,1),  led93(0x0204 ,0), led94(0x0102 ,1), led95(0x0102 ,0), led96(0x0081 ,1), led97(0x0081 ,0), led98(0x0404 ,1), led99(0x0404 ,0);

  L Led[100]={ led0,  led1,  led2,   led3,  led4,  led5,  led6,  led7 , led8,  led9,
               led10, led11, led12,  led13, led14, led15, led16, led17, led18, led19,
               led20, led21, led22,  led23, led24, led25, led26, led27, led28, led29,
               led30, led31, led32,  led33, led34, led35, led36, led37, led38, led39, 
               led40, led41, led42,  led43, led44, led45, led46, led47, led48, led49, 
               led50, led51, led52,  led53, led54, led55, led56, led57, led58, led59, 
               led60, led61, led62,  led63, led64, led65, led66, led67, led68, led69, 
               led70, led71, led72,  led73, led74, led75, led76, led77, led78, led79, 
               led80, led81, led82,  led83, led84, led85, led86, led87, led88, led89, 
               led90, led91, led92,  led93, led94, led95, led96, led97, led98, led99};
   while(true){
      L L0;
      L0 = getLed(0, Led);
      Serial.println(L0.first());
      Serial.println(L0.second());
      // put your main code here, to run repeatedly:
  }
}//fin LOOP


//________________________________  FUNCIONES   ___________________________________________________//

// esta función guarda el pin a high y el pin a low en la estructura parpin
    /**
     * @brief guarda el pin a high y el pin a low en la estructura parpin para poder encender un led
     * 
     * @param nled es el estado del led del que queremos saber que pines tiene a high y a low
     * 
     * @ret miled pareja de pines high-low
     * 
     */
parpin getHiLwpins(L nled){
  word led_status_pins = nled.first();
  bool led_pin_h = nled.second();
  parpin miled;
  byte pos = 0;
  byte count = 0;
  
    while (pos < NUM_PINS && count<2){ 
       if ( (led_status_pins >> pos ) & 1) {
           //en pos actual hay un uno
           ++count;
           
           if(count==1)
             if (led_pin_h == 0)
                miled.pinhigh = pos;
             else
                miled.pinlow = pos;
           
           if(count==2)
            if (led_pin_h == 0)
                miled.pinlow = pos;
            else
                miled.pinhigh = pos;
          }
         ++pos;
    }
  return miled;
}
//___________________________________________________________________________________//

/**
     * @brief para obtener los estados de los pines de un led
     * 
     * @param n es el número del led que queremos saber los pines activos
     * @param Led son todos los leds de la matriz
     * 
     * @ret Led[n] devuelve el estado del led que queríamos.
     * 
     */

L getLed(int n, L *Led){
  return Led[n];
  }
//___________________________________________________________________________________//


/**
  * @brief Dibuja el corazon grande en la matriz con leds
  * 
  * @param Led un vector con los leds que debe encender
  * @param nled cuantos led debe encender
  * 
  */
void G_corazon(L *Led, int nled){
  
  }
//___________________________________________________________________________________//
/**
 * @brief Dibuja el corazon pequeño en la matriz con leds
 * 
 * @param Led un vector con los leds que debe encender
 * @param nled cuantos led debe encender
 * 
 */
void P_corazon(L *Led, int nled){
  
  }
//___________________________________________________________________________________//
void Led_Total_pulsaciones(){}

  
