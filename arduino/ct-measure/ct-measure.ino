int INPUT_PIN = A0;
int SAMPLING_SIZE = 10000;
double CALIBRATION_VALUE = 511.72;
int CT_RATIO = 30;

void setup() {
  Serial.begin(9600);
}

void loop() {
  double sum = 0;

  for (int i = 0; i < SAMPLING_SIZE; i++){
    double value = analogRead(INPUT_PIN);
    sum += value * value;
  }

  double rms = sqrt(sum / SAMPLING_SIZE);
  double voltage = rms - CALIBRATION_VALUE;
  double current = voltage * CT_RATIO;
  
  Serial.println(current);
}
