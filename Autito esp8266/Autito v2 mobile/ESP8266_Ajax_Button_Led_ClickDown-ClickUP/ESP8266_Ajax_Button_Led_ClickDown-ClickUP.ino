/*
 * Sketch: ESP8266_LED_CONTROL_AJAX_02
 * Intended to be run on an ESP8266
 */
 
String header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
 
String html_1 = R"=====(
<!DOCTYPE html>
<html>
 <head>
 <meta name='viewport' content='width=device-width, initial-scale=1.0'/>
 <meta charset='utf-8'>
 <style>
  body {font-size:140%;} 
  #main {display: table; margin: auto;  padding: 0 10px 0 10px; } 
  h2 {text-align:center; } 
  .btn { padding:10px 10px 10px 10px; width:100%;  background-color: #e7e7e7; font-size: 120%;}
 </style>
 
<script>
       
            function CuandoPresiona(id_Button,btn){
                
                switch (id_Button) {
                    case 'btn_Avanzar':
                        comando = 'AVANZAR';
                        break;
                    case 'btn_Izquierda':
                        comando = 'GIRARALAIZQUIERDA';
                        break;
                    case 'btn_Derecha':
                        comando = 'GIRARALADERECHA';
                        break;
                    case 'btn_Retroceder':
                        comando = 'RETROCEDER';
                        break;
                }
                ajaxLoad(comando);

                btn.style.backgroundColor = '#4CAF50';
            };
            
            function CuandoDejaDePresionar(id_Button,btn){
                debugger;

                switch (id_Button) {
                    case 'btn_Avanzar':
                        comando = 'PARARAVANCERETROCESO';
                        break;
                    case 'btn_Izquierda':
                        comando = 'PARARGIROIZQUIERDADERECHA';
                        break;
                    case 'btn_Derecha':
                        comando = 'PARARGIROIZQUIERDADERECHA';
                        break;
                    case 'btn_Retroceder':
                        comando = 'PARARAVANCERETROCESO';
                        break;
                }

                ajaxLoad(comando);

                btn.style.backgroundColor = '#e7e7e7';
            };

   
var ajaxRequest = null;
if (window.XMLHttpRequest)  { ajaxRequest =new XMLHttpRequest(); }
else                        { ajaxRequest =new ActiveXObject("Microsoft.XMLHTTP"); }
 
 
function ajaxLoad(ajaxURL)
{
  if(!ajaxRequest){ alert("AJAX is not supported."); return; }
 
  ajaxRequest.open("GET",ajaxURL,true);
  ajaxRequest.onreadystatechange = function()
  {
    if(ajaxRequest.readyState == 4 && ajaxRequest.status==200)
    {
      var ajaxResult = ajaxRequest.responseText;
    }
  }
  ajaxRequest.send();
}
 
</script>
 
 <title>LED Control</title>
</head>
<body>
 <div id='main'>
  <h2>LED Control</h2>
)====="; 
 
String html_2 = R"=====(  
  <button id="btn_Avanzar" class="btn">Avanzar</button>
  <input type="button" id="btn_Izquierda"   value="Izquierda"   class="btn"   />
  <input type="button" id="btn_Derecha"     value="Derecha"     class="btn"   />
  <input type="button" id="btn_Retroceder"  value="Retroceder"  class="btn"   />
)=====";

String html_3 = R"=====(
  <script>
   debugger
        var id_btn_Avanzar = "btn_Avanzar";
        var id_btn_Izquierda = "btn_Izquierda";
        var id_btn_Derecha = "btn_Derecha";
        var id_btn_Retroceder = "btn_Retroceder";

        var elementAvanzar = document.querySelector('#'+id_btn_Avanzar);
        elementAvanzar.onpointerdown = (e) => { CuandoPresiona(id_btn_Avanzar,elementAvanzar); };
        elementAvanzar.onpointerup = (e) => { CuandoDejaDePresionar(id_btn_Avanzar,elementAvanzar); };
        
        var elementIzquierda = document.querySelector('#'+id_btn_Izquierda);
        elementIzquierda.onpointerdown = (e) => { CuandoPresiona(id_btn_Izquierda,elementIzquierda); };
        elementIzquierda.onpointerup = (e) => { CuandoDejaDePresionar(id_btn_Izquierda,elementIzquierda); };
        
        var elementDerecha = document.querySelector('#'+id_btn_Derecha);
        elementDerecha.onpointerdown = (e) => { CuandoPresiona(id_btn_Derecha,elementDerecha); };
        elementDerecha.onpointerup = (e) => { CuandoDejaDePresionar(id_btn_Derecha,elementDerecha); };
        
        var elementRetroceder = document.querySelector('#'+id_btn_Retroceder);
        elementRetroceder.onpointerdown = (e) => { CuandoPresiona(id_btn_Retroceder,elementRetroceder); };
        elementRetroceder.onpointerup = (e) => { CuandoDejaDePresionar(id_btn_Retroceder,elementRetroceder); };
  </script>
)=====";
 
