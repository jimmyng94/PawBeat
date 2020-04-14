# Website Documentation
## Introduction
Website Link: https://tymonherzyk.github.io/PawPulseWeb/

The PawPulse website was created to function as an educational space for displaing projects in a professional manner. Using the PubNub API the website can also display data aquired from the PawPulse hardware in realtime, both visually and graphically. The website is responsive for smartphones and monitors. The following scripting languages were used to build the website:
* HTML
* CSS
* Javascript

## Files
- `index.html` : HTML page corresponding to the website's **Home** page.

- `projects.html` : HTML page corresponding to the website's **Project** page.

- `liveData.html` : HTML page corresponding to the website's **Live Data** page.

- `style.css` : CSS stylesheet that stores styling commands for all HTML pages.

## File Descriptions
### index.html
The index.html file is a pure HTML file that acts as the "Home" page for the PawPulse website. The page is split into several sections with images and text. The page also features a menu for navigating around the website. A guide explaining the code within this file and how you can create your own index.html is available [here](https://github.com/jimmyng94/PawPulse/wiki/Creating-a-HTML-web-page). This page is styled using the style.css file. 
### liveData.html
The liveData.html file is a HTML file with embedded JavaScript that can recieve and display data recieved from the PawPulse hardware in real-time. This file corresponds to the Live Data page for the PawPulse website. The file utilises the PubNub API in order to aquire the data in real-time and uses EON charts to display this data. A guide explaining how PubNub and EON can be used for displaying data in real-time is available [here](https://github.com/jimmyng94/PawPulse/wiki/Displaying-data-in-real-time-using-the-PubNub-API). The HTML aspect of this page are styled using the style.css file. 
### style.css
The style.css file is a pure CSS file that holds all the styling commands for the HTML in both index.html and liveData.html. A guide explaining how the file was built and how you can create your own CSS styling file is available [here](https://github.com/jimmyng94/PawPulse/wiki/styling-using-CSS).

