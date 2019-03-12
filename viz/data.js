var nodes_data = [
	{"name": "SOURCE", "x": 1, "y": 1, "type": 1},
	{"name": "A", "x": 2, "y": 2, "type": 0},
	{"name": "B", "x": 3, "y": 3, "type": 0},
	{"name": "C", "x": 4, "y": 4, "type": 0},
	{"name": "D", "x": 5, "y": 5, "type": 0},
	{"name": "E", "x": 6, "y": 6, "type": 0},
	{"name": "F", "x": 7, "y": 7, "type": 0},
	{"name": "G", "x": 8, "y": 8, "type": 0},
	{"name": "SINK", "x": 9, "y": 9, "type": 2}
	//
]


var links_data = [
	{"source": "SOURCE", "target": "A"},
	{"source": "SOURCE", "target": "B"},
	{"source": "A", "target": "C"},
	{"source": "C", "target": "A"},
	{"source": "B", "target": "E"},
	{"source": "E", "target": "B"},
	{"source": "B", "target": "D"},
	{"source": "D", "target": "B"},
	{"source": "C", "target": "D"},
	{"source": "D", "target": "C"},
	{"source": "E", "target": "F"},
	{"source": "F", "target": "E"},
	{"source": "F", "target": "G"},
	{"source": "G", "target": "F"},
	{"source": "G", "target": "SINK"},
	{"source": "D", "target": "SINK"}
]

var turns_data = [
	[
		{"source": "E", "target": "B"},
		{"source": "B", "target": "D"},
		{"source": "D", "target": "B"},
		{"source": "C", "target": "D"},
		{"source": "D", "target": "C"},
	],
	[
		{"source": "E", "target": "B"},
		{"source": "B", "target": "D"},
		{"source": "D", "target": "B"},
		{"source": "C", "target": "D"},
		{"source": "D", "target": "C"},
	]
]
