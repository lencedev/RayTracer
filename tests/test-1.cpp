/*
** EPITECH PROJECT, 2023
** B-OOP-400-MPL-4-1-raytracer-hippolyte.aubert
** File description:
** test-1
*/

#include <iostream>
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "Camera.hpp"
#include "ChessTexture.hpp"
#include "Cone.hpp"
#include "Glass.hpp"
#include "Metal.hpp"
#include "Plane.hpp"
#include "Scene.hpp"
#include "Sphere.hpp"
#include "Utils.hpp"
#include "Vector3.hpp"
#include "Matrix4.hpp"

void setup(void) {
    cr_redirect_stdout();
}

TestSuite(raytracer_ChessTexture);

Test(raytracer_ChessTexture, constructor) {
    RayTracer::ChessTexture texture;

    cr_assert_not_null(&texture);
}

Test(raytracer_ChessTexture, constructor_with_even_and_odd_textures) {
    auto even = std::make_shared<RayTracer::BaseTexture>(Math::Vector3(0.2, 0.3, 0.1));
    auto odd = std::make_shared<RayTracer::BaseTexture>(Math::Vector3(0.9, 0.9, 0.9));
    RayTracer::ChessTexture texture(even, odd);

    cr_assert_not_null(&texture);
}

Test(raytracer_ChessTexture, constructor_with_colors) {
    Math::Vector3 c1(0.2, 0.3, 0.1);
    Math::Vector3 c2(0.9, 0.9, 0.9);
    RayTracer::ChessTexture texture(c1, c2);

    cr_assert_not_null(&texture);
}


TestSuite(Math_Vector3);

Test(Math_Vector3, default_constructor) {
    Math::Vector3 vector;

    cr_assert_float_eq(vector.x, 0.0, 1e-6);
    cr_assert_float_eq(vector.y, 0.0, 1e-6);
    cr_assert_float_eq(vector.z, 0.0, 1e-6);
}

Test(Math_Vector3, parameterized_constructor) {
    Math::Vector3 vector(1.0, 2.0, 3.0);

    cr_assert_float_eq(vector.x, 1.0, 1e-6);
    cr_assert_float_eq(vector.y, 2.0, 1e-6);
    cr_assert_float_eq(vector.z, 3.0, 1e-6);
}

Test(Math_Vector3, length) {
    Math::Vector3 vector(1.0, 2.0, 2.0);

    double result = vector.length();

    cr_assert_float_eq(result, 3.0, 1e-6);
}

Test(Math_Vector3, dot) {
    Math::Vector3 vector1(1.0, 2.0, 3.0);
    Math::Vector3 vector2(4.0, 5.0, 6.0);

    double result = vector1.dot(vector2);

    cr_assert_float_eq(result, 32.0, 1e-6);
}

/*
    Ray
*/

TestSuite(RayTracer_Ray);

Test(RayTracer_Ray, default_constructor) {
    RayTracer::Ray ray;
    Math::Vector3 origin(0.0, 0.0, 0.0);
    Math::Vector3 direction(0.0, 0.0, 0.0);

    cr_assert_float_eq(ray.origin.x, origin.x, 1e-6);
    cr_assert_float_eq(ray.origin.y, origin.y, 1e-6);
    cr_assert_float_eq(ray.origin.z, origin.z, 1e-6);
    cr_assert_float_eq(ray.direction.x, direction.x, 1e-6);
    cr_assert_float_eq(ray.direction.y, direction.y, 1e-6);
    cr_assert_float_eq(ray.direction.z, direction.z, 1e-6);
}

Test(RayTracer_Ray, parameterized_constructor) {
    Math::Vector3 origin(1.0, 2.0, 3.0);
    Math::Vector3 direction(4.0, 5.0, 6.0);
    RayTracer::Ray ray(origin, direction);

    cr_assert_float_eq(ray.origin.x, origin.x, 1e-6);
    cr_assert_float_eq(ray.origin.y, origin.y, 1e-6);
    cr_assert_float_eq(ray.origin.z, origin.z, 1e-6);
    cr_assert_float_eq(ray.direction.x, direction.x, 1e-6);
    cr_assert_float_eq(ray.direction.y, direction.y, 1e-6);
    cr_assert_float_eq(ray.direction.z, direction.z, 1e-6);
}

