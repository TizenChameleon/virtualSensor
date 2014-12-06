#include <linux/module.h>
#include <linux/string.h>
#include <linux/init.h>
#include <linux/sysfs.h>
#include <linux/device.h>

static int temp;
static int hum;
struct class *VsensorClass;
struct device *odev;

static ssize_t sensorShow(struct device *dev, struct device_attribute *attr, 
				char *buffer){
	return sprintf(buffer, "%d %d\n", temp, hum);
}

static ssize_t sensorStore(struct device *dev, struct device_attribute *attr, 
				const char *buffer, size_t count){
	sscanf(buffer, "%d %d", &temp, &hum);
	return count;
}

DEVICE_ATTR(oduino_sensor, 0777, sensorShow, sensorStore);


static int __init oduinoSensor_init(void){
	VsensorClass = class_create(THIS_MODULE, "Vsensor");
	odev = device_create(VsensorClass, NULL, 0, NULL, "oduino");
	//oduinoSensor = platform_device_register_simple("oduinoSensor", -1, NULL, 0);
	device_create_file(odev,  &dev_attr_oduino_sensor);
 //	sysfs_create_file(&oduinoSensor->dev.kobj, &dev_attr_oduino_sensor.attr);	

	return 0;
	
}

static void __exit oduinoSensor_exit (void){

//	sysfs_remove_file(&oduinoSensor->dev.kobj, &dev_attr_oduino_sensor.attr);
//	platform_device_unregister(oduinoSensor);
	device_destroy(VsensorClass, 0);
	class_destroy(VsensorClass);
	device_remove_file(odev, &dev_attr_oduino_sensor);
	return;
}

module_init(oduinoSensor_init);
module_exit(oduinoSensor_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("virtual input device");
