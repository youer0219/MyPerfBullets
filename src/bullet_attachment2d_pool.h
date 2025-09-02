#ifndef BULLET_ATTACHMENT_2D_POOL_H
#define BULLET_ATTACHMENT_2D_POOL_H

#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/templates/hash_map.hpp>
#include <godot_cpp/templates/vector.hpp>
#include "bullet_attachment2d.h"

namespace godot {

class BulletAttachment2DPool : public RefCounted {
    GDCLASS(BulletAttachment2DPool, RefCounted)
    
private:
    // 使用资源作为键的分组池
    HashMap<Ref<PackedScene>, Vector<BulletAttachment2D*>> resource_pools;
    Node* parent_node = nullptr;
    
protected:
    // 只需要基本的类注册，不需要方法绑定
    static void _bind_methods() {
        // 空实现或只做最基本的类注册
    }
    
public:
    // 设置父节点（附件将被添加为其子节点）
    void set_parent_node(Node* parent) { parent_node = parent; }
    Node* get_parent_node() const { return parent_node; }
    
    // 获取附件实例
    BulletAttachment2D* get_attachment(const Ref<PackedScene>& scene);
    
    // 归还附件
    void return_attachment(BulletAttachment2D* attachment);
    
    // 预填充池
    void prepopulate(const Ref<PackedScene>& scene, int64_t count);
    
    // 清理特定资源池
    void clear_pool_for_resource(const Ref<PackedScene>& scene);
    
    // 清理所有池
    void clear_all_pools();
    
    // 获取池统计信息（内部使用）
    Dictionary get_pool_info() const;
    
    // 构造/析构
    BulletAttachment2DPool() = default;
    ~BulletAttachment2DPool() { clear_all_pools(); }
};

} // namespace godot

#endif // BULLET_ATTACHMENT_2D_POOL_H
