# termik
Open source GUI terminal for data transmission via serial or network based on [Qt](https://www.qt.io/). The project can be compiled for Linux, Mac and also Windows or whatever Qt supports.

I made this app, cause none of the available terminals for data transmission does not suits my needs.

## usage
Everything is done using shortcuts which is shown after pressing F1.
Transmit data in the terminal is done by pressing Enter.


## features
* Communication via serial or network (TCP/UDP)
* Terminal input and output is supported in ASCII, HEX and DEC data formats
* Option of of app runing from CLI with configuration arguments and possible auto connection to a device
* Logging into txt file
* Logging time of events
* Option of prefix and suffix added to every transmitted data
* Script of Tx data supported, where each line of a file is transmitted with adjustable period in repetitive or single shot mode
* autoscan of all devices in the network



## todo:
	* autoclear not finished
	* tweak NetworkWorker class
	* save/read configuration to json file is not finished
	* network Protocol add to config json save file
	* make handle app arguments class and operate it to in the function main()