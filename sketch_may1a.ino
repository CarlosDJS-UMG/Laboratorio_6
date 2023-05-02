#include <Stepper.h>

class MotorStepper {
  private:
    Stepper motor;
    int pos; // posición actual en grados
    int maxPos; // posición máxima en grados
    int minPos; // posición mínima en grados
    int stepsPerRev; // número de pasos por revolución del motor
    float rpm; // velocidad en revoluciones por minuto
    
  public:
    MotorStepper(int stepsPerRev, int pin1, int pin2, int pin3, int pin4, int minPos, int maxPos) :
      motor(stepsPerRev, pin1, pin2, pin3, pin4),
      stepsPerRev(stepsPerRev),
      minPos(minPos),
      maxPos(maxPos) {
      pos = 0;
      rpm = 0;
    }
    
    void setRPM(float newRPM) {
      rpm = newRPM;
    }
    
    void setPos(int newPos) {
      if (newPos > maxPos) {
        pos = maxPos;
      } else if (newPos < minPos) {
        pos = minPos;
      } else {
        pos = newPos;
      }
      int steps = pos * stepsPerRev / 360;
      motor.step(steps);
    }
    
    void setDirection(bool clockwise) {
      if (clockwise) {
        motor.setSpeed(rpm * stepsPerRev / 60);
      } else {
        motor.setSpeed(-rpm * stepsPerRev / 60);
      }
    }
};

// Ejemplo de uso
MotorStepper motor(2048, 8, 9, 10, 11, 0, 360); // Inicializar motor con 2048 pasos por revolución, conectado a los pines 8, 9, 10 y 11, con posición mínima de 0 grados y posición máxima de 360 grados

void setup() {
  motor.setRPM(30); // Establecer velocidad en 30 RPM
}

void loop() {
  motor.setDirection(true); // Mover en sentido horario
  motor.setPos(90); // Mover a 90 grados
  delay(500);
  motor.setDirection(false); // Mover en sentido antihorario
  motor.setPos(270); // Mover a 270 grados
  delay(500);
}
