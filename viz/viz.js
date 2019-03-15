// Color Array

var color_array = [
    "#63b598", "#ce7d78", "#ea9e70", "#a48a9e", "#c6e1e8", "#648177" ,"#0d5ac1" ,
    "#f205e6" ,"#1c0365" ,"#14a9ad" ,"#4ca2f9" ,"#a4e43f" ,"#d298e2" ,"#6119d0",
    "#d2737d" ,"#c0a43c" ,"#f2510e" ,"#651be6" ,"#79806e" ,"#61da5e" ,"#cd2f00" ,
    "#9348af" ,"#01ac53" ,"#c5a4fb" ,"#996635","#b11573" ,"#4bb473" ,"#75d89e" ,
    "#2f3f94" ,"#2f7b99" ,"#da967d" ,"#34891f" ,"#b0d87b" ,"#ca4751" ,"#7e50a8" ,
    "#c4d647" ,"#e0eeb8" ,"#11dec1" ,"#289812" ,"#566ca0" ,"#ffdbe1" ,"#2f1179" ,
    "#935b6d" ,"#916988" ,"#513d98" ,"#aead3a", "#9e6d71", "#4b5bdc", "#0cd36d",
    "#250662", "#cb5bea", "#228916", "#ac3e1b", "#df514a", "#539397", "#880977",
    "#f697c1", "#ba96ce", "#679c9d", "#c6c42c", "#5d2c52", "#48b41b", "#e1cf3b",
    "#5be4f0", "#57c4d8", "#a4d17a", "#225b8", "#be608b", "#96b00c", "#088baf",
    "#f158bf", "#e145ba", "#ee91e3", "#05d371", "#5426e0", "#4834d0", "#802234",
    "#6749e8", "#0971f0", "#8fb413", "#b2b4f0", "#c3c89d", "#c9a941", "#41d158",
    "#fb21a3", "#51aed9", "#5bb32d", "#807fb", "#21538e", "#89d534", "#d36647",
    "#7fb411", "#0023b8", "#3b8c2a", "#986b53", "#f50422", "#983f7a", "#ea24a3",
    "#79352c", "#521250", "#c79ed2", "#d6dd92", "#e33e52", "#b2be57", "#fa06ec",
    "#1bb699", "#6b2e5f", "#64820f", "#1c271", "#21538e", "#89d534", "#d36647",
    "#7fb411", "#0023b8", "#3b8c2a", "#986b53", "#f50422", "#983f7a", "#ea24a3",
    "#79352c", "#521250", "#c79ed2", "#d6dd92", "#e33e52", "#b2be57", "#fa06ec",
    "#1bb699", "#6b2e5f", "#64820f", "#1c271", "#9cb64a", "#996c48", "#9ab9b7",
    "#06e052", "#e3a481", "#0eb621", "#fc458e", "#b2db15", "#aa226d", "#792ed8",
    "#73872a", "#520d3a", "#cefcb8", "#a5b3d9", "#7d1d85", "#c4fd57", "#f1ae16",
    "#8fe22a", "#ef6e3c", "#243eeb", "#1dc18", "#dd93fd", "#3f8473", "#e7dbce",
    "#421f79", "#7a3d93", "#635f6d", "#93f2d7", "#9b5c2a", "#15b9ee", "#0f5997",
    "#409188", "#911e20", "#1350ce", "#10e5b1", "#fff4d7", "#cb2582", "#ce00be",
    "#32d5d6", "#17232", "#608572", "#c79bc2", "#00f87c", "#77772a", "#6995ba",
    "#fc6b57", "#f07815", "#8fd883", "#060e27", "#96e591", "#21d52e", "#d00043",
    "#b47162", "#1ec227", "#4f0f6f", "#1d1d58", "#947002", "#bde052", "#e08c56",
    "#28fcfd", "#bb09b", "#36486a", "#d02e29", "#1ae6db", "#3e464c", "#a84a8f",
    "#911e7e", "#3f16d9", "#0f525f", "#ac7c0a", "#b4c086", "#c9d730", "#30cc49",
    "#3d6751", "#fb4c03", "#640fc1", "#62c03e", "#d3493a", "#88aa0b", "#406df9",
    "#615af0", "#4be47", "#2a3434", "#4a543f", "#79bca0", "#a8b8d4", "#00efd4",
    "#7ad236", "#7260d8", "#1deaa7", "#06f43a", "#823c59", "#e3d94c", "#dc1c06",
    "#f53b2a", "#b46238", "#2dfff6", "#a82b89", "#1a8011", "#436a9f", "#1a806a",
    "#4cf09d", "#c188a2", "#67eb4b", "#b308d3", "#fc7e41", "#af3101", "#ff065",
    "#71b1f4", "#a2f8a5", "#e23dd0", "#d3486d", "#00f7f9", "#474893", "#3cec35",
    "#1c65cb", "#5d1d0c", "#2d7d2a", "#ff3420", "#5cdd87", "#a259a4", "#e4ac44",
    "#1bede6", "#8798a4", "#d7790f", "#b2c24f", "#de73c2", "#d70a9c", "#25b67",
    "#88e9b8", "#c2b0e2", "#86e98f", "#ae90e2", "#1a806b", "#436a9e", "#0ec0ff",
    "#f812b3", "#b17fc9", "#8d6c2f", "#d3277a", "#2ca1ae", "#9685eb", "#8a96c6",
    "#dba2e6", "#76fc1b", "#608fa4", "#20f6ba", "#07d7f6", "#dce77a", "#77ecca"]

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
    
