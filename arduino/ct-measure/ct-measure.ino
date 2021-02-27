#include "EmonLib.h"
EnergyMonitor emon1; 

int INPUT_PIN = 0;
int SAMPLING_SIZE = 1480;
double CT_CURRENT_VOLTAGE_RATIO = 30;
double INPUT_CALIBRATION = 509;
double EMON_CALIBRATION = 1800/62;

double voltageMultiplier = CT_CURRENT_VOLTAGE_RATIO * 10 / 512;

void setup() {
  Serial.begin(9600);
  emon1.current(INPUT_PIN, EMON_CALIBRATION);
}

double calcIrms(int samplingSize) {
  double sum = 0;

  for (int i = 0; i < samplingSize; i++){
    double inputVoltage = analogRead(INPUT_PIN);
    double current = (inputVoltage - INPUT_CALIBRATION) * voltageMultiplier;
    sum += current * current;
  }

  return sqrt(sum / samplingSize);
}

void loop() {
  double manualIrms = calcIrms(SAMPLING_SIZE);
  double emonIrms = emon1.calcIrms(SAMPLING_SIZE);
  
  Serial.print("manual: ");
  Serial.print(manualIrms);
  Serial.print(" | emonLib: ");
  Serial.print(emonIrms);
  Serial.print('\n');
}
