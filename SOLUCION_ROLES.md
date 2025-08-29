# Solución: Intercambio Correcto de Roles Central/Periférico

## 🚨 **Problema Identificado:**

El cambio en `build.yaml` **NO es suficiente** para cambiar roles. Los roles están hardcodeados en la configuración del shield Sofle:
- `sofle_left` = central por defecto
- `sofle_right` = periférico por defecto

## ✅ **Solución Implementada:**

### 1. **Archivos de Configuración Específicos:**
- **`config/sofle_left.conf`**: Fuerza lado izquierdo como periférico
- **`config/sofle_right.conf`**: Fuerza lado derecho como central + trackball

### 2. **Configuración Limpia:**
- **`config/sofle.conf`**: Limpiado de configuraciones conflictivas
- Trackball configurado solo en el lado central (derecho)

---

## 🔄 **Nuevos Roles:**

### **Lado Derecho (Central):**
- ✅ `CONFIG_ZMK_SPLIT_ROLE_CENTRAL=y`
- ✅ Conexión USB principal
- ✅ Trackball I2C (P0.17/P0.20)
- ✅ Control total del teclado
- ⚠️ OLED puede tener conflictos I2C

### **Lado Izquierdo (Periférico):**
- ✅ `CONFIG_ZMK_SPLIT_ROLE_CENTRAL=n`
- ✅ RGB Underglow (P0.06)
- ✅ OLED independiente
- ✅ Comunicación BLE al central

---

## 🎯 **Para Probar:**

1. **Compila los nuevos firmwares** (GitHub Actions)
2. **Flashea ambos lados** con sus respectivos UF2
3. **Conecta el cable USB al lado DERECHO** (ahora es central)
4. **Conecta el trackball al lado derecho** según guía de cableado
5. **Activa trackball:** `Raise + F12`

---

## 🔍 **Indicadores de Éxito:**

- ✅ **USB funciona SOLO en lado derecho**
- ✅ **OLED derecho muestra información de central**
- ✅ **OLED izquierdo muestra información de periférico**
- ✅ **Trackball responde al movimiento**
- ✅ **RGB underglow funciona en lado izquierdo**

---

¡Ahora los roles deberían intercambiarse correctamente! 🔄