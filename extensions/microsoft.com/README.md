# How to setup Azure ecosystem

## Connect the UP to Azure cloud

* Start with dev essentials [program](https://www.visualstudio.com/cs/dev-essentials/) and activate Azure package
* Create iothub in your Azure portal
* Create device in the iothub that will represent IQRF GW - UP board
* Use Device explorer [app](https://github.com/Azure/azure-iot-sdk-csharp/releases) to connect to iothub
* Copy connection string from your Azure portal
* Generate SAS token using Device explorer - is used as password in MQTT [config](../../summits/workshop17/daemon-config/MqttMessaging.json)
* Update MQTT [config](../../summits/workshop17/daemon-config/MqttMessaging.json) in the iqrf-daemon
* Restart the daemon