Test(RayTracer_Ray, copy_constructor) {
    Math::Vector3 origin(1.0, 2.0, 3.0);
    Math::Vector3 direction(4.0, 5.0, 6.0);
    RayTracer::Ray ray1(origin, direction);
    RayTracer::Ray ray2(ray1);

    cr_assert_float_eq(ray2.origin.x, ray1.origin.x, 1e-6);
    cr_assert_float_eq(ray2.origin.y, ray1.origin.y, 1e-6);
    cr_assert_float_eq(ray2.origin.z, ray1.origin.z, 1e-6);
    cr_assert_float_eq(ray2.direction.x, ray1.direction.x, 1e-6);
    cr_assert_float_eq(ray2.direction.y, ray1.direction.y, 1e-6);
    cr_assert_float_eq(ray2.direction.z, ray1.direction.z, 1e-6);
}

Test(RayTracer_Ray, pointAt) {
    Math::Vector3 origin(1.0, 2.0, 3.0);
    Math::Vector3 direction(4.0, 5.0, 6.0);
    RayTracer::Ray ray(origin, direction);
    double t = 2.0;
    Math::Vector3 result = ray.pointAt(t);

    Math::Vector3 expected_result = origin + t * direction;

    cr_assert_float_eq(result.x, expected_result.x, 1e-6);
    cr_assert_float_eq(result.y, expected_result.y, 1e-6);
    cr_assert_float_eq(result.z, expected_result.z, 1e-6);
}

Test(RayTracer_Ray, assignment_operator) {
    Math::Vector3 origin1(1.0, 2.0, 3.0);
    Math::Vector3 direction1(4.0, 5.0, 6.0);
    RayTracer::Ray ray1(origin1, direction1);

    Math::Vector3 origin2(7.0, 8.0, 9.0);
    Math::Vector3 direction2(10.0, 11.0, 12.0);
    RayTracer::Ray ray2(origin2, direction2);

    ray2 = ray1;

    cr_assert_float_eq(ray2.origin.x, ray1.origin.x, 1e-6);
    cr_assert_float_eq(ray2.origin.y, ray1.origin.y, 1e-6);
    cr_assert_float_eq(ray2.origin.z, ray1.origin.z, 1e-6);
    cr_assert_float_eq(ray2.direction.x, ray1.direction.x, 1e-6);
    cr_assert_float_eq(ray2.direction.y, ray1.direction.y, 1e-6);
    cr_assert_float_eq(ray2.direction.z, ray1.direction.z, 1e-6);
}

/*
    CAMERA
*/

TestSuite(raytracer_Camera);

Test(raytracer_Camera, constructor) {
    Math::Vector3 lookFrom(0.0, 0.0, 0.0);
    Math::Vector3 lookAt(0.0, 0.0, -1.0);
    Math::Vector3 up(0.0, 1.0, 0.0);
    RayTracer::Camera camera(16.0/9.0, 20.0, lookFrom, lookAt, up);

    cr_assert_not_null(&camera);
}

Test(raytracer_Camera, copy_constructor) {
    Math::Vector3 lookFrom(0.0, 0.0, 0.0);
    Math::Vector3 lookAt(0.0, 0.0, -1.0);
    Math::Vector3 up(0.0, 1.0, 0.0);
    RayTracer::Camera camera(16.0/9.0, 20.0, lookFrom, lookAt, up);
    RayTracer::Camera camera_cpy(camera);

    cr_assert_not_null(&camera_cpy);
}

Test(raytracer_Camera, assignment_operator) {
    Math::Vector3 lookFrom(0.0, 0.0, 0.0);
    Math::Vector3 lookAt(0.0, 0.0, -1.0);
    Math::Vector3 up(0.0, 1.0, 0.0);
    RayTracer::Camera camera(16.0/9.0, 20.0, lookFrom, lookAt, up);
    RayTracer::Camera camera_other = camera;

    cr_assert_not_null(&camera_other);
}

Test(raytracer_Camera, ray_method) {
    Math::Vector3 lookFrom(0.0, 0.0, 0.0);
    Math::Vector3 lookAt(0.0, 0.0, -1.0);
    Math::Vector3 up(0.0, 1.0, 0.0);
    RayTracer::Camera camera(16.0/9.0, 20.0, lookFrom, lookAt, up);

    RayTracer::Ray ray = camera.ray(0.5, 0.5);

    cr_assert_float_eq(ray.origin.x, 0.0, 1e-6);
    cr_assert_float_eq(ray.origin.y, 0.0, 1e-6);
    cr_assert_float_eq(ray.origin.z, 0.0, 1e-6);
}

