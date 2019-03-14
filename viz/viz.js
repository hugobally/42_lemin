// Handle window resizing

var get_svg = document.getElementById("viz"),
	get_html = document.getElementsByTagName("html")[0];

var resize_svg = () => {
	get_svg.setAttribute("width", get_html.clientWidth - 20);
	get_svg.setAttribute("height", get_html.clientHeight - 20);
}

resize_svg();

window.addEventListener('resize', resize_svg);

// Graph is stored inside svg

var svg = d3.select("svg"),
    width = +svg.attr("width"),
    height = +svg.attr("height");
    
console.log(svg.attr("width"));

var radius = 15; 

// Set up the simulation and add forces  

var simulation = d3.forceSimulation()
					.nodes(nodes_data);
                              
var link_force =  d3.forceLink(links_data)
                        .id(function(d) { return d.name; });            
         
var charge_force = d3.forceManyBody()
    .strength(-10);  // Default : -100
    
var center_force = d3.forceCenter(width / 2, height / 2);  

simulation
    .force("charge_force", charge_force)
    .force("center_force", center_force)
    .force("links",link_force)
;

// Add tick instructions: 

simulation.on("tick", tickActions);

// Add encompassing group for the zoom 

var g = svg.append("g")
    .attr("class", "everything");

// Draw link lines

var link = g.append("g")
      .attr("class", "links")
    .selectAll("line")
    .data(links_data)
    .enter().append("line")
      .attr("stroke-width", 2)
      .style("stroke", linkColour);        

// Draw node circles

var node = g.append("g")
        .attr("class", "nodes") 
        .selectAll("circle")
        .data(nodes_data)
        .enter()
        .append("circle")
        .attr("r", d => (radius + ((d.type == "1") * radius)))
        .attr("fill", circleColour);
 
// Emphasize start and end

// Add drag capabilities  

var drag_handler = d3.drag()
	.on("start", drag_start)
	.on("drag", drag_drag)
	.on("end", drag_end);	
	
drag_handler(node);

// Add zoom capabilities 

var zoom_handler = d3.zoom()
    .on("zoom", zoom_actions);

zoom_handler(svg);     

/** Functions **/

// Function to choose what color circle we have

function circleColour(d){
	if (d.type == 1){
		return "red";
	}
	else if (d.type == 2){
		return "red";
	}
	else{
		return "beige";
	}
}

// Function to choose the line colour and thickness 

function linkColour(d){
		return "beige";
}

// Drag functions [d is current node]

function drag_start(d) {
 if (!d3.event.active) simulation.alphaTarget(0.3).restart();
    d.fx = d.x;
    d.fy = d.y;
}

function drag_end(d) {
  if (!d3.event.active) simulation.alphaTarget(0);
  d.fx = null;
  d.fy = null;
}

// Makes sure you can't drag the circle outside the box

function drag_drag(d) {
  d.fx = d3.event.x;
  d.fy = d3.event.y;
}

//Zoom functions 
function zoom_actions(){
    g.attr("transform", d3.event.transform)
}

function tickActions() {
    //update circle positions each tick of the simulation 
       node
        .attr("cx", function(d) { return d.x; })
        .attr("cy", function(d) { return d.y; });
        
    //update link positions 
    link
        .attr("x1", function(d) { return d.source.x; })
        .attr("y1", function(d) { return d.source.y; })
        .attr("x2", function(d) { return d.target.x; })
        .attr("y2", function(d) { return d.target.y; });
} 

//  Handle Keyboard
/*
document.addEventListener('keydown', (event) => {
	//const keyName = event.key;
}, false);
*/
