import sys
import coolfluid as cf

env = cf.Core.environment()
env.log_level = 4
env.only_cpu0_writes = True

root = cf.Core.root()
domain = root.create_component('Domain', 'cf3.mesh.Domain')
mesh = domain.create_component('mesh','cf3.mesh.Mesh')


blocks = root.create_component('model', 'cf3.mesh.BlockMesh.BlockArrays')
points = blocks.create_points(dimensions = 2, nb_points = 4)
points[0]  = [0., 0.]
points[1]  = [1., 0.]
points[2]  = [1., 1.]
points[3]  = [0., 1.]
block_nodes = blocks.create_blocks(1)
block_nodes[0] = [0, 1, 2, 3]
block_subdivs = blocks.create_block_subdivisions()
block_subdivs[0] = [40,20]
gradings = blocks.create_block_gradings()
gradings[0] = [1., 1., 1., 1.]
blocks.create_patch_nb_faces(name = 'bottom', nb_faces = 1)[0] = [0, 1]
blocks.create_patch_nb_faces(name = 'right', nb_faces = 1)[0] = [1, 2]
blocks.create_patch_nb_faces(name = 'top', nb_faces = 1)[0] = [2, 3]
blocks.create_patch_nb_faces(name = 'left', nb_faces = 1)[0] = [3, 0]
# blocks.extrude_blocks(positions=[1.], nb_segments=[20], gradings=[1.])
# blocks.partition_blocks(nb_partitions = 4, direction = 0)
# blocks.partition_blocks(nb_partitions = 2, direction = 1)
blocks.partition_blocks(nb_partitions = cf.Core.nb_procs(), direction = 1)
blocks.create_mesh(mesh.uri())

make_par_data = root.create_component('MakeParData', 'cf3.solver.actions.ParallelDataToFields')
make_par_data.mesh = mesh
make_par_data.execute()

outfile = cf.URI('cf3test.cf3mesh')
domain.write_mesh(outfile)

reader = domain.create_component('CF3MeshReader', 'cf3.mesh.cf3mesh.Reader')
reader.mesh = domain.create_component('ReadBackMesh','cf3.mesh.Mesh')
reader.file = outfile
reader.execute()

reader.mesh.print_tree()

differ = domain.create_component('Differ', 'cf3.common.ArrayDiff')
differ.left = mesh.geometry.children.global_indices
differ.right = reader.mesh.geometry.children.global_indices
differ.execute()

mesh.delete_component()
domain.write_mesh(cf.URI('cf3mesh_read.pvtu'))