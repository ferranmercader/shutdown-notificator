# 🔌 ESP32 Shutdown Notificator & Healthcheck

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Platform: ESP32](https://img.shields.io/badge/Platform-ESP32-blue.svg)](https://www.espressif.com/en/products/socs/esp32)
[![Framework: Arduino](https://img.shields.io/badge/Framework-Arduino-00979D.svg)](https://www.arduino.cc/)

Una solución robusta y de ultra-bajo consumo para monitorizar cortes de energía y estado de dispositivos remotos usando **ESP32** e integración con **Healthchecks.io**.

---

## 🚀 Características Principales

- **Notificación de Apagado (Shutdown):** Detecta instantáneamente el corte de energía y envía un webhook antes de que el condensador/batería se agote.
- **Heartbeat (Healthchecks.io):** Envía señales periódicas para asegurar que el dispositivo está online.
- **Ultra-Bajo Consumo:** 
  - Uso agresivo de **Deep Sleep** (consumo <10µA en espera).
  - **IP Estática** para conexiones WiFi ultra-rápidas (<2 segundos).
  - Gestión inteligente de Serial para ahorrar cada microamperio.
- **Doble Versión:** 
  - `MVP`: Simple y fácil de entender.
  - `Deep Sleep`: Optimizada para batería.

## 🛠️ Estructura del Proyecto

```text
├── src/main.cpp                 # Lógica principal (PlatformIO)
├── include/config.h             # Configuración centralizada
├── healthcheck_deep_sleep.ino   # Snippet optimizado (Arduino IDE)
├── healthcheck_mvp.ino          # Snippet básico (Arduino IDE)
└── platformio.ini               # Configuración de compilación
```

## 🔌 Conexión de Hardware (Power Sense)

Para que el ESP32 detecte el corte de luz, se recomienda conectar el pin de monitorización a la fuente de alimentación mediante un divisor de tensión:

1. Conecta la fuente de 5V al pin `POWER_SENSE_PIN` (por defecto GPIO 33).
2. Usa una resistencia de **10kΩ + 20kΩ** para bajar los 5V a **3.3V** (voltaje seguro para ESP32).
3. El programa detectará cuando este pin pase de `HIGH` a `LOW` y enviará la notificación de emergencia.

## ⚙️ Configuración Rápida

Edita `include/config.h` o las variables de configuración en los archivos `.ino`:

```cpp
#define WIFI_SSID "TU_WIFI"
#define WIFI_PASSWORD "TU_PASSWORD"
#define HEALTHCHECKS_PING_URL "https://hc-ping.com/TU-UUID"
```

> [!TIP]
> **Optimización de IP:** Configura la IP estática fuera del rango DHCP de tu router para evitar conflictos y asegurar una conexión instantánea.

## 📦 Uso con Healthchecks.io

Este proyecto está diseñado para funcionar perfectamente con [Healthchecks.io](https://healthchecks.io). 
1. Crea un nuevo Check en el panel.
2. Copia la URL de Ping.
3. Pégala en el código.
4. Si el ESP32 deja de enviar la señal (por corte de luz prolongado o fallo de hardware), recibirás una alerta por Email, Telegram, Slack, etc.

---

## 📄 Licencia

Este proyecto está bajo la Licencia **MIT**. Consulta el archivo `LICENSE` para más detalles.

---
*Desarrollado con ❤️ para la comunidad de ESP32 y Domótica.*
