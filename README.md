# CoalStar-EventManagement
## The system used in the CoalStar/CoalSpark Engine which handles inputs, reports, and many other state changes.

The CoalStar/CoalSpark event management system is designed to grab SDL input events, window events, and mouse events. It should also handle report loggin for engine events, and handle an actionable event system for threadsync events, pre-workload update events, and other such fun times.

For report logging, the management system will output any reports of greater severity than "Warning". In the provided setup, at close it will print out a list of logged reports to the file in the current directory: "logfile.txt".

The code herein is placed under the "Zlib license", and is persuant to that licensure of licensation.