/*
    BoundingBoxes
*/

TestSuite(raytracer_BoundingBoxes);

Test(raytracer_BoundingBoxes, constructor) {
    RayTracer::BoundingBoxes boundingBox;

    cr_assert_not_null(&boundingBox);
}

Test(raytracer_BoundingBoxes, constructor_with_min_and_max) {
    Math::Vector3 min(0.2, 0.3, 0.1);
    Math::Vector3 max(0.9, 0.9, 0.9);
    RayTracer::BoundingBoxes boundingBox(min, max);

    cr_assert_not_null(&boundingBox);
    cr_assert_float_eq(boundingBox.min().x, min.x, 1e-6);
    cr_assert_float_eq(boundingBox.min().y, min.y, 1e-6);
    cr_assert_float_eq(boundingBox.min().z, min.z, 1e-6);
    cr_assert_float_eq(boundingBox.max().x, max.x, 1e-6);
    cr_assert_float_eq(boundingBox.max().y, max.y, 1e-6);
    cr_assert_float_eq(boundingBox.max().z, max.z, 1e-6);
}

Test(raytracer_BoundingBoxes, hit_method) {
    Math::Vector3 min(0.2, 0.3, 0.1);
    Math::Vector3 max(0.9, 0.9, 0.9);
    RayTracer::BoundingBoxes boundingBox(min, max);
    RayTracer::Ray ray(Math::Vector3(0.5, 0.5, 0.5), Math::Vector3(0.0, 0.0, -1.0));

    cr_assert(boundingBox.hit(ray, 0.0, INFINITY));
}

Test(raytracer_BoundingBoxes, surroundingBox_method) {
    Math::Vector3 min1(0.2, 0.3, 0.1);
    Math::Vector3 max1(0.9, 0.9, 0.9);
    RayTracer::BoundingBoxes box1(min1, max1);

    Math::Vector3 min2(0.1, 0.2, 0.0);
    Math::Vector3 max2(1.0, 1.0, 1.0);
    RayTracer::BoundingBoxes box2(min2, max2);

    RayTracer::BoundingBoxes boundingBox = RayTracer::surroundingBox(box1, box2);

    cr_assert_not_null(&boundingBox);
    cr_assert_float_eq(boundingBox.min().x, min2.x, 1e-6);
    cr_assert_float_eq(boundingBox.min().y, min2.y, 1e-6);
    cr_assert_float_eq(boundingBox.min().z, min2.z, 1e-6);
    cr_assert_float_eq(boundingBox.max().x, max2.x, 1e-6);
    cr_assert_float_eq(boundingBox.max().y, max2.y, 1e-6);
    cr_assert_float_eq(boundingBox.max().z, max2.z, 1e-6);
}

/*
    Matrix4
*/

TestSuite(Math_Matrix4);

Test(Math_Matrix4, default_constructor) {
    Math::Matrix4 matrix;

    cr_assert_not_null(&matrix);
}

Test(Math_Matrix4, test_constructor) {

    Math::Matrix4 matrix;

    cr_assert_float_eq(matrix.getMatrix()[0][0], 1.0, 1e-6);
    cr_assert_float_eq(matrix.getMatrix()[0][1], 0.0, 1e-6);
    cr_assert_float_eq(matrix.getMatrix()[0][2], 0.0, 1e-6);
    cr_assert_float_eq(matrix.getMatrix()[0][3], 0.0, 1e-6);
    cr_assert_float_eq(matrix.getMatrix()[1][0], 0.0, 1e-6);
    cr_assert_float_eq(matrix.getMatrix()[1][1], 1.0, 1e-6);
    cr_assert_float_eq(matrix.getMatrix()[1][2], 0.0, 1e-6);
    cr_assert_float_eq(matrix.getMatrix()[1][3], 0.0, 1e-6);
    cr_assert_float_eq(matrix.getMatrix()[2][0], 0.0, 1e-6);
    cr_assert_float_eq(matrix.getMatrix()[2][1], 0.0, 1e-6);
    cr_assert_float_eq(matrix.getMatrix()[2][2], 1.0, 1e-6);
    cr_assert_float_eq(matrix.getMatrix()[2][3], 0.0, 1e-6);
    cr_assert_float_eq(matrix.getMatrix()[3][0], 0.0, 1e-6);
    cr_assert_float_eq(matrix.getMatrix()[3][1], 0.0, 1e-6);
    cr_assert_float_eq(matrix.getMatrix()[3][2], 0.0, 1e-6);
    cr_assert_float_eq(matrix.getMatrix()[3][3], 1.0, 1e-6);
}

