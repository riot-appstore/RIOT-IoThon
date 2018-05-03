### About

This example shows how to write IoT applications using javascript.

### Acknowledgement

This example is based on [Jerryscript](https://github.com/jerryscript-project/jerryscript) which does all the heavy lifting, providing full ECMAScript 5.1 profile on your IoT device (kudos guys!).

### Caveats

- currently, the only actual function available is "print"
- Implementation isn't really PR ready. This is meant to be a rough PoC. There are a few PRs against the main RIOT repo which implement some of the required functionality. (e.g. #7796, which implements the bindings for SAUL and CoAP.)

### How to use

1. Set up a 6LoWPAN border router. One option for this is using the "gnrc_border_router" example on a samr21-xpro. See the readme for how to set up the network.
2. Flash the "gcoap-server-printout" application on this branch onto a samr21-xpro. Run the application and get the global IPv6 address using ifconfig.
3. Change the IPv6 address near the bottom of the double_click.js file to be the address of the gcoap server node that you collected in step 2.
4. Run compile_js.sh, which will combine app_1.js, app_2.js, double_click.js, and service.js into one application, and then flash and run it. This application will send sensor data via serial to your terminal upon a single click; and will send click timing data via CoAP to the server node upon a double click.

Note: you may have to press `RESET` on the board (after the flash) if the board
reboots faster than the terminal program can start..
