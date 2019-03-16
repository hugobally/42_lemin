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
    .force("links",link_force);

// Add tick instructions: 

simulation.on("tick", tickActions);

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
