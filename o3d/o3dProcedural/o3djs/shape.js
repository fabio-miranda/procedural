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


/**
 * @fileoverview This file contains various functions for helping setup
 * shapes for o3d.  It puts them in the "shape" module on the o3djs
 * object.
 *
 *     Note: This library is only a sample. It is not meant to be some official
 *     library. It is provided only as example code.
 *
 */

o3djs.provide('o3djs.shape');

/**
 * A Module for shapes.
 * @namespace
 */
o3djs.shape = o3djs.shape || {};

/**
 * Prepares all the shapes in the given pack by setting their
 * drawList, boundingBox and zSortPoint.
 * @param {!o3d.Pack} pack Pack to manage created objects.
 */
o3djs.shape.prepareShapes = function(pack) {
  var shapes = pack.getObjectsByClassName('o3d.Shape');
  for (var ss = 0; ss < shapes.length; ++ss) {
    var shape = shapes[ss];
    shape.createDrawElements(pack, null);
    var elements = shape.elements;
    for (var ee = 0; ee < elements.length; ++ee) {
      var element = elements[ee];
      var boundingBox = element.getBoundingBox(0);
      var minExtent = boundingBox.minExtent;
      var maxExtent = boundingBox.maxExtent;
      element.boundingBox = boundingBox;
      element.cull = true;
      element.zSortPoint = o3djs.math.div(
          o3djs.math.add(minExtent, maxExtent), 2);

      // This is very application specific but if it's a primitive
      // and if it uses a collada material the material builder
      // assumes 1 TEXCOORD stream per texture. In other words if you have
      // both a specular texture AND a diffuse texture the builder assumes
      // you have 2 TEXCOORD streams. This assumption is often false.
      //
      // To work around this we check how many streams the material
      // expects and if there are not enough UVs streams we duplicate the
      // last TEXCOORD stream until there are, making a BIG assumption that
      // that will work.
      //
      // The problem is maybe you have 4 textures and each of them share
      // texture coordinates. There is information in the collada file about
      // what stream to connect each texture to.
      //
      // TODO We should store that info. The conditioner should either
      // make streams that way or pass on the info so we can do it here.
      if (element.isAClassName('o3d.Primitive')) {
        var material = element.material;
        var streamBank = element.streamBank;
        var lightingType = o3djs.effect.getColladaLightingType(material);
        if (lightingType) {
          var numTexCoordStreamsNeeded =
              o3djs.effect.getNumTexCoordStreamsNeeded(material);
          // Count the number of TEXCOORD streams the streamBank has.
          var streams = streamBank.vertexStreams;
          var lastTexCoordStream = null;
          var numTexCoordStreams = 0;
          for (var ii = 0; ii < streams.length; ++ii) {
            var stream = streams[ii];
            if (stream.semantic == o3djs.base.o3d.Stream.TEXCOORD) {
              lastTexCoordStream = stream;
              ++numTexCoordStreams;
            }
          }
          // Add any missing TEXCOORD streams. It might be more efficient for
          // the GPU to create an effect that doesn't need the extra streams
          // but this is a more generic solution because it means we can reuse
          // the same effect.
          for (var ii = numTexCoordStreams;
               ii < numTexCoordStreamsNeeded;
               ++ii) {
            streamBank.setVertexStream(
                lastTexCoordStream.semantic,
                lastTexCoordStream.semanticIndex + ii - numTexCoordStreams + 1,
                lastTexCoordStream.field,
                lastTexCoordStream.startIndex);
          }
        }
      }
    }
  }
};

/**
 * Attempts to delete the parts of a shape that were created by
 * duplicateShape as well as any drawElements attached to it.
 * @param {!o3d.Shape} shape shape to delete.
 * @param {!o3d.Pack} pack Pack to release objects from.
 */
o3djs.shape.deleteDuplicateShape = function(shape, pack) {
   var elements = shape.elements;
   for (var ee = 0; ee < elements.length; ee++) {
     var element = elements[ee];
     var drawElements = element.drawElements;
     for (var dd = 0; dd < drawElements.length; dd++) {
       var drawElement = drawElements[dd];
       pack.removeObject(drawElement);
     }
     pack.removeObject(element);
   }
   pack.removeObject(shape);
};

/**
 * Copies a shape's elements and streams but not buffers so
 * the two will share vertex and index buffers.
 * @param {!o3d.Pack} pack Pack to manage created objects.
 * @param {!o3d.Shape} source The Shape to copy.
 * @param {string} opt_prefix optional prefix for names of new objects.
 * @return {!o3d.Shape} the new copy of the shape.
 */
o3djs.shape.duplicateShape = function(pack, source, opt_prefix) {
  if (opt_prefix == null) {
    opt_prefix = '';
  }
  var newShape = pack.createObject('Shape');
  var elements = source.elements;
  for (var ee = 0; ee < elements.length; ee++) {
    var sourceElement = elements[ee];
    var newElement = pack.createObject(sourceElement.className);
    newElement.owner = newShape;
    newElement.copyParams(sourceElement);
    // TODO: If we get the chance to parameterize buffers then make
    //     we can delete this code since copyParams will handle it.
    //     For now it only handles primitives by doing it manually.
    if (sourceElement.isAClassName('o3d.Primitive')) {
      newElement.indexBuffer = sourceElement.indexBuffer;
      newElement.startIndex = sourceElement.startIndex;
      newElement.primitiveType = sourceElement.primitiveType;
      newElement.numberVertices = sourceElement.numberVertices;
      newElement.numberPrimitives = sourceElement.numberPrimitives;
    }
  }
  newShape.createDrawElements(pack, null);
  return newShape;
};

