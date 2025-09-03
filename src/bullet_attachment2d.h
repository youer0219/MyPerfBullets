#ifndef BULLET_ATTACHMENT_2D_H
#define BULLET_ATTACHMENT_2D_H

#include <godot_cpp/core/gdvirtual.gen.inc>
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/classes/weak_ref.hpp>

class Spawner;
class BulProps;

namespace godot {

class BulletAttachment2D : public Node2D {
    GDCLASS(BulletAttachment2D, Node2D)
    
private:
    bool active = false;
    // 使用 std::weak_ptr 存储弱引用
    Spawner* spawner_ptr;
    BulProps* bullet_data_ptr;
    
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

    // 设置方法
    void set_spawner(Spawner* spawner);
    void set_bullet_data(BulProps* bullet_data);
    
    // 获取方法
    Spawner* get_spawner() const;
    BulProps* get_bullet_data() const;
    
    // 检查引用是否有效
    bool is_spawner_valid() const;
    bool is_bullet_data_valid() const;
    
    // 清理方法
    void clear_references();

    // 生命周期方法
    void _ready() override;
    
    // 构造/析构
    BulletAttachment2D();
    ~BulletAttachment2D();
};

} // namespace godot

#endif // BULLET_ATTACHMENT_2D_H
