const int HALLPin = 5;
const int LEDPin = 13;
volatile unsigned int contador = 0;
 
void contarRevoluciones()
{
  contador++;// almacena las vueltas totales de una rueda
}

void setup() {
  Serial.begin(9600); // Iniciar la comunicación serial a 9600 baudios
  pinMode(HALLPin, INPUT); // Setteamos el pin digital 5 del Arduino como entrada del sensor magnético
  pinMode(LEDPin, OUTPUT); // Encendemos el pin del Arduino para señal de que se detecto una vuelta
  //attachInterrupt(digitalPinToInterrupt(HALLPin), contarRevoluciones, FALLING); // mandamos a llamar a la funcion contarRevoluciones; LOW es cuando detecta una vuelta y se activa el sensor
}

void loop() {
  // Calculos de distancia recorrida

    // Mensaje de "campo magnético"
  if(digitalRead(HALLPin) == HIGH) { // Salida HIGH, significa Ningún campo magnético detectado
    Serial.print(" ✗  Ningún campo magnético detectado - ");
    digitalWrite(LEDPin, LOW);  // Apagamos el led del Arduino
  } else if(digitalRead(HALLPin) == LOW) { // Salida LOW, significa Campo magnético detectado
    Serial.print(" ✓  Campo magnético detectado - ");   
    digitalWrite(LEDPin, HIGH); // Encendemos el led del Arduino
    contarRevoluciones(); // Llamamos a la función contarRevoluciones()
  }

  Serial.print(" variable contador: " + String(contador));

  float distancia = contador * 0.25; // 1 revolución (distancia) = int vueltas * 22.5 cm (circuferencia en metros de la rueda)
  Serial.print(" - Distancia recorrida: ");
  Serial.print(distancia);
  Serial.println(" metros");

  delay(50); // Pausa de 50 microsegundo para evitar mensajes demasiado rápidos en la terminal
}
