// Add encompassing group for the zoom 

var g = svg.append("g")
    	     .attr("class", "everything");

// Draw link lines

var link = g.append("g")
	      .attr("class", "links")
	    .selectAll("line")
	    .data(links_data)
	    .enter()
	    .append("line")
	      .attr("stroke-width", 50) // default 2
	      .style("stroke", "gray");        

// Draw node circles

var nodeRadius = 25;
var emphasizedNodeRadius = 300;

var node = g.append("g")
              .attr("class", "nodes") 
            .selectAll("circle")
            .data(nodes_data)
            .enter()
			.append("circle")
			  .attr("id", d => {return d.name})
			  .attr("r", getCircleRadius)
           	  .attr("fill", circleColour);

d3.selectAll("circle")
			.filter((d) => {return (d.type != 0)})
			.style("fill-opacity", 1);

// Get circle color from node data

function getCircleRadius(d)
{
		if (d.type != 0)
				return (emphasizedNodeRadius);
		else
				return (nodeRadius);
}

function circleColour(d)
{
	if (d.type == 1)
	    return "white";
	else if (d.type == 2)
	    return "white";
	else
	    return ("#848581");
}