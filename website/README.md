# Website Documentation

Website Link: https://tymonherzyk.github.io/PawPulseWeb/

The **PawPulse** website was created to function as an educational space for displaing projects in a professional manner. Using the **PubNub API** the website can also display data aquired from the **PawPulse** hardware in realtime, both visually and graphically. The website is responsive for smartphones and monitors with built-in layouts for each type. The following scripting languages were used during the construction of the website:
* HTML
* CSS
* Javascript

## Files
- `index.html` : HTML page corresponding to the website's **Home** page.

- `projects.html` : HTML page corresponding to the website's **Project** page.

- `liveData.html` : HTML page corresponding to the website's **Live Data** page.

- `style.css` : CSS stylesheet that stores styling commands for all HTML pages.

## File Descriptions
### Index
The **index.html** file is a pure html file that defines the content of the Home page for the PawPulse website. The file follows the standard html format:
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
The `<head></head>` tags contain information such as the title, metadata and stylesheet links.

The `<body></body>` tags contain information that will be displayed on the website.

Information is split into several section classes:
```
<section class="title-banner">
<section class="index-banner1">
<section class="index-banner2">
```
Each section can be sized and styled within the style.css stylesheet.

Text is added into each section using the appropriate html tags, for example:
```
<h1>
<h2>
<p>
<a>
```
### Projects
### Live Data
### Style


