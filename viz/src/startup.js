// Get svg size and hangle resizing

var get_svg = document.getElementById("viz"),
	get_html = document.getElementsByTagName("html")[0];

var resize_svg = () => {
	get_svg.setAttribute("width", get_html.clientWidth - 20);
	get_svg.setAttribute("height", get_html.clientHeight - 20);
}

window.addEventListener('resize', resize_svg);
resize_svg();

// Create svg canvas

var svg = d3.select("svg"),
    width = +svg.attr("width"),
    height = +svg.attr("height");
