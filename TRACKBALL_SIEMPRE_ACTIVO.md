# Trackball Pimoroni Siempre Activo

## ✅ **Cambios Realizados:**

### **1. Eliminado Toggle de Capa**
- ❌ **Antes:** `Raise + F12` para activar capa trackball
- ✅ **Ahora:** Trackball **siempre activo**, sin necesidad de capas

### **2. Configuración Simplificada**
- ✅ Capa trackball eliminada (layer 4)
- ✅ Toggle `&tog 4` removido del keymap
- ✅ Behaviors innecesarios limpiados
- ✅ Trackball funciona automáticamente al encender

---

## 🎮 **Funcionamiento:**

### **Trackball Físico:**
- **Movimiento** → Cursor del mouse
- **Click** → Click izquierdo automático
- **Scroll** → Funciona con encoders

### **Sin Capas Necesarias:**
- ✅ **Funciona inmediatamente** al encender el teclado
- ✅ **No requiere activación manual**
- ✅ **Más intuitivo y práctico**

---

## 🔧 **Verificar Conexiones:**

### **Lado Derecho (Central + Trackball):**
```
Trackball VCC  → nice!nano VCC (3.3V)
Trackball GND  → nice!nano GND
Trackball SDA  → nice!nano P0.17 (SDA)
Trackball SCL  → nice!nano P0.20 (SCL)
```

### **Si aún no funciona:**
1. ✓ **USB conectado al lado DERECHO** (central)
2. ✓ **Conexiones I2C verificadas**
3. ✓ **Trackball alimentado (3.3V)**
4. ✓ **Cables no intercambiados** (SDA ≠ SCL)

---

## 🎯 **Para Probar:**

1. **Compila el nuevo firmware**
2. **Flashea solo el lado derecho** (el cambio está en sofle.keymap que es global)
3. **Mueve el trackball físico** → debería mover cursor inmediatamente
4. **Click en trackball** → debería hacer click izquierdo

---

## 🔍 **Debugging:**

### **Si el trackball no mueve cursor:**
- ✓ Verifica alimentación 3.3V
- ✓ Confirma conexiones I2C
- ✓ Revisa que lado derecho sea central (USB funciona ahí)

### **Si cursor se mueve erráticamente:**
- ✓ Limpia el trackball físicamente
- ✓ Verifica que cables I2C no tengan interferencias
- ✓ Confirma dirección I2C 0x0A

---

¡El trackball debería funcionar automáticamente ahora! 🎯