Test(Math_Matrix4, test_constructor_with_matrix4) {
    Math::Matrix4 matrix = Math::Matrix4::identity();
    matrix = Math::Matrix4(matrix);
    
    cr_assert_float_eq(matrix.getMatrix()[0][0], 1.0, 1e-6);
    cr_assert_float_eq(matrix.getMatrix()[0][1], 0.0, 1e-6);
    cr_assert_float_eq(matrix.getMatrix()[0][2], 0.0, 1e-6);
    cr_assert_float_eq(matrix.getMatrix()[0][3], 0.0, 1e-6);
    cr_assert_float_eq(matrix.getMatrix()[1][0], 0.0, 1e-6);
    cr_assert_float_eq(matrix.getMatrix()[1][1], 1.0, 1e-6);
    cr_assert_float_eq(matrix.getMatrix()[1][2], 0.0, 1e-6);
    cr_assert_float_eq(matrix.getMatrix()[1][3], 0.0, 1e-6);
    cr_assert_float_eq(matrix.getMatrix()[2][0], 0.0, 1e-6);
    cr_assert_float_eq(matrix.getMatrix()[2][1], 0.0, 1e-6);
    cr_assert_float_eq(matrix.getMatrix()[2][2], 1.0, 1e-6);
    cr_assert_float_eq(matrix.getMatrix()[2][3], 0.0, 1e-6);
    cr_assert_float_eq(matrix.getMatrix()[3][0], 0.0, 1e-6);
    cr_assert_float_eq(matrix.getMatrix()[3][1], 0.0, 1e-6);
    cr_assert_float_eq(matrix.getMatrix()[3][2], 0.0, 1e-6);
    cr_assert_float_eq(matrix.getMatrix()[3][3], 1.0, 1e-6);
}

// ICI FIND L'ERREUR /!/
// Test(Math_Matrix4, test_constructor_with_matrix4_2) {

//     std::array <std::array<double, 4>, 4> array = {
//         std::array<double, 4>{1, 2, 3, 4},
//         std::array<double, 4>{5, 6, 7, 8},
//         std::array<double, 4>{9, 10, 11, 12},
//         std::array<double, 4>{13, 14, 15, 16}
//     };
//     Math::Matrix4 matrix(array);
    
//     cr_assert_float_eq(matrix.getMatrix()[0][0], 1.0, 1e-6);
//     cr_assert_float_eq(matrix.getMatrix()[0][1], 2.0, 1e-6);
//     cr_assert_float_eq(matrix.getMatrix()[0][2], 3.0, 1e-6);
//     cr_assert_float_eq(matrix.getMatrix()[0][3], 4.0, 1e-6);
//     cr_assert_float_eq(matrix.getMatrix()[1][0], 5.0, 1e-6);
//     cr_assert_float_eq(matrix.getMatrix()[1][1], 6.0, 1e-6);
//     cr_assert_float_eq(matrix.getMatrix()[1][2], 7.0, 1e-6);
//     cr_assert_float_eq(matrix.getMatrix()[1][3], 8.0, 1e-6);
//     cr_assert_float_eq(matrix.getMatrix()[2][0], 9.0, 1e-6);
//     cr_assert_float_eq(matrix.getMatrix()[2][1], 10.0, 1e-6);
//     cr_assert_float_eq(matrix.getMatrix()[2][2], 11.0, 1e-6);
//     cr_assert_float_eq(matrix.getMatrix()[2][3], 12.0, 1e-6);
//     cr_assert_float_eq(matrix.getMatrix()[3][0], 13.0, 1e-6);
//     cr_assert_float_eq(matrix.getMatrix()[3][1], 14.0, 1e-6);
//     cr_assert_float_eq(matrix.getMatrix()[3][2], 15.0, 1e-6);
//     cr_assert_float_eq(matrix.getMatrix()[3][3], 16.0, 1e-6);
// }