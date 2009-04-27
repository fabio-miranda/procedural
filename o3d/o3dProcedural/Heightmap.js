
var RENDER_TARGET_WIDTH = 64;
var RENDER_TARGET_HEIGHT = 64;

function Heightmap(parentNode){
	this.shape = null;
	this.heightTexture = null;
	this.transform = null
	this.parentNode = parentNode;
	this.timeParan = 0;
	
	this.create = Heightmap_create;
	this.createMaterial = Heightmap_createMaterial;
	
	this.create();
	
}

function Heightmap_createMaterial(){
	
	//Effects
	var effect = g_heightmapPack.createObject('Effect');
	o3djs.effect.loadEffect(effect, 'calculateHeightmap.shader');
	
	//Material
	var material = g_heightmapPack.createObject('Material');
	material.drawList = g_heightmapViewInfo.performanceDrawList;
	material.effect = effect;
	
	//Time parameter
	effect.createUniformParameters(material);
	this.timeParam = material.getParam('time');
	
	return material
	
}


function Heightmap_create(){
	this.transform = g_heightmapPack.createObject('Transform');
	
	this.material = this.createMaterial();
	
	
	this.shape = CreateSquareShape(this.material, g_heightmapPack);
	
	
	//==================================
	//==================================
	//Create render target, so that the shader can write its result
	//==================================
	//==================================
	/*
	* UNKNOWN_FORMAT
	* XRGB8
	* ARGB8
	* GR16F
	* ABGR16F
	* R32F
	* GR32F
	* ABGR32F
	* DXT1
	* DXT3
	* DXT5
	 */
	
	this.heightTexture = g_heightmapPack.createTexture2D(RENDER_TARGET_WIDTH,
                                         RENDER_TARGET_HEIGHT,
                                         g_o3d.Texture.ABGR32F, 1, true);
										 
	var depthSurface = g_heightmapPack.createDepthStencilSurface(RENDER_TARGET_WIDTH,
                                                      RENDER_TARGET_HEIGHT);
										 
	
	this.renderSurface = this.heightTexture.getRenderSurface(0, g_heightmapPack);
	
	this.renderSurfaceSet = g_heightmapPack.createObject('RenderSurfaceSet');
	this.renderSurfaceSet.renderSurface = this.renderSurface;
	this.renderSurfaceSet.renderDepthStencilSurface = depthSurface;
	this.renderSurfaceSet.parent = g_heightmapRenderRoot;
	
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
	this.shape.createDrawElements(g_heightmapPack, null);
	
	//this.transform.visible = true
	//this.transform.priority = 100;
	
	//==================================
	//==================================
	
	
}
