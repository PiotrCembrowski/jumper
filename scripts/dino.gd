extends CharacterBody2D


const SPEED : int = 1600
const JUMP_VELOCITY : int = -800


func _physics_process(delta: float) -> void:


	if Input.is_action_just_pressed("ui_accept") and is_on_floor():
		velocity.y = JUMP_VELOCITY
		$JumpSound.play()
	
	else:
		velocity += get_gravity() * delta
		$AnimatedSprite2D.play("jump")

	if is_on_floor():
		$AnimatedSprite2D.play("idle")
		var direction := Input.get_axis("ui_left", "ui_right")
		if direction:
			velocity.x = direction * SPEED / 3.5
			$AnimatedSprite2D.play("run")
		else:
			velocity.x = move_toward(velocity.x, 0, SPEED)


	

	move_and_slide()
