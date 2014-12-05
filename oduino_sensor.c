#include <linux/module.h>

#include <linux/init.h>
#include <linux/fs.h>
#include <linux/platform_device.h>
#include <linux/input.h>

static int temp=0, hum=0;
static struct platform_device *oduinoSensor;

static ssize_t sensorShow(struct device *dev, struct device_attribute *attr, 
				char *buffer){
	sprintf(buffer, "%d %d", temp, hum);
	return 0;
}

static ssize_t sensorStore(struct device *dev, struct device_attribute *attr, 
				const char *buffer, size_t count){
	sscanf(buffer, "%d %d", &temp, &hum);
	return 0;
}

DEVICE_ATTR(oduino_sensor, 0644, sensorShow, sensorStore);



static int __init oduinoSensor_init(void){
	
	oduinoSensor = platform_device_register_simple("oduinoSensor", -1, NULL, 0);
	if(IS_ERR(oduinoSensor)){
		printk("oduinoSensor_init : error during platfrom device register\n");
	}

 	sysfs_create_file(&oduinoSensor->dev.kobj, &dev_attr_oduino_sensor.attr);	

	return 0;
	
}

static void __exit oduinoSensor_exit (void){

	sysfs_remove_file(&oduinoSensor->dev.kobj, &dev_attr_oduino_sensor.attr);
	platform_device_unregister(oduinoSensor);

	return;
}

module_init(oduinoSensor_init);
module_exit(oduinoSensor_exit);

MODULE_LICENSE("GPL");
