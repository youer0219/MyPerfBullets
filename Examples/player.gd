extends Area2D

var input: Vector2
@export var power: float
##The id of the spawner used for shooting (If the Spawner has a startmode of Signal)


func _physics_process(delta):
	var velocity = Vector2.ZERO
	input = Vector2(Input.get_axis("ui_left", "ui_right"), Input.get_axis("ui_up", "ui_down")).normalized()
	velocity = input * power
	if input.x == 0:
		velocity.x = 0
	if input.y == 0:
		velocity.y = 0
	position += velocity * delta
	
	#This checks if the spawner is in manual mode, and if it is, it sets the manual start to true. This causes one firing of the pattern.
	if get_node_or_null("PlayerShot") != null: #just because I used this script in multiple examples
		if $PlayerShot.startMode == 2:
			if Input.is_action_just_pressed("ui_accept"):
				$PlayerShot.set_manual_start(true)


func _on_bullet_hit(result, bullet_index:int, spawner:Spawner):
#	spawner.free_bullet_to_pool(bulletIndex) #can be used if returnBulletsToPoolAutomatically is false (see documentation on README)
	print("hit ", result[0]["collider"])
	
	var runtime_bullet = spawner.get_bullet_from_index(bullet_index)
	print(runtime_bullet.runtime_data)
	var attachment_2d = runtime_bullet.bullet_attachment
	if attachment_2d:
		print("attachment_2d.name: ",attachment_2d.name)
		print("attachment_2d.global_position: ",attachment_2d.global_position)
		print("attachment_2d.position: ",attachment_2d.position)


func _on_area_shape_entered(area_rid: RID, area: Area2D, area_shape_index: int, local_shape_index: int) -> void:
	pass # Replace with function body.


func _on_body_shape_entered(body_rid: RID, body: Node2D, body_shape_index: int, local_shape_index: int) -> void:
	pass # Replace with function body.
