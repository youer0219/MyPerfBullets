extends Spawner

func _physics_process(_delta: float) -> void:
	var active_bullets = get_active_bullets().size()
	
	print("active_bullets: ",active_bullets)
