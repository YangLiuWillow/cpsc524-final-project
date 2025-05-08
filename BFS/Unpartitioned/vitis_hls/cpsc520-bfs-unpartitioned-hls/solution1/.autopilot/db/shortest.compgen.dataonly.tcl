# This script segment is generated automatically by AutoPilot

set axilite_register_dict [dict create]
set port_control {
column_indices { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 16
	offset_end 27
}
row_offsets { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 28
	offset_end 39
}
visited { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 40
	offset_end 51
}
queue { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 52
	offset_end 63
}
}
dict set axilite_register_dict control $port_control


set port_sqrt {
src { 
	dir I
	width 32
	depth 1
	mode ap_none
	offset 16
	offset_end 23
}
}
dict set axilite_register_dict sqrt $port_sqrt


