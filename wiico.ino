#include <WiiChuck.h>
#include <PicoGamepad.h>
#include <limits.h>

Accessory controller;
PicoGamepad gamepad;

int min_x;
int max_x;

void setup() {
  controller.begin();
  controller.type = WIICLASSIC;
  controller.readData();
  min_x = controller.getJoyXLeft() - 1;
  max_x = controller.getJoyXLeft() + 1;
}

void loop() {
  // delay(1000);
  controller.readData();

  // lets do the classic controller for now
  if(controller.getButtonHome() && controller.getButtonPlus()){
    min_x = min(controller.getJoyXLeft(), min_x);
    max_x = max(controller.getJoyXLeft(), max_x);
    printf("min: %d | max: %d\n", min_x, max_x);
    
    return;
  }
  
  int adjusted = map(controller.getJoyXLeft(), min_x, max_x, SHRT_MIN+1, SHRT_MAX);
  printf("X Value: %d | Adjusted Value: %d\n", controller.getJoyXLeft(), adjusted);

  gamepad.SetButton(17, controller.getJoyXLeft() == min_x || controller.getJoyXLeft() == max_x);

  // face buttons
  gamepad.SetButton(0, controller.getButtonA());
  gamepad.SetButton(1, controller.getButtonB());
  gamepad.SetButton(2, controller.getButtonX());
  gamepad.SetButton(3, controller.getButtonY());

  // right stick
  gamepad.SetX(map(controller.getJoyXLeft(), min_x, max_x, SHRT_MIN, SHRT_MAX));  // joystick X axis
  // gamepad.SetY(controller.getJoyXRight()); // raw values
  // gamepad.SetX(controller.getJoyXRight());  // joystick X axis

  gamepad.send_update();
}
