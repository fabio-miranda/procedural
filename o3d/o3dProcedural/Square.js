


function CreateSquareShape(material, pack, size, position_x, position_y, position_z){
	
	size = size || 1.0;
	position_x = position_x || 0;
	position_y = position_y || 0;
	position_z = position_z || 0;
	
	
	//==================================
	//==================================
	// Create a Shape object for the mesh.
	//==================================
	//==================================
	var shape = pack.createObject('Shape');

	// Create the Primitive that will contain the geometry data for
	// the cube.
	var patchPrimitive = pack.createObject('Primitive');

	// Create a StreamBank to hold the streams of vertex data.
	var streamBank = pack.createObject('StreamBank');

	// Assign the material that was passed in to the primitive.
	patchPrimitive.material = material;

	// Assign the Primitive to the Shape.
	patchPrimitive.owner = shape;

	// Assign the StreamBank to the Primitive.
	patchPrimitive.streamBank = streamBank;

	// The cube is made of 12 triangles. There's eight vertices in total which
	// are shared between the face triangles.
	patchPrimitive.primitiveType = g_o3d.Primitive.TRIANGLELIST;
	patchPrimitive.numberPrimitives = 2;
	patchPrimitive.numberVertices = 4;
	
	
	var positionArray = [
	-0.5*size + position_x, -0.5*size + position_y,  0.5*size + position_z,  // vertex 0
	 0.5*size + position_x, -0.5*size + position_y,  0.5*size + position_z,  // vertex 1
	 0.5*size + position_x,  0.5*size + position_y,  0.5*size + position_z,  // vertex 2
	-0.5*size + position_x,  0.5*size + position_y,  0.5*size + position_z  // vertex 3
	];
	var indicesArray = [
	  0, 1, 2,  // face 1
	  2, 3, 0
	];

	// Create buffers containing the vertex data.
	var positionsBuffer = pack.createObject('VertexBuffer');
	var positionsField = positionsBuffer.createField('FloatField', 3);
	positionsBuffer.set(positionArray);

	var indexBuffer = pack.createObject('IndexBuffer');
	indexBuffer.set(indicesArray);

	// Associate the positions Buffer with the StreamBank.
	streamBank.setVertexStream(
	  g_o3d.Stream.POSITION, // semantic: This stream stores vertex positions
	  0,                     // semantic index: First (and only) position stream
	  positionsField,        // field: the field this stream uses.
	  0);                    // start_index: How many elements to skip in the
							 //     field.

	// Associate the triangle indices Buffer with the primitive.
	patchPrimitive.indexBuffer = indexBuffer;
	//==================================
	//==================================
	
	
	//==================================
	//==================================
	//========Creates texture===========
	//==================================
	//==================================
	var texCoordsArray = [0, 0,
						  1, 0,
						  1, 1,
						  0, 1];
	
	var texCoordsBuffer = pack.createObject('VertexBuffer');
	var texCoordsField = texCoordsBuffer.createField('FloatField', 2);
	texCoordsBuffer.set(texCoordsArray);
	
	streamBank.setVertexStream(
	   g_o3d.Stream.TEXCOORD,  // semantic
	   0,                      // semantic index
	   texCoordsField,         // field
	   0);                     // start_index
	//==================================
	//==================================
	
	
	return patchPrimitive;
	
	
}

