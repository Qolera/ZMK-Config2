# Guía de Configuración del Pimoroni Trackball con ZMK

## 📋 Requisitos Previos

1. **Hardware necesario:**
   - Pimoroni Trackball Breakout (PIM447)
   - Cables para conexión I2C (4 cables)
   - Resistencias pull-up de 4.7kΩ (si no están integradas)

2. **Conexiones físicas:**
   ```
   Pimoroni    →    Nice!Nano v2
   --------------------------------
   3-5V (VCC)  →    3.3V
   SDA         →    Pin 0.17 (P0.17)
   SCL         →    Pin 0.20 (P0.20)
   GND         →    GND
   INT         →    (No conectar inicialmente)
   ```

## 🚀 Pasos de Implementación

### Paso 1: Crear nueva rama
```bash
git checkout -b pimoroni-trackball
```

### Paso 2: Actualizar archivos de configuración
Reemplaza los siguientes archivos con las versiones proporcionadas:
- `config/west.yml`
- `config/sofle.conf`
- `config/boards/nice_nano_v2.overlay`
- `config/sofle.keymap`

### Paso 3: Actualizar dependencias
```bash
west update
```

### Paso 4: Compilar firmware
```bash
# Limpiar compilaciones anteriores
rm -rf build/

# Compilar mitad izquierda
west build -p -d build/left -b nice_nano_v2 -- -DSHIELD="sofle_left nice_oled" -DZMK_CONFIG="$(pwd)/config"

# Compilar mitad derecha  
west build -p -d build/right -b nice_nano_v2 -- -DSHIELD="sofle_right nice_oled" -DZMK_CONFIG="$(pwd)/config"
```

### Paso 5: Flashear firmware
1. Conecta el Nice!Nano por USB
2. Presiona reset dos veces para entrar en modo bootloader
3. Copia el archivo `.uf2` correspondiente al disco USB que aparece

## 🔧 Solución de Problemas

### Error: "PIM447 driver not found"
**Solución:** Asegúrate de usar el fork correcto en `west.yml`:
```yaml
- name: zmk
  remote: cdc-mkb
  revision: mouse-pim447
```

### Error: "I2C communication failed"
**Posibles causas:**
1. **Velocidad I2C incorrecta:** El Pimoroni solo funciona hasta 250kHz
2. **Pines incorrectos:** Verifica las conexiones físicas
3. **Falta de pull-ups:** Añade resistencias de 4.7kΩ en SDA y SCL

### El trackball no responde
1. **Verifica la dirección I2C:**
   ```c
   reg = <0x0a>;  // Dirección por defecto del Pimoroni
   ```

2. **Habilita logging para debug:**
   ```bash
   # En sofle.conf, descomenta:
   CONFIG_ZMK_USB_LOGGING=y
   CONFIG_LOG=y
   CONFIG_I2C_LOG_LEVEL_DBG=y
   ```

3. **Verifica que el módulo esté habilitado:**
   ```bash
   CONFIG_PIM447_TRACKBALL=y
   ```

### El cursor se mueve muy rápido/lento
Ajusta en `sofle.conf`:
```bash
CONFIG_PIM447_SCALE_X=15  # Aumenta para más velocidad
CONFIG_PIM447_SCALE_Y=15  # Disminuye para menos velocidad
```

### Los ejes están invertidos
En `sofle.conf`:
```bash
CONFIG_PIM447_INVERT_X=y
CONFIG_PIM447_INVERT_Y=y
```

## 🎮 Uso del Trackball

### Controles básicos:
- **Movimiento:** Mueve el trackball para mover el cursor
- **Click izquierdo:** Presiona el trackball o usa la tecla asignada
- **Click derecho:** Usa la tecla asignada en el keymap
- **Scroll:** Activa el modo scroll con la capa LOWER

### Capas de mouse:
- **Capa LOWER:** Activa scroll con el trackball
- **Capa MOUSE:** Controles completos de mouse

## 📝 Notas Importantes

1. **Firmware del Pimoroni:** Si tienes problemas con interrupciones, actualiza el firmware del trackball desde el repositorio oficial de Pimoroni.

2. **Consumo de energía:** El polling constante puede aumentar el consumo. Considera ajustar `CONFIG_ZMK_MOUSE_TICK_DURATION` para balancear respuesta y batería.

3. **Compatibilidad Bluetooth:** El mouse sobre Bluetooth requiere que el dispositivo receptor soporte HID mouse. Algunos dispositivos pueden requerir re-emparejamiento.

## 🔗 Referencias

- [PR original de cdc-mkb](https://github.com/zmkfirmware/zmk/pull/961)
- [Documentación Pimoroni](https://shop.pimoroni.com/products/trackball-breakout)
- [ZMK Mouse Support](https://github.com/zmkfirmware/zmk/issues/312)

## 💡 Alternativas si no funciona

Si el fork de cdc-mkb no funciona, puedes probar:

1. **Fork de NoirGuo:**
   ```yaml
   - name: zmk
     remote: NoirGuo
     revision: trackball
   ```

2. **Usar un microcontrolador intermediario:**
   - Programa un Arduino Pro Micro con QMK
   - Conéctalo como dispositivo HID al Nice!Nano

3. **Esperar al soporte oficial:**
   - El equipo de ZMK está trabajando en soporte oficial de mouse/trackball