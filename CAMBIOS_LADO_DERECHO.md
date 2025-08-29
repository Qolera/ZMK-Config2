# Cambios para Trackball en Lado Derecho (Central)

## 🔄 Cambios Realizados

### 1. **build.yaml**
- **Cambiado:** El lado derecho ahora es el central (con USB/studio-rpc)
- **Efecto:** El lado derecho controlará el trackball y tendrá la conexión principal

### 2. **Configuración Split**
- **Lado Derecho:** Central + Trackball (I2C en P0.17/P0.20)
- **Lado Izquierdo:** Periférico + RGB Underglow (SPI en P0.06)

### 3. **Overlays Específicos**
- **`sofle_right.overlay`:** Configuración I2C + Trackball
- **`sofle_left.overlay`:** Configuración SPI + RGB
- **`nice_nano_v2.overlay`:** Limpiado (sin configuraciones específicas)

---

## ⚡ Funcionamiento

### **Lado Derecho (Central):**
- ✅ Controla el trackball Pimoroni
- ✅ Conexión USB principal
- ✅ Manejo de todas las funciones del teclado
- ⚠️ OLED puede tener conflictos I2C

### **Lado Izquierdo (Periférico):**
- ✅ RGB Underglow funcional
- ✅ OLED debería funcionar (bus I2C separado)
- ✅ Comunicación BLE con lado derecho

---

## 🎮 Uso del Trackball

1. **Enciende el lado derecho** (central)
2. **Presiona Raise + F12** para activar capa trackball
3. **Mueve el trackball físico** → cursor del mouse
4. **Click en trackball** → click izquierdo
5. **Controles manuales** en la capa 4

---

## 🔧 Solución de Problemas

### Si el trackball no funciona:
1. ✓ Verifica conexiones I2C (SDA P0.17, SCL P0.20)
2. ✓ Confirma que el lado derecho es el que se conecta por USB
3. ✓ Activa la capa trackball (Raise + F12)

### Si OLED no funciona:
1. ✓ Puede haber conflicto I2C con trackball en lado derecho
2. ✓ OLED izquierdo debería funcionar normalmente
3. ✓ Considera deshabilitar OLED derecho temporalmente

---

## 📋 Para Compilar

1. Sube los cambios a GitHub
2. GitHub Actions compilará automáticamente
3. Descarga el firmware del **lado derecho** (central)
4. Flashea ambos lados con sus respectivos UF2

---

¡El trackball debería funcionar ahora en el lado derecho! 🎯