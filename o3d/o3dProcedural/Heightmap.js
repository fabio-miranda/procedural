
var RENDER_TARGET_WIDTH = 128;
var RENDER_TARGET_HEIGHT = 128;

function Heightmap(parentNode){
	this.shape = null;
	this.heightTexture = null;
	this.transform = null
	this.parentNode = parentNode;
	this.viewInfo = null
	this.timeParan = 0;
	
	this.create = Heightmap_create;
	this.createMaterial = Heightmap_createMaterial;
	this.createTexture = Heightmap_createTexture;
	
	this.create();
	
}

function Heightmap_createMaterial(){
	
	//Effects
	var effect = g_pack.createObject('Effect');
	o3djs.effect.loadEffect(effect, 'calculateHeightmap.shader');
	
	//Material
	var material = g_pack.createObject('Material');
	material.drawList = this.viewInfo.performanceDrawList;
	//material.drawList = g_patchViewInfo.performanceDrawList;
	material.effect = effect;
	
	//Time parameter
	effect.createUniformParameters(material);
	this.timeParam = material.getParam('time');
	
	return material
	
}

function Heightmap_createTexture(){
	
	this.heightTexture = g_pack.createTexture2D(RENDER_TARGET_WIDTH,
                                         RENDER_TARGET_HEIGHT,
                                         g_o3d.Texture.XRGB8, 1, true);
										 
	
	this.renderSurface = this.heightTexture.getRenderSurface(0, g_pack);
	
	this.renderSurfaceSet = g_pack.createObject('RenderSurfaceSet');
	this.renderSurfaceSet.renderSurface = this.renderSurface;
	//this.renderSurfaceSet.renderDepthStencilSurface = depthSurface;
	
	
	this.renderNode = g_pack.createObject('RenderNode');
	this.renderNode.priority = 1;
	this.renderNode.parent = g_heightmapRenderRoot;
	
	this.renderSurfaceSet.parent = this.renderNode;
	
	
}


function Heightmap_create(){
	this.transform = g_pack.createObject('Transform');
	
	this.createTexture();
	
	
	this.viewInfo = o3djs.rendergraph.createBasicView(g_pack,
															g_heightmapRoot,
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
														
														
	var material = this.createMaterial();
	this.shape = CreateSquareShape(material, g_pack);
	
	
	//==================================
	//==================================
	//Create render target, so that the shader can write its result
	//==================================
	//==================================

	
	
	
	//==================================
	//==================================
	
	//==================================
	//==================================
	//====Parent to the parentNode======
	//==================================
	//==================================
	// Create a new transform and parent the Shape under it.
	//heightmapTransform = g_pack.createObject('Transform');
	this.transform.addShape(this.shape);

	// Parent the cube's transform to the client root.
	this.transform.parent = this.parentNode;
	
	// Generate the draw elements for the cube shape.
	this.shape.createDrawElements(g_pack, null);
	
	//this.transform.visible = true
	//this.transform.priority = 100;
	
	//==================================
	//==================================
	
	
}
