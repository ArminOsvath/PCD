# PCD
Barbu Jonel + Osvath Armin


Prerequisites: make
sudo apt-get install python3-pip
pip3 install opencv-python

How to run:

  0) You must be in the same directory as the makefile file 
  1) Open 2 terminals
  2) In either run the command `make`
  3) In one terminal run `make runs`
  4) In the other terminal run `make runa`

It works like this:
  make runs calls 
    serevr/server
  make runa calls 
  	client/client -I unnamed.jpg -v 1 -b -B -c -e -G -g -h -m -s
  
  Client:
  the client sends the image name then a processed struct of the argument
  then it sets it's paths and writes the picture: opens the image, gets the size, writes the size and writes the content of the image; Not yet implemented: receiving the images back;

  Server:
  server receives the img name and the processed structure of the filters, then sets up the paths and reads the picture, the size of the picture then writes the content of the picture; 
  Then the server forks myFilter.filtersize amount of times executing the scripts for each filter;
  the main function waits for the children to finish; Not yet implemented (mydirs) getting the output images from a folder and writing it to the client

