#include "bullet_attachment2d_pool.h"
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

// 实现文件只需要包含方法实现，不需要_bind_methods
BulletAttachment2D* BulletAttachment2DPool::get_attachment(const Ref<PackedScene>& scene) {
    if (scene.is_null() || !scene->can_instantiate()) {
        UtilityFunctions::printerr("BulletAttachment2DPool: Invalid scene resource provided");
        return nullptr;
    }
    
    // 检查资源池是否存在
    if (resource_pools.has(scene)) {
        Vector<BulletAttachment2D*>& pool = resource_pools[scene];
        
        // 查找可用的附件
        for (int i = 0; i < pool.size(); i++) {
            if (!pool[i]->is_active()) {
                BulletAttachment2D* attachment = pool[i];
                pool.remove_at(i);
                attachment->activate();
                return attachment;
            }
        }
    }
    
    // 池中没有可用实例，创建新的
    if (!parent_node) {
        UtilityFunctions::printerr("BulletAttachment2DPool: Parent node not set, cannot create new attachment");
        return nullptr;
    }
    
    Node* new_node = scene->instantiate();
    if (!new_node) {
        UtilityFunctions::printerr("BulletAttachment2DPool: Failed to instantiate scene");
        return nullptr;
    }
    
    BulletAttachment2D* attachment = Object::cast_to<BulletAttachment2D>(new_node);
    if (!attachment) {
        UtilityFunctions::printerr("BulletAttachment2DPool: Instantiated node is not a BulletAttachment2D");
        new_node->queue_free();
        return nullptr;
    }
    
    parent_node->add_child(attachment);
    attachment->activate();
    
    // 添加到资源池
    resource_pools[scene].push_back(attachment);
    return attachment;
}

void BulletAttachment2DPool::return_attachment(BulletAttachment2D* attachment) {
    if (!attachment) return;
    
    // 查找附件所属的资源场景
    Ref<PackedScene> found_scene;
    for (const KeyValue<Ref<PackedScene>, Vector<BulletAttachment2D*>>& pair : resource_pools) {
        for (BulletAttachment2D* pool_attachment : pair.value) {
            if (pool_attachment == attachment) {
                found_scene = pair.key;
                break;
            }
        }
        if (found_scene.is_valid()) break;
    }
    
    if (found_scene.is_null()) {
        UtilityFunctions::printerr("BulletAttachment2DPool: Attachment not found in any pool, destroying");
        attachment->queue_free();
        return;
    }
    
    attachment->deactivate();
    
    // 添加到资源池
    resource_pools[found_scene].push_back(attachment);
}

void BulletAttachment2DPool::prepopulate(const Ref<PackedScene>& scene, int64_t count) {
    if (scene.is_null() || !scene->can_instantiate() || count <= 0) {
        UtilityFunctions::printerr("BulletAttachment2DPool: Invalid prepopulate parameters");
        return;
    }
    
    if (!parent_node) {
        UtilityFunctions::printerr("BulletAttachment2DPool: Parent node not set, cannot prepopulate");
        return;
    }
    
    Vector<BulletAttachment2D*>& pool = resource_pools[scene];
    
    for (int64_t i = 0; i < count; i++) {
        Node* new_node = scene->instantiate();
        if (!new_node) continue;
        
        BulletAttachment2D* attachment = Object::cast_to<BulletAttachment2D>(new_node);
        if (!attachment) {
            new_node->queue_free();
            continue;
        }
        
        parent_node->add_child(attachment);
        attachment->deactivate();
        pool.push_back(attachment);
    }
}

void BulletAttachment2DPool::clear_pool_for_resource(const Ref<PackedScene>& scene) {
    if (!resource_pools.has(scene)) return;
    
    Vector<BulletAttachment2D*>& pool = resource_pools[scene];
    for (int i = 0; i < pool.size(); i++) {
        if (!pool[i]->is_active()) {
            pool[i]->queue_free();
        }
    }
    pool.clear();
    resource_pools.erase(scene);
}

void BulletAttachment2DPool::clear_all_pools() {
    for (KeyValue<Ref<PackedScene>, Vector<BulletAttachment2D*>>& pair : resource_pools) {
        for (BulletAttachment2D* attachment : pair.value) {
            if (!attachment->is_active()) {
                attachment->queue_free();
            }
        }
    }
    resource_pools.clear();
}

Dictionary BulletAttachment2DPool::get_pool_info() const {
    Dictionary info;
    for (const KeyValue<Ref<PackedScene>, Vector<BulletAttachment2D*>>& pair : resource_pools) {
        int inactive_count = 0;
        for (BulletAttachment2D* attachment : pair.value) {
            if (!attachment->is_active()) inactive_count++;
        }
        
        String resource_path = pair.key->get_path();
        info[resource_path] = inactive_count;
    }
    return info;
}
