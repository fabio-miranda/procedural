
o3djs.require('o3djs.util');
o3djs.require('o3djs.math');
o3djs.require('o3djs.camera');
o3djs.require('o3djs.rendergraph');
o3djs.require('o3djs.effect');
o3djs.require('o3djs.primitives');
o3djs.require('o3djs.canvas');


// global variables
var g_o3d;
var g_math;
var g_client;
var g_pack;
var g_clock = 0;
var g_timeMult = 1;
var g_patch;
var g_permMatrix;
var g_patchViewInfo;
var g_heightmapRenderRoot;
var p_patchRenderRoot;
var g_patchRoot;
var g_heightmapRoot;



function init() {

	window.g_finished = false;
	window.g_timeMult = 1;
	window.g_clock = 0;

	
	//o3djs.util.setMainEngine(o3djs.util.Engine.V8);
	o3djs.util.addScriptUri('');
	o3djs.util.makeClients(initStep2)
}

function uninit() {
	if (g_client) {
		g_client.cleanup();
	}
}


function initStep2(clientElements){
	
	var o3dElement = clientElements[0];
	window.g_client = g_client = o3dElement.client;
	g_o3d = o3dElement.o3d;
	g_math = o3djs.math;
	o3djs.base.init(o3dElement);
	g_pack = g_client.createPack();
	
	
	initGraph();
	initCamera();
	
	g_permMatrix = new PermMatrix();
	g_patch = new Patch(g_patchRoot, g_heightmapRoot, 1, 1.0, 0, 0, 0);
	
	g_client.setRenderCallback(renderCallback);
	
	
	//temp:
	//o3djs.event.addEventListener(o3dElement, 'mousedown', turnoffHeightmapShader);
	
	
		
	window.g_finished = true;

	


}

function initGraph(){
	
	g_patchRoot = g_pack.createObject('Transform');
	g_patchRoot.parent = g_client.root;
	g_heightmapRoot = g_pack.createObject('Transform');
	g_heightmapRoot.parent = g_client.root;
	
	g_patchRenderRoot = g_pack.createObject('RenderNode');
	g_patchRenderRoot.priority = 0;
	g_patchRenderRoot.parent = g_client.renderGraphRoot;
	
	g_heightmapRenderRoot = g_pack.createObject('RenderNode');
	g_heightmapRenderRoot.priority = 1;
	g_heightmapRenderRoot.parent = g_client.renderGraphRoot;
	
	
}

function initCamera(){
	
	g_patchViewInfo = o3djs.rendergraph.createBasicView(g_pack,
														g_patchRoot,
														g_patchRenderRoot);
	
	
	// Set up a simple perspective view.
	g_patchViewInfo.drawContext.projection = g_math.matrix4.perspective(
																g_math.degToRad(30), // 30 degree fov.
																g_client.width / g_client.height,
																1,                  // Near plane.
																5000);              // Far plane.

	// Set up our view transformation to look towards the world origin
	g_patchViewInfo.drawContext.view = g_math.matrix4.lookAt([0, 0, 5],  // eye
														[0, 0, 0],  // target
														[0, 1, 0]); // up
	
	
	
}


function turnoffHeightmapShader(){
	
	//alert(g_heightmap.heightTexture.getValue());
	
	//g_patch.heightmap.renderNode.active = false
	g_patch.heightmap.swapTextures();
	
	//g_patch = new Patch(g_patchRoot, g_heightmapRoot);
	//g_patchRenderRoot.priority = 1;
	//g_heightmapRenderRoot.priority = 0;
	
	//alert('!!')
	
	
}


function renderCallback(renderEvent) {
	
	g_re = renderEvent;
	
	g_clock += renderEvent.elapsedTime * g_timeMult;
	// Rotate the cube around the Y axis.
	//g_cubeTransform.identity();
	//g_cubeTransform.rotateY(2.0 * g_clock);
	
	//g_patch.heightmap.timeParam.value = g_clock / 10.0;
	//g_patch.heightmap.swapTextures();
	
	//alert(this.patch.heightmap.timeParam)
	g_patch.heightmap.swapTextures();
}

