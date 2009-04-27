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
 * @fileoverview This file contains various functions for quaternion arithmetic
 * and converting between rotation matrices and quaternions.  It adds them to
 * the "quaternions" module on the o3djs object.  Javascript arrays with
 * four entries are used to represent quaternions, and functions are provided
 * for doing operations on those.
 *
 * Operations are done assuming quaternions are of the form:
 * q[0] + q[1]i + q[2]j + q[3]k and using the hamiltonian rules for
 * multiplication as described on Brougham Bridge:
 * i^2 = j^2 = k^2 = ijk = -1.
 *
 */

o3djs.provide('o3djs.quaternions');

/**
 * A Module for quaternion math.
 * @namespace
 */
o3djs.quaternions = o3djs.quaternions || {};

/**
 * A Quaternion.
 * @type {!Array.<number>}
 */
o3djs.quaternions.Quaterion = goog.typedef;

/**
 * Quickly determines if the object a is a scalar or a quaternion;
 * assumes that the argument is either a number (scalar), or an array of
 * numbers.
 * @param {(number|!o3djs.quaternions.Quaterion)} a A number or array the type
 *     of which is in question.
 * @return {string} Either the string 'Scalar' or 'Quaternion'.
 */
o3djs.quaternions.mathType = function(a) {
  if (typeof(a) === 'number')
    return 'Scalar';
  return 'Quaternion';
};

/**
 * Copies a quaternion.
 * @param {!o3djs.quaternions.Quaterion} q The quaternion.
 * @return {!o3djs.quaternions.Quaterion} A new quaternion identical to q.
 */
o3djs.quaternions.copy = function(q) {
  return q.slice();
};

/**
 * Negates a quaternion.
 * @param {!o3djs.quaternions.Quaterion} q The quaternion.
 * @return {!o3djs.quaternions.Quaterion} -q.
 */
o3djs.quaternions.negative = function(q) {
  return [-q[0], -q[1], -q[2], -q[3]];
};

/**
 * Adds two Quaternions.
 * @param {!o3djs.quaternions.Quaterion} a Operand Quaternion.
 * @param {!o3djs.quaternions.Quaterion} b Operand Quaternion.
 * @return {!o3djs.quaternions.Quaterion} The sum of a and b.
 */
o3djs.quaternions.addQuaternionQuaternion = function(a, b) {
  return [a[0] + b[0],
          a[1] + b[1],
          a[2] + b[2],
          a[3] + b[3]];
};

/**
 * Adds a quaternion to a scalar.
 * @param {!o3djs.quaternions.Quaterion} a Operand Quaternion.
 * @param {numbers} b Operand Scalar.
 * @return {!o3djs.quaternions.Quaterion} The sum of a and b.
 */
o3djs.quaternions.addQuaternionScalar = function(a, b) {
  return [a[0] + b].concat(a.slice(1, 4));
};

/**
 * Adds a scalar to a quaternion.
 * @param {number} a Operand scalar.
 * @param {!o3djs.quaternions.Quaterion} b Operand quaternion.
 * @return {!o3djs.quaternions.Quaterion} The sum of a and b.
 */
o3djs.quaternions.addScalarQuaternion = function(a, b) {
  return [a + b[0]].concat(b.slice(1, 4));
};

/**
 * Subtracts two quaternions.
 * @param {!o3djs.quaternions.Quaterion} a Operand quaternion.
 * @param {!o3djs.quaternions.Quaterion} b Operand quaternion.
 * @return {!o3djs.quaternions.Quaterion} The difference a - b.
 */
o3djs.quaternions.subQuaternionQuaternion = function(a, b) {
  return [a[0] - b[0],
          a[1] - b[1],
          a[2] - b[2],
          a[3] - b[3]];
};

/**
 * Subtracts a scalar from a quaternion.
 * @param {!o3djs.quaternions.Quaterion} a Operand quaternion.
 * @param {number} b Operand scalar.
 * @return {!o3djs.quaternions.Quaterion} The difference a - b.
 */
o3djs.quaternions.subQuaternionScalar = function(a, b) {
  return [a[0] - b].concat(a.slice(1, 4));
};

/**
 * Subtracts a quaternion from a scalar.
 * @param {number} a Operand scalar.
 * @param {!o3djs.quaternions.Quaterion} b Operand quaternion.
 * @return {!o3djs.quaternions.Quaterion} The difference a - b.
 */
