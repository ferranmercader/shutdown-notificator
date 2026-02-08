# 🔌 ESP32 Shutdown Notificator & Healthcheck

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Platform: ESP32](https://img.shields.io/badge/Platform-ESP32-blue.svg)](https://www.espressif.com/en/products/socs/esp32)
[![Framework: Arduino](https://img.shields.io/badge/Framework-Arduino-00979D.svg)](https://www.arduino.cc/)

Una solución robusta y de ultra-bajo consumo para monitorizar cortes de energía y estado de dispositivos remotos usando **ESP32** e integración con **Healthchecks.io**.

---

## 🚀 Funcionamiento

Este proyecto utiliza un sistema de **Heartbeat (Latido)**. El ESP32 envía una señal periódica a Healthchecks.io:

1. **Monitorización Pasiva:** Healthchecks.io espera recibir un "ping" cada X tiempo.
2. **Detección de Fallo:** Si el ESP32 se apaga (por un corte de luz) y deja de enviar la señal, Healthchecks.io detecta la ausencia del latido.
3. **Notificación:** Al superar el tiempo de gracia, Healthchecks.io envía una alerta automática a tu **Telegram, Email, Slack**, etc.

## 🛠️ Estructura del Proyecto

El proyecto se compone de snippets listos para usar en el **Arduino IDE**:

```text
├── healthcheck_deep_sleep.ino   # Versión de máxima eficiencia energética y elegancia técnica
├── healthcheck_mvp.ino          # Versión básica (Siempre encendido)
├── LICENSE                      # Licencia MIT
└── README.md                    # Documentación
```

## 🔋 Características de Consumo

- **Ultra-Bajo Consumo:** 
  - Uso agresivo de **Deep Sleep** (consumo <10µA en espera).
  - **IP Estática** para conexiones WiFi ultra-rápidas (<2 segundos).
  - Gestión inteligente de Serial para ahorrar energía.
- **Doble Versión:** 
  - `MVP`: Fácil de probar y siempre online.
  - `Deep Sleep`: Una solución más elegante orientada a la eficiencia (reduce el consumo eléctrico a largo plazo).

## ⚙️ Configuración Rápida

Edita las variables al inicio de los archivos `.ino`:

```cpp
const char* ssid = "TU_WIFI";
const char* password = "TU_PASSWORD";
const char* hc_url = "https://hc-ping.com/TU-UUID";
```

> [!TIP]
> **Optimización de IP (Solo para Deep Sleep):** Configurar una IP estática en el código de la versión `deep_sleep` asegura una conexión casi instantánea tras despertar, ahorrando energía en cada ciclo y logrando una ejecución más limpia.

## 📦 Configuración en Healthchecks.io

1. Crea un nuevo Check en tu panel de [Healthchecks.io](https://healthchecks.io).
2. Configura el **Periodo** (ej. 1 minuto) y el **Tiempo de Gracia**.
3. Configura tus canales de notificación (ej. Telegram bot).
4. Copia la URL de Ping y pégala en tu código ESP32.

---

## 📄 Licencia

Este proyecto está bajo la Licencia **MIT**. Consulta el archivo `LICENSE` para más detalles.

---
*Desarrollado con ❤️ para la comunidad de ESP32 y Domótica.*