String html_4 = R"=====(    
 </div>
</body>
</html>
)====="; 
 
#include <ESP8266WiFi.h>
 
// change these values to match your network
char ssid[] = "Telecentro-3090";       //  your network SSID (name)
char pass[] = "QKKMIFZPJ7CX";          //  your network password
 
WiFiServer server(80);
 
 
String request = "";
int LED_Pin = 02;

//Motor Trasero
int IN1 = 13 ;        // L298N in1 motors Right     GPIO13(D7)
int IN2 = 12 ;        // L298N in2 motors Right     GPIO12(D6)
//Motor Delantero
int IN3 = 14 ;        // L298N in3 motors Left      GPIO14(D5)
int IN4 = 0  ;       // L298N in4 motors Left      GPIO0 (D3)
 
void setup() 
{
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
  
    pinMode(LED_Pin, OUTPUT);     
 
    Serial.begin(115200);
    Serial.println();
    Serial.println("Serial started at 115200");
    Serial.println("ESP8266_LED_CONTROL_AJAX_02");
    Serial.println();
 
    // Connect to a WiFi network
    Serial.print(F("Connecting to "));  Serial.println(ssid);
    WiFi.begin(ssid, pass);
 
    while (WiFi.status() != WL_CONNECTED) 
    {
        Serial.print(".");
        delay(500);
    }
 
    Serial.println("");
    Serial.println(F("[CONNECTED]"));
    Serial.print("[IP ");              
    Serial.print(WiFi.localIP()); 
    Serial.println("]");
 
    // start a server
    server.begin();
    Serial.println("Server started");
 
} // void setup()
 
 
 
void loop() 
{
    // Check if a client has connected
    WiFiClient client = server.available();
    if (!client)  {  return;  }
 
    // Read the first line of the request
    request = client.readStringUntil('\r');
 
    Serial.print("request: "); Serial.println(request); 

    if      (request.indexOf("AVANZAR") > 0 )                   { IrHaciaAdelante();      Serial.println("avazar");}
    else if (request.indexOf("PARARAVANCERETROCESO") > 0 )      { PararAvanceRetroceso(); Serial.println("parar"); }
    else if (request.indexOf("GIRARALAIZQUIERDA") > 0 )         { GirarALaIzquierda();    Serial.println("izquierda");}
    else if (request.indexOf("GIRARALADERECHA") > 0 )           { GirarALaDerecha();      Serial.println("derecha");}
    else if (request.indexOf("RETROCEDER") > 0 )                { IrHaciaAtras();         Serial.println("atras");}
    else if (request.indexOf("PARARGIROIZQUIERDADERECHA") > 0 ) { PararRotacion();        Serial.println("parargiroizqdere"); }
    else{
      client.flush();
        client.print( header );
        client.print( html_1 );   
        client.print( html_2 ); 
        client.print( html_3 ); 
        client.print( html_4 ); 
        delay(5);
    }

    

 
  // The client will actually be disconnected when the function returns and 'client' object is detroyed
} // void loop()

//REGION Funciones del motor
          void IrHaciaAdelante(){
                //Cancelar la intruccion contraria para no quemar los componentes
                digitalWrite(IN1, LOW);
                digitalWrite(IN2, LOW);
                    
                //Tracciona las traseras hacia adelante
                digitalWrite(IN1, HIGH);
                digitalWrite(IN2, LOW);
             }
          void IrHaciaAtras(){
                //Cancelar la intruccion contraria para no quemar los componentes
                digitalWrite(IN1, LOW);
                digitalWrite(IN2, LOW);
                  
                //Tracciona las traseras hacia atras
                digitalWrite(IN1, LOW);
                digitalWrite(IN2, HIGH);
             }
          void PararAvanceRetroceso(){
              
                //Cancelar la intruccion para no quemar los componentes
                digitalWrite(IN1, LOW);
                digitalWrite(IN2, LOW);
             }
            
          void GirarALaDerecha(){
                //Cancelar la intruccion contraria para no quemar los componentes
                digitalWrite(IN3, LOW);
                digitalWrite(IN4, LOW);
                    
                //Rota las delanteras hacia la Derecha
                digitalWrite(IN3, LOW);
                digitalWrite(IN4, HIGH);
             }
          void GirarALaIzquierda(){
                //Cancelar la intruccion contraria para no quemar los componentes
                digitalWrite(IN3, LOW);
                digitalWrite(IN4, LOW);
                  
                 //Rota las delanteras hacia la Izquierda
                digitalWrite(IN3, HIGH);
                digitalWrite(IN4, LOW);
             }
          void PararRotacion(){
                //Cancelar la intruccion para no quemar los componentes
                digitalWrite(IN3, LOW);
                digitalWrite(IN4, LOW);
             }
//END REGION Funciones motor
