# Setting up a Platforms
## clean OS (ubilinux3 / ubilinux4)
A set of commands that all install. [here](https://github.com/JoTioTech/IQRF-IoT/tree/master/install_script)


##  OS (ubilinux3 / ubilinux4) with installed IQRF Daemon and configuratio WebApp
### Run Docker 
Install Docker -> See the inspiration [here](https://gitlab.iqrf.org/open-source/iqrf-daemon/blob/master/DOCKER.md)

### Setup Node-RED ecosystem 
### docker_net
```Bash
sudo docker network create -d bridge --subnet 172.25.0.0/16 isolated_nw
```
### MQTT Broker
```Bash
sudo docker run -d --name mqtt -p 1883:1883 -p 9001:9001 --network=isolated_nw --ip=172.25.3.1 --restart=always eclipse-mosquitto 
```
### NodeRed
```Bash
sudo docker run -d -p 1880:1880 --restart=always --network=isolated_nw --ip=172.25.4.1 --name redgw jotio/iqrf_nr_iot:latest 
```
### configure NodeRed Flow
Open:
http://[IP address of UpBoard]:1880

Import the contents of this [file](https://gitlab.iqrf.org/open-source/iot-starter-kit/blob/master/extensions/jotio.cz/Nodered_Local_demo.json) into nodered. 



