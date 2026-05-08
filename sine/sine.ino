#include "sine_pred.h"
#include <tflm_esp32.h>
#include <eloquent_tinyml.h>

#define NUMBER_OF_INPUTS 1
#define NUMBER_OF_OUTPUTS 1
#define ARENA_SIZE 4000  //Byte reservados en RAM para el modelo


Eloquent::TF::Sequential<1, ARENA_SIZE> tf;


float value;

void setup() {

  Serial.begin(115200);


  Serial.println("__TENSORFLOW SINE PREDICTION__");


  tf.setNumInputs(NUMBER_OF_INPUTS);
  tf.setNumOutputs(NUMBER_OF_OUTPUTS);

  tf.resolver.AddFullyConnected();
  //tf.resolver.AddSoftmax(); //Útil para clasificación

  while (!tf.begin(sine_pred).isOk()) {

    Serial.println(tf.exception.toString());

  }
        
  Serial.println("Model loaded successfully");
}

void loop() {
  


  value += 0.1f;
  if (value > 2 * PI) value = 0.0f;
  Serial.println(value);
  float input[1] = {value};



  // Make predictions
  if (!tf.predict(input).isOk()){

      Serial.println(tf.exception.toString());
      return;

  }


    float value_sin = tf.output(0);
    
    float real_sin  = sin(value);
    float error     = abs(value_sin - real_sin);
   

    Serial.print("Valor X: ");
    Serial.println(value);

    Serial.print("Real Sine: ");
    Serial.println(real_sin);
   
   
    Serial.print("Predicted Sine: ");
    Serial.println(value_sin);
   

    // Benchmark
    Serial.print("Prediction time: ");
    Serial.print(tf.benchmark.microseconds());
    Serial.println("us");

    delay(3000);  
    
}