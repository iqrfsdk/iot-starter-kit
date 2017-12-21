# IBM Cloud

## Connect the IQRF gateway to IBM Cloud

[![IoT Starter Kit - Part3: IBM Cloud](https://img.youtube.com/vi/wka40rh9ZUc/0.jpg)](https://www.youtube.com/watch?v=wka40rh9ZUc "IoT Starter Kit - Part3: IBM Cloud")

## How to start with IBM Bluemix cloud platform

Steps:

- Go to www.bluemix.net and click to Create a free account
- Fill in email, name, country, phone number and password
- Click to Create account, respond on email sent during registration
- You find confirmation for the account in your email

# IBM Bluemix

Steps:

- Go to Catalog -> Boilerplates -> Internet of Things Platform Starter
- Fill in App name and push Create
    It will create you Coudant Databaze, Watson IoT Platform and Node-RED
    You will find all what do you create in the Dashboard

# Watson IoT Platform

Steps:

- Go to your Watson IoT Platform and press Launch
- Devices -> Add Device -> Create Device Type and fill all the information
    Create Device Type and Device - at the and it will show you Token (Remember your token you will need it!)
    After you create this device go to Apps -> Generate API Key - Copy your API key and Token (Remember your token you will need it!)

# Node-RED (Cloud Foundry Apps)

Steps:

- Go to your Node-RED and import there Dashboard.json and Node-RED-cloud.json
- IBM IoT Out Node - fill all info 
     Authentication -> API Key
     Output Type -> Device Event
     Device Type -> {your device type / from Device}
     Device Id -> {your device ID / from Device}
     Event Type -> {IQRF}
     Format -> json
     Data  -> msg.payload
     
  Edit API Key 
     API Key -> {your API Key / form Apps}
     API Token -> {your API Token / form Apps}
     
# Watson IoT Platform

Steps:

- Go back to your Watson IoT Platform
- Devices -> click on your device and now you will see the data from your device there (you have to also see the data in Node-RED Debug flow)
- when you see the data you can also create a dashboards in your Watson IoT Platform
     Boards -> Create new Board -> Add new Card -> Choose Card type and fill the data which you want to visualize
     
     
     





