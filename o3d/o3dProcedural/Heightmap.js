
var RENDER_TARGET_WIDTH = 64;
var RENDER_TARGET_HEIGHT = 64;




function Heightmap(parentNode, numIterations, size){
	this.primitive = null;
	this.texture1 = null;
	this.texture2 = null;
	this.transform = null
	this.parentNode = parentNode;
	this.viewInfo = null;
	this.sampler = null;
	this.swap = false;
	this.clearTex1 = false;
	this.clearTex2 = false;
	this.materialCalculateHeightmap = null;
	this.materialClearTexture = null;
	
	this.size = size;
	this.numIterations = numIterations;
	this.currentIteration = 0;
	
	this.create = Heightmap_create;
	this.createTexture = Heightmap_createTexture;
	this.createMaterialClearTexture = Heightmap_createMaterialClearTexture;
	this.createMaterialCalculateHeightmap = Heightmap_createMaterialCalculateHeightmap;
	this.createView = Heightmap_createView;
	this.swapTextures = Heightmap_swapTextures;
	
	this.create();
	
}

function Heightmap_createMaterialClearTexture(){
	
	//Effects
	var effect = g_pack.createObject('Effect');
	o3djs.effect.loadEffect(effect, 'clearTexture.shader');
	
	//Material
	var material = g_pack.createObject('Material');
	material.drawList = this.viewInfo.performanceDrawList;
	//material.drawList = g_patchViewInfo.performanceDrawList;
	material.effect = effect;
	
	return material
	
}

function Heightmap_createMaterialCalculateHeightmap(){
	
	//Effects
	var effect = g_pack.createObject('Effect');
	o3djs.effect.loadEffect(effect, 'calculateHeightmap.shader');
	
	//Material
	var material = g_pack.createObject('Material');
	material.drawList = this.viewInfo.performanceDrawList;
	//material.drawList = g_patchViewInfo.performanceDrawList;
	material.effect = effect;
	
	//Pass the texture to the shader
	effect.createUniformParameters(material);
	var samplerParam = material.getParam('texSampler');
	this.sampler = g_pack.createObject('Sampler');
	this.sampler.texture = this.texture1;
	samplerParam.value = this.sampler;
	
	//Pass the permutation texture
	samplerParamPerm = material.getParam('permTexture');
	samplerPerm = g_pack.createObject('Sampler');
	samplerPerm.texture = g_permMatrix.texture;
	samplerParamPerm.value = samplerPerm;
	
	
	
	return material
	
}

function Heightmap_createTexture(){
	
	var texture = g_pack.createTexture2D(RENDER_TARGET_WIDTH,
                                         RENDER_TARGET_HEIGHT,
                                         g_o3d.Texture.XRGB8, 1, true);
	/*							 
	var canvas = g_pack.createObject('Canvas');
	canvas.setSize(RENDER_TARGET_WIDTH, RENDER_TARGET_HEIGHT);
	canvas.clear([1, 0, 0, 1]);
	
	canvas.copyToTexture(texture);
	*/
	return texture;
	
	
}

function Heightmap_createView(){
	
	this.viewInfo = o3djs.rendergraph.createBasicView(g_pack,
															this.parentNode,
															this.renderSurfaceSet,
															[1, 1, 1, 1]);
						
	this.viewInfo.drawContext.projection = g_math.matrix4.perspective(
																		g_math.degToRad(30), // 30 degree fov.
																		RENDER_TARGET_WIDTH / RENDER_TARGET_HEIGHT,
																		1,                  // Near plane.
																		5);              // Far plane.

	
	this.viewInfo.drawContext.view = g_math.matrix4.lookAt([0, 0, 2],  // eye
														[0, 0, 0],  // target
														[0, 1, 0]); // up
	
}

function Heightmap_swapTextures(){
	
	//Clear the two textures
	if(this.clearTex1 == false || this.clearTex2 == false){
		//alert('@');
		
		
		if(this.clearTex1 == false){
			this.clearTex1 = true;
			
			
			this.sampler.texture = this.texture2; //input
			this.renderSurfaceSet.renderSurface = this.texture2.getRenderSurface(0, g_pack); //output
			
			
		}
		
		else if(this.clearTex2 == false){
			this.clearTex2 = true;
			
			this.sampler.texture = this.texture1; //input
			this.renderSurfaceSet.renderSurface = this.texture1.getRenderSurface(0, g_pack); //output
		}
			
			
		if(this.clearTex1 == true && this.clearTex2 == true){
			this.primitive.material = this.materialCalculateHeightmap;

			
		}
	}
	//Swap
	else{
		//alert('1');
		if(this.currentIteration < this.numIterations){
			if (this.swap == true) {
				this.sampler.texture = this.texture1; //input
				this.renderSurfaceSet.renderSurface = this.texture2.getRenderSurface(0, g_pack); //output
				g_patch.sampler.texture = this.texture2;
				this.swap = false;
			}
			else{
				this.sampler.texture = this.texture2; //input
				this.renderSurfaceSet.renderSurface = this.texture1.getRenderSurface(0, g_pack); //output
				g_patch.sampler.texture = this.texture1;
				this.swap = true;
			}
			
			this.currentIteration++;
		}
	}
}


function Heightmap_create(){
	this.transform = g_pack.createObject('Transform');
	
	
	this.texture1 = this.createTexture();
	this.texture2 = this.createTexture();
	
	
	//==================================
	//==================================
	//Create render target, so that the shader can write its result
	//==================================
	//==================================
	this.renderSurface = this.texture2.getRenderSurface(0, g_pack);
	
	this.renderSurfaceSet = g_pack.createObject('RenderSurfaceSet');
	this.renderSurfaceSet.renderSurface = this.renderSurface;
	
	
	this.renderNode = g_pack.createObject('RenderNode');
	this.renderNode.priority = 1;
	this.renderNode.parent = g_heightmapRenderRoot;
	
	this.renderSurfaceSet.parent = this.renderNode;
	
														
	this.createView();									
	this.materialClearTexture = this.createMaterialClearTexture();
	this.materialCalculateHeightmap = this.createMaterialCalculateHeightmap();
	this.primitive = CreateSquareShape(this.materialClearTexture, g_pack);
	//==================================
	//==================================
	
	//==================================
	//==================================
	//====Parent to the parentNode======
	//==================================
	//==================================
	// Create a new transform and parent the Shape under it.
	//heightmapTransform = g_pack.createObject('Transform');
	this.transform.addShape(this.primitive.owner);

	// Parent the cube's transform to the client root.
	this.transform.parent = this.parentNode;
	
	// Generate the draw elements for the cube shape.
	this.primitive.owner.createDrawElements(g_pack, null);
	
	//this.transform.visible = true
	//this.transform.priority = 100;
	
	//==================================
	//==================================
	
	
}
