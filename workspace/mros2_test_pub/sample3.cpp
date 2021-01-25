#include <kernel.h>
#include <t_syslog.h>
#include <t_stdlib.h>
#include "syssvc/serial.h"
#include "syssvc/syslog.h"
#include "kernel_cfg.h"
#include <rtps/rtps.h>
#include "sample1.h"
#include "cmsis_os.h"
#include "lwip.h"
#include <cstdint>

#include "stm32f7xx_hal.h"
#include "stm32f7xx_nucleo_144.h"

#include "GPIO.h"

#include "mros2.h"
#include "TEST.hpp"
#include "std_msgs/msg/string.hpp"

// To avoid link error
void* __dso_handle=0;

void startRTPStest();

void setTrue(void* args){
	*static_cast<volatile bool*>(args) = true;
}

mros2::Subscriber sub;
mros2::Publisher pub;

void userCallback(std_msgs::msg::String &msg)
{
}

void main_task(void)
{
	MX_LWIP_Init();
	mros2::init(NULL, NULL);
	mros2::Node node = mros2::Node::create_node();
	sub = node.create_subscription("to_stm", 1, userCallback);
	pub = node.create_publisher<std_msgs::msg::String>("to_linux", NULL);
	std_msgs::msg::String msg;
	int cnt = 0;
	while(true){
		msg.data = "Hello " + std::to_string(cnt++);
		syslog(LOG_NOTICE, "publish message [%s]", msg.data.c_str());
		pub.publish(msg);
		dly_tsk(1000000);
	}
	mros2::spin();
}

void
led_cyclic_handler(intptr_t exinf)
{
  BSP_LED_Toggle(LED2);
}
