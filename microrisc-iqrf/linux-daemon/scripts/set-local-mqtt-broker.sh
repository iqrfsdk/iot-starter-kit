#!/bin/bash

LOCAL_FILE=configuration/MqttMessaging_local.json

if [ -s "${LOCAL_FILE}" ]; then
	sudo cp configuration/MqttMessaging.json configuration/MqttMessaging_azure.json
	sudo mv configuration/MqttMessaging_local.json configuration/MqttMessaging.json
fi
