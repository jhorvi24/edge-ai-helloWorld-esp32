# 🤖 Edge AI en ESP32 — Predicción de la Función Seno

![TensorFlow](https://img.shields.io/badge/TensorFlow-FF6F00?style=for-the-badge&logo=tensorflow&logoColor=white)
![Arduino](https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![ESP32](https://img.shields.io/badge/ESP32-E7352C?style=for-the-badge&logo=espressif&logoColor=white)
![Python](https://img.shields.io/badge/Python-3776AB?style=for-the-badge&logo=python&logoColor=white)

El "Hola Mundo" de Edge AI: un modelo de red neuronal entrenado con TensorFlow en Google Colab y desplegado en un microcontrolador ESP32 usando TensorFlow Lite.

---

## 📌 ¿Qué hace este proyecto?

El modelo recibe un valor `x` (entre 0 y 2π) y predice `sin(x)`. Cada 3 segundos, el ESP32 imprime por el puerto serial el valor real del seno, el valor predicho por el modelo y el tiempo de inferencia en microsegundos.

---

## 📁 Estructura del repositorio

```
├── esp32_edge.ipynb     # 📓 Notebook de Google Colab: entrenamiento y conversión del modelo
└── sine/
    ├── sine.ino         # ⚙️  Sketch de Arduino para el ESP32
    └── sine_pred.h      # 🧠 Modelo TFLite convertido a array de bytes (C header)
```

---

## 🔄 Flujo del proyecto

```
🏋️ Entrenamiento (Colab)  →  🔧 Conversión a TFLite  →  📦 Exportar como .h  →  🚀 Desplegar en ESP32
```

### 1. 🏋️ Entrenamiento del modelo (`esp32_edge.ipynb`)

- Se generan 1000 muestras aleatorias de `x` en el rango `[0, 2π]`
- Se calcula `y = sin(x)` para cada muestra
- Se entrena una red neuronal densa (fully connected) con Keras
- El modelo se convierte a TensorFlow Lite y se exporta como un array de bytes en C (`sine_pred.h`)

### 2. 🚀 Despliegue en el ESP32 (`sine/sine.ino`)

- Se usa la librería [eloquent_tinyml](https://github.com/eloquentarduino/EloquentTinyML) junto con `tflm_esp32`
- El modelo se carga en memoria (arena de 4000 bytes)
- En cada iteración del `loop()`, se incrementa `x` en 0.1 y se realiza una predicción
- Se imprime por Serial: el valor de `x`, el seno real, el seno predicho y el tiempo de inferencia

---

## 🛠️ Requisitos

### 🔩 Hardware
- ESP32 (cualquier variante con suficiente RAM)

### 💻 Software
- [Arduino IDE](https://www.arduino.cc/en/software) con soporte para ESP32
- Librería `tflm_esp32`
- Librería `eloquent_tinyml`
- Python 3 + TensorFlow (para ejecutar el notebook en Colab)

---

## 🚀 Cómo usar

### 📓 Entrenar el modelo
1. Abre `esp32_edge.ipynb` en [Google Colab](https://colab.research.google.com/)
2. Ejecuta todas las celdas
3. Descarga el archivo `sine_pred.h` generado y reemplaza el existente en `sine/`

### ⚡ Cargar en el ESP32
1. Abre `sine/sine.ino` en el Arduino IDE
2. Asegúrate de que `sine_pred.h` está en la misma carpeta
3. Instala las librerías `tflm_esp32` y `eloquent_tinyml` desde el gestor de librerías
4. Selecciona tu placa ESP32 y el puerto correcto
5. Sube el sketch y abre el Monitor Serial a **115200 baudios**

### 📟 Salida esperada en el Monitor Serial

```
__TENSORFLOW SINE PREDICTION__
Model loaded successfully
0.10
Valor X: 0.10
Real Sine: 0.10
Predicted Sine: 0.09
Prediction time: 312us
```

---

## 📚 Referencias

- 📄 [TensorFlow Lite for Microcontrollers](https://www.tensorflow.org/lite/microcontrollers)
- 📄 [EloquentTinyML](https://github.com/eloquentarduino/EloquentTinyML)
- 📄 [Hello World TFLite example (Google)](https://github.com/tensorflow/tflite-micro/tree/main/tensorflow/lite/micro/examples/hello_world)
