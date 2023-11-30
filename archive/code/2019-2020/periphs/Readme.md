# Code de test des différents périphériques (low-level drivers) 
---
## test

Classe de debug ( UART OPENSDA, 7segment display, leds, rotary switch and pushbuttons).

Implémente un buffer circulaire et envoi par interruption.

##### TODO

* Solve issue with rotary switch missing counts -> check electrical continuity on pcb and correct port config
* Known issue with SW2 and BLUE_LED interferring : see pcb layout
* Extra : simplify usage of uart with a uart class in cpp

---
## Motor

Controle pwm des moteurs gauche et droit.

##### TODO

* Tabuler des vitesses en m/s pour diverses entrees en PWM (pour calibrer MOTOR_CAL_SPEED)

---
## Servo

Controle du servo avec limites d'angle.

##### TODO

* Check zero and max angle values

---

## encoder_v2

Retour de vitesse des roues

##### TODO

* Vérifier la bonne valeur de vitesse retournée par la classe pour une vitesse mesurée en réel

---

## Direction

Controlleur utilisant Motor, Servo, encoder_v2

##### TODO

* Calibrer coefficient entraxe
* calibrer correcteur KP
* vérifier la non saturation SPEED_LIMIT en fonctionnement normal

---
---

## Nom du dossier

Fonctions implementées

##### TODO

* Choses à faire
* ...
