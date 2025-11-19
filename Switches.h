#ifndef Switches_h
#define Switches_h

#include <Arduino.h>
#include <functional>

class Switches {
private:
    int pin;                          // Pin fisico (se usato)
    bool pullup;                      // true = INPUT_PULLUP
    bool pressed;                     // stato precedente
    bool isheld;                      // true se mantenuto premuto

    uint32_t hold_lim;                // tempo minimo per considerare "held"
    uint32_t hold_init;               // momento in cui è stato premuto

    std::function<bool()> customButtonReader; // lettura personalizzata (es. PCF8574)

    bool getButtonState();            // legge lo stato del bottone

public:
    // Costruttore di default (pin non valido)
    Switches();

    // Costruttore con pin fisico
    Switches(int pin, uint32_t hold_lim = 2000, bool pullup = false);

    // Costruttore con funzione custom (es. lettura da PCF8574)
    Switches(std::function<bool()> customReader, uint32_t hold_lim = 2000);

    // Getter
    int getPin();
    bool getPullup();
    bool isHeld();

    // Eventi
    bool justPressed();
    bool justReleased();
};

#endif
