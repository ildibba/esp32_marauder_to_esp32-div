#include "Switches.h"

// Costruttore di default
Switches::Switches() {
    this->pin = -1;  // Pin non valido
    this->pullup = false;
    this->pressed = false;
    this->isheld = false;
    this->hold_lim = 2000;
    this->hold_init = 0;
    this->customButtonReader = nullptr;
}

// Costruttore con pin fisico
Switches::Switches(int pin, uint32_t hold_lim, bool pullup) {
    this->pin = pin;
    this->pullup = pullup;
    this->pressed = false;
    this->isheld = false;
    this->hold_lim = hold_lim;
    this->hold_init = 0;
    this->customButtonReader = nullptr;

    if (pullup)
        pinMode(this->pin, INPUT_PULLUP);
    else
        pinMode(this->pin, INPUT);
}

// Costruttore con lettura personalizzata
Switches::Switches(std::function<bool()> customReader, uint32_t hold_lim) {
    this->pin = -1;
    this->pullup = false;
    this->pressed = false;
    this->isheld = false;
    this->hold_lim = hold_lim;
    this->hold_init = 0;
    this->customButtonReader = customReader;
}

// Getter pin
int Switches::getPin() {
    return this->pin;
}

// Getter pullup
bool Switches::getPullup() {
    return this->pullup;
}

// Stato hold
bool Switches::isHeld() {
    return this->isheld;
}

// Legge lo stato del bottone
bool Switches::getButtonState() {
    if (this->customButtonReader) {
        return this->customButtonReader(); // lettura custom
    }

    if (this->pin < 0) return false; // pin non valido

    int buttonState = digitalRead(this->pin);

    if (this->pullup)
        return (buttonState == LOW);
    else
        return (buttonState == HIGH);
}

// Rileva pressione
bool Switches::justPressed() {
    bool btn_state = this->getButtonState();

    if (btn_state && !this->pressed) {   // appena premuto
        this->hold_init = millis();
        this->pressed = true;
        this->isheld = false;
        return true;
    } 
    else if (btn_state && this->pressed) {  // ancora premuto
        uint32_t hold_time = millis() - this->hold_init;
        this->isheld = (hold_time >= this->hold_lim);
        return false;
    } 
    else {  // rilasciato
        this->pressed = false;
        this->isheld = false;
        return false;
    }
}

// Rileva rilascio
bool Switches::justReleased() {
    bool btn_state = this->getButtonState();

    if (!btn_state && this->pressed) {  // appena rilasciato
        this->pressed = false;
        this->isheld = false;
        return true;
    } 
    return false;
}
