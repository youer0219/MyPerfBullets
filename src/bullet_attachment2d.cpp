#include "bullet_attachment2d.hpp"
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void BulletAttachment2D::_bind_methods() {
    ClassDB::bind_method(D_METHOD("activate"), &BulletAttachment2D::activate);
    ClassDB::bind_method(D_METHOD("deactivate"), &BulletAttachment2D::deactivate);
    ClassDB::bind_method(D_METHOD("is_active"), &BulletAttachment2D::is_active);
    
    // 正确绑定虚拟方法
    GDVIRTUAL_BIND(_activate)
    GDVIRTUAL_BIND(_deactivate)
    
    // 信号定义
    ADD_SIGNAL(MethodInfo("activated"));
    ADD_SIGNAL(MethodInfo("deactivated"));
}

BulletAttachment2D::BulletAttachment2D() {
    // 初始化代码
}

BulletAttachment2D::~BulletAttachment2D() {
    // 清理代码
}

void BulletAttachment2D::_ready() {
    // 默认处于停用状态
    if (!active) {
        set_process(false);
        set_physics_process(false);
        set_visible(false);
    }
}

void BulletAttachment2D::activate() {
    if (active) return;
    
    active = true;
    
    // 调用虚拟方法（如果GDScript有重写则调用重写版本）
    if (GDVIRTUAL_IS_OVERRIDDEN(_activate)) {
        GDVIRTUAL_CALL(_activate);
    } else {
        // 如果没有重写，调用默认实现
        _activate();
    }
    
    emit_signal("activated");
}

void BulletAttachment2D::deactivate() {
    if (!active) return;
    
    active = false;
    
    // 调用虚拟方法（如果GDScript有重写则调用重写版本）
    if (GDVIRTUAL_IS_OVERRIDDEN(_deactivate)) {
        GDVIRTUAL_CALL(_deactivate);
    } else {
        // 如果没有重写，调用默认实现
        _deactivate();
    }
    
    emit_signal("deactivated");
}

bool BulletAttachment2D::is_active() const {
    return active;
}

void BulletAttachment2D::_activate() {
    // 默认激活行为
    set_visible(true);
    set_process(true);
    set_physics_process(true);
}

void BulletAttachment2D::_deactivate() {
    // 默认停用行为
    set_visible(false);
    set_process(false);
    set_physics_process(false);
    
    // 重置状态
    set_position(Vector2(0, 0));
    set_rotation(0);
}
