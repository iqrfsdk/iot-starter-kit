#!/bin/bash

LOCAL_FILE=configuration/MqttMessaging_azure.json

if [ -s "${LOCAL_FILE}" ]; then
	sudo cp configuration/MqttMessaging.json configuration/MqttMessaging_local.json
	sudo mv configuration/MqttMessaging_azure.json configuration/MqttMessaging.json
fi
