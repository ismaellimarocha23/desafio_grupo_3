//Desafio grupo 3 
#include <HTTPClient.h>
#include <WiFi.h>

const char* wifi_ssid = "Nome do Wifi";
const char* wifi_password = "senha do wifi";

//Certificado da API que inclui a chave pública para criptografia usada no protocolo https
const char* ca_cert = \
"-----BEGIN CERTIFICATE-----\n" \
"MIIDujCCAqKgAwIBAgILBAAAAAABD4Ym5g0wDQYJKoZIhvcNAQEFBQAwTDEgMB4G\n" \
"A1UECxMXR2xvYmFsU2lnbiBSb290IENBIC0gUjIxEzARBgNVBAoTCkdsb2JhbFNp\n" \
"Z24xEzARBgNVBAMTCkdsb2JhbFNpZ24wHhcNMDYxMjE1MDgwMDAwWhcNMjExMjE1\n" \
"MDgwMDAwWjBMMSAwHgYDVQQLExdHbG9iYWxTaWduIFJvb3QgQ0EgLSBSMjETMBEG\n" \
"A1UEChMKR2xvYmFsU2lnbjETMBEGA1UEAxMKR2xvYmFsU2lnbjCCASIwDQYJKoZI\n" \
"hvcNAQEBBQADggEPADCCAQoCggEBAKbPJA6+Lm8omUVCxKs+IVSbC9N/hHD6ErPL\n" \
"v4dfxn+G07IwXNb9rfF73OX4YJYJkhD10FPe+3t+c4isUoh7SqbKSaZeqKeMWhG8\n" \
"eoLrvozps6yWJQeXSpkqBy+0Hne/ig+1AnwblrjFuTosvNYSuetZfeLQBoZfXklq\n" \
"tTleiDTsvHgMCJiEbKjNS7SgfQx5TfC4LcshytVsW33hoCmEofnTlEnLJGKRILzd\n" \
"C9XZzPnqJworc5HGnRusyMvo4KD0L5CLTfuwNhv2GXqF4G3yYROIXJ/gkwpRl4pa\n" \
"zq+r1feqCapgvdzZX99yqWATXgAByUr6P6TqBwMhAo6CygPCm48CAwEAAaOBnDCB\n" \
"mTAOBgNVHQ8BAf8EBAMCAQYwDwYDVR0TAQH/BAUwAwEB/zAdBgNVHQ4EFgQUm+IH\n" \
"V2ccHsBqBt5ZtJot39wZhi4wNgYDVR0fBC8wLTAroCmgJ4YlaHR0cDovL2NybC5n\n" \
"bG9iYWxzaWduLm5ldC9yb290LXIyLmNybDAfBgNVHSMEGDAWgBSb4gdXZxwewGoG\n" \
"3lm0mi3f3BmGLjANBgkqhkiG9w0BAQUFAAOCAQEAmYFThxxol4aR7OBKuEQLq4Gs\n" \
"J0/WwbgcQ3izDJr86iw8bmEbTUsp9Z8FHSbBuOmDAGJFtqkIk7mpM0sYmsL4h4hO\n" \
"291xNBrBVNpGP+DTKqttVCL1OmLNIG+6KYnX3ZHu01yiPqFbQfXf5WRDLenVOavS\n" \
"ot+3i9DAgBkcRcAtjOj4LaR0VknFBbVPFd5uRHg5h6h+u/N5GJG79G+dwfCMNYxd\n" \
"AfvDbbnvRG15RjF+Cv6pgsH/76tuIMRQyV+dTZsXjAzlAcmgQWpzU/qlULRuJQ/7\n" \
"TBj0/VLZjmmx6BEP3ojY+x1J96relc8geMJgEtslQIxq/H5COEBkEveegeGTLg==\n" \
"-----END CERTIFICATE-----\n";


void connect_wifi(){
  WiFi.begin(wifi_ssid, wifi_password);//inicia uma tentativa de conectar ao wifi

  int begin_conection_time = millis();//marca o tempo de início da tentativa

  //espera até o wifi conectar ou passar 1 minuto tentando
  while(WiFi.status() != WL_CONNECTED && millis() - begin_conection_time < 60000){    
    delay(1000);
    Serial.println("Conectando ao wifi....");
  }

  if(WiFi.status() == WL_CONNECTED ){
    Serial.println("Conectado a rede wifi");
  }
}

void setup() {
  
  Serial.begin(115200);
  delay(1000);  
  
  connect_wifi();
}

void loop() {
  
  if ((WiFi.status() == WL_CONNECTED)) { 
      
    HTTPClient http;// define o objeto com métodos para fazer uma requisição http

    http.begin("https://URL", ca_cert);//especifica a URL da API e o certificado

    String code = "6bdb104d07ed03ee335b1a85798ec144c9ccdd4f6c556d63ccfcdd095cacac0a";
    String payload = "palavra";
    String http_body_json = "{\"code\":\""+code+"\","+"\"payload\":\""+payload+"\"}";
  

    //Verifica o código de retorno da requisição
    int httpResponseCode = http.POST(http_body_json);   //Realiza a requisição http com método POST
    
    if(httpResponseCode>0){
    
      String response = http.getString();                       //Get the response to the request
    
      Serial.println(httpResponseCode);   //Print return code
      Serial.println(response);           //Print request answer
    
    }else{
    
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    
    }
    
    http.end();  //Termina a "conexão"

  }else{
  Serial.println("Wifi desconectado!");
  }
}