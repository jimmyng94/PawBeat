# Website Documentation
## Introduction
Website Link: https://tymonherzyk.github.io/PawPulseWeb/

The **PawPulse** website was created to function as an educational space for displaing projects in a professional manner. Using the **PubNub API** the website can also display data aquired from the **PawPulse** hardware in realtime, both visually and graphically. The website is responsive for smartphones and monitors. The following scripting languages were used to build the website:
* HTML
* CSS
* Javascript

## Files
- `index.html` : HTML page corresponding to the website's **Home** page.

- `projects.html` : HTML page corresponding to the website's **Project** page.

- `liveData.html` : HTML page corresponding to the website's **Live Data** page.

- `style.css` : CSS stylesheet that stores styling commands for all HTML pages.

## File Descriptions
### Index.html
The **index.html** file is a pure html file that defines the contents of the Home page for the PawPulse website. The file follows the standard html format:
```
<html>

  <head>
  </head>
  
  <body>
    <header></header>
    <main></main>
    <footer></footer>
   </body>
   
</html>   
```
The `<html></html>` tags contain all the HTML code.

The `<head></head>` tags contain information such as the title, metadata and stylesheet links.

The `<body></body>` tags contain all the content that is displayed on the page.

The `<header></header>` tags contain the top navigational menu.

The `<main></main>` tags contain the main content that is displayed.

The `<footer></footer>` tags contains the bottom navigational menu.


Information is split into several section classes:
```
<section class="title-banner">
<section class="index-banner1">
<section class="index-banner2">
```
Text is added into each section using the appropriate html tags, for example:
```
<h1>
<h2>
<p>
<a>
```
Sections and text are all sized and styled individually using the **style.css** file. 
### Projects
### Live Data
### Style


