# Trabajo Práctico 3, Electrónica IV, FACET UNT 2022: Alarma simple

Un sistema de alarma es un elemento de seguridad pasivo que advierte sobre la ocurrencia de situaciones anomalas tales como intrusiones en un espacio físico monitoreado. Dichas advertencias o alertas pueden darse en forma local y/o remota.
En este práctico se desarrollará un sistema de alarma sencillo en base a la placa de desarrollo "bluepill" del microcontrolador STM32F103C8T6. El desarrollo se realizará siguiendo la metodología de desarrollo basado en pruebas "Test Driven Development".

La alarma tendrá las siguientes características mínimas

+ Control de armado/desarme
+ Vigilancia con una zona temporizada. Como actividad extra pueden implementarse más zonas, zonas no temporizadas y la función de pánico.
+ Sistema de alerta
+ Indicación de estado
    + Armado
    + Temporización
    + Actividad
    + Alarma ocurrida

El control de armado/desarme es un elemento de interfaz de usuario que permite armar y desarmar la alarma. El requisito mínimo para esta función será un interruptor con llave (para propósitos de la práctica simulado por un interruptor corriente). Como actividad extra puede implementarse el armado/desarme con teclado numérico y/o sistema RFID.

La función de vigilancia se llevará a cabo mediante el monitoreo de un conjunto de sensores de intrusión. Se empleará un circuito cerrado con sensores conectados en serie. La actividad en la zona monitoreada provocará la interrupción del circuito. Como actividad extra puede implementarse sensores inalámbricos.

La función de alerta indica cuando la alarma se encuentra en estado disparada. Se empleará un zumbador o algún indicador luminoso. Como actividad extra podrá conectarse una sirena o bien realizar un sistema de aviso remoto a través de una conexión de red o telefónica.

Las indicaciones de estado se realizarán mediante indicadores LED, excepto la temporización que se indicará mediante un zumbador. Como actividad extra podrá implementarse un sistema remoto de monitoreo de estado de alarma.


# Ejemplos de uso

## Alarma desarmada

Si la alarma se encuentra desarmada y los sensores detectan actividad en la zona monitoreada entonces el indicador de actividad debe encenderse, pero no debe establecerse la condición de alarma.

## Armado de la alarma

Si la alarma se encuentra desarmada y el usuario da el comando de armado entonces la alarma transicionará al estado de armada, restablecerá el indicador de alarma ocurrida e iniciará la temporización de armado.

## Actividad durante temporización de armado

Si ocurre actividad en una zona temporizada durante la temporización de armado entonces la alarma debe ignorar dicha actividad.

## Temporización de desarme

Si la alarma se encuentra armada y detecta activida en una zona temporizada debe iniciar la temporización de desarme, siendo esto indicado por el indicador de temporización.

## Desarme de la alarma

Si la alarma está en estado de armado o temporización de desarme y el usuario da el comando de desarme entonces la alarma debe pasar al estado de desarmada. El indicador de alarma ocurrida no debe ser afectado.

## Disparo de la alarma

Si la alarma está armada y vence la temporización de desarme o se detecta un evento en una zona no temporizada entonces la alarma debe pasar al estado de disparada. Indicará la situación de alarma mediante el sistema de alerta y activará el indicador de alarma ocurrida.

## Fin de condición de alarma por desarmado

Si la alarma está disparada y el usuario da el comando de desarme entonces finalizará la condición de disparo pasando a estado desarmada. Se desactivará el sistema de alerta pero el indicador de alarma ocurrida permanecerá activo.

## Fin de condición de alarma por tiempo sin actividad

Si la alarma está disparada y no se acusa más actividad durante un tiempo de restablecimiento de alarma entonces debe transicionar a la condición de armada. Se desactivará el sistema de alerta pero permanecerá actio el indicador de alarma ocurrida.

