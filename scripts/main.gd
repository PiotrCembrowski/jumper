extends Node

const DINO_START_POSITION := Vector2i(150, 485)
const CAM_START_POSITION := Vector2i(576, 324)

const SPEED : int = 10

func _ready() -> void:
	new_game()


func new_game():
	$Dino.position = DINO_START_POSITION
	$Dino.velocity = Vector2i(0,0)
	$Camera2D.position = CAM_START_POSITION
	$Ground.position = Vector2i(0,0)

func _process(delta: float) -> void:
	$Dino.position.x += SPEED
	$Camera2D.position.x += SPEED
