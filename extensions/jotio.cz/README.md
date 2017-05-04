# Setting up a Platforms

# Run Docker 
Install Docker -> See the inspiration [here](https://github.com/iqrfsdk/iqrf-daemon/blob/master/DOCKER.md)

# Setup Node-RED ecosystem 
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
sudo docker run -d -p 1880:1880 --restart=always --name redgw nodered/node-red-docker
sudo docker network connect isolated_nw redgw
docker exec -it redgw /bin/bash
npm i node-red/node-red-dashboard
```
### configure NodeRed Flow


# Setup Azure ecosystem 
### docker_net
```javascript
// Convert Hex value to integer.
function main(hexValue) {
    return parseInt(hexValue, 16);
}
```
### MQTT Broker
```sql
SELECT
    *
     ,UDF.hex2Int(Substring (response,25,2)) AS Temperature
     ,UDF.hex2Int(Substring (response,28,2)) AS Light
     ,UDF.hex2Int(Substring (response,31,2)) AS Potentiometer
INTO
    DataOUT
FROM
    DataIN
```

