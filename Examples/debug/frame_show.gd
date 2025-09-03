extends VBoxContainer

@onready var fps_label: Label = $Fps_Label
@onready var physics_2d_collision_pairs_label: Label = $Physics_2d_Collision_Pairs_Label

@export var enable:bool = true

func _physics_process(_delta: float) -> void:
	if not enable:
		return
	
	var current_fps = Performance.get_monitor(Performance.TIME_FPS)
	fps_label.text = "当前帧率: %.1f FPS" % current_fps

	var physics_2d_collision_pairs = Performance.get_monitor(Performance.PHYSICS_2D_COLLISION_PAIRS)
	physics_2d_collision_pairs_label.text = "2D碰撞对数: %.1f 对" % physics_2d_collision_pairs