o3djs.quaternions.subScalarQuaternion = function(a, b) {
  return [a - b[0], -b[1], -b[2], -b[3]];
};

/**
 * Multiplies a scalar by a quaternion.
 * @param {Array} k The scalar.
 * @param {Array} q The quaternion.
 * @return {Array} The product of k and q.
 */
o3djs.quaternions.mulScalarQuaternion = function(k, q) {
  return [k * q[0], k * q[1], k * q[2], k * q[3]];
};

/**
 * Multiplies a quaternion by a scalar.
 * @param {!o3djs.quaternions.Quaterion} q The Quaternion.
 * @param {number} k The scalar.
 * @return {!o3djs.quaternions.Quaterion} The product of k and v.
 */
o3djs.quaternions.mulQuaternionScalar = function(q, k) {
  return [k * q[0], k * q[1], k * q[2], k * q[3]];
};

/**
 * Multiplies two quaternions.
 * @param {!o3djs.quaternions.Quaterion} a Operand quaternion.
 * @param {!o3djs.quaternions.Quaterion} b Operand quaternion.
 * @return {!o3djs.quaternions.Quaterion} The quaternion product a * b.
 */
o3djs.quaternions.mulQuaternionQuaternion = function(a, b) {
  var a0 = a[0];
  var a1 = a[1];
  var a2 = a[2];
  var a3 = a[3];
  var b0 = b[0];
  var b1 = b[1];
  var b2 = b[2];
  var b3 = b[3];

  return [
    a0 * b0 - a1 * b1 - a2 * b2 - a3 * b3,
    a0 * b1 + a1 * b0 + a2 * b3 - a3 * b2,
    a0 * b2 - a1 * b3 + a2 * b0 + a3 * b1,
    a0 * b3 + a1 * b2 - a2 * b1 + a3 * b0];
};

/**
 * Divides two quaternions; assumes the convention that a/b = a*(1/b).
 * @param {!o3djs.quaternions.Quaterion} a Operand quaternion.
 * @param {!o3djs.quaternions.Quaterion} b Operand quaternion.
 * @return {!o3djs.quaternions.Quaterion} The quaternion quotient a / b.
 */
o3djs.quaternions.divQuaternionQuaternion = function(a, b) {
  var a0 = a[0];
  var a1 = a[1];
  var a2 = a[2];
  var a3 = a[3];
  var b0 = b[0];
  var b1 = b[1];
  var b2 = b[2];
  var b3 = b[3];

  var d = b0 * b0 + b1 * b1 + b2 * b2 + b3 * b3;
  return [
      (a0 * b0 + a1 * b1 + a2 * b2 + a3 * b3) / d,
      (a1 * b0 - a0 * b1 - a2 * b3 + a3 * b2) / d,
      (a1 * b3 - a0 * b2 + a2 * b0 - a3 * b1) / d,
      (a2 * b1 + a3 * b0 - a0 * b3 - a1 * b2) / d];
};

/**
 * Divides a Quaternion by a scalar.
 * @param {!o3djs.quaternions.Quaterion} q The quaternion.
 * @param {number} k The scalar.
 * @return {!o3djs.quaternions.Quaterion} q The quaternion q divided by k.
 */
o3djs.quaternions.divQuaternionScalar = function(q, k) {
  return [q[0] / k, q[1] / k, q[2] / k, q[3] / k];
};

/**
 * Divides a scalar by a quaternion.
 * @param {number} a Operand scalar.
 * @param {!o3djs.quaternions.Quaterion} b Operand quaternion.
 * @return {!o3djs.quaternions.Quaterion} The quaternion product.
 */
o3djs.quaternions.divScalarQuaternion = function(a, b) {
  var b0 = b[0];
  var b1 = b[1];
  var b2 = b[2];
  var b3 = b[3];

  var d = b0 * b0 + b1 * b1 + b2 * b2 + b3 * b3;
  return [a * b0 / d, -a * b[1] / d, -a * b[2] / d, -a * b[3] / d];
};

/**
 * Computes the multiplicative inverse of a quaternion.
 * @param {!o3djs.quaternions.Quaterion} q The quaternion.
 * @return {!o3djs.quaternions.Quaterion} The multiplicative inverse of q.
 */
o3djs.quaternions.inverse = function(q) {
  var q0 = q[0];
  var q1 = q[1];
  var q2 = q[2];
  var q3 = q[3];

  var d = q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3;
  return [q0 / d, -q[1] / d, -q[2] / d, -q[3] / d];
};

