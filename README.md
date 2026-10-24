# Travaux pratiques Arduino

Ce dossier regroupe 14 projets pour apprendre à utiliser les entrées et sorties d'une carte Arduino, lire des capteurs et commander des composants électroniques. Chaque sous-dossier contient un programme `.ino` indépendant.

## Idée générale

Les TP suivent une progression : faire clignoter une LED, réagir à un bouton, varier une luminosité, afficher des informations, piloter un servomoteur, puis exploiter des capteurs et un lecteur RFID. Ils permettent de travailler les entrées numériques et analogiques, le PWM, les communications I²C et SPI, ainsi que les temporisations.

## Présentation des TP

| Projet | Travail réalisé et principe | Composants principaux et connexions prévues par le code |
| --- | --- | --- |
| [TP01 - Clignotement](TP01_LED_Blink/TP01_LED_Blink.ino) | Allumer la LED pendant 500 ms, puis l'éteindre pendant 500 ms, en boucle. Découvrir la configuration d'une sortie numérique et `delay()`. | LED commandée par D13 ; résistance de limitation si LED externe. |
| [TP02 - Bouton et LED](TP02_PushButton_LED/TP02_PushButton_LED.ino) | Allumer la LED tant que le bouton est appuyé. Utiliser la résistance de rappel interne : un appui correspond à `LOW`. | LED sur D13 ; bouton entre D2 et GND. |
| [TP03 - Variation de luminosité](TP03_LED_Fading_PWM/TP03_LED_Fading_PWM.ino) | Augmenter puis diminuer progressivement la commande PWM de 0 à 255, avec un pas toutes les 10 ms. | LED avec résistance sur D9 ; carte dont cette broche prend en charge le PWM. |
| [TP04 - Écran OLED](TP04_OLED_HelloWorld/TP04_OLED_HelloWorld.ino) | Initialiser un écran OLED et afficher un écran entièrement blanc pour vérifier son fonctionnement. Malgré le nom du dossier, aucun texte « Hello World » n'est affiché. | OLED SSD1306 de 128 × 64 pixels, sur le bus I²C à l'adresse `0x3C` ; aucune broche de réinitialisation dédiée n'est déclarée. |
| [TP05 - Basculement d'une LED](TP05_ButtonToggleLED/TP05_ButtonToggleLED.ino) | Inverser l'état de la LED à chaque nouvel appui. Attendre plus de 50 ms de stabilité du signal pour filtrer les rebonds du bouton. | Bouton entre D2 et GND, avec rappel interne ; LED avec résistance sur D9. |
| [TP06 - Servomoteur et capteur tactile](TP06_TouchServoSmooth/TP06_TouchServoSmooth.ino) | Sur un front montant du capteur, déplacer le servo de 0° à 90° par pas de 1°, attendre une seconde, puis revenir à 0°. La vitesse demandée est de 120°/s. Une machine à états gère le cycle avec `millis()` et `micros()`. | Servomoteur, signal sur D9 ; capteur tactile à sortie numérique sur D2. |
| [TP07 - Distance et écran LCD](TP07_LCD16x2_Ultrasonic_Distance/TP07_LCD16x2_Ultrasonic_Distance.ino) | Envoyer une impulsion de déclenchement de 10 µs, mesurer la durée de l'écho et calculer la distance en centimètres. Afficher la mesure ou l'absence d'écho sur le LCD. | Capteur ultrasonique à broches TRIG/ECHO, par exemple HC-SR04 : TRIG sur D9, ECHO sur D10 ; LCD 16 × 2 avec interface I²C à l'adresse `0x27`. |
| [TP08 - Compte à rebours](TP08_4Digit_Countdown/TP08_4Digit_Countdown.ino) | Décompter de 9999 jusqu'à 0, à raison d'une unité par seconde. Rafraîchir un chiffre toutes les 2 ms par multiplexage pour partager les sept lignes de segments. | Afficheur à quatre chiffres et sept segments ; segments A à G sur D2 à D8 ; sélection des chiffres sur D12, D11, D10 et D9. Segments actifs à `HIGH`, chiffres sélectionnés à `LOW`. Résistances de limitation nécessaires pour les segments. |
| [TP09 - Joystick et chenillard](TP09_Joystick_LED_Signals/TP09_Joystick_LED_Signals.ino) | Allumer successivement cinq LED, avec un pas toutes les 150 ms. La lecture du joystick choisit le sens de parcours : sous 400 ou au-dessus de 600. Entre ces seuils, le sens précédent est conservé. | Axe Y d'un joystick analogique sur A1 ; cinq LED avec résistances sur D3 à D7. |
| [TP10 - Température et humidité](TP10_DHT11_Temperature_Humidity/TP10_DHT11_Temperature_Humidity.ino) | Lire la température et l'humidité avec un DHT11, puis les envoyer au moniteur série. Détecter les mesures invalides et espacer les cycles de deux secondes. | Capteur DHT11, signal sur D2 ; moniteur série à 9600 bauds. |
| [TP11 - Détection de mouvement](TP11_PIR_Motion_Detection_HW416B/TP11_PIR_Motion_Detection_HW416B.ino) | Lire la sortie d'un capteur PIR toutes les 500 ms. Allumer la LED intégrée lorsque la sortie est à `HIGH` et afficher l'état sur le moniteur série. | Capteur PIR HW416B, sortie sur D2 ; LED intégrée de la carte ; moniteur série à 9600 bauds. |
| [TP12 - Commande d'un relais](TP12_Relay_LED_Control/TP12_Relay_LED_Control.ino) | Alterner les niveaux `HIGH` et `LOW` toutes les 500 ms sur la sortie de commande. L'état réel du relais dépend de la polarité de son module. | Module relais commandé par D7 ; charge de démonstration éventuelle, telle qu'une LED avec sa résistance, sur les contacts du relais. |
| [TP13 - Contrôle d'accès RFID](TP13_RFID_RC522_Access_Control/TP13_RFID_RC522_Access_Control.ino) | Lire l'identifiant d'un badge et comparer ses quatre octets à l'UID autorisé `17 4C 31 07`. Afficher l'autorisation ou le refus sur le moniteur série, puis terminer l'échange avec la carte. | Lecteur RC522 sur le bus SPI, sélection SS sur D10 et réinitialisation RST sur D9 ; badge compatible ; moniteur série à 9600 bauds. |
| [Exercice complémentaire - Bouton et SG90](TP14_ButtonServo_SG90/TP14_ButtonServo_SG90.ino) | Après un appui stable pendant au moins 60 ms, commander le servo à 180°, puis le ramener à 0° après une seconde. La temporisation laisse la lecture du bouton active. Les nouveaux appuis pendant le cycle ne déclenchent pas de mouvement supplémentaire. | Servomoteur SG90, signal sur D9 ; bouton sur D2, actif à `HIGH`, avec rappel externe adapté car l'entrée est configurée en `INPUT`. |

## Matériel utilisé dans l'ensemble des projets

- Une carte Arduino adaptée aux broches et aux niveaux électriques des montages.
- Des LED et leurs résistances de limitation, des boutons-poussoirs et un joystick analogique.
- Un servomoteur, notamment un SG90 pour l'exercice complémentaire, et un capteur tactile numérique.
- Un écran OLED SSD1306 et un écran LCD 16 × 2 avec interface I²C.
- Un afficheur à quatre chiffres et sept segments.
- Un capteur ultrasonique, un DHT11 et un capteur de mouvement PIR HW416B.
- Un module relais, un lecteur RFID RC522 et un badge compatible.
- Une plaque d'essai, des fils de connexion et les alimentations adaptées aux composants.

Les références et connexions ci-dessus sont déduites des programmes et des noms des projets. Le modèle exact de la carte n'est pas indiqué. Les broches physiques SDA/SCL pour l'I²C et MOSI/MISO/SCK pour le SPI dépendent de la carte choisie. Le modèle exact du capteur ultrasonique et la charge raccordée au relais ne sont pas précisés dans les programmes.

## Bibliothèques utilisées

| Bibliothèque | Utilisation |
| --- | --- |
| `Servo` | Commande des servomoteurs. |
| `Wire` | Communication I²C avec les écrans. |
| `Adafruit_GFX` et `Adafruit_SSD1306` | Gestion de l'écran OLED. |
| `LiquidCrystal_I2C` | Gestion du LCD 16 × 2. |
| `DHT` | Lecture du DHT11. |
| `SPI` et `MFRC522` | Communication avec le lecteur RFID RC522. |

## Travail de documentation réalisé

Les 14 programmes ont été relus. Au total, 25 commentaires courts en français ont été ajoutés dans 12 projets pour expliquer les points utiles : rappel des boutons, anti-rebond, temporisations, déplacement du servo, conversion de distance, multiplexage et vérification d'un UID RFID.

Les exemples de clignotement simple et de commande du relais sont restés inchangés, leur logique étant directement lisible. Le code exécutable, les noms, les broches et les délais ont été conservés. Les bibliothèques n'ont pas été modifiées.

## Organisation et utilisation

Ouvrir le fichier `.ino` du TP souhaité dans l'IDE Arduino. Chaque projet s'utilise séparément avec son propre montage. Les programmes qui écrivent sur le port série utilisent 9600 bauds, sauf le TP06 qui utilise 115200 bauds.

Cette documentation décrit le comportement prévu par les programmes. Aucun téléversement ni essai matériel n'a été effectué pendant la revue.
