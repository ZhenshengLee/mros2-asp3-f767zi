#include "app.h"
#include "mros2.h"
#include "shape_msgs/msg/mesh.hpp"

#include "stm32f7xx_nucleo_144.h"

mros2::Subscriber sub;
mros2::Publisher pub;

void userCallback(shape_msgs::msg::Mesh *msg)
{
  MROS2_INFO("subscribed!");
  MROS2_INFO("publishing!");
  pub.publish(*msg);
}

int main(int argc, char * argv[])
{
  MROS2_INFO("mROS 2 application is started");

  mros2::init(argc, argv);
  MROS2_DEBUG("mROS 2 initialization is completed");
  BSP_LED_Toggle(LED1);

  mros2::Node node = mros2::Node::create_node("mros2_node");
  pub = node.create_publisher<shape_msgs::msg::Mesh>("to_linux", 10);
  sub = node.create_subscription<shape_msgs::msg::Mesh>("to_stm", 10, userCallback);
  shape_msgs::msg::Mesh msg;

  MROS2_INFO("ready to pub/sub message");
  mros2::spin();
  BSP_LED_Toggle(LED3);
}

void main_task(void)
{
  main(0, NULL);
}

void
led_cyclic_handler(intptr_t exinf)
{
  BSP_LED_Toggle(LED2);
}