/**
 * Multiplies two objects which are either scalars or quaternions.
 * @param {(!o3djs.quaternions.Quaterion|number)} a Operand.
 * @param {(!o3djs.quaternions.Quaterion|number)} b Operand.
 * @return {(!o3djs.quaternions.Quaterion|number)} The product of a and b.
 */
o3djs.quaternions.mul = function(a, b) {
  return o3djs.quaternions['mul' + o3djs.quaternions.mathType(a) +
      o3djs.quaternions.mathType(b)](a, b);
};

/**
 * Divides two objects which are either scalars or quaternions.
 * @param {(!o3djs.quaternions.Quaterion|number)} a Operand.
 * @param {(!o3djs.quaternions.Quaterion|number)} b Operand.
 * @return {(!o3djs.quaternions.Quaterion|number)} The quotient of a and b.
 */
o3djs.quaternions.div = function(a, b) {
  return o3djs.quaternions['div' + o3djs.quaternions.mathType(a) +
      o3djs.quaternions.mathType(b)](a, b);
};

/**
 * Adds two objects which are either scalars or quaternions.
 * @param {(!o3djs.quaternions.Quaterion|number)} a Operand.
 * @param {(!o3djs.quaternions.Quaterion|number)} b Operand.
 * @return {(!o3djs.quaternions.Quaterion|number)} The sum of a and b.
 */
o3djs.quaternions.add = function(a, b) {
  return o3djs.quaternions['add' + o3djs.quaternions.mathType(a) +
      o3djs.quaternions.mathType(b)](a, b);
};

/**
 * Subtracts two objects which are either scalars or quaternions.
 * @param {(!o3djs.quaternions.Quaterion|number)} a Operand.
 * @param {(!o3djs.quaternions.Quaterion|number)} b Operand.
 * @return {(!o3djs.quaternions.Quaterion|number)} The difference of a and b.
 */
o3djs.quaternions.sub = function(a, b) {
  return o3djs.quaternions['sub' + o3djs.quaternions.mathType(a) +
      o3djs.quaternions.mathType(b)](a, b);
};

/**
 * Computes the length of a Quaternion, i.e. the square root of the
 * sum of the squares of the coefficients.
 * @param {!o3djs.quaternions.Quaterion} a The Quaternion.
 * @return {number} The length of a.
 */
o3djs.quaternions.length = function(a) {
  return Math.sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2] + a[3] * a[3]);
};

/**
 * Computes the square of the length of a quaternion, i.e. the sum of the
 * squares of the coefficients.
 * @param {!o3djs.quaternions.Quaterion} a The quaternion.
 * @return {number} The square of the length of a.
 */
o3djs.quaternions.lengthSquared = function(a) {
  return a[0] * a[0] + a[1] * a[1] + a[2] * a[2] + a[3] * a[3];
};

/**
 * Divides a Quaternion by its length and returns the quotient.
 * @param {!o3djs.quaternions.Quaterion} a The Quaternion.
 * @return {!o3djs.quaternions.Quaterion} A unit length quaternion pointing in
 *     the same direction as a.
 */
o3djs.quaternions.normalize = function(a) {
  var d = Math.sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2] + a[3] * a[3]);
  return [a[0] / d, a[1] / d, a[2] / d, a[3] / d];
};

/**
 * Computes the conjugate of the given quaternion.
 * @param {!o3djs.quaternions.Quaterion} q The quaternion.
 * @return {!o3djs.quaternions.Quaterion} The conjugate of q.
 */
o3djs.quaternions.conjugate = function(q) {
  return [q[0], -q[1], -q[2], -q[3]];
};


/**
 * Creates a quaternion which rotates around the x-axis by the given angle.
 * @param {number} angle The angle by which to rotate (in radians).
 * @return {!o3djs.quaternions.Quaterion} The quaternion.
 */
o3djs.quaternions.rotationX = function(angle) {
  return [Math.cos(angle / 2), Math.sin(angle / 2), 0, 0];
};

/**
 * Creates a quaternion which rotates around the y-axis by the given angle.
 * @param {number} angle The angle by which to rotate (in radians).
 * @return {!o3djs.quaternions.Quaterion} The quaternion.
 */
o3djs.quaternions.rotationY = function(angle) {
  return [Math.cos(angle / 2), 0, Math.sin(angle / 2), 0];
};

