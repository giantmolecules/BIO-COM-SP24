
// Based on the Talkie library. https://github.com/going-digital/Talkie.
// Copyright 2011 Peter Knight
// Copyright (C) 2018  Armin Joachimsmeyer
// armin.joachimsmeyer@gmail.com


#include <Arduino.h>

#include "Talkie.h"
#include "Vocab_US_Large.h"
#include "Vocab_Special.h"
#include "Vocab_US_TI99.h"
#include "Vocab_US_Clock.h"
#include "Vocab_US_Acorn.h"


Talkie voice;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
}
void loop() {

  voice.say(spPAUSE2);
  voice.say(spa_PLEASE);
  voice.say(spPAUSE1);
  voice.say(spa_DO);
  voice.say(spa_NOT);
  voice.say(spa_DO);
  voice.say(spa_THAT);

  voice.say(spPAUSE2);
  voice.say(spa_PLEASE);
  voice.say(spa_DONT);
  voice.say(spPAUSE1);
  voice.say(spa_THAT);
  voice.say(spa_IS);
  voice.say(spa_BAD);

  voice.say(spPAUSE2);
  voice.say(spa_PLEASE);
  voice.say(spa_DO);
  voice.say(spa_THAT);
  voice.say(spa_AGAIN);
}
