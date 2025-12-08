extends Node

const DINO_START_POSITION := Vector2i(350, 150)
const CAM_START_POSITION := Vector2i(576, 324)

const SPEED : int = 1
var screen_size : Vector2i

func _ready() -> void:
	screen_size = get_window().size
	new_game()


func new_game():
	$Dino.position = DINO_START_POSITION
	$Dino.velocity = Vector2i(0,0)
	$Camera2D.position = CAM_START_POSITION
	$Ground.position = Vector2i(0,0)

func _process(delta: float) -> void:
	$Camera2D.position.y -= SPEED
