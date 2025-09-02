#ifndef BULLET_ATTACHMENT_2D_H
#define BULLET_ATTACHMENT_2D_H

#include <godot_cpp/core/gdvirtual.gen.inc>
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/resource.hpp>

namespace godot {

class BulletAttachment2D : public Node2D {
    GDCLASS(BulletAttachment2D, Node2D)
    
private:
    bool active = false;
    
protected:
    static void _bind_methods();
    
    // 虚拟方法声明
    GDVIRTUAL0(_activate)
    GDVIRTUAL0(_deactivate)
    
    // 可重写的虚方法
    virtual void _activate();
    virtual void _deactivate();
    
public:
    // 激活/停用附件
    void activate();
    void deactivate();
    bool is_active() const;
    
    // 生命周期方法
    void _ready() override;
    
    // 构造/析构
    BulletAttachment2D();
    ~BulletAttachment2D();
};

} // namespace godot

#endif // BULLET_ATTACHMENT_2D_H
