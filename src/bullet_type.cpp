#include "bullet_type.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/dictionary.hpp>

void BulletType::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_initial_speed", "ispd"), &BulletType::set_initial_speed);
    ClassDB::bind_method(D_METHOD("get_initial_speed"), &BulletType::get_initial_speed);

    ClassDB::bind_method(D_METHOD("set_max_lifetime", "life"), &BulletType::set_max_lifetime);
    ClassDB::bind_method(D_METHOD("get_max_lifetime"), &BulletType::get_max_lifetime);

    ClassDB::bind_method(D_METHOD("set_animation_speed", "speed"), &BulletType::set_animation_speed);
    ClassDB::bind_method(D_METHOD("get_animation_speed"), &BulletType::get_animation_speed);

    ClassDB::bind_method(D_METHOD("set_acceleration", "acc"), &BulletType::set_acceleration);
    ClassDB::bind_method(D_METHOD("get_acceleration"), &BulletType::get_acceleration);

    ClassDB::bind_method(D_METHOD("set_min_speed", "miSpeed"), &BulletType::set_min_speed);
    ClassDB::bind_method(D_METHOD("get_min_speed"), &BulletType::get_min_speed);

    ClassDB::bind_method(D_METHOD("set_max_speed", "maSpeed"), &BulletType::set_max_speed);
    ClassDB::bind_method(D_METHOD("get_max_speed"), &BulletType::get_max_speed);

    ClassDB::bind_method(D_METHOD("set_shape", "s"), &BulletType::set_shape);
    ClassDB::bind_method(D_METHOD("get_shape"), &BulletType::get_shape);

    ClassDB::bind_method(D_METHOD("set_mask", "m"), &BulletType::set_mask);
    ClassDB::bind_method(D_METHOD("get_mask"), &BulletType::get_mask);

    ClassDB::bind_method(D_METHOD("set_collide_with_bodies", "c"), &BulletType::set_collide_with_bodies);
    ClassDB::bind_method(D_METHOD("get_collide_with_bodies"), &BulletType::get_collide_with_bodies);

    ClassDB::bind_method(D_METHOD("set_collide_with_areas", "c"), &BulletType::set_collide_with_areas);
    ClassDB::bind_method(D_METHOD("get_collide_with_areas"), &BulletType::get_collide_with_areas);

    ClassDB::bind_method(D_METHOD("set_scale", "s"), &BulletType::set_scale);
    ClassDB::bind_method(D_METHOD("get_scale"), &BulletType::get_scale);

    ClassDB::bind_method(D_METHOD("set_number_of_queries", "num"), &BulletType::set_number_of_queries);
    ClassDB::bind_method(D_METHOD("get_number_of_queries"), &BulletType::get_number_of_queries);

    ClassDB::bind_method(D_METHOD("set_custom_data", "data"), &BulletType::set_custom_data);
    ClassDB::bind_method(D_METHOD("get_custom_data"), &BulletType::get_custom_data);

    ClassDB::bind_method(D_METHOD("set_attachment_scene", "scene"), &BulletType::set_attachment_scene);
    ClassDB::bind_method(D_METHOD("get_attachment_scene"), &BulletType::get_attachment_scene);

    ClassDB::add_property("BulletType", PropertyInfo(Variant::FLOAT, "initial_speed"), "set_initial_speed", "get_initial_speed");
    ClassDB::add_property("BulletType", PropertyInfo(Variant::OBJECT, "shape", PROPERTY_HINT_RESOURCE_TYPE, "Shape2D"), "set_shape", "get_shape");
    ClassDB::add_property("BulletType", PropertyInfo(Variant::FLOAT, "scale"), "set_scale", "get_scale");
    ClassDB::add_property("BulletType", PropertyInfo(Variant::FLOAT, "acceleration"), "set_acceleration", "get_acceleration");
    ClassDB::add_property("BulletType", PropertyInfo(Variant::FLOAT, "max_lifetime"), "set_max_lifetime", "get_max_lifetime");
    ClassDB::add_property("BulletType", PropertyInfo(Variant::FLOAT, "animation_speed"), "set_animation_speed", "get_animation_speed");
    ClassDB::add_property("BulletType", PropertyInfo(Variant::FLOAT, "min_speed"), "set_min_speed", "get_min_speed");
    ClassDB::add_property("BulletType", PropertyInfo(Variant::FLOAT, "max_speed"), "set_max_speed", "get_max_speed");
    ClassDB::add_property_group("BulletType", "Collision", "");
    ClassDB::add_property("BulletType", PropertyInfo(Variant::INT, "mask", PROPERTY_HINT_LAYERS_2D_PHYSICS), "set_mask", "get_mask");
    ClassDB::add_property("BulletType", PropertyInfo(Variant::INT, "number_of_queries"), "set_number_of_queries", "get_number_of_queries");
    ClassDB::add_property("BulletType", PropertyInfo(Variant::BOOL, "collide_with_bodies"), "set_collide_with_bodies", "get_collide_with_bodies");
    ClassDB::add_property("BulletType", PropertyInfo(Variant::BOOL, "collide_with_areas"), "set_collide_with_areas", "get_collide_with_areas");
    ClassDB::add_property("BulletType", PropertyInfo(Variant::DICTIONARY, "custom_data"), "set_custom_data", "get_custom_data");
    ClassDB::add_property_group("BulletType", "AttachmentNode", "");
    ClassDB::add_property("BulletType", PropertyInfo(Variant::OBJECT, "attachment_scene", PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"), "set_attachment_scene", "get_attachment_scene");

}

BulletType::BulletType() {
}

BulletType::~BulletType() {
    // Destructor code here
}

void BulletType::set_initial_speed(float ispd) {
    initialSpeed = ispd;
}

float BulletType::get_initial_speed() const {
    return initialSpeed;
}

void BulletType::set_max_lifetime(float life) {
    maxLifetime = life;
}

float BulletType::get_max_lifetime() const {
    return maxLifetime;
}


void BulletType::set_animation_speed(float speed) {
    animationSpeed = speed;
}

float BulletType::get_animation_speed() const {
    return animationSpeed;
}

void BulletType::set_acceleration(float acc) {
    acceleration = acc; 
}

float BulletType::get_acceleration() const {
    return acceleration; 
}

void BulletType::set_min_speed(float miSpeed) {
    minSpeed = miSpeed; 
}

float BulletType::get_min_speed() const {
    return minSpeed; 
}

void BulletType::set_max_speed(float maSpeed) { 
    maxSpeed = maSpeed; 
}

float BulletType::get_max_speed() const {
    return maxSpeed; 
    }

void BulletType::set_shape(Ref<Shape2D> s) {
    shape = s; 
}

Ref<Shape2D> BulletType::get_shape() const {
    return shape; 
}

void BulletType::set_mask(int m){
    mask = m;
}

int BulletType::get_mask() const{
    return mask;
}

void BulletType::set_collide_with_bodies(bool c){
    collideWithBodies = c;
}

bool BulletType::get_collide_with_bodies() const{
    return collideWithBodies;
}

void BulletType::set_collide_with_areas(bool c){
    collideWithAreas = c;
}

bool BulletType::get_collide_with_areas() const{
    return collideWithAreas;
}

void BulletType::set_scale(float s){
    scale = s;
}

float BulletType::get_scale() const{
    return scale;
}

void BulletType::set_number_of_queries(int num) {
    numberOfQueries = num;
}

int BulletType::get_number_of_queries() const{
    return numberOfQueries;
}

void BulletType::set_custom_data(const Dictionary &p_data) {
    custom_data = p_data;
}

Dictionary BulletType::get_custom_data() const {
    return custom_data;
}

void BulletType::set_attachment_scene(const Ref<PackedScene> &p_scene) {
    attachment_scene = p_scene;
}

Ref<PackedScene> BulletType::get_attachment_scene() const {
    return attachment_scene;
}