var radius = 3; 

// Set up the simulation and add forces  

var simulation = d3.forceSimulation()
					.nodes(nodes_data);
                              
var link_force =  d3.forceLink(links_data)
                        .id(function(d) { return d.name; });            
         
var charge_force = d3.forceManyBody()
    .strength(-1000);  // Default : -100
    
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
        .attr("r", d => (radius + ((d.type != "0") * radius)))
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
		return "blue";
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
		return "gray";
}

// Drag functions [d is current node]

function drag_start(d) {
    if (!d3.event.active) simulation.alphaTarget(0.3).restart();
        d.fx = d.x;
        d.fy = d.y;
}

function drag_end(d) {
  if (!d3.event.active) simulation.alphaTarget(0);
  d.fx = d.x;
  d.fy = d.y;
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


// Model moves every turn


var turnDuration = 300;
var zoomDuration = 1000;

function executeTurn(i, j, movesGroup) {

    var source = d3.selectAll("circle")
                    .filter((d) => {if (d) return d.name == turns_data[i][j].source});

    var target = d3.selectAll("circle")
                    .filter((d) => {if (d) return d.name == turns_data[i][j].target});

    var circleMove = movesGroup.append("circle")
                    .attr("class", "move")
                    .attr("cx", source.attr("cx"))
                    .attr("cy", source.attr("cy"))
                    .attr("r", 10)
                    .attr("fill", "white");

    d3.selectAll("line")
        .filter((d) => {return d.source.name == source.name})
          .remove();

    circleMove.transition()
                    .duration(turnDuration)
                    .attr("cx", target.attr("cx"))
                    .attr("cy", target.attr("cy"))

  }
  
function sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}

async function runTurnsModel () {

        var movesGroup;

        simulation.stop();
        zoomFit(zoomDuration);
        await(sleep(zoomDuration));

        movesGroup = g.append("g")
                        .attr("id", "movesGroup")
                        .lower();//temporary fix
        
        d3.selectAll(".links").lower();

        for (var i = 0; i < turns_data.length; i++) {
            for (var j = 0; j < turns_data[i].length; j++) {
                executeTurn(i, j, movesGroup);
            }
            await(sleep(turnDuration));
            d3.selectAll(".move").remove();
        }
}

document.addEventListener('keydown', (event) => {
    const keyName = event.key;
  
    if (keyName === ' ') {
        runTurnsModel();
    }
  }, false);

// Zoom on all nodes

var root = d3.select("svg");

function lapsedZoomFit(ticks, transitionDuration) {
    for (var i = ticks || 100; i > 0; --i) force.tick();
    force.stop();
    zoomFit(transitionDuration);
}

function zoomFit(transitionDuration) {
    var bounds = root.node().getBBox();
    var parent = root.node().parentElement;
    var fullWidth = parent.clientWidth || parent.parentNode.clientWidth,
        fullHeight = parent.clientHeight || parent.parentNode.clientHeight;
    var width = bounds.width,
        height = bounds.height;
    var midX = bounds.x + width / 2,
        midY = bounds.y + height / 2;
    if (width == 0 || height == 0) return; // nothing to fit
    var scale = 0.85 / Math.max(width / fullWidth, height / fullHeight);
    var translate = [fullWidth / 2 - scale * midX, fullHeight / 2 - scale * midY];

    console.trace("zoomFit", translate, scale);

    var transform = d3.zoomIdentity
        .translate(translate[0], translate[1])
        .scale(scale);

    root
        .transition()
        .duration(transitionDuration || 0) // milliseconds
        .call(zoom_handler.transform, transform);
}