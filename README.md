# Salat Rocker 🤘

- BME280 temperature pressure hunidity sensor
- DS18B20 temperature sensore
- Fans via relais
- motors via relais
	- Motorabschaltung über Endschalter, die den Motor mittels Interrupt abschalten: attachInterrupt(digitalPinToInterrupt(pin_Endschalter), damper_motor_off, FALLING)  
- Protokollierung in protocol.txt mit Zeit und allen Werten
- ständige Ausgabe der Werte, Einstellungen und Zustände auf Display
- Menü zum Setzen/Ändern der Einstellungen.
		-attachInterrupt(digitalPinToInterrupt(pin_Endschalter), damper_motor_off, FALLING); //in dampers_setup verschieben!


platform.io project ATmel4809