/**
 * Creates a quaternion which rotates around the z-axis by the given angle.
 * @param {number} angle The angle by which to rotate (in radians).
 * @return {!o3djs.quaternions.Quaterion} The quaternion.
 */
o3djs.quaternions.rotationZ = function(angle) {
  return [Math.cos(angle / 2), 0, 0, Math.sin(angle / 2)];
};

/**
 * Creates a quaternion which rotates around the given axis by the given
 * angle.
 * @param {!o3djs.math.Vector3} axis The axis about which to rotate.
 * @param {number} angle The angle by which to rotate (in radians).
 * @return {!o3djs.quaternions.Quaterion} A quaternion which rotates angle
 *     radians around the axis.
 */
o3djs.quaternions.axisRotation = function(axis, angle) {
  var d = Math.sqrt(axis[0] * axis[0] +
                    axis[1] * axis[1] +
                    axis[2] * axis[2]);
  var sin = Math.sin(angle / 2);
  var cos = Math.cos(angle / 2);
  return [cos, sin * axis[0] / d, sin * axis[1] / d, sin * axis[2] / d];
};

/**
 * Computes a 4-by-4 rotation matrix (with trivial translation component)
 * given a quaternion.  We assume the convention that to rotate a vector v by
 * a quaternion r means to express that vector as a quaternion q by letting
 * q = [0, v[0], v[1], v[2]] and then obtain the rotated vector by evaluating
 * the expression (r * q) / r.
 * @param {!o3djs.quaternions.Quaterion} q The quaternion.
 * @return {!o3djs.math.Matrix4} A 4-by-4 rotation matrix.
 */
o3djs.quaternions.quaternionToRotation = function(q) {
  var q0 = q[0];
  var q1 = q[1];
  var q2 = q[2];
  var q3 = q[3];

  var q0q0 = q0 * q0;
  var q0q1 = q0 * q1;
  var q0q2 = q0 * q2;
  var q0q3 = q0 * q3;
  var q1q0 = q1 * q0;
  var q1q1 = q1 * q1;
  var q1q2 = q1 * q2;
  var q1q3 = q1 * q3;
  var q2q0 = q2 * q0;
  var q2q1 = q2 * q1;
  var q2q2 = q2 * q2;
  var q2q3 = q2 * q3;
  var q3q0 = q3 * q0;
  var q3q1 = q3 * q1;
  var q3q2 = q3 * q2;
  var q3q3 = q3 * q3;

  var d = q0q0 + q1q1 + q2q2 + q3q3;

  return [
    [(q0q0 + q1q1 - q2q2 - q3q3) / d,
     2 * (q0q3 + q1q2) / d,
     2 * (q1q3 - q0q2) / d, 0],
    [2 * (q1q2 - q0q3) / d,
     (q0q0 - q1q1 + q2q2 - q3q3) / d,
     2 * (q0q1 + q2q3) / d, 0],
    [2 * (q0q2 + q1q3) / d,
     2 * (q2q3 - q0q1) / d,
     (q0q0 - q1q1 - q2q2 + q3q3) / d, 0],
    [0, 0, 0, 1]];
};

/**
 * Computes a quaternion whose rotation is equivalent to the given matrix.
 * @param {!o3djs.math.Matrix4} m A 3-by-3 or 4-by-4 rotation matrix.
 * @return {!o3djs.quaternions.Quaterion} A quaternion q such that
 *     quaternions.quaternionToRotation(q) is m.
 */
o3djs.quaternions.rotationToQuaternion = function(m) {
  var u;
  var v;
  var w;

  // Choose u, v, and w such that u is the index of the biggest diagonal entry
  // of m, and u v w is an even permutation of 0 1 and 2.
  if (m[0][0] > m[1][1] && m[0][0] > m[2][2]) {
    u = 0;
    v = 1;
    w = 2;
  } else if (m[1][1] > m[0][0] && m[1][1] > m[2][2]) {
    u = 1;
    v = 2;
    w = 0;
  } else {
    u = 2;
    v = 0;
    w = 1;
  }

  var r = Math.sqrt(1 + m[u][u] - m[v][v] - m[w][w]);
  var q = [];
  q[0] = 0.5 * (m[v][w] - m[w][v]) / r;
  q[u + 1] = 0.5 * r;
  q[v + 1] = 0.5 * (m[v][u] + m[u][v]) / r;
  q[w + 1] = 0.5 * (m[u][w] + m[w][u]) / r;

  return q;
};

