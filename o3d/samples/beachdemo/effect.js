/*
 * Copyright 2009, Google Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *     * Neither the name of Google Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

// All Rights Reserved.

/**
 * @fileoverview This file contains a customized portion of the code from
 *    effect.js.
 *
 * TODO refactor the code in effect.js to use templates to help
 * generate shaders so this is no longer needed.
 *
 */

/**
 * Builds a shader string for a given standard COLLADA material type.
 *
 * @param {o3d.Material} material Material for which to build the shader.
 * @param {String} effectType Type of effect to create ('phong', 'lambert',
 *     'constant').
 * @return {description: string, shader: string} A description and the shader
 *     string.
 */
var beachDemoBuildStandardShaderString = function(material,
                                                  effectType) {
  var bumpSampler = material.getParam('bumpSampler');
  var bumpUVInterpolant;

  /**
   * Extracts the texture type from a texture param.
   * @param {!o3d.ParamTexture} textureParam The texture parameter to
   *     inspect.
   * @return {string} The texture type (1D, 2D, 3D or CUBE).
   */
  var getTextureType = function(textureParam) {
    var texture = textureParam.value;
    if (!texture) return '2D';  // No texture value, have to make a guess.
    switch (texture.className) {
      case 'o3d.Texture1D' : return '1D';
      case 'o3d.Texture2D' : return '2D';
      case 'o3d.Texture3D' : return '3D';
      case 'o3d.TextureCUBE' : return 'CUBE';
      default : return '2D';
    }
  }

  /**
   * Extracts the sampler type from a sampler param.  It does it by inspecting
   * the texture associated with the sampler.
   * @param {!o3d.ParamTexture} samplerParam The texture parameter to
   *     inspect.
   * @return {string} The texture type (1D, 2D, 3D or CUBE).
   */
  var getSamplerType = function(samplerParam) {
    var sampler = samplerParam.value;
    if (!sampler) return '2D';
    var textureParam = sampler.getParam('Texture');
    if (textureParam)
      return getTextureType(textureParam);
    else
      return '2D';
  };

  /**
   * Builds uniform variables common to all standard lighting types.
   * @return {string} The effect code for the common shader uniforms.
   */
  var buildCommonUniforms = function() {
    return 'uniform float4x4 world : WORLD;\n' +
           'uniform float4x4 worldViewProjection : WORLDVIEWPROJECTION;\n' +
           'uniform float3 lightWorldPos;\n' +
           'uniform float4 lightColor;\n' +
           'uniform float  clipHeight;\n';
  };

  /**
   * Builds uniform variables common to lambert, phong and blinn lighting types.
   * @return {string} The effect code for the common shader uniforms.
   */
  var buildLightingUniforms = function() {
    return 'uniform float4x4 viewInverse : VIEWINVERSE;\n' +
           'uniform float4x4 worldInverseTranspose : WORLDINVERSETRANSPOSE;\n';
  };

  /**
   * Builds uniform parameters for a given color input.  If the material
   * has a sampler parameter, a sampler uniform is created, otherwise a
   * float4 color value is created.
   * @param {!o3d.Material} material The material to inspect.
   * @param {!Array.<string>} descriptions Array to add descriptions too.
   * @param {string} name The name of the parameter to look for.  Usually
   *                      emissive, ambient, diffuse or specular.
   * @param {boolean} opt_addColorParam Whether to add a color param if no
   *     sampler exists. Default = true.
   * @return {string} The effect code for the uniform parameter.
   */
  var buildColorParam = function(material, descriptions, name,
                                 opt_addColorParam) {
    if (opt_addColorParam === undefined) {
      opt_addColorParam = true;
    }
    var samplerParam = material.getParam(name + 'Sampler');
    if (samplerParam) {
      var type = getSamplerType(samplerParam);
      descriptions.push(name + type + 'Texture');
      return 'sampler' + type + ' ' + name + 'Sampler;\n'
    } else if (opt_addColorParam) {
      descriptions.push(name + 'Color');
      return 'uniform float4 ' + name + ';\n';
    } else {
      return '';
    }
  };

  /**
   * Builds the effect code to retrieve a given color input.  If the material
   * has a sampler parameter of that name, a texture lookup is done.  Otherwise
   * it's a no-op, since the value is retrieved directly from the color uniform
   * of that name.
   * @param {!o3d.Material} material The material to inspect.
   * @param {string} name The name of the parameter to look for.  Usually
   *                      emissive, ambient, diffuse or specular.
   * @return {string} The effect code for the uniform parameter retrieval.
   */
  var getColorParam = function(material, name) {
    var samplerParam = material.getParam(name + 'Sampler');
    if (samplerParam) {
      var type = getSamplerType(samplerParam);
      return '  float4 ' + name + ' = tex' + type +
             '(' + name + 'Sampler, input.' + name + 'UV);\n'
    } else {
      return '';
    }
  };

  /**
   * Builds the vertex and fragment shader entry point in the format that
   * o3d can parse.
   * @return {string} The effect code for the entry points.
   */
  var buildEntryPoints = function() {
    return '  // #o3d VertexShaderEntryPoint vertexShaderFunction\n' +
           '  // #o3d PixelShaderEntryPoint pixelShaderFunction\n' +
           '  // #o3d MatrixLoadOrder RowMajor\n';
  };

  /**
   * Builds vertex and fragment shader string for the Constant lighting type.
   * @param {!o3d.Material} material The material for which to build
   *     shaders.
   * @param {!Array.<string>} descriptions Array to add descriptions too.
   * @return {string} The effect code for the shader, ready to be parsed.
   */
  var buildConstantShaderString = function(material, descriptions) {
    descriptions.push('constant');
    return buildCommonUniforms() +
           buildColorParam(material, descriptions, 'emissive') +
           buildVertexDecls(material, false, false) +
           buildVertexShaderStart() +
           buildUVPassthroughs(material) +
           '  return output;\n' +
           '}\n' +
           'float4 pixelShaderFunction(OutVertex input) : COLOR {\n' +
           getColorParam(material, 'emissive') +
           buildAlphaComputation('emissive.a') +
           '  return float4(emissive.xyz, alpha);\n' +
           '}\n' +
           '\n' +
           buildEntryPoints();
  };

  /**
   * Builds vertex and fragment shader string for the Lambert lighting type.
   * @param {!o3d.Material} material The material for which to build
   *     shaders.
   * @param {!Array.<string>} descriptions Array to add descriptions too.
   * @return {string} The effect code for the shader, ready to be parsed.
   */
  var buildLambertShaderString = function(material, descriptions) {
    descriptions.push('lambert');
    return buildCommonUniforms() +
           buildLightingUniforms() +
           buildColorParam(material, descriptions, 'emissive') +
           buildColorParam(material, descriptions, 'ambient') +
           buildColorParam(material, descriptions, 'diffuse') +
           buildColorParam(material, descriptions, 'bump', false) +
           buildVertexDecls(material, true, false) +
           buildVertexShaderStart() +
           buildUVPassthroughs(material) +
           '  output.normal = mul(float4(input.normal.xyz,0),\n' +
           '                      worldInverseTranspose).xyz;\n' +
           bumpVertexShaderCode() +
           '  return output;\n' +
           '}\n' +
           'float4 pixelShaderFunction(OutVertex input) : COLOR\n' +
           '{\n' +
           getColorParam(material, 'emissive') +
           getColorParam(material, 'ambient') +
           getColorParam(material, 'diffuse') +
           getNormalShaderCode() +
           '  float3 surfaceToLight = normalize(lightWorldPos -\n' +
           '                                    input.worldPosition);\n' +
           '  float4 litR = lit(dot(normal, surfaceToLight), 0, 0);\n' +
           buildAlphaComputation('diffuse.a') +
           '  return float4((emissive +\n' +
           '      lightColor * (ambient * diffuse + diffuse * litR.y)).rgb,' +
           '      alpha);\n' +
           '}\n' +
           '\n' +
           buildEntryPoints();

  };

  /**
   * Builds vertex and fragment shader string for the Blinn lighting type.
   * @param {!o3d.Material} material The material for which to build
   *     shaders.
   * @param {!Array.<string>} descriptions Array to add descriptions too.
   * @return {string} The effect code for the shader, ready to be parsed.
   * TODO: This is actually just a copy of the Phong code.
   *     Change to Blinn.
   */
  var buildBlinnShaderString = function(material, descriptions) {
    descriptions.push('blinn');
    return buildCommonUniforms() +
        buildLightingUniforms() +
        buildColorParam(material, descriptions, 'emissive') +
        buildColorParam(material, descriptions, 'ambient') +
        buildColorParam(material, descriptions, 'diffuse') +
        buildColorParam(material, descriptions, 'specular') +
        buildColorParam(material, descriptions, 'bump', false) +
        'uniform float shininess;\n' +
        buildVertexDecls(material, true, true) +
        buildVertexShaderStart() +
        buildUVPassthroughs(material) +
        '  output.normal = mul(float4(input.normal.xyz,0),\n' +
        '                      worldInverseTranspose).xyz;\n' +
        bumpVertexShaderCode() +
        '  return output;\n' +
        '}\n' +
        'float4 pixelShaderFunction(OutVertex input) : COLOR\n' +
        '{\n' +
        getColorParam(material, 'emissive') +
        getColorParam(material, 'ambient') +
        getColorParam(material, 'diffuse') +
        getColorParam(material, 'specular') +
        getNormalShaderCode() +
        '  float3 surfaceToLight = normalize(lightWorldPos -\n' +
        '                                    input.worldPosition);\n' +
        '  float3 surfaceToView = normalize(viewInverse[3] -\n' +
        '                                   input.worldPosition);\n' +
        '  float3 halfVector = normalize(surfaceToLight + surfaceToView);\n' +
        '  float4 litR = lit(dot(normal, surfaceToLight), \n' +
        '                    dot(normal, halfVector), shininess);\n' +
        buildAlphaComputation('diffuse.a') +
        '  return float4((emissive +\n' +
        '  lightColor * (ambient * diffuse + diffuse * litR.y +\n' +
        '                        + specular * litR.z)).rgb,' +
        '      alpha);\n' +
        '}\n' +
        '\n' +
        buildEntryPoints();
  };

  /**
   * Builds vertex and fragment shader string for the Phong lighting type.
   * @param {!o3d.Material} material The material for which to build
   *     shaders.
   * @param {!Array.<string>} descriptions Array to add descriptions too.
   * @return {string} The effect code for the shader, ready to be parsed.
   */
  var buildPhongShaderString = function(material, descriptions) {
    descriptions.push('phong');
    return buildCommonUniforms() +
        buildLightingUniforms() +
        buildColorParam(material, descriptions, 'emissive') +
        buildColorParam(material, descriptions, 'ambient') +
        buildColorParam(material, descriptions, 'diffuse') +
        buildColorParam(material, descriptions, 'specular') +
        buildColorParam(material, descriptions, 'bump', false) +
        'uniform float shininess;\n' +
        buildVertexDecls(material, true, true) +
        buildVertexShaderStart() +
        buildUVPassthroughs(material) +
        '  output.normal = mul(float4(input.normal.xyz,0),\n' +
        '                      worldInverseTranspose).xyz;\n' +
        bumpVertexShaderCode() +
        '  return output;\n' +
        '}\n' +
        'float4 pixelShaderFunction(OutVertex input) : COLOR\n' +
        '{\n' +
        getColorParam(material, 'emissive') +
        getColorParam(material, 'ambient') +
        getColorParam(material, 'diffuse') +
        getColorParam(material, 'specular') +
        getNormalShaderCode() +
        '  float3 surfaceToLight = normalize(lightWorldPos -\n' +
        '                                    input.worldPosition);\n' +
        '  float3 surfaceToView = normalize(viewInverse[3] -\n' +
        '                                   input.worldPosition);\n' +
        '  float3 halfVector = normalize(surfaceToLight + surfaceToView);\n' +
        '  float4 litR = lit(dot(normal, surfaceToLight), \n' +
        '                    dot(normal, halfVector), shininess);\n' +
        buildAlphaComputation('diffuse.a') +
        '  return float4((emissive +\n' +
        '  lightColor * (ambient * diffuse + diffuse * litR.y +\n' +
        '                        + specular * litR.z)).rgb,' +
        '      alpha);\n' +
        '}\n' +
        '\n' +
        buildEntryPoints();
  };

  // An integer value which keeps track of the next available interpolant.
  var interpolant;

  /**
   * Builds the alpha computation.
   * @param {string} inputAlpha the variable name of the original alpha.
   * @return {string} The shader code.
   */
  var buildAlphaComputation = function(inputAlpha) {
    return 'float alpha = input.worldPosition.z > clipHeight ? 0 : ' +
        inputAlpha + ';\n';
  };

  /**
   * Builds the start of a vertex shader.
   * @return {string} The shader code.
   */
  var buildVertexShaderStart = function() {
    return '' +
        'OutVertex vertexShaderFunction(InVertex input) {\n' +
        '  OutVertex output;\n' +
        '  output.position = mul(input.position, worldViewProjection);\n' +
        '  output.worldPosition = mul(input.position, world);\n';
  };

  /**
   * Builds the texture coordinate declaration for a given color input
   * (usually emissive, anmbient, diffuse or specular).  If the color
   * input does not have a sampler, no TEXCOORD declaration is built.
   * @param {!o3d.Material} material The material to inspect.
   * @param {string} name The name of the color input.
   * @return {string} The code for the texture coordinate declaration.
   */
  var buildTexCoord = function(material, name) {
    if (material.getParam(name + 'Sampler')) {
      return '  float2 ' + name + 'UV : TEXCOORD' + interpolant++ + ';\n';
    } else {
      return '';
    }
  };

  /**
   * Builds all the texture coordinate declarations for a vertex attribute
   * declaration.
   * @param {!o3d.Material} material The material to inspect.
   * @return {string} The code for the texture coordinate declarations.
   */
  var buildTexCoords = function(material) {
    interpolant = 0;
    return buildTexCoord(material, 'emissive') +
           buildTexCoord(material, 'ambient') +
           buildTexCoord(material, 'diffuse') +
           buildTexCoord(material, 'specular');
  };

  /**
   * Builds the texture coordinate passthrough statement for a given
   * color input (usually emissive, ambient, diffuse or specular).  These
   * assigments are used in the vertex shader to pass the texcoords to be
   * interpolated to the rasterizer.  If the color input does not have
   * a sampler, no code is generated.
   * @param {!o3d.Material} material The material to inspect.
   * @param {string} name The name of the color input.
   * @return {string} The code for the texture coordinate passthrough statement.
   */
  var buildUVPassthrough = function(material, name) {
    if (material.getParam(name + 'Sampler')) {
      return '  output.' + name + 'UV = input.' + name + 'UV;\n';
    } else {
      return '';
    }
  };

  /**
   * Builds all the texture coordinate passthrough statements for the
   * vertex shader.
   * @param {!o3d.Material} material The material to inspect.
   * @return {string} The code for the texture coordinate passthrough
   *                  statements.
   */
  var buildUVPassthroughs = function(material) {
    return buildUVPassthrough(material, 'emissive') +
           buildUVPassthrough(material, 'ambient') +
           buildUVPassthrough(material, 'diffuse') +
           buildUVPassthrough(material, 'specular') +
           buildUVPassthrough(material, 'bump');
  };

  /**
   * Builds bump input coords if needed.
   * @return {string} The code for bump input coords.
   */
  var buildBumpInputCoords = function() {
    return bumpSampler ?
        ('  float3 tangent      : TANGENT;\n' +
         '  float3 binormal     : BINORMAL;\n' +
         '  float2 bumpUV       : TEXCOORD' + interpolant++ + ';\n') : '';
  };

  /**
   * Builds bump output coords if needed.
   * @return {string} The code for bump input coords.
   */
  var buildBumpOutputCoords = function() {
    return bumpSampler ?
        ('  float3 tangent      : TEXCOORD' + interpolant++ + ';\n' +
         '  float3 binormal     : TEXCOORD' + interpolant++ + ';\n' +
         '  float2 bumpUV       : TEXCOORD' + interpolant++ + ';\n') : '';
  };

  /**
   * Builds the normal map part of the vertex shader.
   * @return {string} The code for normal mapping in the vertex shader.
   */
  var bumpVertexShaderCode = function() {
    return bumpSampler ?
        ('  output.binormal = ' +
         'mul(float4(input.binormal,0), worldInverseTranspose).xyz;\n' +
         '  output.tangent = ' +
         'mul(float4(input.tangent,0), worldInverseTranspose).xyz;\n') : '';
  };

  /**
   * Builds the normal calculation of the pixel shader.
   * @return {string} The code for normal computation in the pixel shader.
   */
  var getNormalShaderCode = function() {
    return bumpSampler ?
        ('float3x3 tangentToWorld = float3x3(input.tangent,\n' +
         '                                   input.binormal,\n' +
         '                                   input.normal);\n' +
         'float3 tangentNormal = tex2D(bumpSampler, input.bumpUV.xy).xyz -\n' +
         '                       float3(0.5, 0.5, 0.5);\n' +
         'float3 normal = mul(tangentNormal, tangentToWorld);\n' +
         'normal = normalize(normal);\n') :
        '  float3 normal = normalize(input.normal);\n';
  };

  /**
   * Builds the vertex declarations for a given material.
   * @param {!o3d.Material} material The material to inspect.
   * @param {boolean} diffuse Whether to include diffuse interpolations.
   * @param {boolean} specular Whether to include specular interpolations.
   * @return {string} The code for the vertex declarations.
   */
  var buildVertexDecls = function(material, diffuse, specular) {
    var str = 'struct InVertex {\n' +
              '  float4 position     : POSITION;\n' +
              '  float4 normal       : NORMAL;\n' +
              buildTexCoords(material) +
              buildBumpInputCoords() +
              '};\n' +
              'struct OutVertex {\n' +
              '  float4 position     : POSITION;\n' +
              buildTexCoords(material) +
              buildBumpOutputCoords() +
              '  float4 worldPosition: TEXCOORD' + interpolant++ + ';\n';
    if (diffuse || specular) {
      str += '  float3 normal        : TEXCOORD' + interpolant++ + ';\n';
    }
    str += '};\n'
    return str;
  };

  // Create a shader string of the appropriate type, based on the
  // effectType.
  var str;
  var descriptions = [];
  if (effectType == 'phong') {
    str = buildPhongShaderString(material, descriptions);
  } else if (effectType == 'lambert') {
    str = buildLambertShaderString(material, descriptions);
  } else if (effectType == 'blinn') {
    str = buildBlinnShaderString(material, descriptions);
  } else if (effectType == 'constant') {
    str = buildConstantShaderString(material, descriptions);
  } else {
    throw ('unknown effect type "' + effectType + '"');
  }

  return {description: descriptions.join('_'), shader: str};
};


