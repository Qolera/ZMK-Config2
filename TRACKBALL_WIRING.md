# Guía de Cableado: Trackball Pimoroni + Sofle + nice!nano v2

## 🎯 Resumen

Esta guía te ayudará a conectar el **Pimoroni Trackball Breakout** a tu teclado **Sofle** con **nice!nano v2** para ZMK firmware.

---

## 📋 Componentes Necesarios

### Hardware Base:
- ✅ Teclado Sofle con nice!nano v2
- ✅ Pimoroni Trackball Breakout (PIM447)
- ✅ 4 cables jumper hembra-hembra
- ✅ Conectores Dupont (opcional para conexiones removibles)

### Hardware Opcional:
- 🔧 Resistencias pull-up 4.7kΩ (2 unidades) - probablemente no necesarias
- 🔧 Mount 3D para trackball en Sofle
- 🔧 Tornillos M2 para montaje

---

## 🔌 Diagrama de Conexiones

### Pimoroni Trackball → nice!nano v2

| **Trackball Pin** | **Función** | **nice!nano Pin** | **GPIO** | **Notas** |
|-------------------|-------------|-------------------|----------|-----------|
| **VCC**           | Alimentación 3.3V | **VCC (3.3V)**   | -        | Poder principal |
| **GND**           | Tierra      | **GND**           | -        | Conexión a tierra |
| **SDA**           | I2C Data    | **SDA**           | **P0.17** | Ya configurado ✅ |
| **SCL**           | I2C Clock   | **SCL**           | **P0.20** | Ya configurado ✅ |
| **INT**           | Interrupción| **No conectar**   | -        | Opcional |

---

## 🎛️ Configuración I2C Actual

### ✅ Estado Actual (Ya Configurado):
```yaml
I2C Bus: I2C0
Dirección Trackball: 0x0A
Velocidad: I2C_BITRATE_FAST (400kHz)
Pull-ups: Configurados automáticamente por ZMK
```

### 🔍 Dispositivos en el Bus I2C:
- **Trackball Pimoroni** → Dirección: `0x0A`
- **OLED Display** → Dirección: `0x3C` o `0x3D` (si está presente)

---

## ⚡ Verificación de Pines

### ✅ Pines Disponibles y Sin Conflictos:

| **Periférico** | **Pin Usado** | **Función** | **Estado** |
|----------------|---------------|-------------|------------|
| RGB Underglow  | P0.06         | SPI MOSI    | ✅ No conflicto |
| I2C (Trackball)| P0.17, P0.20  | SDA, SCL    | ✅ Ya configurado |
| Encoders       | Otros pins    | GPIO        | ✅ No conflicto |

---

## 🔧 Procedimiento de Cableado

### Paso 1: Preparación
1. **Apaga** el teclado y desconecta la batería
2. Identifica los pines en el nice!nano v2
3. Prepara los cables jumper

### Paso 2: Conexiones Principales
```
Trackball VCC  →  nice!nano VCC (3.3V)
Trackball GND  →  nice!nano GND
Trackball SDA  →  nice!nano P0.17 (SDA)
Trackball SCL  →  nice!nano P0.20 (SCL)
```

### Paso 3: Verificación
1. Conecta la batería
2. Enciende el teclado
3. Activa la capa trackball: `Raise + F12`
4. Prueba el movimiento del trackball

---

## ⚠️ Consideraciones Importantes

### 🔋 Alimentación:
- **Voltaje:** 3.3V (compatible con nice!nano v2)
- **Consumo:** Bajo consumo, compatible con operación inalámbrica

### 📡 I2C:
- **Velocidad máxima recomendada:** 400kHz
- **Pull-ups:** ZMK incluye pull-ups internos
- **Bus compartido:** Puede coexistir con OLED displays

### 🚫 Precauciones:
- **NO conectes** el pin INT del trackball (no es necesario)
- **NO uses** 5V, solo 3.3V
- **Evita** cortocircuitos entre SDA y SCL

---

## 🎮 Uso del Trackball

### Activación:
1. Presiona **Raise + F12** para alternar la capa trackball
2. El trackball estará activo en la capa 4

### Controles Disponibles:
- **Movimiento físico** del trackball → Movimiento del cursor
- **Click trackball** → Click izquierdo
- **Fila 1:** Clicks manuales (L, R, Middle)
- **Fila 2:** Movimiento manual (WASD)
- **Encoders:** Scroll vertical

---

## 🛠️ Solución de Problemas

### El trackball no responde:
1. ✓ Verifica las conexiones VCC y GND
2. ✓ Confirma que SDA y SCL están bien conectados
3. ✓ Activa la capa trackball (Raise + F12)

### Movimiento errático:
1. ✓ Revisa que no hay interferencias en cables I2C
2. ✓ Verifica que no hay cortocircuitos
3. ✓ Limpia el trackball físicamente

### Conflicts con otros dispositivos:
1. ✓ Confirma direcciones I2C únicas
2. ✓ Verifica integridad del bus I2C

---

## 📚 Referencias Técnicas

- **ZMK Pointing Devices:** https://zmk.dev/docs/features/pointing
- **nice!nano Pinout:** https://nicekeyboards.com/docs/nice-nano/pinout-schematic/
- **Pimoroni Trackball:** Dirección I2C por defecto `0x0A`

---

## ✅ Checklist Final

- [ ] Cables conectados correctamente
- [ ] Alimentación 3.3V verificada
- [ ] Configuración ZMK actualizada
- [ ] Capa trackball activable (Raise + F12)
- [ ] Movimiento del cursor funcional
- [ ] Clicks funcionando correctamente

---

¡Tu trackball Pimoroni está listo para usar con ZMK! 🎉