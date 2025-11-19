




/*

Wire.begin(21, 22); // SDA=21, SCL=22
  if (!pcf.begin()) {
    Serial.println("Errore inizializzazione PCF8574!");
    while (1);
  }
  
  */
  
  
Wire.begin(21, 22); // SDA=21, SCL=22

pcf.begin();