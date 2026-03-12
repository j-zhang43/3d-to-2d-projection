import bpy

file_name = ".../inputs_blender.txt"

obj = bpy.context.active_object
if obj and obj.type == 'MESH': 
    depsgraph = bpy.context.evaluated_depsgraph_get()
    obj_eval = obj.evaluated_get(depsgraph)
    mesh_data = obj_eval.to_mesh()

    with open(file_name, 'w') as f:
        
        f.write(f"{len(mesh_data.vertices)}\n")
        for v in mesh_data.vertices:
            f.write(f"{v.co.x} {v.co.y} {v.co.z} \n")
            
        f.write(f"{len(mesh_data.edges)}\n")
        for e in mesh_data.edges:
            v1, v2 = e.vertices
            f.write(f"{v1} {v2} \n")