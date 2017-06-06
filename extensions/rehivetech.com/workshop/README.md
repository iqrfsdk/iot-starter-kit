![RehiveTech](/extensions/rehivetech.com/images/logo.png)

## 1. Install management on your Gateway

- Create an account at "https://management.rehivetech.com" and add your gateway to the management system. Follow the instructions [here](/extensions/rehivetech.com/README.md)
- Check if the gateway is in the system.

## 2. Run the actions

- Go to menu **Management -> Create new action ("+" icon)** and create an action to find out ethernet interface status ``ifconfig eth0``
- Run web terminal: **Monitoring -> (your device )-> tools -> create SSH Tunnel** to get to the system console.

## 3. Turn on IQRF daemon 

- Go to the device configuration **Monitoring -> (your device) -> Menu -> Configuration**, enable IQRF daemon and set refresh time to 10 seconds.
- Check if the IQRF information is in the device details.

## 4. Update DPA Handle Firmware

- Download DPA handler firmware ([CustomDpaHandler-ledg-blink.hex](/extensions/rehivetech.com/workshop/CustomDpaHandler-ledg-blink.hex), [CustomDpaHandler-no-blink.hex](/extensions/rehivetech.com/workshop/CustomDpaHandler-no-blink.hex)) and uppload them into the management system.
- Update DPA Handler by ``CustomDpaHandler-ledg-blink.hex`` in your nodes and let the Green LED blink on a node.
