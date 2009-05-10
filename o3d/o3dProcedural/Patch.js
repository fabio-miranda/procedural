

function Patch(patchParentNode, heightmapParentNode, numIterations, size, position_x, position_y, position_z){
	this.position = [position_x, position_y, position_z];
	this.size = size;
	this.primitive = null;
	this.heightmap = null;
	this.parentNode = patchParentNode;
	this.heightmap = new Heightmap(heightmapParentNode, numIterations, size);
	this.sampler = null;
	
	this.create = Patch_create;
	this.createMaterial = Patch_createMaterial;
	
	
	this.create();
	
	
}

function Patch_createMaterial(){
	
	//Effects
	var effect = g_pack.createObject('Effect');
	o3djs.effect.loadEffect(effect, 'renderPatch.shader');
	
	
	
	//Material
	var material = g_pack.createObject('Material');
	material.drawList = g_patchViewInfo.performanceDrawList;
	material.effect = effect;
	
	
	//Pass the heightmap texture to the shader
	effect.createUniformParameters(material);
	//var samplerParam = material.getParam('heightmap');
	//this.sampler = g_pack.createObject('Sampler');
	//this.sampler.texture = this.heightmap.texture2;
	//samplerParam.value = this.sampler;
	//var aux = [0.0, 0.0];
	material.getParam('heightmap').value = this.heightmap.texture2.get(0);
	
	return material
	
}

function Patch_create(){
	//Node
	patchTransform = g_pack.createObject('Transform');
	
	//this.heightmap = new Heightmap(this.heightmapParentNode);
	var material = this.createMaterial();
	this.primitive = CreateSquareShape(material, g_pack, this.size, this.position[0], this.position[1], this.position[2]);
	
	//==================================
	//==================================
	//====Parent to the parentNode======
	//==================================
	//==================================
	// Parent the Shape under the transform.
	patchTransform.addShape(this.primitive.owner);

	// Parent the cube's transform to the client root.
	patchTransform.parent = this.parentNode;

	// Generate the draw elements for the cube shape.
	this.primitive.owner.createDrawElements(g_pack, null);
	//==================================
	//==================================
	
	
	
	
	
	
}


